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
,m_pOneStreakArray(NULL)
{
    
}

GameLogic::~GameLogic()
{
    CC_SAFE_RELEASE_NULL(m_pMap);
    CC_SAFE_RELEASE_NULL(m_pScoreLabel);
    CC_SAFE_RELEASE_NULL(m_pRestartButton);
    CC_SAFE_RELEASE_NULL(m_pOneStreakArray);
}


void GameLogic::init()
{
    this->setOneStreakArray(CCArray::create());
}

void GameLogic::onBlockTouched(int x, int y)
{
    Block *block = this->getMap()->getBlockByPosition(x, y);
    
    if (m_pOneStreakArray->containsObject(block))
    {
        int index = m_pOneStreakArray->indexOfObject((CCObject*)block);
        while (m_pOneStreakArray->count() > index + 1)
        {
            Block *block = (Block*)m_pOneStreakArray->lastObject();
            block->setBlockStatus(m_BlockStatusNormal);
            m_pOneStreakArray->removeLastObject();
            block->updateView();
        }
    }
    
    Block *lastBlock = NULL;
    
    if (m_pOneStreakArray->count() > 0)
    {
        lastBlock = (Block*) m_pOneStreakArray->lastObject();
    }
    
    if (lastBlock != NULL)
    {
        if (
            (lastBlock->getX() == block->getX() &&
            (lastBlock->getY() == block->getY() - 1 || lastBlock->getY() == block->getY() + 1))
            ||
            (lastBlock->getY() == block->getY() &&
             (lastBlock->getX() == block->getX() - 1 || lastBlock->getX() == block->getX() + 1))
            )
        {
            if (lastBlock->getBlockType() == block->getBlockType()
                || lastBlock->getBlockType() == m_BlockTypePowerup
                || block->getBlockType() == m_BlockTypePowerup)
            {
                block->setBlockStatus(m_BlockStatusSelected);
                block->updateView();
                m_pOneStreakArray->addObject(block);
            }
        }
    }
    else
    {
        block->setBlockStatus(m_BlockStatusSelected);
        block->updateView();
        m_pOneStreakArray->addObject(block);
    }
}

void GameLogic::onStreakEnded()
{
    if (m_pOneStreakArray->count() >= MIN_SCORE_STREAK)
    {
        this->getMap()->removeBlocks(m_pOneStreakArray);
        m_iScore += m_pOneStreakArray->count();

        std::stringstream ss;
        ss << m_iScore;

        m_pScoreLabel->setString(ss.str().c_str());
    }
    else
    {
        CCObject *pObj = NULL;
        CCARRAY_FOREACH(m_pOneStreakArray, pObj)
        {
            Block *block = (Block*) pObj;
            block->setBlockStatus(m_BlockStatusNormal);
        }
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
    
    m_pOneStreakArray->removeAllObjects();
    this->getMap()->updateMap();
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