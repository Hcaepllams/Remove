//
//  GameLogic.h
//  Remove
//
//  Created by 陶 然景 on 13-8-21.
//
//

#ifndef __Remove__GameLogic__
#define __Remove__GameLogic__

#include "cocos-ext.h"
#include "cocos2d.h"

#include "Map.h"

USING_NS_CC;
USING_NS_CC_EXT;

class GameLogic
{
public:
    static GameLogic* sharedInstance();
    
    GameLogic();
    ~GameLogic();
    
    void init();
    
    void onBlockTouched(int x, int y);
    
protected:
    int m_iScore;

    CC_SYNTHESIZE_RETAIN(Map*, m_pMap, Map);
};

#endif /* defined(__Remove__GameLogic__) */
