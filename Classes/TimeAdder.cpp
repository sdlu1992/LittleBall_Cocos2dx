//
//  TimeAdder.cpp
//  LittleAnd
//
//  Created by sdlu on 13-3-29.
//
//

#include "Enemy.h"
#include "string.h"
#include "iostream"

bool TimeAdder::init(){
    time = getRandomTime();
    return false;
}

void TimeAdder::setTime(int t){
    time = t;
}
float TimeAdder::getRandomTime(){
    return CCRANDOM_0_1()*5+1;
}

float TimeAdder::amendVelocity(){
    velocity /= 2;
    return velocity;
}

float TimeAdder::getRandomRadius(){
    return RANDOM_0_1()*winSize.width/24;
    
}

void TimeAdder::dealWith(Hero* hero){
    _layer->totalTime += time;
    removeFromList();
}

void TimeAdder::dealWithGuard(Hero *hero){
    dealWith(hero);
}

void TimeAdder::removeFromList(){
    _layer->_time_adders->removeObject(this);
}