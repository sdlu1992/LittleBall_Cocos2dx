#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"


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

// on "init" you need to initialize y instance
bool HelloWorld::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create("quit.png","quit_press.png",this,menu_selector(HelloWorld::menuCloseCallback) );
    pCloseItem->setScale(0.7);
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 250, 150) );
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);
    
    CCMenuItemImage *pStartItem = CCMenuItemImage::create("start.png", "start_press.png",this,menu_selector(HelloWorld::menuStartCallback));
    pStartItem->setScale(0.7);
    pStartItem->setPosition(ccp(250,150));
    CCMenu* start = CCMenu::create(pStartItem,NULL);
    start->setPosition(CCPointZero);
    this->addChild(start,1);
    CCLog("1");
    //    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Thonburi", 34);
    
    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* title = CCSprite::create("collect_candy.png");
    title->setScale(0.7);
    title->setPosition(ccp(size.width/2,size.height/1.5));
    
    // position the label on the center of the screen
//    pLabel->setPosition( ccp(size.width / 2, size.height - 20) );
    
    // add the label as a child to this layer
//    this->addChild(pLabel, 1);
    
    // add "HelloWorld" splash screen"
//    CCSize s = CCDirector::sharedDirector()->getWinSize();
//
//    CCRenderTexture *rend = CCRenderTexture::create(s.width, s.height, kCCTexture2DPixelFormat_RGBA4444, CC_GL_DEPTH24_STENCIL8);
//   
//    glStencilMask(0xFF);
//
//    rend->beginWithClear(0.5, 0.4, 0.7, 100);
//    glEnable(GL_STENCIL_TEST);
//    glStencilFunc(GL_ALWAYS, 1, 0xFF);
//    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
//    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
//    glColorMask(1, 1, 1, 1);
//    rend->end();
//    rend->setPosition(ccp(s.width/2, s.height/2));
//    this->addChild(rend);
    pSprite = CCSprite::create("background.png");
    
    // position the sprite on the center of the screen
    pSprite->setPosition( ccp(size.width/2, size.height/2) );
    setTouchEnabled(true);
    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    addChild(title,0);
    return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::menuStartCallback(CCObject* pSender)
{
    CCLog("1");
        gameScene = GameScene::create();
    CCLog("2");
    gameScene->getLayer()->getLabel()->setString("游戲開始！");
        //場景切換特效
    CCLog("3");
    CCDirector::sharedDirector()->replaceScene(CCTransitionFadeBL::create(1, gameScene));
    //        CCDirector::sharedDirector()->replaceScene(gameScene);
    
}
void HelloWorld::ccTouchesEnded(CCSet* cSet, CCEvent *cEvent){
    
    CCTouch* cTouch = (CCTouch*)(cSet->anyObject());
    CCPoint location = cTouch->getLocation();
    CCRect rec = getRect(pSprite);
    if(rec.containsPoint(location)){
    }
    CCLog("++++++++after  x:%f, y:%f", location.x, location.y);
    // pSprite->setPosition(location);
}

CCRect HelloWorld::getRect(CCNode* pNode){
    CCRect rc;
    rc.origin = pNode->getPosition();
    rc.size = pNode->getContentSize();
    rc.origin.x -= rc.size.width*0.5;
    rc.origin.y -= rc.size.width*0.5;
    return rc;
}