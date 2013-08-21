//
//  BlockManager.cpp
//  Remove
//
//  Created by 陶 然景 on 13-8-21.
//
//

#include "Block.h"
#include "Constants.h"

///////////////////////////

Block::Block()
:m_iX(0)
,m_iY(0)
,m_eBlockType(m_BlockTypeEmpty)
{
    
}

Block::~Block()
{
    
}

bool Block::init(int x, int y, enumBlockType type)
{
    if (!CCLayerColor::init())
    {
        return false;
    }
    
    this->setContentSize(CCSizeMake(BLOCK_WIDTH, BLOCK_HEIGHT));
    this->setOpacity(255);
    
    this->setX(x);
    this->setY(y);
    this->setBlockType(type);
    
    this->setPosition(ccp(x * (BLOCK_WIDTH + GAP_X), y * (BLOCK_HEIGHT + GAP_Y)));
    
    this->updateView();
    
    return true;
}

Block* Block::create(int x, int y, enumBlockType type)
{
    Block *pRet = new Block();
    if (pRet && pRet->init(x, y, type))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    } 
}

void Block::updateView()
{
    ccColor3B color = ccWHITE;
    this->setVisible(true);
    switch (m_eBlockType)
    {
        case m_BlockTypeEmpty:
            this->setVisible(false);
            break;
        case m_BlockTypeColor1:
            color = ccWHITE;
            break;
        case m_BlockTypeColor2:
            color = ccYELLOW;
            break;
        case m_BlockTypeColor3:
            color = ccBLUE;
            break;
        case m_BlockTypeColor4:
            color = ccGREEN;
            break;
        case m_BlockTypeColor5:
            color = ccRED;
            break;
        default:
            color = ccGRAY;
            break;
    }
    this->setColor(color);
}