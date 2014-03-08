//  GameScene.h
//  TTT
//
//  Created by sdlu on 13-3-12.
//
//

#ifndef __TTT__GameScene__
#define __TTT__GameScene__

#include <iostream>
#include "cocos2d.h"
#include "Hero.h"
#include "Enemy.h"
#include "string.h"
class EffectAid;
#define PRO_ENEMY 0.9
#define PRO_GUARD 0.05
#define PRO_BOMB 0.05
#define PRO_SPEED 0.05
#define PRO_TIME_ADDER 0.05
#define PRO_COPY 0.5
#define SaveStringToXML CCUserDefault::sharedUserDefault()->setStringForKey
#define SaveIntegerToXML CCUserDefault::sharedUserDefault()->setIntegerForKey
#define SaveFloatToXML CCUserDefault::sharedUserDefault()->setFloatForKey
#define SaveBooleanToXML CCUserDefault::sharedUserDefault()->setBoolForKey
#define LoadStringFromXML CCUserDefault::sharedUserDefault()->getStringForKey
#define LoadIntegerFromXML CCUserDefault::sharedUserDefault()->getIntegerForKey
#define LoadBooleanFromXML CCUserDefault::sharedUserDefault()->getBoolForKey
#define LoadFloatFromXML CCUserDefault::sharedUserDefault()->getFloatForKey

#define ADD_BATCH_NODE(__NODE__,__FILE__)\
__NODE__ = CCSpriteBatchNode::create(__FILE__, 29);\
__NODE__->setPosition(CCPointZero);\
this->addChild(__NODE__);

using namespace std;
class GameLayer : public cocos2d::CCLayerColor{
public:
    string NUMBER_WHITE ;
    string NUMBER_ORANGE;
    string NUMBER_RED;
    GameLayer():_label(NULL) {};
    ~GameLayer();
    bool init();
    void initData();
    //暫停時的button
    cocos2d::CCSprite* resumeBT;
    void pauseItemCallback(CCObject* pSender);
    //暫停與恢復
    void onPause(CCObject* pSender);
    void onResume(CCObject* pSender);
    //Hero* hero ;
    int temporaryMark,mark;
    //屏幕的宽高
    cocos2d::CCSize winSize;
    //真实屏幕的宽高和480X800的比例
    float screenWidthScale,screenHeightScale;
    //連擊數
    int combo;
    void gameDone();
    //增加主角
    int addHero(cocos2d::CCPoint p,float t);
    //增加敌人
    void addElements();
    //元素的数组
    cocos2d::CCArray* _elements;
    //敌人的数组
    cocos2d::CCArray* _enemys;
    //保护罩数组
    cocos2d::CCArray* _guards;
    //炸弹的数组
    cocos2d::CCArray* _bombs;
    //Speed的數組
    cocos2d::CCArray* _speeds;
    //TimeAdder的数组
    cocos2d::CCArray* _time_adders;
    //太極球的數組
    cocos2d::CCArray* _copies;
    //猪脚的数组
    cocos2d::CCArray* _heros;
    static cocos2d::CCScene *scene();
    //重力感应，控制猪脚的唯位移
    void didAccelerate(cocos2d::CCAcceleration *pAccelerationValue);
    
    void spriteMoveFinished(cocos2d::CCNode* sender);
    void removeBaseBall(cocos2d::CCNode* enemy);
    //对游戏进行一些判断
    void updateGame(float dt);
    //更新分数
    void updateMark(float dt);
    //更新游戏时间和各元素的时间
    void updateTime(float dt);
    cocos2d::CCRect screenRect;

    CREATE_FUNC(GameLayer);
    CC_SYNTHESIZE_READONLY(cocos2d::CCLabelTTF*, _label, Label);
    //关于字体的，真实屏幕高度与800的比例
    float labelWidthScale,labelHeightScale;
    //分数的label
    cocos2d::CCLabelAtlas *markLabel;
    //游戏时间，剩余时间
    float totalTime ,gameTime,restTime;
    //剩余时间的label
    cocos2d::CCLabelAtlas *restTimeLabel;
    //保护罩剩余时间的label
    cocos2d::CCLabelAtlas *guardLabel;
    //連擊數的label
    cocos2d::CCLabelAtlas *comboLabel;
    //以下是各個label的座標
    cocos2d::CCPoint markLabelPoint;
    cocos2d::CCPoint restTimeLabelPoint;
    cocos2d::CCPoint guardTimeLabelPoint1;
    cocos2d::CCPoint guardTimeLabelPoint2;
    cocos2d::CCPoint comboLabelPoint;
    //游戏开启时动画
    void setBeginLabel();
    //分数的label
    void setMarkLabel();
    //剩余时间的label
    void setRestTimeLabel();
    void restTimeCallback(CCObject* pSender);
    //保护罩剩余时间的label
    void setGuardTimeLabel();
    //連擊數的label
    void setComboLabel();
    //連擊數的label動畫
    void setComboLabelAnimation();
    cocos2d::CCArray* toDestory;
    void setAccTrue(float dt);
    cocos2d::CCSpriteBatchNode* enemyBatchNode[3];
    cocos2d::CCSpriteBatchNode* bombBatchNode;
    cocos2d::CCSpriteBatchNode* guardBatchNode;
    cocos2d::CCSpriteBatchNode* speedBatchNode;
    cocos2d::CCSpriteBatchNode* timeAdderBatchNode[6];
    cocos2d::CCSpriteBatchNode* copyBatchNode;
};

class GameScene : public cocos2d::CCScene {
public:
    GameScene():_layer(NULL) {};
    virtual ~GameScene();
    virtual bool init();
    
    CREATE_FUNC(GameScene);
    CC_SYNTHESIZE_READONLY(GameLayer*, _layer, Layer);
    
};
#endif /* defined(__TTT__GameScene__) */