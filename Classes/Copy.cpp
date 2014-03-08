//
//  Copy.cpp
//  LittleAnd
//
//  Created by sdlu on 13-5-31.
//
//

#include "Enemy.h"

bool Copy::init(){
    amendVelocity();
    return false;
}

float Copy::amendVelocity(){
    velocity *= 2;
    return velocity;
}

float Copy::getRandomRadius(){
    return RANDOM_0_1()*winSize.width/24;
    
}

//多一個英雄出來
void Copy::dealWith(Hero* hero){
    _layer->addHero(this->getPosition(),5);
    removeFromList();
}

void Copy::dealWithGuard(Hero *hero){
    dealWith(hero);
}

void Copy::removeFromList(){
    _layer->_copies->removeObject(this);
}