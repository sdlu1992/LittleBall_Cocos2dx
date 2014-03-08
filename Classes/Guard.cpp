//
//  Guard.cpp
//  LittleAnd
//
//  Created by sdlu on 13-3-26.
//
//

#include "Enemy.h"

using namespace cocos2d;

bool Guard::init(){
    setScale(1.3);
    return false;
}

float Guard::amendVelocity(){
    velocity = 0;
    return velocity;
}

float Guard::getRandomRadius(){
    
    return RANDOM_0_1()*winSize.width/24;
    
}

void Guard::dealWith(Hero* hero){
    hero->isGuarding = true;
    removeFromList();
}

void Guard::dealWithGuard(Hero *hero){
    hero->guardTime = 5.0f;
    removeFromList();
}

void Guard::removeFromList(){
    _layer->_guards->removeObject(this);
}