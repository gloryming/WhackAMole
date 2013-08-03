#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "GameSprite.h"

using namespace cocos2d;

class HelloWorld : public cocos2d::CCLayer
{
    CCSize _winSize;
    CCArray *moles;
    
    CCAnimation *laughAnim;
    CCAnimation *hitAnim;
    
    CCLabelTTF *label;
    int score;
    int totalSpawns;
    bool gameOver;

public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HelloWorld);
    
    void tryPopMoles(CCTime dt);
    void popMole(GameSprite *mole);
    float converFontSize(float fontSize);
    CCAnimation* animationFromPlist_delay(const char *animPlist, float delay);
    void setTappable(void *sender);
    void unSetTappable(void *sender);
    void registerWithTouchDispatcher();
    bool ccTouchBegan(CCTouch *touch, CCEvent *event);
};

#endif // __HELLOWORLD_SCENE_H__
