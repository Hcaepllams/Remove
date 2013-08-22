//
//  PowerupC.h
//  Remove
//
//  Created by 陶 然景 on 13-8-22.
//
//

#ifndef __Remove__PowerupC__
#define __Remove__PowerupC__

#include "PowerupInterface.h"

class PowerupC: public PowerupInterface
{
public:
    PowerupC();
    ~PowerupC();
    
    CREATE_FUNC(PowerupC);
    virtual bool init();
};


#endif /* defined(__Remove__PowerupC__) */
