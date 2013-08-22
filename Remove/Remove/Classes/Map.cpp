//
//  Map.cpp
//  Remove
//
//  Created by 陶 然景 on 13-8-21.
//
//

#include "Map.h"
#include "Constants.h"
#include "GameLogic.h"
#include "PowerupA.h"
#include "PowerupB.h"
#include "PowerupC.h"


Map::Map()
:m_pXArray(NULL)
{
    
}

Map::~Map()
{
    CC_SAFE_RELEASE_NULL(m_pXArray);
}

bool Map::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    
    this->setTouchEnabled(true);
    
    m_pXArray = CCArray::create();
    m_pXArray->retain();
    
    for (int x = 0; x < MAP_WIDTH; x ++)
    {
        for (int y = 0; y < MAP_HEIGHT; y ++)
        {
            if (m_pXArray->count() <= x)
            {
                m_pXArray->addObject(CCArray::create());
            }
            
            CCArray *yArray = (CCArray*) m_pXArray->objectAtIndex(x);
            
            int color = CCRANDOM_0_1() * 10 / 2 + 1;
            Block *block = Block::create(x, y, (enumBlockType)color);
            yArray->addObject(block);
            
            this->addChild(block);
        }
    }
    
    
    return true;
}

Block* Map::getBlockByPosition(int x, int y)
{
    CCArray *yArray = (CCArray*)m_pXArray->objectAtIndex(x);
    
    if (yArray == NULL)
    {
        return NULL;
    }
    
    Block *block = NULL;
    block = (Block*) yArray->objectAtIndex(y);
    return block;
}

void Map::updateMap()
{
    for (int x = 0; x < MAP_WIDTH; x ++)
    {
        for (int y = 0; y < MAP_HEIGHT; y ++)
        {
            Block* block = this->getBlockByPosition(x, y);
            if (block != NULL)
            {
                block->updateView();
            }
        }
    }
}

void Map::refreshMapTouchedStatus()
{
    for (int x = 0; x < MAP_WIDTH; x ++)
    {
        for (int y = 0; y < MAP_HEIGHT; y ++)
        {
            Block* block = this->getBlockByPosition(x, y);
            if (block != NULL)
            {
                block->setTouched(false);
            }
        }
    }
}

void Map::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool Map::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCPoint point = pTouch->getLocation();
    
    if (point.x >= (MAP_WIDTH * (BLOCK_WIDTH + GAP_X) - GAP_X) ||
        point.y >= (MAP_HEIGHT * (BLOCK_HEIGHT + GAP_Y) - GAP_Y))
    {
        return false;
    }
    
    int x = point.x / (BLOCK_WIDTH + GAP_X);
    if ((int)point.x % (BLOCK_WIDTH + GAP_X) > BLOCK_WIDTH)
    {
        return false;
    }
    
    int y = point.y / (BLOCK_HEIGHT + GAP_Y);
    if ((int)point.y % (BLOCK_HEIGHT + GAP_Y) > BLOCK_HEIGHT)
    {
        return false;
    }
    
    GameLogic::sharedInstance()->onBlockTouched(x, y);
    
    return true;
}

void Map::removeBlocks(cocos2d::CCArray *blocks)
{
    CCObject *pObj = NULL;
    CCARRAY_FOREACH(blocks, pObj)
    {
        Block *block = (Block*)pObj;
        block->setBlockType(m_BlockTypeEmpty);
        block->setPowerup(NULL);
        block->updateView();
    }
    this->compressTheMap();
    this->fullFillMap(blocks->count());
}

