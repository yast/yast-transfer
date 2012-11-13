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
 *   YaST2 SCR: Curl agent implementation
 *
 * Authors:
 *   Anas Nashif <nashif@suse.de>
 *
 * $Id$
 */

#include <scr/Y2AgentComponent.h>
#include <scr/Y2CCAgentComponent.h>

#include "CurlAgent.h"


typedef Y2AgentComp <CurlAgent> Y2CurlAgentComp;

Y2CCAgentComp <Y2CurlAgentComp> g_y2ccag_curl ("ag_curl");

/*

#include "Y2CCCurlAgent.h"
#include "Y2CurlAgentComponent.h"


Y2CCCurlAgent::Y2CCCurlAgent()
    : Y2ComponentCreator(Y2ComponentBroker::BUILTIN)
{
}


bool
Y2CCCurlAgent::isServerCreator() const
{
    return true;
}


Y2Component *
Y2CCCurlAgent::create(const char *name) const
{
    if (!strcmp(name, "ag_curl")) return new Y2CurlAgentComponent();
    else return 0;
}


Y2CCCurlAgent g_y2ccag_curl;*/
