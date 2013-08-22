//
//  PowerupA.cpp
//  Remove
//
//  Created by 陶 然景 on 13-8-22.
//
//

#include "PowerupA.h"

PowerupA::PowerupA()
{
    
}

PowerupA::~PowerupA()
{
    
}

bool PowerupA::init()
{
    this->setPowerupName(CCString::create("A"));
    return true;
}