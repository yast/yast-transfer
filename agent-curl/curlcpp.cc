// ============================================================================
//	curlcpp.cp
//	(c) 2001 - Eric Lavigne
// ============================================================================

#include "curlcpp.h"

// ============================================================================

#if 0

  /* This is the FILE * or void * the regular output should be written to. */
--  CINIT(FILE, OBJECTPOINT, 1),

  /* The full URL to get/put */
--  CINIT(URL,  OBJECTPOINT, 2),

  /* Port number to connect to, if other than default. Specify the CONF_PORT
     flag in the CURLOPT_FLAGS to activate this */
--  CINIT(PORT, LONG, 3),

  /* Name of proxy to use. Specify the CONF_PROXY flag in the CURLOPT_FLAGS to
     activate this */
--  CINIT(PROXY, OBJECTPOINT, 4),
  
  /* Name and password to use when fetching. Specify the CONF_USERPWD flag in
     the CURLOPT_FLAGS to activate this */
--  CINIT(USERPWD, OBJECTPOINT, 5),

  /* Name and password to use with Proxy. Specify the CONF_PROXYUSERPWD 
     flag in the CURLOPT_FLAGS to activate this */
--  CINIT(PROXYUSERPWD, OBJECTPOINT, 6),

  /* Range to get, specified as an ASCII string. Specify the CONF_RANGE flag
     in the CURLOPT_FLAGS to activate this */
  CINIT(RANGE, OBJECTPOINT, 7),

  /* not used */

  /* Specified file stream to upload from (use as input): */
--  CINIT(INFILE, OBJECTPOINT, 9),

  /* Buffer to receive error messages in, must be at least CURL_ERROR_SIZE
   * bytes big. If this is not used, error messages go to stderr instead: */
--  CINIT(ERRORBUFFER, OBJECTPOINT, 10),

  /* Function that will be called to store the output (instead of fwrite). The
   * parameters will use fwrite() syntax, make sure to follow them. */
--  CINIT(WRITEFUNCTION, FUNCTIONPOINT, 11),

  /* Function that will be called to read the input (instead of fread). The
   * parameters will use fread() syntax, make sure to follow them. */
--  CINIT(READFUNCTION, FUNCTIONPOINT, 12),

  /* Time-out the read operation after this amount of seconds */
--  CINIT(TIMEOUT, LONG, 13),

  /* If the CURLOPT_INFILE is used, this can be used to inform libcurl about
   * how large the file being sent really is. That allows better error
   * checking and better verifies that the upload was succcessful. -1 means
   * unknown size. */
--  CINIT(INFILESIZE, LONG, 14),

  /* POST input fields. */
--  CINIT(POSTFIELDS, OBJECTPOINT, 15),

  /* Set the referer page (needed by some CGIs) */
--  CINIT(REFERER, OBJECTPOINT, 16),

  /* Set the FTP PORT string (interface name, named or numerical IP address)
     Use i.e '-' to use default address. */
  CINIT(FTPPORT, OBJECTPOINT, 17),

  /* Set the User-Agent string (examined by some CGIs) */
--  CINIT(USERAGENT, OBJECTPOINT, 18),

  /* If the download receives less than "low speed limit" bytes/second
   * during "low speed time" seconds, the operations is aborted.
   * You could i.e if you have a pretty high speed connection, abort if
   * it is less than 2000 bytes/sec during 20 seconds.   
   */

  /* Set the "low speed limit" */
--  CINIT(LOW_SPEED_LIMIT, LONG , 19),

  /* Set the "low speed time" */
--  CINIT(LOW_SPEED_TIME, LONG, 20),

  /* Set the continuation offset */
  CINIT(RESUME_FROM, LONG, 21),

  /* Set cookie in request: */
  CINIT(COOKIE, OBJECTPOINT, 22),

  /* This points to a linked list of headers, struct HttpHeader kind */
--  CINIT(HTTPHEADER, OBJECTPOINT, 23),

  /* This points to a linked list of post entries, struct HttpPost */
--  CINIT(HTTPPOST, OBJECTPOINT, 24),

  /* name of the file keeping your private SSL-certificate */
s  CINIT(SSLCERT, OBJECTPOINT, 25),

  /* password for the SSL-certificate */
s  CINIT(SSLCERTPASSWD, OBJECTPOINT, 26),
  
  /* send TYPE parameter? */ #####bad comment
  CINIT(CRLF, LONG, 27),

  /* send linked-list of QUOTE commands */
--  CINIT(QUOTE, OBJECTPOINT, 28),

  /* send FILE * or void * to store headers to, if you use a callback it
     is simply passed to the callback unmodified */
