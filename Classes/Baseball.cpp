//
//  Baseball.cpp
//  LittleAnd
//
//  Created by sdlu on 13-3-12.
//
//

#include "HelloWorldScene.h"
#include "Baseball.h"
#include "GameScene.h"

using namespace cocos2d;

bool BaseBall::init(){
    currentScale = 1.0f;
    winSize = getScreenSize();
    velocity = getRandomVelocity();
    getRandomPosition();
    angle= getRandomAngle();
    liveTime = 0;
    lifeTime = 10;
    sensor = true;
    screenRect = CCRectMake(0, 0, winSize.width, winSize.height);
    this->setScale(currentScale);
    getRadius();
    this->retain();
    return false;
}

cocos2d::CCPoint BaseBall::getRandomPosition(){
    
    float x = CCRANDOM_0_1()*winSize.width;
    float y = CCRANDOM_0_1()*winSize.height;
    cocos2d::CCPoint cp = ccp(x, y);
    this->setPosition(cp);
    return cp;
}

float BaseBall::getRandomVelocity(){
    
    return (CCRANDOM_0_1()+0.5)*winSize.width/600.0f;
}

float BaseBall::getRandomAngle(){
    
    return CCRANDOM_0_1()*3.1415926*2;
}

cocos2d::CCSize BaseBall::getScreenSize(){
    
    return cocos2d::CCDirector::sharedDirector()->getWinSize();
}

float BaseBall::getVelocity(){
    return velocity;
}

float BaseBall::getAngle(){
    return angle;
}

float BaseBall::getMoveX(){
    return velocity*cos(angle);
}

float BaseBall::getMoveY(){
    return velocity*sin(angle);
}

float BaseBall::getRadius(){
    radius = getContentSize().width/2*currentScale;
    return radius;
}

float BaseBall::calRadius(){
    
    return this->getContentSize().width/2;
}

CCRect BaseBall::getRect(){
    return CCRectMake(this->getPosition().x-(this->getContentSize().width/2), this->getPosition().y-(this->getContentSize().height/2), this->getContentSize().width, this->getContentSize().height);
    
}

bool BaseBall::dealBoundary(){
    //  CCLog("x%f,y%f,radius%f",getPositionX(),getPositionY(),radius);
    //    radius = getContentSize().width/2+5;
    float x = getPositionX();
    float y = getPositionY();
    if (x-radius<=0) {
        setPositionX(radius);
        angle = 3.14 - angle;
        return true;
        
    }else if (x+radius>=winSize.width) {
        setPositionX(winSize.width-radius);
        angle = 3.14 - angle;
        return true;
        
    }else if (y-radius<=0) {
        setPositionY(radius);
        angle = 3.14*2 - angle;
        return true;
    }else if (y+radius>=winSize.height) {
        setPositionY(winSize.height-radius);
        angle = 3.14*2 - angle ;
        return true;
    }
    //  CCLog("isChonghe::%d",this->getRect().intersectsRect(screenRect));
    return false;
}

void BaseBall::going(){
    
    this->CCNode::setPosition(this->getPositionX()+ velocity*cosf(angle), this->getPositionY()+velocity*sinf(angle));
}

void BaseBall::addLiveTime(float dt){
    liveTime += dt;
}

bool BaseBall::isOld(){
    return liveTime>=lifeTime;
}

void BaseBall::setGameLayer(GameLayer *_layer){
    this->_layer = _layer;
}

void BaseBall::setSensor(bool sensor){
    this->sensor = sensor;
}

bool BaseBall::isSensor(){
    return sensor;
}

void BaseBall::dealWith(Hero* hero){
    
}

void BaseBall::dealWithGuard(Hero *hero){
    
}

void BaseBall::removeFromList(){
    
}
