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

#include <scr/Y2AgentComponent.h>
#include <scr/Y2CCAgentComponent.h>

#include "TftpAgent.h"


typedef Y2AgentComp <TftpAgent> Y2TftpAgentComp;

Y2CCAgentComp <Y2TftpAgentComp> g_y2ccag_tftp ("ag_tftp");
/*

#include "Y2CCTftpAgent.h"
#include "Y2TftpAgentComponent.h"


Y2CCTftpAgent::Y2CCTftpAgent()
    : Y2ComponentCreator(Y2ComponentBroker::BUILTIN)
{
}


bool
Y2CCTftpAgent::isServerCreator() const
{
    return true;
}


Y2Component *
Y2CCTftpAgent::create(const char *name) const
{
    if (!strcmp(name, "ag_tftp")) return new Y2TftpAgentComponent();
    else return 0;
}


Y2CCTftpAgent g_y2ccag_tftp;*/
