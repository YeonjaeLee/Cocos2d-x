#ifndef __SceneTrans2_INTROSCENE__
#define __SceneTrans2_INTROSCENE__

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif

#include "cocos2d.h"

using namespace cocos2d;

class IntroScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(IntroScene);

	Size winSize;
	void tick(float dt);

	int count = 0;
};
#endif // __SceneTrans2_INTROSCENE__