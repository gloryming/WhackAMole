#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

#pragma mark - initilize
HelloWorld::HelloWorld()
:_moles(NULL),
_laughAnim(NULL),
_hitAnim(NULL),
_label(NULL)
{
    
}

HelloWorld::~HelloWorld()
{
    CC_SAFE_RELEASE_NULL(_moles);
    
    
}

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();
    
    
    CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();
    CCLOG("screenSize.width =%f,  screenSize.height = %f", screenSize.width, screenSize.height);
    


    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    _winSize = CCDirector::sharedDirector()->getWinSize();
    CCLOG("width =%f, height = %f", _winSize.width, _winSize.height);
    
    // Add background
    CCSprite *dirt = CCSprite::createWithSpriteFrameName("bg_dirt.png");
    dirt->setScale(2.0);
    dirt->setPosition(ccp(_winSize.width * 0.5, _winSize.height * 0.5));
    this->addChild(dirt, -2);
    
    // Add foreground
    CCSprite *lower = CCSprite::createWithSpriteFrameName("grass_lower.png");
    lower->setAnchorPoint(ccp(0.5, 1));
    lower->setPosition(ccp(_winSize.width * 0.5, _winSize.height * 0.5));
    lower->getTexture()->setAliasTexParameters();
    this->addChild(lower, 1);
    
    CCSprite *upper = CCSprite::createWithSpriteFrameName("grass_upper.png");
    upper->setAnchorPoint(ccp(0.5, 0));
    upper->setPosition(ccp(_winSize.width * 0.5, _winSize.height * 0.5));
    upper->getTexture()->setAliasTexParameters();
    this->addChild(upper, -1);
    
    // load sprites
    CCSpriteBatchNode *spriteNode = CCSpriteBatchNode::create("sprites.pvr.ccz");
    this->addChild(spriteNode, 0);
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("sprites.plist");
    
    
    float offset = 155;
    float startPoint = 85 + offset;
    CCSize frameSize = CCEGLView::sharedOpenGLView()->getFrameSize();
    if ( fabs(frameSize.width - 1024) < FLT_EPSILON) {
        offset = offset * (1024 / 480.0);
        startPoint = startPoint * (1024 / 480.0) ;
    }
    
    // Add mole2
    GameSprite *mole2 = GameSprite::gameSpriteWithFile("mole_1.png");
    mole2->setPosition(HelloWorld::convertPoint(ccp(startPoint, 85)));
    spriteNode->addChild(mole2);
    
    // Add mole1
    GameSprite *mole1 = GameSprite::gameSpriteWithFile("mole_1.png");
    mole1->setPosition(HelloWorld::convertPoint(ccpSub(mole2->getPosition(), ccp(offset, mole2->getPositionY() - 85))));
    spriteNode->addChild(mole1);
    
    
    // Add mole3
    GameSprite *mole3 = GameSprite::gameSpriteWithFile("mole_1.png");
    mole3->setPosition(HelloWorld::convertPoint(ccpAdd(mole2->getPosition(), ccp(offset, 85 - mole2->getPositionY()))));
    spriteNode->addChild(mole3);
    _moles = CCArray::create(mole1, mole2, mole3, NULL);
    _moles->retain();
    this->schedule(schedule_selector(HelloWorld::tryPopMoles), 0.5);
    
    _laughAnim = HelloWorld::animationFromPlist_delay("_laughAnim.plist", 0.2);
    _hitAnim = HelloWorld::animationFromPlist_delay("hitAnim.plist", 0.04);
    CCAnimationCache::sharedAnimationCache()->addAnimation(_laughAnim, "_laughAnim");
    CCAnimationCache::sharedAnimationCache()->addAnimation(_hitAnim, "hitAnim");
    
    this->setTouchEnabled(true);
    
    float margin = 10.0;
    _label = CCLabelTTF::create("score:0", "Verdana", HelloWorld::converFontSize(14.0));
    _label->cocos2d::CCNode::setAnchorPoint(ccp(1, 0));
    _label->setPosition(ccp(_winSize.width - margin, margin));
    this->addChild(_label, 10);
    
    SimpleAudioEngine::sharedEngine()->preloadEffect("laugh.caf");
    SimpleAudioEngine::sharedEngine()->preloadEffect("ow.caf");
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("whack.caf", true);
    
    return true;
}

#pragma mark - logic

CCPoint HelloWorld::convertPoint(CCPoint point){
    CCSize frameSize = CCEGLView::sharedOpenGLView()->getFrameSize();
    if ( fabs(frameSize.width - 1024) < FLT_EPSILON) {
        return ccp(0.9 * point.x + 47, point.y + 100);
    }
    if (fabs(frameSize.width - 1136) < FLT_EPSILON) {
        return ccp(point.x, point.y - 18);
    }
    return point;
}

