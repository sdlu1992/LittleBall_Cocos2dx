//
//  GameScene.cpp
//  TTT
//
//  Created by sdlu on 13-3-12.
//
//

#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "Baseball.h"

using namespace cocos2d;
using namespace CocosDenshion;
bool GameScene::init(){
    if(CCScene::init()){
        this->_layer = GameLayer::create();
        this->_layer->retain();
        this->adaChild(_layer);
        return true;
    } else{
        return false;
    }
}

GameScene::~GameScene(){
    if (_layer) {
        _layer->release();
        _layer = NULL;
    }
}


bool GameLayer::init(){
    CCLog("11");
    if ( CCLayerColor::init() ) {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("backmusic.mp3", true);
        srand((unsigned int)time(NULL));
        this->initWithColor(ccc4(100, 100, 100, 100));
    CCLog("11");
        
        initData();
    CCLog("12");
        CCSprite* backSprite = CCSprite::create("background.png");
        backSprite->setPosition(ccp(winSize.width/2,winSize.height/2));
        this->addChild(backSprite);
        screenRect = CCRectMake(0, 0, winSize.width, winSize.height);
        setAccelerometerEnabled(true);
        setTouchEnabled(true);
        setBeginLabel();
        
        setMarkLabel();
        setRestTimeLabel();
        setGuardTimeLabel();
        setComboLabel();
        addHero(ccp(winSize.width/2, winSize.height/2),-2);
        this->schedule(schedule_selector(GameLayer::addElements), 0.7 );
        this->schedule(schedule_selector(GameLayer::updateGame));
        this->schedule(schedule_selector(GameLayer::updateMark),0.05);
        this->schedule(schedule_selector(GameLayer::updateTime),0.05);
		return true;
	} else {
		return false;
	}
}

GameLayer::~GameLayer()
{
	if (_label)
	{
		_label->release();
		_label = NULL;
	}
    if(_enemys){
        _enemys->release();
        _enemys = NULL;
    }
    //  if(	)
}

void GameLayer::initData(){
    
    winSize = CCDirector::sharedDirector()->getWinSize();
    //字体的大小是和屏幕适配相关的，以下的scale即针对不同分辨率做的比率放大
    labelWidthScale = winSize.width/960.0f;
    labelHeightScale = winSize.height/640.0f;
    screenWidthScale  = winSize.width/960.0f;
    screenHeightScale = winSize.height/640.0f;
//    labelWidthScale = 1;
//    labelHeightScale = 1;
//    screenWidthScale  = 1;
//    screenHeightScale = 1;
    markLabelPoint = ccp(110*screenWidthScale,winSize.height-80*screenHeightScale);
    restTimeLabelPoint = ccp(winSize.width-200*screenWidthScale,winSize.height-60*screenHeightScale);
    guardTimeLabelPoint1 = ccp(winSize.width+10,winSize.height-100*screenHeightScale);
    guardTimeLabelPoint2 = ccp(winSize.width-200*screenWidthScale,winSize.height-150*screenHeightScale);
    comboLabelPoint = ccp(40*screenWidthScale,winSize.height-140*screenHeightScale);
    NUMBER_WHITE = "number_white.png";
    NUMBER_ORANGE= "number_orange.png";
    NUMBER_RED = "number_red.png";
    mark = 0,temporaryMark = mark;
    CCLog("123");
    totalTime = 60;
    gameTime = 0;
    combo = 0;
    restTime = totalTime-gameTime;
    toDestory = new CCArray;
    _enemys = new CCArray;
    _elements = new CCArray;
    _guards = new CCArray;
    _bombs = new CCArray;
    _heros = new CCArray;
    _speeds = new CCArray;
    _time_adders = new CCArray;
    _copies = new CCArray;
    CCLog("124");
    ADD_BATCH_NODE(enemyBatchNode[0], "enemy1.png");
    ADD_BATCH_NODE(enemyBatchNode[1], "enemy2.png");
    ADD_BATCH_NODE(enemyBatchNode[2], "enemy3.png");
    CCLog("125");
    for (int i = 1; i<7; i++) {
        char name[256];
        char *n = name;
        sprintf(n, "timeadder_%d.png",i);
        ADD_BATCH_NODE(timeAdderBatchNode[i], n);
    }
    CCLog("126");
    ADD_BATCH_NODE(bombBatchNode, "bomb.png")
    ADD_BATCH_NODE(guardBatchNode, "guard.png");
    ADD_BATCH_NODE(speedBatchNode, "speed.png");
    ADD_BATCH_NODE(copyBatchNode, "copy.png");
    CCSprite* scoreName = CCSprite::create("score.png");
    scoreName->setPosition(ccp(50*screenWidthScale,winSize.height-60*screenHeightScale));
    addChild(scoreName,1);
}

