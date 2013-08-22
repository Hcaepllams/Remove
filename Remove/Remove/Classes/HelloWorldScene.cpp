#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Map.h"
#include "GameLogic.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    Map *map = Map::create();
    this->addChild(map);
    
    GameLogic::sharedInstance()->setMap(map);
    
    CCLabelTTF *scoreLabel = CCLabelTTF::create("0", "Helvetica", 30);
    
    GameLogic::sharedInstance()->setScoreLabel(scoreLabel);
    
    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *restartButton = CCMenuItemImage::create(
                                                          "CloseNormal.png",
                                                          "CloseSelected.png",
                                                          this,
                                                          menu_selector(HelloWorld::menuCloseCallback) );
    restartButton->setEnabled(false);
    restartButton->setVisible(false);
    GameLogic::sharedInstance()->setRestartButton(restartButton);
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(restartButton, NULL);
    pMenu->setPosition( ccp(700, 50) );
    this->addChild(pMenu, 1);
    
    this->addChild(scoreLabel);
    scoreLabel->setPosition(ccp(700, 100));
    
    return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    GameLogic::sharedInstance()->restartGame();
}
