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

#ifndef _TftpAgent_h
#define _TftpAgent_h

#include <Y2.h>
#include <scr/SCRAgent.h>

/**
 * @short An interface class between YaST2 and Tftp Agent
 */
class TftpAgent : public SCRAgent
{
    private:
        /**
         * Agent private variables
         */

    public:
        /**
         * Default constructor.
         */
        TftpAgent();
        /** 
         * Destructor.
         */
        virtual ~TftpAgent();

        /**
         * Provides SCR Read ().
         * @param path Path that should be read.
         * @param arg Additional parameter.
         */
        virtual YCPValue Read(const YCPPath &path, const YCPValue& arg = YCPNull(), const YCPValue& opt = YCPNull());

        /**
         * Provides SCR Execute ().
         */

	virtual YCPValue Execute(const YCPPath& path, const YCPValue& value , const YCPValue& arg );
        /**
         * Provides SCR Write ().
         */
        virtual YCPValue Write(const YCPPath &path, const YCPValue& value, const YCPValue& arg );

        /**
         * Provides SCR Write ().
         */
        virtual YCPValue Dir(const YCPPath& path);

        /**
         * Used for mounting the agent.
         */    
        virtual YCPValue otherCommand(const YCPTerm& term);
};

#endif /* _TftpAgent_h */
