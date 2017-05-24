#ifndef __SceneTrans2_GAMEOVERSCENE__
#define __SceneTrans2_GAMEOVERSCENE__

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif

#include "cocos2d.h"

using namespace cocos2d;

class GameoverScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(GameoverScene);

	Size winSize;
};
#endif // __SceneTrans2_GAMEOVERSCENE__