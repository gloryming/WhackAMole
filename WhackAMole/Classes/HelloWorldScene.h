#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "GameSprite.h"

using namespace cocos2d;

class HelloWorld : public cocos2d::CCLayer
{

public:
    HelloWorld();
    ~HelloWorld();
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    CREATE_FUNC(HelloWorld);
    
    void registerWithTouchDispatcher();
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CCPoint convertPoint(CCPoint point);
    void tryPopMoles(CCTime dt);
    void popMole(GameSprite *mole);
    float converFontSize(float fontSize);
    CCAnimation* animationFromPlist_delay(const char *animPlist, float delay);
    void setTappable(void *sender);
    void unSetTappable(void *sender);
    
    
    bool ccTouchBegan(CCTouch *touch, CCEvent *event);
    
private:
    CCSize          _winSize;
    CCArray*        _moles;
    CCAnimation*    _laughAnim;
    CCAnimation*    _hitAnim;
    CCLabelTTF*     _label;
    
    int             _score;
    int             _totalSpawns;
    bool            _gameOver;
};

#endif // __HELLOWORLD_SCENE_H__
