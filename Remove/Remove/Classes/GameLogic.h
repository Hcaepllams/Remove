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
    void onStreakEnded();
    
    void restartGame();
    
protected:
    int m_iScore;

    CC_SYNTHESIZE_RETAIN(Map*, m_pMap, Map);
    CC_SYNTHESIZE_RETAIN(CCLabelTTF*, m_pScoreLabel, ScoreLabel)
    CC_SYNTHESIZE_RETAIN(CCMenuItem*, m_pRestartButton, RestartButton);
    
    CC_SYNTHESIZE_RETAIN(CCArray*, m_pOneStreakArray, OneStreakArray);
};

#endif /* defined(__Remove__GameLogic__) */
