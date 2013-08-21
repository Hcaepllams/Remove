//
//  Map.h
//  Remove
//
//  Created by 陶 然景 on 13-8-21.
//
//

#ifndef __Remove__Map__
#define __Remove__Map__

#include "cocos-ext.h"
#include "cocos2d.h"

#include "Block.h"

USING_NS_CC;
USING_NS_CC_EXT;

class Map: public CCLayer
{
public:
    CREATE_FUNC(Map);
    
    Map();
    ~Map();
    
    bool init();
    
    
    Block* getBlockByPosition(int x, int y);
    
    void updateMap();
    
    void removeBlocks(CCArray *blocks);
    
    virtual void registerWithTouchDispatcher(void);
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

private:
    CCArray* m_pXArray; //An array contains all Y list
    void compressTheMap();
    void fullFillMap(int removedBlockCount);
};

#endif /* defined(__Remove__Map__) */
