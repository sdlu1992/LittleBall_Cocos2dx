//
//  Bomb.cpp
//  LittleAnd
//
//  Created by sdlu on 13-3-27.
//
//

#include "Enemy.h"

using namespace cocos2d;

bool Bomb::init(){
    amendVelocity();
    return false;
}

float Bomb::getRandomRadius(){
    return RANDOM_0_1()*winSize.width/24;
}

void Bomb::dealWith(Hero* hero){
    //TODO刪除全部
    CCObject* aa = NULL;
    removeFromList();
    _layer->mark *= 0.7;
    //计划是炸弹要把所有的球消掉，但是出问题了
//    CCARRAY_FOREACH(_layer->_enemys, aa){
//        BaseBall* b = dynamic_cast<BaseBall*>(aa);
//        _layer->toDestory->addObject(b);
//        _layer->_enemys->removeObject(b);
//        _layer->_elements->removeObject(b);
//        
//    }
    _layer->combo = 0;
}

void Bomb::dealWithGuard(Hero *hero){
    _layer->combo += 1;
    _layer->mark += 9;
    removeFromList();
    
}

float Bomb::amendVelocity(){
    velocity /= 5;
    return velocity;
}

void Bomb::removeFromList(){
    _layer->_bombs->removeObject(this);
}