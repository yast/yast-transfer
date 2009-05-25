/*
 * YaST2: Core system
 *
 * Description:
 *   YaST2 SCR: Tftp agent implementation
 *
 * Authors:
 *   Anas Nashif <nashif@suse.de>
 *
 * $Id$
 */

#include "TftpAgent.h"

extern "C"
{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
}

#define RESERVE_BUFFER(buffer,len)           char buffer[len]

static const char *tftp_error_msg[] = {
	"Undefined error",
	"File not found",
	"Access violation",
	"Disk full or allocation error",
	"Illegal TFTP operation",
	"Unknown transfer ID",
	"File already exists",
	"No such user"
};

const int tftp_cmd_get = 1;
const int tftp_cmd_put = 2;


static char * xstrdup (const char *s) {
    char *t;
 
    if (s == NULL)
        return NULL;
 
    t = strdup (s);
 
    if (t == NULL)
        y2error ("Error: memory_exhausted");
 
    return t;
}

static inline int tftp(const int cmd, const struct hostent *host,
	const char *serverfile, int localfd, const int port, int tftp_bufsize)
{
    const int cmd_get = cmd & tftp_cmd_get;
    const int cmd_put = cmd & tftp_cmd_put;
    const int bb_tftp_num_retries = 5;

    struct sockaddr_in sa;
    struct sockaddr_in from;
    struct timeval tv;
    socklen_t fromlen;
    fd_set rfds;
    char *cp;
    unsigned short tmp;
    int socketfd;
    int len;
    int opcode = 0;
    int finished = 0;
    int timeout = bb_tftp_num_retries;
    int block_nr = 1;
    RESERVE_BUFFER(buf, tftp_bufsize + 4); // Why 4 ?

    tftp_bufsize += 4;

    if ((socketfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
	y2error("socket");
	    return EXIT_FAILURE;
    }

    len = sizeof(sa);

    memset(&sa, 0, len);
    bind(socketfd, (struct sockaddr *)&sa, len);

    sa.sin_family = host->h_addrtype;
    sa.sin_port = htons(port);
    memcpy(&sa.sin_addr, (struct in_addr *) host->h_addr,
		sizeof(sa.sin_addr));

    /* build opcode */

    if (cmd_get) {
	opcode = 1;	// read request = 1
    }

    if (cmd_put) {
	    opcode = 2;	// write request = 2
    }

    while (1) {
	/* build packet of type "opcode" */
	cp = buf;

	*((unsigned short *) cp) = htons(opcode);

	cp += 2;

	/* add filename and mode */

	if ((cmd_get && (opcode == 1)) || // read request = 1
			(cmd_put && (opcode == 2))) { // write request = 2

	    /* what is this trying to do ? */
	    while (cp != &buf[tftp_bufsize - 1]) {
		if ((*cp = *serverfile++) == '\0')
		    break;
		    cp++;
		}
			/* and this ? */
		if ((*cp != '\0') || (&buf[tftp_bufsize - 1] - cp) < 7) {
		    y2error("too long server-filename");
		    break;
		}
		memcpy(cp + 1, "octet", 6);
		cp += 7;
	    }

	    /* add ack and data */

	    if ((cmd_get && (opcode == 4)) || // acknowledgement = 4
		    (cmd_put && (opcode == 3))) { // data packet == 3

		*((unsigned short *) cp) = htons(block_nr);
		cp += 2;
		block_nr++;
		if (cmd_put && (opcode == 3)) { // data packet == 3
		    len = read(localfd, cp, tftp_bufsize - 4);

		    if (len < 0) {
			    y2error("Error while reading from file");
			    break;
		    }

		    if (len != (tftp_bufsize - 4)) {
			finished++;
		    }

		    cp += len;
		} else if (finished) {
// dont break here, we need the ACK for the last package
//		    break;
		}
	    }
		/* send packet */
	    do {
		len = cp - buf;
		y2debug("sending %u bytes", len);
    		    /*
		    for (cp = buf; cp < &buf[len]; cp++)
			    y2debug("%02x ", *cp);
		    */
		if (sendto(socketfd, buf, len, 0,
				    (struct sockaddr *) &sa, sizeof(sa)) < 0) {
		    y2error("send");
		    len = -1;
		    break;
		}
		if( cmd_get && (opcode == 4) && finished )
		    // ACK sent
		    break;
		/* receive packet */
		memset(&from, 0, sizeof(from));
		fromlen = sizeof(from);

		tv.tv_sec = 5; // TFPT_TIMEOUT = 5
		tv.tv_usec = 0;

		FD_ZERO(&rfds);
		FD_SET(socketfd, &rfds);

		switch (select(FD_SETSIZE, &rfds, NULL, NULL, &tv)) {
		    case 1:
			len = recvfrom(socketfd, buf, tftp_bufsize, 0,
    					    (struct sockaddr *) &from, &fromlen);

			if (len < 0) {
			    y2error("recvfrom");
			    break;
			}

			timeout = 0;

	    		if (sa.sin_port == htons(port)) 
			{
			    sa.sin_port = from.sin_port;
			}
			if (sa.sin_port == from.sin_port) 
			{
			    break;
			}
			/* fall-through for bad packets! */
			/* discard the packet - treat as timeout */
			timeout = bb_tftp_num_retries;

    		    case 0:
			y2error("timeout");

			if (timeout == 0) 
			{
			    len = -1;
			    y2error("last timeout");
			} 
			else 
			{
			    timeout--;
			}
			break;

		    default:
			y2error("select");
			len = -1;
		    }
	    } while (timeout && (len >= 0));

	    if (len < 0 || finished ) {
		break;
	    }

	    /* process received packet */


	    opcode = ntohs(*((unsigned short *) buf));
	    tmp = ntohs(*((unsigned short *) &buf[2]));

	    y2debug("received %d bytes: %04x %04x\n", len, opcode, tmp);

	    if (cmd_get && (opcode == 3)) { // data packet == 3
		if (tmp == block_nr) {
    		    len = write(localfd, &buf[4], len - 4);

		    if (len < 0) {
			y2error("write");
			break;
		    }

		    if (len != (tftp_bufsize - 4)) {
			finished++;
		    }

		    opcode = 4; // acknowledgement = 4
		    continue;
		}
	    }

	    if (cmd_put && (opcode == 4)) { // acknowledgement = 4
		if (tmp == (block_nr - 1)) {
		    if (finished) {
			break;
		    }

		    opcode = 3; // data packet == 3
		    continue;
		}
	    }

	    if (opcode == 5) { // error code == 5
		char *msg = NULL;
/*
		if (buf[4] != '\0') {
		    msg = &buf[4];
		    buf[tftp_bufsize - 1] = '\0';
		}
*/
		if (tmp < (sizeof(tftp_error_msg) / sizeof(char *))) 
		{
		    msg = (char *) tftp_error_msg[tmp];
		}
		if (msg) 
		{
		    y2error("server says: %s\n", msg);
		}
		break;
	    }
	}
    close(socketfd);
    return finished ? EXIT_SUCCESS : EXIT_FAILURE;
}

int dotftp(char *serverstr, char *localfile, char *action)
{
    struct hostent *host = NULL;
    char *serverfile = NULL;
    int port = 69;
    int cmd = 0;
    int fd = -1;
    int flags = 0;
    int bad = 1;
    int result;
    int blocksize = 512;
    char *cp, *s; 
	
    if (strncmp(action, "get", 3) == 0) {
	cmd = tftp_cmd_get; 
	flags = O_WRONLY | O_CREAT;
	y2debug("Getting file...");
    } else if (strncmp(action, "put", 3) == 0){
	cmd = tftp_cmd_put; 
	flags = O_RDONLY;
	y2debug("Putting file...");
    } 

    for (cp = serverstr; *cp != '\0'; cp++)
	if (*cp == ':')
	    break;

    if (*cp == ':') 
    {
	serverfile = cp + 1;
	s = xstrdup(serverstr);
	s[cp - serverstr] = '\0';

	if ((host = gethostbyname(s))) 
	{
	    bad = 0;
	}
	free(s);
    }
    if (bad) 
    {
	y2error("bad \"server:file\" combination");
	return(EXIT_FAILURE);
    }	
    fd = open(localfile, flags, 0644);
    if (fd < 0) 
    {
	y2error("local file can't be opened");
    }
    y2debug("using server \"%s\", serverfile \"%s\","
				    "localfile \"%s\".\n",
				    inet_ntoa(*((struct in_addr *) host->h_addr)),
				    serverfile, localfile);

    result = tftp(cmd, host, serverfile, fd, port, blocksize);
    close(fd);

    return(result);
}



/*
 * Get single values from map
 */
string getValue ( const YCPMap map, const string key)
{
    for (YCPMapIterator i = map->begin(); i != map->end (); i++)
    {
	if (!i.key()->isString())   // key must be a string
	{
	    y2error("Cannot write invalid key %s, must be a string",
	    i.value()->toString().c_str());
	}
	else        // everything OK
	{
	    string variablename = i.key()->asString()->value();
	    if ( variablename == key )        
	    {
		if (!i.value()->isString() )
		{
		    y2error("Invalid value %s. Key %s requires one value",
		    i.value()->toString().c_str(), key.c_str());
		    break; 
		}
		string valuecomment = i.value()->asString()->value(); 
		return ( valuecomment );
	    }
	}
    }
    return ( "" );
}

/**
 * Constructor
 */
TftpAgent::TftpAgent() : SCRAgent()
{
}

/**
 * Destructor
 */
TftpAgent::~TftpAgent()
{
}

/**
 * Dir
 */
YCPList TftpAgent::Dir(const YCPPath& path)
{
    y2error("Wrong path '%s' in Dir().", path->toString().c_str());
    return YCPNull();
}

/**
 * Read
 */
YCPValue TftpAgent::Read(const YCPPath &path, const YCPValue& arg, const YCPValue& opt)
{
    y2error("Wrong path '%s' in Read().", path->toString().c_str());
    return YCPVoid();
}

/**
 * Execute
 * 
 */

YCPValue TftpAgent::Execute (const YCPPath& path, const YCPValue& value , 
		const YCPValue& arg )
{
	int ret;
	string path_name = path->component_str (0);

	if (  path_name == "get" )
	{
		if ( !value.isNull()
				&& value->isString()
				&& !arg.isNull()
				&& arg->isString())
		{
			ret = dotftp((char *)value->asString()->value().c_str(), 
					(char *)arg->asString()->value().c_str(), 
					"get");
			if (ret == 0)
				return YCPBoolean(true);
			else
				return YCPBoolean(false);
		}
        }
        else if (  path_name == "put")
	{
		if ( !value.isNull()
				&& value->isString()
				&& !arg.isNull()
				&& arg->isString())
		{
			ret = dotftp((char *)value->asString()->value().c_str(), 
					(char *)arg->asString()->value().c_str(), 
					"put");
			if (ret == 0)
				return YCPBoolean(true);
			else
				return YCPBoolean(false);
		}
	} else {
    	y2error("Wrong path '%s' in Execute().", path->toString().c_str());
    	return YCPVoid();

	}
	return YCPVoid();
}

/**
 * Write
 */
YCPBoolean TftpAgent::Write(const YCPPath &path, const YCPValue& value, const YCPValue& arg)
{
    y2error("Wrong path '%s' in Write().", path->toString().c_str());
    return YCPBoolean(false);
}


/**
 * otherCommand
 */
YCPValue TftpAgent::otherCommand(const YCPTerm& term)
{
    string sym = term->name();

    if (sym == "TftpAgent") {
        /* Your initialization */
        return YCPVoid();
    }

    return YCPNull();
}