--  CINIT(WRITEHEADER, OBJECTPOINT, 29),

  /* point to a file to read the initial cookies from, also enables
     "cookie awareness" */
  CINIT(COOKIEFILE, OBJECTPOINT, 31),

  /* What version to specifly try to use.
     See CURL_SSLVERSION defines below. */
s  CINIT(SSLVERSION, LONG, 32),

  /* What kind of HTTP time condition to use, see defines */
  CINIT(TIMECONDITION, LONG, 33),

  /* Time to use with the above condition. Specified in number of seconds
     since 1 Jan 1970 */
  CINIT(TIMEVALUE, LONG, 34),

  /* HTTP request, for odd commands like DELETE, TRACE and others */
  /* OBSOLETE DEFINE, left for tradition only */
  CINIT(HTTPREQUEST, OBJECTPOINT, 35),

  /* Custom request, for customizing the get command like
     HTTP: DELETE, TRACE and others
     FTP: to use a different list command
     */
  CINIT(CUSTOMREQUEST, OBJECTPOINT, 36),

  /* HTTP request, for odd commands like DELETE, TRACE and others */
--  CINIT(STDERR, OBJECTPOINT, 37),	######bad comment

  /* 38 is not used */

  /* send linked-list of post-transfer QUOTE commands */
--  CINIT(POSTQUOTE, OBJECTPOINT, 39),

  /* Pass a pointer to string of the output using full variable-replacement
     as described elsewhere. */
bug  CINIT(WRITEINFO, OBJECTPOINT, 40),

  /* Previous FLAG bits */
--  CINIT(VERBOSE, LONG, 41),      /* talk a lot */
  CINIT(HEADER, LONG, 42),       /* throw the header out too */
  CINIT(NOPROGRESS, LONG, 43),   /* shut off the progress meter */
  CINIT(NOBODY, LONG, 44),       /* use HEAD to get http document */
  CINIT(FAILONERROR, LONG, 45),  /* no output on http error codes >= 300 */
  CINIT(UPLOAD, LONG, 46),       /* this is an upload */
--  CINIT(POST, LONG, 47),         /* HTTP POST method */
  CINIT(FTPLISTONLY, LONG, 48),  /* Use NLST when listing ftp dir */

  CINIT(FTPAPPEND, LONG, 50),    /* Append instead of overwrite on upload! */
--  CINIT(NETRC, LONG, 51),        /* read user+password from .netrc */
  CINIT(FOLLOWLOCATION, LONG, 52),  /* use Location: Luke! */

  /* This FTPASCII name is now obsolete, to be removed, use the TRANSFERTEXT
     instead. It goes for more protocols than just ftp... */
--  CINIT(FTPASCII, LONG, 53),     /* use TYPE A for transfer */

  CINIT(TRANSFERTEXT, LONG, 53), /* transfer data in text/ASCII format */
  CINIT(PUT, LONG, 54),          /* PUT the input file */

--  CINIT(MUTE, LONG, 55),         /* OBSOLETE OPTION, removed in 7.8 */

  /* Function that will be called instead of the internal progress display
   * function. This function should be defined as the curl_progress_callback
   * prototype defines. */
--  CINIT(PROGRESSFUNCTION, FUNCTIONPOINT, 56),

  /* Data passed to the progress callback */
--  CINIT(PROGRESSDATA, OBJECTPOINT, 57),

  /* We want the referer field set automatically when following locations */
N  CINIT(AUTOREFERER, LONG, 58),

  /* Port of the proxy, can be set in the proxy string as well with:
     "[host]:[port]" */
--  CINIT(PROXYPORT, LONG, 59),

  /* size of the POST input data, if strlen() is not good to use */
--  CINIT(POSTFIELDSIZE, LONG, 60),

  /* tunnel non-http operations through a HTTP proxy */
--  CINIT(HTTPPROXYTUNNEL, LONG, 61),

  /* Set the interface string to use as outgoing network interface */
  CINIT(INTERFACE, OBJECTPOINT, 62),

  /* Set the krb4 security level, this also enables krb4 awareness.  This is a
   * string, 'clear', 'safe', 'confidential' or 'private'.  If the string is
   * set but doesn't match one of these, 'private' will be used.  */
s  CINIT(KRB4LEVEL, OBJECTPOINT, 63),

  /* Set if we should verify the peer in ssl handshake, set 1 to verify. */
s  CINIT(SSL_VERIFYPEER, LONG, 64),
  
  /* The CApath or CAfile used to validate the peer certificate
     this option is used only if SSL_VERIFYPEER is true */
