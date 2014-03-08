//
//  EffectAid.cpp
//  LittleAnd
//
//  Created by sdlu on 13-3-30.
//
//

#include "Enemy.h"
//還有問題，即提前消失的問題
bool EffectAid::init(){
    
    BaseBall::init();
    fileName = "fire.png";
    velocity = 0;
    lifeTime = 0.5f;
    sensor = false;
    type = TYPE_EFFECT_AID;
    this->initWithFile(fileName.c_str());
    galaxy = CCParticleGalaxy::create();
    galaxy->retain();
   // galaxy->autorelease();
    this->addChild(galaxy);
    galaxy->setTexture(CCTextureCache::sharedTextureCache()->addImage("fire.png"));
    galaxy->setPosition(ccp(getContentSize().width/2,getContentSize().height/2));

    return true;
    
}

void EffectAid::dealWith(Hero* hero){
    
}

void EffectAid::dealWithGuard(Hero *hero){
    dealWith(hero);
}

void EffectAid::moveTowards(float duration,cocos2d::CCPoint destination){
    this->runAction(CCMoveTo::create(duration, destination));
}

void EffectAid::removeFromList(){

}
