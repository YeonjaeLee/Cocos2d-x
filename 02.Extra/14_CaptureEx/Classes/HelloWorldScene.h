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

	void onCaptured(Ref*);
	void afterCaptured(bool succeed, const std::string& outputFile);

	std::string _filename;
	static const int childTag = 119;
};

#endif // __HELLOWORLD_SCENE_H__