s  CINIT(CAINFO, OBJECTPOINT, 65),

  /* Function pointer to replace the internal password prompt */
--  CINIT(PASSWDFUNCTION, FUNCTIONPOINT, 66),

  /* Custom pointer that gets passed as first argument to the password
     function */
--  CINIT(PASSWDDATA, OBJECTPOINT, 67),
  
  /* Maximum number of http redirects to follow */
--  CINIT(MAXREDIRS, LONG, 68),

  /* Pass a pointer to a time_t to get a possible date of the requested
     document! Pass a NULL to shut it off. */
  CINIT(FILETIME, OBJECTPOINT, 69),

  /* This points to a linked list of telnet options */
  CINIT(TELNETOPTIONS, OBJECTPOINT, 70),

  /* Max amount of cached alive connections */
  CINIT(MAXCONNECTS, LONG, 71),

  /* What policy to use when closing connections when the cache is filled
     up */
ni  CINIT(CLOSEPOLICY, LONG, 72),

  /* Callback to use when CURLCLOSEPOLICY_CALLBACK is set */
ni  CINIT(CLOSEFUNCTION, FUNCTIONPOINT, 73),

  /* Set to explicitly use a new connection for the upcoming transfer.
     Do not use this unless you're absolutely sure of this, as it makes the
     operation slower and is less friendly for the network. */
  CINIT(FRESH_CONNECT, LONG, 74),

  /* Set to explicitly forbid the upcoming transfer's connection to be re-used
     when done. Do not use this unless you're absolutely sure of this, as it
     makes the operation slower and is less friendly for the network. */
  CINIT(FORBID_REUSE, LONG, 75),

  /* Set to a file name that contains random data for libcurl to use to
     seed the random engine when doing SSL connects. */
s  CINIT(RANDOM_FILE, OBJECTPOINT, 76),

  /* Set to the Entropy Gathering Daemon socket pathname */
  CINIT(EGDSOCKET, OBJECTPOINT, 77),

  /* Time-out connect operations after this amount of seconds, if connects
     are OK within this time, then fine... This only aborts the connect
     phase. [Only works on unix-style/SIGALRM operating systems] */
--  CINIT(CONNECTTIMEOUT, LONG, 78),

  /* Function that will be called to store headers (instead of fwrite). The
   * parameters will use fwrite() syntax, make sure to follow them. */
--  CINIT(HEADERFUNCTION, FUNCTIONPOINT, 79),

  /* Set this to force the HTTP request to get back to GET. Only really usable
     if POST, PUT or a custom request have been used first.
   */
--  CINIT(HTTPGET, LONG, 80),

  /* Set if we should verify the Common name from the peer certificate in ssl
   * handshake, set 1 to check existence, 2 to ensure that it matches the
   * provided hostname. */
s  CINIT(SSL_VERIFYHOST, LONG, 81),

  /* Specify which file name to write all known cookies in after completed
     operation. Set file name to "-" (dash) to make it go to stdout. */
  CINIT(COOKIEJAR, OBJECTPOINT, 82),

  /* Specify which SSL ciphers to use */
s  CINIT(SSL_CIPHER_LIST, OBJECTPOINT, 83),

  /* Specify which HTTP version to use! This must be set to one of the
     CURL_HTTP_VERSION* enums set below. */
--  CINIT(HTTP_VERSION, LONG, 84),

  /* Specificly switch on or off the FTP engine's use of the EPSV command. By
     default, that one will always be attempted before the more traditional
     PASV command. */     
--  CINIT(FTP_USE_EPSV, LONG, 85),

#endif

// ============================================================================

curlCleanup curlCleanup::scurlCleanup;

// ============================================================================
// ============================================================================

curlEasy::curlEasy() :
	mData(NULL)
{
	mData = curl_easy_init();
}

// ============================================================================

curlEasy::~curlEasy()
{
	if (mData != NULL)
		curl_easy_cleanup(mData);
}

// ============================================================================

void curlEasy::SetURL(const char *anURL)
{
	mURL.Set(anURL);
}

// ============================================================================

void curlEasy::SetPort(long aPort)
{
	(void) curl_easy_setopt(mData, CURLOPT_PORT, aPort);
}

// ============================================================================

void curlEasy::SetConnectTimeOut(unsigned long aTimeOut)
{
	(void) curl_easy_setopt(mData, CURLOPT_CONNECTTIMEOUT, aTimeOut);
}

// ============================================================================

