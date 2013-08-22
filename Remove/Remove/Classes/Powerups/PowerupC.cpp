//
//  PowerupC.cpp
//  Remove
//
//  Created by 陶 然景 on 13-8-22.
//
//

#include "PowerupC.h"

PowerupC::PowerupC()
{
    
}

PowerupC::~PowerupC()
{
    
}

bool PowerupC::init()
{
    this->setPowerupName(CCString::create("C"));
    return true;
}