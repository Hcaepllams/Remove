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
    
    CC_SAFE_RELEASE_NULL(m_pXArray);
    
    this->removeAllChildrenWithCleanup(true);
    
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
    for (int x = 0; x < m_pXArray->count(); x ++)
    {
        for (int y = 0; y < ((CCArray*)m_pXArray->objectAtIndex(x))->count(); y ++)
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
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, true);
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
//    this->compressTheMap();
//    this->fullFillMap(blocks->count());
    this->fullFillMap(blocks->count());
    this->compressTheMap();
    this->addPowerups(blocks->count());
    
}

void Map::compressTheMap()
{
    CCObject *pObjArray = NULL;
    int x = 0;
    CCARRAY_FOREACH(m_pXArray, pObjArray)
    {
        CCArray *pYArray = (CCArray*) pObjArray;
        for (int y = 0; y < pYArray->count(); y ++)
        {
            Block *block = (Block*)pYArray->objectAtIndex(y);
            if (block->getBlockType() == m_BlockTypeEmpty)
            {
                // Find it, just simply remove it.
                pYArray->removeObjectAtIndex(y);
                --y;
                this->removeChild(block, true);
            }
            else
            {
                // else set the correct x and y to the block;
                block->setX(x);
                block->setY(y);
            }
            
        }
        ++x;
    }
    this->updateMap();
//    // now remove all all empty block;
//    pObjArray = NULL;
//    CCARRAY_FOREACH(m_pXArray, pObjArray)
//    {
//        CCArray *pYArray = (CCArray*) pObjArray;
//        if (pYArray->count() > MAP_HEIGHT)
//            // there are some empty block at the end of the arry
//        {
//            while (pYArray->count() > MAP_HEIGHT)
//            {
//                pYArray->removeLastObject();
//            }
//        }
//    }
}

void Map::fullFillMap(int removedBlockCount)
{
    
    /***
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
     */
    
    CCObject *pObjArray = NULL;
    
    // Now fill the block with equal count of empty blocks with a new color
    int x = 0;
    CCARRAY_FOREACH(m_pXArray, pObjArray)
    {
        CCArray *pYArray = (CCArray*) pObjArray;
        CCObject *pObjBlock = NULL;
        int emptyCount = 0;
        CCARRAY_FOREACH(pYArray, pObjBlock)
        {
            Block *block = (Block*)pObjBlock;
            if (block->getBlockType() == m_BlockTypeEmpty)
            {
                int color = CCRANDOM_0_1() * 10 / 2 + 1;
                Block *block = Block::create(x, emptyCount + MAP_HEIGHT, (enumBlockType) color);
                pYArray->addObject(block);
                this->addChild(block);
                
                ++emptyCount;
            }
        }
        ++x;
    }
    
    this->updateMap();
}

void Map::addPowerups(int removedBlockCount)
{
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

CCArray *Map::findLongestStreak(Block *block)
{
    CCArray *returnArray = CCArray::create();
    
    if (block->getPowerup() != NULL)
    {
        // the user clicked the block with a powerup.
        // So lets assume this block a color and find the longest streak.
        
        for (int i = 1; i <= 5; i ++)
        {
            block->setBlockType((enumBlockType)i);
            CCArray *tmpArray = this->findNearbyBlocks(block->getX(), block->getY(), block);
            if (returnArray->count() <= tmpArray->count())
            {
                returnArray = tmpArray;
            }
            this->refreshMapTouchedStatus();
        }
        // set status back.
        block->setBlockType(m_BlockTypePowerup);
    }
    else
    {
        returnArray = this->findNearbyBlocks(block->getX(), block->getY(), block);
    }
    
    return returnArray;
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

bool Map::checkMapAvilableStatus()
{   
    for (int x = 0; x < MAP_WIDTH; x ++)
    {
        for (int y = 0; y < MAP_HEIGHT; y ++)
        {
            Block* block = this->getBlockByPosition(x, y);
            if (block != NULL)
            {
                if (this->findLongestStreak(block)->count() >= MIN_SCORE_STREAK)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

void Map::shuffleMap()
{
    for (int x = 0; x < MAP_WIDTH; x ++)
    {
        for (int y = 0; y < MAP_HEIGHT; y ++)
        {
            int targetX = (int)(CCRANDOM_0_1() * MAP_WIDTH);
            int targetY = (int)(CCRANDOM_0_1() * MAP_HEIGHT);
            Block *block0 = this->getBlockByPosition(x, y);
            Block *block1 = this->getBlockByPosition(targetX, targetY);
            this->exchangeBlocks(block0, block1);
        }
    }
    
    this->updateMap();
    
    this->refreshMapTouchedStatus();
    
    if (!this->checkMapAvilableStatus())
    {
        this->shuffleMap();
    }
    else
    {
        return;
    }
}

void Map::exchangeBlocks(Block *block0, Block *block1)
{
//    Block *tmpBlock = Block::create(block1->getX(), block1->getY(), block1->getBlockType());
//    tmpBlock->setPowerup(block1->getPowerup());
//    
//    block1->setBlockType(block0->getBlockType());
//    block1->setPowerup(block0->getPowerup());
//    
//    block0->setBlockType(tmpBlock->getBlockType());
//    block0->setPowerup(tmpBlock->getPowerup());
    
    ((CCArray*)m_pXArray->objectAtIndex(block0->getX()))->replaceObjectAtIndex(block0->getY(), block1);
    ((CCArray*)m_pXArray->objectAtIndex(block1->getX()))->replaceObjectAtIndex(block1->getY(), block0);
    
    int tmpX = block0->getX();
    int tmpY = block0->getY();
    
    block0->setX(block1->getX());
    block0->setY(block1->getY());
    
    block1->setX(tmpX);
    block1->setY(tmpY);
    
    block0->runAction(CCMoveTo::create(MOVE_ANIM_DURATION, ccp(block0->getX() * (BLOCK_WIDTH + GAP_X), block0->getY() * (BLOCK_HEIGHT + GAP_Y))));
    block1->runAction(CCMoveTo::create(MOVE_ANIM_DURATION, ccp(block1->getX() * (BLOCK_WIDTH + GAP_X), block1->getY() * (BLOCK_HEIGHT + GAP_Y))));
}