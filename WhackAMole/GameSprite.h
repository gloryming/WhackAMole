//
//  GameSprite.h
//  WhackAMole
//
//  Created by 郭 一鸣 on 13-8-2.
//
//

#ifndef __WhackAMole__GameSprite__
#define __WhackAMole__GameSprite__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class GameSprite : public CCSprite {
    CCSize _screenSize;
    bool userData;
public:
    GameSprite();
    ~GameSprite();
    
    static GameSprite* gameSpriteWithFile(const char *pszFileName);
    void setUserData(GameSprite *mole, bool flag);
    bool getUserData(GameSprite *mole);
};


#endif /* defined(__WhackAMole__GameSprite__) */
