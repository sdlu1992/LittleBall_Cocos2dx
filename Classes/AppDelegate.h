//
//  TTTAppDelegate.h
//  TTT
//
//  Created by sdlu on 13-3-11.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//

#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "CCApplication.h"
#include "cocos2d.h"
/**
 @brief    The cocos2d Application.
 
 The reason to implement with private inheritance is to hide some interface details of CCDirector.
 */
class  AppDelegate : private cocos2d::CCApplication
{
public:
    cocos2d::CCDirector *pDirector;
    AppDelegate();
    virtual ~AppDelegate();
    
    /**
     @brief    Implement CCDirector and CCScene init code here.
     @return true    Initialize success, app continue.
     @return false   Initialize failed, app terminate.
     */
    virtual bool applicationDidFinishLaunching();
    
    /**
     @brief  The function is called when the application enters the background
     @param  the pointer of the application instance
     */
    virtual void applicationDidEnterBackground();
    
    /**
     @brief  The function is called when the application enters the foreground
     @param  the pointer of the application instance
     */
    virtual void applicationWillEnterForeground();
};

#endif // _APP_DELEGATE_H_
