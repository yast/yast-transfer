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

#ifndef Y2CCCurlAgent_h
#define Y2CCCurlAgent_h

#include "Y2.h"

/**
 * @short And a component creator for the component
 */
class Y2CCCurlAgent : public Y2ComponentCreator
{
    public:
        /**
         * Enters this component creator into the global list of component creators.
         */
        Y2CCCurlAgent();
    
        /**
         * Specifies, whether this creator creates Y2Servers.
         */
        virtual bool isServerCreator() const;
    
        /**
         * Implements the actual creating of the component.
         */
        virtual Y2Component *create(const char *name) const;
};

#endif
