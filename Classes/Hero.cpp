//
//  Hero.cpp
//  LittleAnd
//
//  Created by sdlu on 13-3-12.
//
//

#include "Hero.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d;
using namespace CocosDenshion;
bool Hero::init(){
    isGuarding = false;
    guardTime = 5.0f;
    vX = 0;
    vY = 0;
    flag = 3;
    this->initWithFile("hero1.png");
    CCLOG("This contentwidth:%f",getContentSize().width);
    bot = CCSprite::create("hero1.png");
    mid = CCSprite::create("hero2.png");
    top = CCSprite::create("hero3.png");
    guard = CCSprite::create("guard_on.png");
    int n = getContentSize().width/2;
    bot->setPosition(ccp(n,n));
    mid->setPosition(ccp(n,n));
    top->setPosition(ccp(n,n));
    guard->setPosition(ccp(n,n));
    guard->setScale(0);
    bot->runAction(CCSequence::create(CCRepeatForever::create(CCRotateBy::create(3, 360)),NULL));
    std::cout<<getRadius()<<std::endl;
    cocos2d::CCSize winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
    // Get screen size and set the position of hero.
    this->cocos2d::CCNode::setPosition(ccp(winSize.width/2,winSize.height/2));
    setScale(0.9);
    radius = getRadius();
    addChild(bot);
    addChild(mid);
    addChild(top);
    addChild(guard);
    return true;
}

//TODO getRadius from saved files
float Hero::getRadius(){
    return getContentSize().width/2;
}

bool Hero::setRadius(float r){
    radius = r;
    return true;
}

bool Hero::setLifeTime(float t){
    lifeTime = t;
}

void Hero::changeTop(){
    if (flag == 3) {
        flag =4;
        top->initWithFile("hero4.png");
    } else if(flag == 4){
        flag = 3;
        top->initWithFile("hero3.png");
    }
    change();
}

void Hero::changeTopTo3(){
    top->initWithFile("hero3.png");
}

void Hero::change(){
    
}

void Hero::displayGuard(){
    guard->runAction(CCSequence::create(CCScaleTo::create(0.2, 1.1),NULL));
    
}

void Hero::cancelGuard(){
    guard->runAction(CCSequence::create(CCScaleTo::create(0.2, 0.1),NULL));
    
}