void GameLayer::onPause(CCObject* pSender){
    CCDirector::sharedDirector()->pause();
}

void GameLayer::onResume(CCObject* pSender){
    CCDirector::sharedDirector()->resume();
}

void GameLayer::setBeginLabel(){
    this->_label = CCLabelTTF::create("","Artial", 32);
    _label->retain();
    _label->setColor( ccc3(255, 250, 250) );
    _label->setPosition( ccp(winSize.width/2, 0) );
    this->addChild(_label);
    CCMoveTo* cm = CCMoveTo::create(1, ccp(winSize.width/2, winSize.height+20));
    CCCallFunc* cc = CCCallFunc::create(this, callfunc_selector(GameLayer::gameDone));
    CCAction* cq = CCSequence::create(cm,cc,NULL);
    _label->runAction(cq);
}

void GameLayer::setMarkLabel(){
    markLabel = new CCLabelAtlas();
    markLabel->initWithString("0", NUMBER_ORANGE.c_str(), 35*labelWidthScale, 42*labelHeightScale, '0');
    markLabel->setPosition(markLabelPoint);
    this->addChild(markLabel);
}

void GameLayer::setRestTimeLabel(){
    restTimeLabel = new CCLabelAtlas();
    restTimeLabel->initWithString("60", NUMBER_WHITE.c_str(), 38*labelWidthScale, 45*labelHeightScale, '0');
    restTimeLabel->setPosition(CCPointZero);
    CCMenuItemLabel* pItemLabel = CCMenuItemLabel::create(restTimeLabel, this, menu_selector(GameLayer::restTimeCallback));
    pItemLabel->setPosition(restTimeLabelPoint);
    CCMenu* menu = CCMenu::create(pItemLabel,NULL);
    menu->setPosition(CCPointZero);
    this->addChild(menu);
}

void GameLayer::restTimeCallback(CCObject* pSender){
    CCLog("restTimeCallback");
    onPause(pSender);
    resumeBT = CCSprite::create("Icon-72.png");
    resumeBT->setPosition(ccp(winSize.width/2, winSize.height/2));
    this->addChild(resumeBT,2);
    CCMenuItemFont* item = CCMenuItemFont::create("resume", this, menu_selector(GameLayer::pauseItemCallback));
    CCMenu* menu = CCMenu::create(item,NULL);
    //    menu->setPosition(ccp(winSize.width/2, winSize.height/2));
    menu->setPosition(CCPointZero);
    resumeBT->addChild(menu);
}

void GameLayer::pauseItemCallback(cocos2d::CCObject *pSender){
    onResume(pSender);
    this->removeChild(resumeBT, true);
}

void GameLayer::setGuardTimeLabel(){
    guardLabel = new CCLabelAtlas();
    guardLabel->initWithString("5", NUMBER_WHITE.c_str(), 38*labelWidthScale, 43*labelHeightScale, '0');
    guardLabel->setPosition(guardTimeLabelPoint1);
    this->addChild(guardLabel);
}

void GameLayer::setComboLabel(){
    comboLabel = new CCLabelAtlas();
    comboLabel->initWithString("0", NUMBER_ORANGE.c_str(), 35*labelWidthScale, 40*labelHeightScale, '0');
    comboLabel->setPosition(comboLabelPoint);
    this->addChild(comboLabel);
    comboLabel->setVisible(false);
}

void GameLayer::setComboLabelAnimation(){
    comboLabel->setVisible(combo>=5);
    if (comboLabel->isVisible()) {
        char a[5];
        sprintf(a, "%d",combo);
        comboLabel->setString(a);
        CCMoveTo* move1 = CCMoveTo::create(0.05, ccp(comboLabel->getPositionX()-comboLabel->getContentSize().width/4,comboLabel->getPositionY()-comboLabel->getContentSize().height/4));
        CCMoveTo* move2 = CCMoveTo::create(0.1, comboLabelPoint);
        CCScaleTo* big = CCScaleTo::create(0.05, 1.5);
        CCScaleTo* small = CCScaleTo::create(0.1, 1);
        comboLabel->runAction(CCSequence::create(move1,move2,NULL));
        
        comboLabel->runAction(CCSequence::create(big,small,NULL));
    }
    
}

int GameLayer::addHero(CCPoint p,float t){
    Hero* hero = Hero::create();
    hero->setPosition(p);
    hero->setLifeTime(t);
    this->addChild(hero);
    _heros->addObject(hero);
    return _heros->count();
}

