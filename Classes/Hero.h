//
//  Hero.h
//  LittleAnd
//
//  Created by sdlu on 13-3-12.
//
//

#ifndef __LittleAnd__Hero__
#define __LittleAnd__Hero__

#include <iostream>
#include "cocos2d.h"

class Hero : public cocos2d::CCSprite{
public:
    virtual bool init();
    float radius;
    CREATE_FUNC(Hero);
    float getRadius();
    bool setRadius(float r);
    bool isGuarding;
    float guardTime;
    float lifeTime;
    float vX,vY;
    bool setLifeTime(float t);
    void changeTop();
    void changeTopTo3();
    int flag;
    void change();
    void displayGuard();
    void cancelGuard();
    CCSprite* guard;
    cocos2d::CCSprite* bot;
    cocos2d::CCSprite* mid;
    cocos2d::CCSprite* top;
};
#endif /* defined(__LittleAnd__Hero__) */
