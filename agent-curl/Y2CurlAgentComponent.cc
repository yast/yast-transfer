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

#include "Y2CurlAgentComponent.h"
#include <scr/SCRInterpreter.h>
#include "CurlAgent.h"


Y2CurlAgentComponent::Y2CurlAgentComponent()
    : interpreter(0),
      agent(0)
{
}


Y2CurlAgentComponent::~Y2CurlAgentComponent()
{
    if (interpreter) {
        delete interpreter;
        delete agent;
    }
}


bool
Y2CurlAgentComponent::isServer() const
{
    return true;
}

string
Y2CurlAgentComponent::name() const
{
    return "ag_curl";
}


YCPValue Y2CurlAgentComponent::evaluate(const YCPValue& value)
{
    if (!interpreter) {
        agent = new CurlAgent();
        interpreter = new SCRInterpreter(agent);
    }
    
    return interpreter->evaluate(value);
}

