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

#ifndef _CurlAgent_h
#define _CurlAgent_h

#include <Y2.h>
#include <scr/SCRAgent.h>
#include <scr/SCRInterpreter.h>

/**
 * @short An interface class between YaST2 and Curl Agent
 */
class CurlAgent : public SCRAgent
{
private:
    /**
     * Agent private variables
     */

public:
    /**
     * Default constructor.
     */
    CurlAgent();

    /**
     * Destructor.
     */
    virtual ~CurlAgent();

    /**
     * Provides SCR Read ().
     * @param path Path that should be read.
     * @param arg Additional parameter.
     */
    virtual YCPValue Read(const YCPPath &path,
			  const YCPValue& arg = YCPNull());

    /**
     * Provides SCR Write ().
     */
    virtual YCPValue Write(const YCPPath &path,
			   const YCPValue& value,
			   const YCPValue& arg = YCPNull());


    /**
     * Provides SCR Execute ().
     */
    virtual YCPValue Execute(const YCPPath &path,
			     const YCPValue& value = YCPNull(),
			     const YCPValue& arg = YCPNull());

    /**
     * Provides SCR Dir ().
     */
    virtual YCPValue Dir(const YCPPath& path);

    /**
     * Used for mounting the agent.
     */
    virtual YCPValue otherCommand(const YCPTerm& term);
    virtual YCPValue Ftpdir( const char *kHTTPURL_Str, const char *HTTPTarget);
    virtual YCPValue Get( const char *kHTTPURL_Str, const char *HTTPTarget);
    virtual YCPValue  Post(  const char *kHTTPPostURL_Str, const char *kHTTPPost_Str, const char *HTTPTarget);
    virtual YCPValue SendXMLRPCRequest(  const char *kHTTPPostURL_Str, const char *HTTPTarget, const char *kHTTPPost_Str);
    virtual string getMapValue ( const YCPMap map, const string key, const string defaultValue);

    

private:

    
  /**
   * user
   */
    string user;
    string password;
    string userPassword;
  /**
   * proxy user
   */
    string proxyUser;
    string proxyPassword;


};

#endif /* _CurlAgent_h */
