//
//  Map.h
//  Remove
//
//  Created by 陶 然景 on 13-8-21.
//
//

#ifndef __Remove__Map__
#define __Remove__Map__

#include "cocos-ext.h"
#include "cocos2d.h"

#include "Block.h"

USING_NS_CC;
USING_NS_CC_EXT;



extern const int MAP_WIDTH;
extern const int MAP_HEIGHT;


class Map: public CCLayer
{
public:
    CREATE_FUNC(Map);
    
    Map();
    ~Map();
    
    bool init();
    
    
    Block* getBlockByPosition(int x, int y);
    
    void updateMap();
    
private:
    CCArray* m_pXArray; //An array contains all Y list 
};

#endif /* defined(__Remove__Map__) */
