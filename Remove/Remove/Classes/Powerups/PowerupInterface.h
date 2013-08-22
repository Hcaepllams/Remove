//
//  PowerupInterface.h
//  Remove
//
//  Created by 陶 然景 on 13-8-22.
//
//

#ifndef __Remove__PowerupInterface__
#define __Remove__PowerupInterface__

#include "cocos-ext.h"
#include "cocos2d.h"

USING_NS_CC;
USING_NS_CC_EXT;

class PowerupInterface: public CCObject
{
public:
    PowerupInterface():m_pPowerupName(NULL){};
    ~PowerupInterface(){};
    
    CREATE_FUNC(PowerupInterface);
    
    virtual bool init() {return false;};
    virtual bool execute() {return false;};
    
    CC_SYNTHESIZE_RETAIN(CCString*, m_pPowerupName, PowerupName);
};

#endif /* defined(__Remove__PowerupInterface__) */
