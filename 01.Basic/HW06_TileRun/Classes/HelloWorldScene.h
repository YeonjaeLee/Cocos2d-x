﻿#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif

#include "cocos2d.h"

class HelloWorld : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(HelloWorld);

	cocos2d::Size		winSize;
	cocos2d::Vec2		womanPosition;
	cocos2d::Sprite*	woman;

	cocos2d::TMXTiledMap* tmap;
	cocos2d::TMXLayer*	background;
	cocos2d::TMXLayer*	metainfo;

	void createWoman();
	
	cocos2d::Vec2 tileCoordForPosition(cocos2d::Vec2 position);
	void setPlayerPosition(cocos2d::Vec2 position);

	void myTick(float f);
	int i = 0;

};

#endif // __HELLOWORLD_SCENE_H__