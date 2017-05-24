﻿#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif

#include "cocos2d.h"

using namespace cocos2d;

class HelloWorld : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(HelloWorld);

	Sprite* pWoman1;
	Sprite* pWoman2;

	void SpriteProgressToRadial(Ref* pSender);
	void SpriteProgressToHorizontal(Ref* pSender);
	void SpriteProgressToVertical(Ref* pSender);
	void SpriteProgressToRadialMidpointChanged(Ref* pSender);
	void SpriteProgressBarVarious(Ref* pSender);
	void SpriteProgressBarTintAndFade(Ref* pSender);
};

#endif // __HELLOWORLD_SCENE_H__