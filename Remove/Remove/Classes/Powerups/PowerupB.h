//
//  PowerupB.h
//  Remove
//
//  Created by 陶 然景 on 13-8-22.
//
//

#ifndef __Remove__PowerupB__
#define __Remove__PowerupB__

#include "PowerupInterface.h"

class PowerupB: public PowerupInterface
{
public:
    PowerupB();
    ~PowerupB();
    
    CREATE_FUNC(PowerupB);
    virtual bool init();
};

#endif /* defined(__Remove__PowerupB__) */
