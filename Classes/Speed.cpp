//
//  Speed.cpp
//  LittleAnd
//
//  Created by sdlu on 13-3-29.
//
//

#include "Enemy.h"

bool Speed::init(){
    amendVelocity();
    return false;
}

float Speed::amendVelocity(){
    velocity /= 2;
    return velocity;
}

float Speed::getRandomRadius(){
    return RANDOM_0_1()*winSize.width/24;
    
}

void Speed::dealWith(Hero* hero){
    hero->vX *=10;
    hero->vY *=10;
    removeFromList();
}

void Speed::dealWithGuard(Hero *hero){
    dealWith(hero);
}

void Speed::removeFromList(){
    _layer->_speeds->removeObject(this);
}