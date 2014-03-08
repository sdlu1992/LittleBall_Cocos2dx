//
//  Enemy.h
//  LittleAnd
//
//  Created by sdlu on 13-3-13.
//
//

#ifndef __LittleAnd__Enemy__
#define __LittleAnd__Enemy__

#include <iostream>
#include "cocos2d.h"
#include "Baseball.h"
#include "GameScene.h"
#define CREATE_WITH_TEXTURE(__TYPE__)\
static __TYPE__* createWithTexture(cocos2d::CCTexture2D *pTexture)\
{\
    __TYPE__ *pRet = new __TYPE__();\
    if (pRet && pRet->initTexture(pTexture))\
    {\
        pRet->autorelease();\
        return pRet;\
    }\
    else\
    {\
        delete pRet;\
        pRet = NULL;\
        return NULL;\
    }\
}

#define INIT_TEXTURE(__TYPE__)\
bool initTexture(cocos2d::CCTexture2D *pTexture){\
    BaseBall::init();\
    this->initWithTexture(pTexture);\
    this->init();\
    type = __TYPE__;\
    return true;\
}

#define CREATE_WITH_FRAME_NAME(__TYPE__)\
static __TYPE__* createWithSpriteFrameName(const char *pszSpriteFrameName)\
{\
__TYPE__ *pRet = new __TYPE__();\
if (pRet && pRet->initWithSpriteFrameName(pszSpriteFrameName))\
{\
pRet->autorelease();\
return pRet;\
}\
else\
{\
delete pRet;\
pRet = NULL;\
return NULL;\
}\
}

#define INIT_FRAME_NAME(__TYPE__)\
bool initWithSpriteFrameName(const char *pszSpriteFrameName){\
    this->initWithSpriteFrameName(pszSpriteFrameName);\
    BaseBall::init();\
    this->init();\
    type = __TYPE__;\
    return true;\
}

using namespace cocos2d;

class Enemy : public BaseBall{
public:
    
    virtual bool init();
//    bool initTexture(cocos2d::CCTexture2D *pTexture);
    cocos2d::CCPoint mPosition;
//    static Enemy* createWithTexture(cocos2d::CCTexture2D* pTexture);
    float getRandomVelocity();
    float getRandomRadius();
    void dealWith(Hero* hero);
    void dealWithGuard(Hero* hero);
    void removeFromList();
    CREATE_FUNC(Enemy);
    CREATE_WITH_TEXTURE(Enemy);
    INIT_TEXTURE(TYPE_ENEMY);
};

class Guard : public BaseBall{
public:
    virtual bool init();
    cocos2d::CCPoint mPosition;
    float amendVelocity();
    float getRandomRadius();
    void dealWith(Hero* hero);
    void dealWithGuard(Hero* hero);
    void removeFromList();
    CREATE_FUNC(Guard);
    CREATE_WITH_TEXTURE(Guard);
    INIT_TEXTURE(TYPE_GUARD);
};

class Bomb : public BaseBall{
public:
    virtual bool init();
    cocos2d::CCPoint mPosition;
    float amendVelocity();
    float getRandomRadius();
    void dealWith(Hero* hero);
    void dealWithGuard(Hero* hero);
    void removeFromList();
    CREATE_FUNC(Bomb);
    CREATE_WITH_TEXTURE(Bomb);
    CREATE_WITH_FRAME_NAME(Bomb);
    INIT_TEXTURE(TYPE_BOMB);
    INIT_FRAME_NAME(TYPE_BOMB);
};

class Speed : public BaseBall{
public:
    virtual bool init();
    cocos2d::CCPoint mPosition;
    float amendVelocity();
    float getRandomRadius();
    void dealWith(Hero* hero);
    void dealWithGuard(Hero* hero);
    void removeFromList();
    CREATE_FUNC(Speed);
    CREATE_WITH_TEXTURE(Speed);
    INIT_TEXTURE(TYPE_SPEED);
};

class TimeAdder: public BaseBall{
public:
    virtual bool init();
    cocos2d::CCPoint mPosition;
    float amendVelocity();
    float getRandomRadius();
    void dealWith(Hero* hero);
    void dealWithGuard(Hero* hero);
    float getRandomTime();
    void setTime(int t);
    void removeFromList();
    CREATE_FUNC(TimeAdder);
    CREATE_WITH_TEXTURE(TimeAdder);
    INIT_TEXTURE(TYPE_TIME_ADDER);
};

class Copy : public BaseBall{
public:
    
    virtual bool init();
    //    bool initTexture(cocos2d::CCTexture2D *pTexture);
    cocos2d::CCPoint mPosition;
    //    static Enemy* createWithTexture(cocos2d::CCTexture2D* pTexture);
    float getRandomVelocity();
    float getRandomRadius();
    float amendVelocity();
    void dealWith(Hero* hero);
    void dealWithGuard(Hero* hero);
    void removeFromList();
    CREATE_FUNC(Copy);
    CREATE_WITH_TEXTURE(Copy);
    INIT_TEXTURE(TYPE_COPY);
};


class EffectAid: public BaseBall{
public:
    virtual bool init();
    cocos2d::CCPoint mPosition;
    cocos2d::CCParticleSystem* galaxy;
    void dealWith(Hero* hero);
    void dealWithGuard(Hero* hero);
    void moveTowards(float duration,cocos2d::CCPoint destination);
    void removeFromList();
    CREATE_FUNC(EffectAid);
};


#endif /* defined(__LittleAnd__Enemy__) */
