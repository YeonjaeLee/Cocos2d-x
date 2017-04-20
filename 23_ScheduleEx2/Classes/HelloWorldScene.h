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

	void doStart(Ref* pSender);
	void doPause(Ref* pSender);
	void doResume(Ref* pSender);
	void doChange(Ref* pSender);
	void doStop(Ref* pSender);
	void tick1(float f);
	void tick2(float f);

	bool bChange;
};

#endif // __HELLOWORLD_SCENE_H__