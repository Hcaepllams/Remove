//
//  GameLogic.cpp
//  Remove
//
//  Created by 陶 然景 on 13-8-21.
//
//

#include "GameLogic.h"
static GameLogic* m_pSharedInstance = NULL;

GameLogic *GameLogic::sharedInstance()
{
    if (m_pSharedInstance == NULL)
    {
        m_pSharedInstance = new GameLogic();
        m_pSharedInstance->init();
    }
    return m_pSharedInstance;
}

GameLogic::GameLogic()
:m_iScore(0)
,m_pMap(NULL)
{
    
}

GameLogic::~GameLogic()
{
    CC_SAFE_RELEASE_NULL(m_pMap);
}


void GameLogic::init()
{
    
}

void GameLogic::onBlockTouched(int x, int y)
{
    Block *block = this->getMap()->getBlockByPosition(x, y);
    CCArray *blocksNeedToBeRemoved = CCArray::create();
    blocksNeedToBeRemoved = this->getMap()->findNearbyBlocks(x, y, block);
    
    if (blocksNeedToBeRemoved->count() > 2)
    {
        this->getMap()->removeBlocks(blocksNeedToBeRemoved);
    }
    
    this->getMap()->refreshMapTouchedStatus();
}
