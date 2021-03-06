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

	cocos2d::Sprite* pMan;

	void doAction(Ref* pSender);
	void ActionSequence(Ref* pSender);
	void doReverse(Ref* pSender);
};

#endif // __HELLOWORLD_SCENE_H__