void HelloWorld::tryPopMoles(CCTime dt){
    if (_gameOver) {
        return;
    }
    _label->setString(CCString::createWithFormat("score: %d", _score)->getCString());
    if (_totalSpawns >= 50) {
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        
        CCLabelTTF *goLabel = CCLabelTTF::create("Level Complete", "Verdana", HelloWorld::converFontSize(48));
        goLabel->setPosition(ccp(winSize.width / 2, winSize.height / 2));
        goLabel->setScale(0.1);
        this->addChild(goLabel, 10);
        goLabel->runAction(CCScaleTo::create(0.5, 1.0));
        
        _gameOver = true;
    }
    GameSprite *mole;
    for (int i = 0; i < 3; i++) {
        mole = (GameSprite *)_moles->objectAtIndex(i);
        if (arc4random() % 3 == 0) {
            if (mole->numberOfRunningActions() == 0) {
                this->popMole(mole);
            }
        }
    }
    
    return;
}

void HelloWorld::setTappable(void *sender){
    GameSprite *mole = (GameSprite *)sender;
    mole->setUserData(mole, true);
    SimpleAudioEngine::sharedEngine()->playEffect("laugh.caf");
}

void HelloWorld::unSetTappable(void *sender){
    GameSprite *mole = (GameSprite *)sender;
    mole->setUserData(mole, false);
}

void HelloWorld::popMole(GameSprite *mole){
    
    if (_totalSpawns > 50) {
        return;
    }
    _totalSpawns++;
    
    mole->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("mole_1.png"));
    CCMoveBy *moveUp = CCMoveBy::create(0.2, ccp(0, _winSize.height * 0.25));
    CCCallFunc *setTappable = CCCallFuncN::create(this, callfuncN_selector(HelloWorld::setTappable));
    CCEaseInOut *easeMoveUp = CCEaseInOut::create(moveUp, 3.0);
    //    CCDelayTime *delay = CCDelayTime::create(0.5);
    CCAnimation *laughN = CCAnimationCache::sharedAnimationCache()->animationByName("_laughAnim");
    laughN->setRestoreOriginalFrame(true);
    CCAnimate *laugh = CCAnimate::create(laughN);
    CCCallFunc *unSetTappable = CCCallFuncN::create(this, callfuncN_selector(HelloWorld::unSetTappable));
    CCAction *easeMoveDown = easeMoveUp->reverse();
    mole->runAction(CCSequence::create(easeMoveUp, setTappable, laugh, unSetTappable, easeMoveDown, NULL));
}

float HelloWorld::converFontSize(float fontSize){
    if (_winSize.width >= 1024 ) {
        return fontSize * 2;
    }
    else{
        return fontSize;
    }
}

void HelloWorld::registerWithTouchDispatcher(){
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, false);
}

bool HelloWorld::ccTouchBegan(CCTouch *touch, CCEvent *event){
    CCPoint touchLocation = this->convertToNodeSpace(touch->getLocation());
    for (int i = 0; i < _moles->count(); i++) {
        GameSprite *mole = (GameSprite *)_moles->objectAtIndex(i);
        if (mole->GameSprite::getUserData(mole) == false) {
            continue;
        }
        if (mole->boundingBox().containsPoint(touchLocation)) {
            SimpleAudioEngine::sharedEngine()->playEffect("ow.caf");
            mole->GameSprite::setUserData(mole, false);
            _score += 10;
            
            mole->stopAllActions();
            CCAnimation *hitN = (CCAnimation *)CCAnimationCache::sharedAnimationCache()->animationByName("hitAnim");
            CCAnimate *hit = CCAnimate::create(hitN);
            CCMoveBy *moveDown = CCMoveBy::create(0.2, ccp(0, -_winSize.height * 0.25));
            CCEaseInOut *easeMoveDown = CCEaseInOut::create(moveDown, 3.0);
            mole->runAction(CCSequence::create(hit, easeMoveDown, NULL));
        }
    }
    
    return true;
}

CCAnimation* HelloWorld::animationFromPlist_delay(const char *animPlist, float delay){
    CCArray *animImages = CCArray::createWithContentsOfFile(animPlist);
    CCArray *animFrames = CCArray::create();
    for (int i = 0; i < animImages->count(); i++) {
        CCString *temp = (CCString *)animImages->objectAtIndex(i);
        const char *animImage = temp->getCString();
        animFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(animImage));
    }
    
    return CCAnimation::createWithSpriteFrames(animFrames, delay);
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
