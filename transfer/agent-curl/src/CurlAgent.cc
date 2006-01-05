/*
 * YaST2: Core system
 *
 * Description:
 *   YaST2 SCR: Curl agent implementation
 *
 * Authors:
 *   Anas Nashif <nashif@suse.de>
 *
 * $Id$
 */

#include "CurlAgent.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "curl/curl.h"

/**
 * Constructor
 */
CurlAgent::CurlAgent() : SCRAgent()
{
    easySSL_val = false;
}

/**
 * Destructor
 */
CurlAgent::~CurlAgent()
{
}

void CurlAgent::easySSL( bool easy )
{
    easySSL_val = easy;
    return;
}

YCPValue CurlAgent::Get( const char *url, const char *target)
{

	FILE *outfile;
	CURL *curl;
	CURLcode res;
	YCPMap	   Response;
	char	*content;
	double	dsize, totaltime;
	long	code;


	outfile = fopen(target, "w");
	if (!outfile)
	{
		y2error("Cant open file %s", target);
		return YCPVoid();
	}

	curl_global_init(CURL_GLOBAL_DEFAULT);

	curl = curl_easy_init();
	if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url);
        if( easySSL_val )
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		res = curl_easy_setopt(curl, CURLOPT_WRITEDATA, outfile);
		if ( res != 0 ) {
			fclose( outfile );
			y2error("Cant open file %s", target);
			y2milestone("Cant open file %s", target);
			return YCPVoid();
		}

		res = curl_easy_perform(curl);
		if(CURLE_OK != res) {
			/* we failed */
			y2error("curl told us %d\n", res);
			return YCPVoid();
		}


		res =curl_easy_getinfo(curl,CURLINFO_CONTENT_TYPE,&content);

		if(CURLE_OK != res) {
			y2error("curl told us %d\n", res);
			return YCPVoid();
		}

		if (content) {
		Response->add(YCPString("content-type"), YCPString(content));
		}

		res =curl_easy_getinfo(curl,CURLINFO_HTTP_CODE,&code);
		if(CURLE_OK != res) {
			y2error("curl told us %d\n", res);
			return YCPVoid();
		}
		Response->add(YCPString("code"), YCPInteger(code));
		res =curl_easy_getinfo(curl,CURLINFO_TOTAL_TIME,&totaltime);
		if(CURLE_OK != res) {
			y2error("curl told us %d\n", res);
			return YCPVoid();
		}

		Response->add(YCPString("totaltime"), YCPFloat(totaltime));
		res =curl_easy_getinfo(curl,CURLINFO_SIZE_DOWNLOAD,&dsize);

		if(CURLE_OK != res) {
			y2error("curl told us %d\n", res);
			return YCPVoid();
		}
		Response->add(YCPString("dsize"), YCPFloat(dsize));

		y2milestone("curl returned -> response code: %ld, total size: %g, total time %f, content type: %s\n", code, dsize, totaltime, content);
		/* always cleanup */
		curl_easy_cleanup(curl);


	}
	fclose( outfile );


	return Response;


}

/*
YCPValue  CurlAgent::Post(  const char *url, const char *post, const char *target)
{
	curlEasyHTTP    Request;
	CURLcode        Result;
	curlInfo	    info;
	// Response Map
	YCPMap	   Response;

	curlOutputFileTrait Output(target);
	Request.mOutputStorage.SetTrait(&Output, false);

	Request.mPost.Set(post);

	Request.SetVerbose(false);
	Request.SetURL(url);
	Result = Request.Perform();
	Request.GetInfo(info);

	if (Result != CURLE_OK)
	{
		y2error("Error: %s", Request.GetErrorStr());
		Response->add(YCPString("code"), YCPInteger ( info.mHTTPCode));
		return Response;
	}
	else
	{

		Response->add(YCPString("code"), YCPInteger ( info.mHTTPCode));
		Response->add(YCPString("totaltime"), YCPFloat ( info.mTotalTime));
		Response->add(YCPString("dsize"), YCPFloat ( info.mSizeDownload));
		return Response;
	}
	return Response;

}

*/

/*
 * Get single values from map
 */
string CurlAgent::getMapValue ( const YCPMap map, const string key, const string defaultValue)
{
	for (YCPMapIterator i = map->begin(); i != map->end (); i++)
	{
		if (!i.key()->isString())   // key must be a string
		{
			y2error("Cannot write invalid key %s, must be a string",
					i.value()->toString().c_str());
		}
		else        // everything is OK
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
	return ( defaultValue );
}






/*--------------------------------------------------------------------------*
 * Execute path of the curl agent
 *--------------------------------------------------------------------------*/
YCPValue CurlAgent::Execute (const YCPPath& path,
		const YCPValue& value,
		const YCPValue& arg)
{
	string path_name = path->component_str (0);
	YCPValue ret = YCPVoid();

	YCPMap options = arg->asMap();
	string Output = getMapValue ( options,"output" , "");
	string Data = getMapValue ( options,"data" , "");

	y2milestone("Data: %s", Data.c_str());
	y2milestone("Output: %s", Output.c_str());

	if (  path_name == "get" )
	{
		if ( !value.isNull()
				&& value->isString()
				&& !arg.isNull())
		{
			ret = Get( (const char *)value->asString()->value().c_str(),
					(const char *) Output.c_str() );
		}
	}

    else if (path_name == "easySSL")
    {
        if ( !value.isNull() ) {
            easySSL( (bool)(value->asBoolean()->value()) );
        }
    }
/*
	else if (path_name == "post")
	{
		if ( !value.isNull()
				&& value->isString()
				&& !arg.isNull())
		{
			ret = Post(
					(const char *) value->asString()->value().c_str(),
					(const char *) Data.c_str(),
					(const char *) Output.c_str()
					);
		}

	}
*/
	else
	{
		y2error("Unknown path");
	}


	return ret;
}




/**
 * Dir
 */
YCPList CurlAgent::Dir(const YCPPath& path)
{
	y2error("Wrong path '%s' in Read().", path->toString().c_str());
	return YCPNull();
}

/**
 * Read
 */
YCPValue CurlAgent::Read(const YCPPath &path, const YCPValue& arg, const YCPValue& opt)
{
	y2error("Wrong path '%s' in Read().", path->toString().c_str());
	return YCPVoid();
}

/**
 * Write
 */
YCPBoolean CurlAgent::Write(const YCPPath &path, const YCPValue& value,
		const YCPValue& arg)
{
	y2error("Wrong path '%s' in Write().", path->toString().c_str());
	return YCPBoolean(false);
}

/**
 * otherCommand
 */
YCPValue CurlAgent::otherCommand(const YCPTerm& term)
{
    string sym = term->name ();

	if (sym == "CurlAgent") {
        /* Your initialization */
        return YCPVoid();
    }

    return YCPNull();
}