void GameLayer::addElements(){
    BaseBall* e = NULL;
    //大部分element同時只能存在一個
    while (true) {
        if (_elements->count()>20) {
            continue;
        }
        float num = CCRANDOM_0_1();
        if (num<PRO_GUARD) {
            if (_guards->count()>0) {
                continue;
            }
            e = Guard::createWithTexture(guardBatchNode->getTexture());
            _guards->addObject(e);
        } else if(num<PRO_BOMB+PRO_GUARD){
            if (_bombs->count()>0) {
                CCLog("Bomb count%d",_bombs->count());
                continue;
            }
            e = Bomb::createWithTexture(bombBatchNode->getTexture());
            _bombs->addObject(e);
            
        } else if(num<PRO_SPEED+PRO_GUARD+PRO_BOMB){
            if (_speeds->count()>0) {
                continue;
            }
            e = Speed::createWithTexture(speedBatchNode->getTexture());
            _speeds->addObject(e);
        } else if(num<PRO_TIME_ADDER+PRO_SPEED+PRO_GUARD+PRO_BOMB){
            if (_time_adders->count()>0) {
                continue;
            }
            int time = RANDOM_0_1()*5+1;
            e = TimeAdder::createWithTexture(timeAdderBatchNode[time]->getTexture());
            e->time = time;
//            e = TimeAdder::create();
            _time_adders->addObject(e);
        } else if (num<PRO_COPY+PRO_TIME_ADDER+PRO_SPEED+PRO_GUARD+PRO_BOMB){
            if (_copies->count()>0||_heros->count()>1) {
                continue;
            }
            e = Copy::createWithTexture(copyBatchNode->getTexture());
            _copies->addObject(e);
        } else {
            e = Enemy::createWithTexture(enemyBatchNode[(int)(RANDOM_0_1()*3)]->getTexture());
            _enemys->addObject(e);
        }
        e->setGameLayer(this);
        this->addChild(e);
        _elements->addObject(e);
        break;
        
    }
    
}

void GameLayer::gameDone()
{
	//CCDirector::sharedDirector()->replaceScene( HelloWorld::scene() );
    _label->release();
    _label = NULL;
}

void GameLayer::didAccelerate(cocos2d::CCAcceleration *pValue){
    
    float deceleration = 0.8f;
    float sensitivity = 10.0f;
    bool isBoundary = false;
    float maxVelocity = 100;
    CCObject* hh = NULL;
    int i = 0;
    CCARRAY_FOREACH(_heros, hh){
        Hero* hero = dynamic_cast<Hero*>(hh);
        float radius = hero->getRadius();
        
        hero->vX = hero->vX*deceleration + pValue->x*sensitivity*(1+i);
        hero->vY = hero->vY*deceleration + pValue->y*sensitivity*(1+i);
        //生成的球和原来的球运动方向相反
        hero->vX = i?-hero->vX:hero->vX;
        hero->vY = i?-hero->vY:hero->vY;
        float x ,y;
        x = hero->vX + hero->getPositionX();
        y = hero->vY + hero->getPositionY();
        
        //hero must in screen
        if (x+radius>winSize.width) {
            x = winSize.width-radius;
            hero->vX = -hero->vX+1;
            isBoundary = true;
        }
        if(x-radius<0){
            x = radius;
            hero->vX = -hero->vX+1;
            isBoundary = true;
        }
        if(y+radius>winSize.height){
            y = winSize.height-radius;
            hero->vY = -hero->vY+1;
            isBoundary = true;
            
        }
        if(y-radius<0){
            y = radius;
            hero->vY = -hero->vY+1;
            isBoundary = true;
        }
//        if (isBoundary) {
//            setAccelerometerEnabled(false);
//            this->schedule(schedule_selector(GameLayer::setAccTrue),0.1f);
//            isBoundary = false;
//        }
        hero->setPosition(ccp(x,y));
        i++;
    }
    
}

void GameLayer::setAccTrue(float dt){
    setAccelerometerEnabled(true);
}

void GameLayer::spriteMoveFinished(cocos2d::CCNode *sender){
    CCSprite* enemy = (CCSprite*)sender;
    enemy->runAction(CCSequence::create(CCScaleTo::create(0.5, 0),CCCallFuncN::create(this, callfuncN_selector(GameLayer::removeBaseBall)),NULL));
}

void GameLayer::removeBaseBall(cocos2d::CCNode *enemy){
    this->removeChild(enemy, true);
    _elements->removeObject(enemy);
    
}

/**
 進行碰撞檢測之類
 */
