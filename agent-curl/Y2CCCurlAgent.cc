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


Y2CCCurlAgent g_y2ccag_curl;
