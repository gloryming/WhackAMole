//
//  GameSprite.cpp
//  WhackAMole
//
//  Created by 郭 一鸣 on 13-8-2.
//
//

#include "GameSprite.h"

GameSprite::GameSprite(){
    
}

GameSprite::~GameSprite(){
    
}

GameSprite* GameSprite::gameSpriteWithFile(const char *pszFileName){
    GameSprite *sprite = new GameSprite();
    if (sprite && sprite->initWithSpriteFrameName(pszFileName)) {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}
/*
CCPoint GameSprite::convertPoint(CCPoint point){
    if (_screenSize.height >= 768) {
        return ccp(32 + point.x * 2, 64 + point.y * 2);
    }
    else{
        return point;
    }
}
*/
void GameSprite::setUserData(GameSprite *mole, bool flag){
    mole->userData = flag;
}

bool GameSprite::getUserData(GameSprite *mole){
    return mole->userData;
}
