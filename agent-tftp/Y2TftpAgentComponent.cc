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

#include "Y2TftpAgentComponent.h"
#include <scr/SCRInterpreter.h>
#include "TftpAgent.h"


Y2TftpAgentComponent::Y2TftpAgentComponent()
    : interpreter(0),
      agent(0)
{
}


Y2TftpAgentComponent::~Y2TftpAgentComponent()
{
    if (interpreter) {
        delete interpreter;
        delete agent;
    }
}


bool
Y2TftpAgentComponent::isServer() const
{
    return true;
}

string
Y2TftpAgentComponent::name() const
{
    return "ag_tftp";
}


YCPValue Y2TftpAgentComponent::evaluate(const YCPValue& value)
{
    if (!interpreter) {
        agent = new TftpAgent();
        interpreter = new SCRInterpreter(agent);
    }
    
    return interpreter->evaluate(value);
}

