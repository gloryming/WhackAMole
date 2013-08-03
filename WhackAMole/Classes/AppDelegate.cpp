//
//  WhackAMoleAppDelegate.cpp
//  WhackAMole
//
//  Created by 郭 一鸣 on 13-8-2.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    
    CCSize screenSize = CCDirector::sharedDirector()->getWinSizeInPixels();
    CCFileUtils *pFileUtils = CCFileUtils::sharedFileUtils();
    std::vector<std::string> searchPaths;
    
    CCSize designSize = CCSizeMake(512, 320);
    CCSize resourceSize;
    
    // if the device is iPad
    if (screenSize.height >= 768) {
        searchPaths.push_back("hd");
        searchPaths.push_back("sd");
        resourceSize = CCSizeMake(1024, 768);
        
        // for retina iPad
        if (screenSize.width > 1024) {
            designSize.width = screenSize.width / 2.0;
        }
    }
    // if the device is iPhone
    else{
        // for retina iPhone
        if (screenSize.height > 320) {
            searchPaths.push_back("hd");
            searchPaths.push_back("sd");
            resourceSize = CCSizeMake(960, 640);
            
            // for iPhone5
            if (screenSize.width > 960) {
                designSize.height = screenSize.height / 2.0;
            }
        }
        else{
            searchPaths.push_back("sd");
            resourceSize = CCSizeMake(480, 320);
        }
    }
    searchPaths.push_back("WhackAMoleSounds");
    pFileUtils->setSearchPaths(searchPaths);
    pDirector->setContentScaleFactor(resourceSize.height / designSize.height);
    
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionFixedHeight);
    
    // load background and foreground
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("background.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("foreground.plist");

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    CCScene *pScene = HelloWorld::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}
