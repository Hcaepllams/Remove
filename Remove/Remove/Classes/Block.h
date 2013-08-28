//
//  BlockManager.h
//  Remove
//
//  Created by 陶 然景 on 13-8-21.
//
//

#ifndef __Remove__BlockManager__
#define __Remove__BlockManager__

#include <iostream>
#include "cocos-ext.h"
#include "cocos2d.h"
#include "PowerupInterface.h"
USING_NS_CC;
USING_NS_CC_EXT;

typedef enum
{
    m_BlockTypeEmpty = 0,
    m_BlockTypeColor1,
    m_BlockTypeColor2,
    m_BlockTypeColor3,
    m_BlockTypeColor4,
    m_BlockTypeColor5,
    m_BlockTypePowerup
}enumBlockType;

typedef enum
{
    m_BlockStatusNormal = 0,
    m_BlockStatusSelected = 1
}enumBlockStatus;

class Block: public CCLayerColor
{
public:
    Block();
    ~Block();
    
    static Block* create(int x, int y, enumBlockType type);
    bool init(int x, int y, enumBlockType type);
    
    void updateView();
    
    CC_SYNTHESIZE(int, m_iX, X);
    CC_SYNTHESIZE(int, m_iY, Y);
    
    CC_SYNTHESIZE(enumBlockType, m_eBlockType, BlockType);
    CC_SYNTHESIZE(enumBlockStatus, m_eBlockStatus, BlockStatus);
    
    CC_SYNTHESIZE(bool, m_bTouched, Touched);// this value is used in removed alogrithm.
    CC_SYNTHESIZE_RETAIN(CCLabelTTF*, m_pPowerupLabel, PowerupLabel);
    
    CC_SYNTHESIZE_RETAIN(PowerupInterface*, m_pPowerup, Powerup);
    

};

#endif /* defined(__Remove__BlockManager__) */
