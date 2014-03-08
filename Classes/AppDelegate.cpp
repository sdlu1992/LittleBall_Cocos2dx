//
//  TTTAppDelegate.cpp
//  TTT
//
//  Created by sdlu on 13-3-11.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//

#include "AppDelegate.h"


#include "HelloWorldScene.h"

USING_NS_CC;

AppDelegate::AppDelegate()
{
    
}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director	
    pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    
//    CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    CCLog("%f,%f",screenSize.width,screenSize.height);
    CCLog("%f,%f",screenSize.width/960.0f,screenSize.height/640.f);
    
    if (screenSize.height > 320)
    {
        CCFileUtils::sharedFileUtils()->setResourceDirectory("hd");
        pDirector->setContentScaleFactor(960.0f/screenSize.width);
    }
    else
    {
        CCFileUtils::sharedFileUtils()->setResourceDirectory("sd");
        pDirector->setContentScaleFactor(640.0f/screenSize.height);
    }
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(screenSize.width, screenSize.height, kResolutionNoBorder);
    
    // turn on display FPS
//    pDirector->setDisplayStats(true);
    
    // set FPS. the default value is 1.0/60 if you don't call this
//    pDirector->setAnimationInterval(1.0 / 60);
    
    // create a scene. it's an autorelease object
    CCScene *pScene = HelloWorld::scene();
    
    // run
    pDirector->runWithScene(pScene);
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();
    
    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();
    
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}