//
//  Map.cpp
//  Remove
//
//  Created by 陶 然景 on 13-8-21.
//
//

#include "Map.h"
#define _MAP_WIDTH 10
#define _MAP_HEIGHT 10

const int MAP_WIDTH = _MAP_WIDTH;
const int MAP_HEIGHT = _MAP_HEIGHT;

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