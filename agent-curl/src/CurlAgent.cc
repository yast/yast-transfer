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
#include "curlcpp.h"

/**
 * Constructor
 */
CurlAgent::CurlAgent() : SCRAgent()
{
}

/**
 * Destructor
 */
CurlAgent::~CurlAgent()
{
}




YCPValue CurlAgent::Get( const char *url, const char *target)
{
	curlEasyHTTP    Request;
	CURLcode        Result;
	curlInfo	    info;

	// Response Map
	YCPMap	   Response;

	curlOutputFileTrait Output(target);
	Request.mOutputStorage.SetTrait(&Output, false);

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
		Response->add(YCPString("code"), YCPInteger ( (long int) info.mHTTPCode));
		Response->add(YCPString("totaltime"), YCPFloat ( info.mTotalTime));
		Response->add(YCPString("dsize"), YCPFloat ( info.mSizeDownload));
		return Response;
	}

	return Response;
}


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
	else
	{
		y2error("Unknown path");
	}


	return ret;
}




/**
 * Dir
 */
YCPValue CurlAgent::Dir(const YCPPath& path)
{
	y2error("Wrong path '%s' in Read().", path->toString().c_str());
	return YCPVoid();
}

/**
 * Read
 */
YCPValue CurlAgent::Read(const YCPPath &path, const YCPValue& arg)
{
	y2error("Wrong path '%s' in Read().", path->toString().c_str());
	return YCPVoid();
}

/**
 * Write
 */
YCPValue CurlAgent::Write(const YCPPath &path, const YCPValue& value,
		const YCPValue& arg)
{
	y2error("Wrong path '%s' in Write().", path->toString().c_str());
	return YCPVoid();
}

/**
 * otherCommand
 */
YCPValue CurlAgent::otherCommand(const YCPTerm& term)
{
	string sym = term->symbol()->symbol();

	if (sym == "CurlAgent") {
		/* Your initialization */
		return YCPVoid();
	}

	return YCPNull();
}