void GameLayer::updateGame(float dt){
    CCObject* en = NULL;
    CCObject* he = NULL;
    char aa[7] ;
    char* a = aa;
//    CCLog("dt:%f",dt);
    CCARRAY_FOREACH(_heros, he){
        Hero* hh = dynamic_cast<Hero*>(he);
        if (hh->isGuarding) {
            if (hh->guardTime -5.0f <= 0.1 ) {
                guardLabel->runAction(CCSequence::create(CCMoveTo::create(0.1f,guardTimeLabelPoint2 ),NULL));
            }
            if (hh->guard->getScale()==0) {
                hh->displayGuard();
            }
            hh->guardTime -= dt;
            sprintf(a, "%.2f",hh->guardTime);
            guardLabel->setString(a);
            if(hh->guardTime<=0){
                hh->isGuarding = false;
                hh->guardTime = 5.0f;
                hh->cancelGuard();
                guardLabel->runAction(CCSequence::create(CCMoveTo::create(0.1f, guardTimeLabelPoint1),NULL));
            }
        }
            hh->lifeTime -= dt;
        if (hh->lifeTime>-1&&hh->lifeTime<=0&&_heros->count()>1) {
                _heros->removeObject(hh);
                this->removeChild(hh, true);
                break;
            }
        
        CCARRAY_FOREACH(_elements, en){
            BaseBall* bb = dynamic_cast<BaseBall*>(en);
            //控制小球運動軌跡
            bb->going();
            bb->addLiveTime(dt);
            
            if (bb->isOld()) {
                //delete
                bb->removeFromList();
                bb->runAction(CCSequence::create(CCScaleTo::create(0.5, 0),CCCallFuncN::create(this, callfuncN_selector(GameLayer::removeBaseBall)),NULL));
            }
            if(bb->dealBoundary()){
                //碰到邊界了
            }
            if (bb->isSensor()) {
                //检测主角是否和敌人碰撞
                if (hh->getRadius()+bb->getRadius()>=ccpDistance(hh->getPosition(), bb->getPosition())) {
                    bb->setSensor(false);
                    hh->vX *= 0.7;
                    hh->vY *= 0.7;
                    if (bb->type == TYPE_TIME_ADDER) {
                        EffectAid* ef = EffectAid::create();
                        ef->setPosition(hh->getPosition());
                        ef->moveTowards(0.2f, ccp(winSize.width-40,winSize.height-40));
                        _elements->addObject(ef);
                        addChild(ef);
                    }
                    if (hh->isGuarding) {
                        bb->dealWithGuard(hh);
                    } else {
                        bb->dealWith(hh);
                    }
                    _elements->removeObject(bb);
                    toDestory->addObject(bb);
                    //連擊數大於等於5時才顯示
                    setComboLabelAnimation();
                }
            }
        }
        
    }
    
    CCARRAY_FOREACH(toDestory, en){
        BaseBall* bb = dynamic_cast<BaseBall*>(en);
        bb->runAction(CCSequence::create(CCScaleTo::create(0.2, 0.5),CCCallFuncN::create(this, callfuncN_selector(GameLayer::removeBaseBall)),NULL));
        // removeBaseBall(bb);
        toDestory->removeObject(bb);
        bb->release();
    }
}

//更新分数，当分数增长速度较低时，分数变化速度较慢，分数增长速度很快时，增长速度很快。
void GameLayer::updateMark(float dt){
    char b[10];
    char* a = b;
    if (temporaryMark!=mark) {
        
        if(mark-temporaryMark>10){
            temporaryMark += (mark -temporaryMark)/10;
        } else if(temporaryMark<mark){
            temporaryMark++;
        } else if(temporaryMark-mark>30){
            temporaryMark += (mark - temporaryMark)/30;
        } else if(temporaryMark>mark){
            temporaryMark--;
        }
        sprintf(a, "%d",temporaryMark);
        markLabel->setString(a);
        
    }
}

void GameLayer::updateTime(float dt){
    char b[10];
    char* a = b;
    gameTime += dt;
    restTime = totalTime - gameTime;
    if (restTime<=0) {
        restTime = 0;
        //game over
        return;
    }
    if (restTime<=10&&restTimeLabel->getScale()==1.0f) {
        restTimeLabel->initWithString("60", NUMBER_RED.c_str(), 38*labelWidthScale, 43*labelHeightScale, '0');
        restTimeLabel->setScale(1.2f);
    } else if(restTime>10&&restTimeLabel->getScale() == 1.2f){
        restTimeLabel->initWithString("60", NUMBER_WHITE.c_str(), 38*labelWidthScale, 43*labelHeightScale, '0');
        restTimeLabel->setScale(1.0f);
    }
    CCObject* h = NULL;
    if (restTime<=10) {
        CCARRAY_FOREACH(_heros, h){
            Hero* hh = dynamic_cast<Hero*>(h);
            hh->changeTop();
        }
    } else{
        CCARRAY_FOREACH(_heros, h){
            Hero* hh = dynamic_cast<Hero*>(h);
            hh->changeTopTo3();
        }
    }
    int n = restTime;
    int m = (int)((restTime-n)*100);
    sprintf(a, "%d:%d",n,m);
    restTimeLabel->setString(a);
}