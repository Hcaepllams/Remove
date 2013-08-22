//
//  GameLogic.cpp
//  Remove
//
//  Created by 陶 然景 on 13-8-21.
//
//

#include "GameLogic.h"
#include "Constants.h"

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
,m_pScoreLabel(NULL)
,m_pRestartButton(NULL)
{
    
}

GameLogic::~GameLogic()
{
    CC_SAFE_RELEASE_NULL(m_pMap);
    CC_SAFE_RELEASE_NULL(m_pScoreLabel);
    CC_SAFE_RELEASE_NULL(m_pRestartButton);
}


void GameLogic::init()
{
    
}

void GameLogic::onBlockTouched(int x, int y)
{
    Block *block = this->getMap()->getBlockByPosition(x, y);
    CCArray *blocksNeedToBeRemoved = CCArray::create();
    
    blocksNeedToBeRemoved = this->getMap()->findLongestStreak(block);
    
    if (blocksNeedToBeRemoved->count() >= MIN_SCORE_STREAK)
    {
        this->getMap()->removeBlocks(blocksNeedToBeRemoved);
        m_iScore += blocksNeedToBeRemoved->count();
        
        std::stringstream ss;
        ss << m_iScore;
        
        m_pScoreLabel->setString(ss.str().c_str());
    }
    
    if (m_iScore >= END_GAME_SCORE_CAP)
    {
        this->getMap()->setTouchEnabled(false);
        m_pRestartButton->setEnabled(true);
        m_pRestartButton->setVisible(true);
    }
    
    this->getMap()->refreshMapTouchedStatus();
    
    if (!this->getMap()->checkMapAvilableStatus())
    {
        this->getMap()->shuffleMap();
    }
    
    this->getMap()->refreshMapTouchedStatus();
}

void GameLogic::restartGame()
{
    
    
    this->getMap()->init();
    this->getMap()->updateMap();
    m_iScore = 0;
    m_pScoreLabel->setString("0");
    
    m_pRestartButton->setEnabled(false);
    m_pRestartButton->setVisible(false);
}