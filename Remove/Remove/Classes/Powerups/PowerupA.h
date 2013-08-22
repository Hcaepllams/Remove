//
//  PowerupA.h
//  Remove
//
//  Created by 陶 然景 on 13-8-22.
//
//

#ifndef __Remove__PowerupA__
#define __Remove__PowerupA__

#include "PowerupInterface.h"

class PowerupA: public PowerupInterface
{
public:
    PowerupA();
    ~PowerupA();
    
    CREATE_FUNC(PowerupA);
    virtual bool init();
};


#endif /* defined(__Remove__PowerupA__) */
