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
,m_bTouched(false)
,m_pPowerupLabel(NULL)
,m_pPowerup(NULL)
{
    
}

Block::~Block()
{
    CC_SAFE_RELEASE_NULL(m_pPowerupLabel);
    CC_SAFE_RELEASE_NULL(m_pPowerup);
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
    
    this->setPowerupLabel(CCLabelTTF::create("", "Helvetica", 24));
    this->addChild(m_pPowerupLabel);
    this->getPowerupLabel()->setPosition(ccp(this->getContentSize().width / 2, this->getContentSize().height / 2));
    
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
    m_pPowerupLabel->setString("");
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
    
    if (this->getPowerup() != NULL)
    {
        this->getPowerupLabel()->setString(this->getPowerup()->getPowerupName()->getCString());
    }
    
    this->setColor(color);
}