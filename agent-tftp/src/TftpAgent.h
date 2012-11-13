/****************************************************************************

Copyright (c) 2000 - 2012 Novell, Inc.
All Rights Reserved.

This program is free software; you can redistribute it and/or
modify it under the terms of version 2 of the GNU General Public License as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.   See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, contact Novell, Inc.

To contact Novell about this file by physical or electronic mail,
you may find current contact information at www.novell.com

****************************************************************************/
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
        virtual YCPValue Read(const YCPPath &path, const YCPValue& arg = YCPNull(), const YCPValue& opt = YCPNull ());

        /**
         * Provides SCR Execute ().
         */

	virtual YCPValue Execute(const YCPPath& path, const YCPValue& value , const YCPValue& arg );
        /**
         * Provides SCR Write ().
         */
        virtual YCPBoolean Write(const YCPPath &path, const YCPValue& value, const YCPValue& arg );

        /**
         * Provides SCR Write ().
         */
        virtual YCPList Dir(const YCPPath& path);

        /**
         * Used for mounting the agent.
         */    
        virtual YCPValue otherCommand(const YCPTerm& term);
};

#endif /* _TftpAgent_h */
