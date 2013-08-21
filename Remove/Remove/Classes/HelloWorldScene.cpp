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
    
    return true;
}