void Map::compressTheMap()
{
    CCObject *pObjArray = NULL;
    CCARRAY_FOREACH(m_pXArray, pObjArray)
    {
        CCArray *pYArray = (CCArray*) pObjArray;
        for (int y = 0; y < pYArray->count(); y ++)
        {
            Block *block = (Block*)pYArray->objectAtIndex(y);
            if (block->getBlockType() == m_BlockTypeEmpty)
            {
                //Exchange the empty to the nearest block with color
                for (int tmp = y + 1; tmp < pYArray->count(); tmp ++)
                {
                    Block *targetBlock = (Block*)pYArray->objectAtIndex(tmp);
                    if (targetBlock->getBlockType() != m_BlockTypeEmpty)
                    {
                        // Find it! Now exchange them;
                        block->setBlockType(targetBlock->getBlockType());
                        targetBlock->setBlockType(m_BlockTypeEmpty);
                        break;
                    }
                    // Else continue finding.
                }
            }
            // Else do nothing.
        }
    }
}

void Map::fullFillMap(int removedBlockCount)
{
    CCObject *pObjArray = NULL;
       
    // Now fill the empty block with a new color
    CCARRAY_FOREACH(m_pXArray, pObjArray)
    {
        CCArray *pYArray = (CCArray*) pObjArray;
        CCObject *pObjBlock = NULL;
        CCARRAY_FOREACH(pYArray, pObjBlock)
        {
            Block *block = (Block*)pObjBlock;
            if (block->getBlockType() == m_BlockTypeEmpty)
            {
                int color = CCRANDOM_0_1() * 10 / 2 + 1;
                block->setBlockType((enumBlockType) color);
            }
        }
    }
    
    CCPoint randomPosition = ccp(0, 0);
    if (removedBlockCount >= 5)
    {
        do {
            randomPosition.x = (int)(CCRANDOM_0_1() * MAP_WIDTH);
            randomPosition.y = (int)(CCRANDOM_0_1() * MAP_HEIGHT);
        } while (this->getBlockByPosition(randomPosition.x, randomPosition.y)->getPowerup() != NULL);
        
    }
    
    if (removedBlockCount >= 5 && removedBlockCount < 8)
    {
        this->getBlockByPosition(randomPosition.x, randomPosition.y)->setBlockType(m_BlockTypePowerup);
        PowerupA *powerup = PowerupA::create();
        this->getBlockByPosition(randomPosition.x, randomPosition.y)->setPowerup(powerup);
        
        // Powerup A
    }
    else if (removedBlockCount >= 8 && removedBlockCount < 12)
    {
        this->getBlockByPosition(randomPosition.x, randomPosition.y)->setBlockType(m_BlockTypePowerup);
        PowerupB *powerup = PowerupB::create();
        this->getBlockByPosition(randomPosition.x, randomPosition.y)->setPowerup(powerup);
        // Powerup B
    }
    else if (removedBlockCount >= 12)
    {
        this->getBlockByPosition(randomPosition.x, randomPosition.y)->setBlockType(m_BlockTypePowerup);
        PowerupC *powerup = PowerupC::create();
        this->getBlockByPosition(randomPosition.x, randomPosition.y)->setPowerup(powerup);
        // Powerup C
    }
    
    this->updateMap();
}

CCArray *Map::findNearbyBlocks(int x, int y, Block *targetBlock)
{
    CCArray *returnArray = CCArray::create();
    Block *block = this->getBlockByPosition(x, y);
    if (block->getTouched() == true)
    {
        return returnArray;
    }
    
    block->setTouched(true);
    
    if (block->getBlockType() == targetBlock->getBlockType()
        || block->getPowerup() != NULL)
    {
        returnArray->addObject(block);
        
        if (x + 1 < MAP_WIDTH)
        {
            returnArray->addObjectsFromArray(findNearbyBlocks(x + 1, y, targetBlock));
        }
        
        if (x - 1 >= 0)
        {
            returnArray->addObjectsFromArray(findNearbyBlocks(x - 1, y, targetBlock));
        }
        
        if (y + 1 < MAP_HEIGHT)
        {
            returnArray->addObjectsFromArray(findNearbyBlocks(x, y + 1, targetBlock));
        }
        
        if (y - 1 >= 0)
        {
            returnArray->addObjectsFromArray(findNearbyBlocks(x, y - 1, targetBlock));
        }
    }
    
    
    
    
    
    return returnArray;
}