//
//  Enemy.cpp
//  LittleAnd
//
//  Created by sdlu on 13-3-13.
//
//

#include "Enemy.h"
using namespace cocos2d;
bool Enemy::init(){
    CCRepeatForever* a = CCRepeatForever::create(static_cast<CCSequence*>( CCSequence::create(CCScaleTo::create(0.6, 0.5),CCScaleTo::create(0.4, 1.0),NULL)));
    runAction(a);
    return false;
}

float Enemy::getRandomRadius(){
    return RANDOM_0_1()*winSize.width/24;
}

void Enemy::dealWith(Hero* hero){
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("peng.mp3");
    this->_layer->mark += 9;
    _layer->combo += 1;
    removeFromList();
}

void Enemy::dealWithGuard(Hero *hero){
    dealWith(hero);
}

void Enemy::removeFromList(){
    _layer->_enemys->removeObject(this);
}