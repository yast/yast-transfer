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

#ifndef Y2CCTftpAgent_h
#define Y2CCTftpAgent_h

#include "Y2.h"

/**
 * @short And a component creator for the component
 */
class Y2CCTftpAgent : public Y2ComponentCreator
{
    public:
        /**
         * Enters this component creator into the global list of component creators.
         */
        Y2CCTftpAgent();
    
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
