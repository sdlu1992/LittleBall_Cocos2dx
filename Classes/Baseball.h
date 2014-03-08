//
//  Baseball.h
//  LittleAnd
//
//  Created by sdlu on 13-3-12.
//
//

#ifndef __LittleAnd__Baseball__
#define __LittleAnd__Baseball__

#include <iostream>
#include "cocos2d.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
class GameLayer;
#define RANDOM_0_1() ((float)rand()/RAND_MAX)

#define TYPE_ENEMY 1
#define TYPE_GUARD 2
#define TYPE_BOMB 3
#define TYPE_SPEED 4
#define TYPE_TIME_ADDER 5
#define TYPE_COPY 6
#define TYPE_EFFECT_AID 99

class BaseBallBatchNode : public cocos2d::CCSpriteBatchNode{
public:
    
};

class BaseBall : public cocos2d::CCSprite{
public:
    cocos2d::CCSize winSize;
    cocos2d::CCPoint getRandomPosition();
    float getRandomVelocity();
    float getRandomAngle();
    float getVelocity();
    float getAngle();
    float getMoveX();
    float getMoveY();
    bool dealBoundary();
    float getRadius();
    cocos2d::CCRect getRect();
    cocos2d::CCSize getScreenSize();
    //virtual ~BaseBall();
    virtual bool init();
    CREATE_FUNC(BaseBall);
    void going();
    void addLiveTime(float dt);
    bool isOld();
    int type;
    std::string fileName;
    void setGameLayer(cocos2d::CCLayer* _layer );
    virtual void dealWith(Hero* hero);
    virtual void dealWithGuard(Hero* hero);
    void setGameLayer(GameLayer* _layer);
    GameLayer* _layer;
    virtual void removeFromList();
    bool isSensor();
    float currentScale ;
    void setSensor(bool sensor);
    int time;
protected:
    float velocity;
    float liveTime ;
    float lifeTime ;
    //是否碰撞
    bool sensor;
private:
    float radius;
    float angle;
    cocos2d::CCRect rect;
    cocos2d::CCRect screenRect;
    float calRadius();
    
    
};

#endif /* defined(__LittleAnd__Baseball__) */