void curlEasy::SetOverallTimeOut(unsigned long aTimeOut)
{
	(void) curl_easy_setopt(mData, CURLOPT_TIMEOUT, aTimeOut);
}

// ============================================================================

void curlEasy::SetLowSpeedAbort(unsigned long aByteLimit, unsigned long aTimeLimit)
{
	(void) curl_easy_setopt(mData, CURLOPT_LOW_SPEED_LIMIT, aByteLimit);
	(void) curl_easy_setopt(mData, CURLOPT_LOW_SPEED_TIME, aTimeLimit);
}

// ============================================================================

void curlEasy::SetVerbose(bool afVerbose)
{
	(void) curl_easy_setopt(mData, CURLOPT_VERBOSE, (long) afVerbose);
}

// ============================================================================

void curlEasy::SetUseNETRC(bool afUseNETRC)
{
	(void) curl_easy_setopt(mData, CURLOPT_NETRC, (long) afUseNETRC);
}

// ============================================================================

void curlEasy::GetInfo(curlInfo &anInfo)
{
	anInfo.Update(mData);
}

// ============================================================================

bool curlEasy::Setup()
{
	if (!mHeaderStorage.Setup(mData, CURLOPT_WRITEHEADER))
		return false;		
	if (!mOutputStorage.Setup(mData, CURLOPT_FILE))
		return false;
	if (!mErrorStorage.Setup(mData, CURLOPT_STDERR))
		return false;

	// Assume a HTTP Get, this may be modified below
	(void) curl_easy_setopt(mData, CURLOPT_HTTPGET, (long) true);
	(void) curl_easy_setopt(mData, CURLOPT_URL, mURL.Get());

	mUserPassword.Setup(mData, CURLOPT_USERPWD);
	mPasswordCallBack.Setup(mData);
	
	mProgressCallBack.Setup(mData);
	
	mHTTPProxy.Setup(mData);		
	
	mErrorBuffer[0] = 0;
	(void) curl_easy_setopt(mData, CURLOPT_ERRORBUFFER, mErrorBuffer);
	
	return true;
}

// ============================================================================

CURLcode curlEasy::Perform()
{
	if (mData == NULL)
		return CURLE_FAILED_INIT;

	if (!Setup())
		return CURLE_FAILED_INIT;
	
	return curl_easy_perform(mData);
}

// ============================================================================
// ============================================================================

curlEasyHTTP::curlEasyHTTP()
{
}

// ============================================================================

curlEasyHTTP::~curlEasyHTTP()
{
}

// ============================================================================

void curlEasyHTTP::SetReferer(const char *aReferer)
{
	mReferer.Set(aReferer);
}

// ============================================================================

void curlEasyHTTP::SetUserAgent(const char *aUserAgent)
{
	mUserAgent.Set(aUserAgent);
}

// ============================================================================

void curlEasyHTTP::SetMaxRedirect(unsigned long aCount)
{
	(void) curl_easy_setopt(mData, CURLOPT_MAXREDIRS, aCount);
}

// ============================================================================

void curlEasyHTTP::SetHTTPVersion(long aVersion)
{
	(void) curl_easy_setopt(mData, CURLOPT_HTTP_VERSION, aVersion);
}

// ============================================================================

bool curlEasyHTTP::Setup()
{
	if (!curlEasy::Setup())
		return false;
	
	(void) curl_easy_setopt(mData, CURLOPT_REFERER, mReferer.Get());
	(void) curl_easy_setopt(mData, CURLOPT_USERAGENT, mUserAgent.Get());

	mHeaders.Setup(mData, CURLOPT_HTTPHEADER);
	mPostMultiPart.Setup(mData);
	mPost.Setup(mData);
	
	return true;
}

// ============================================================================
// ============================================================================

curlEasyFTP::curlEasyFTP()
{
}

// ============================================================================

curlEasyFTP::~curlEasyFTP()
{
}

// ============================================================================

void curlEasyFTP::SetUseEPSV(bool afUse)
{
	(void) curl_easy_setopt(mData, CURLOPT_FTP_USE_EPSV, (long) afUse);
}

// ============================================================================

void curlEasyFTP::SetListFileNamesOnly(bool afListFileNameOnly)
{
	(void) curl_easy_setopt(mData, CURLOPT_FTPLISTONLY, (long) afListFileNameOnly);
}

// ============================================================================

bool curlEasyFTP::Setup()
{
	if (!curlEasy::Setup())
		return false;
	
	mCommandsBeforeTransfer.Setup(mData, CURLOPT_QUOTE);
	mCommandsAfterTransfer.Setup(mData, CURLOPT_POSTQUOTE);
	
	return true;
}

