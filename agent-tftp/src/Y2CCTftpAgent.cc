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


Y2CCTftpAgent g_y2ccag_tftp;
