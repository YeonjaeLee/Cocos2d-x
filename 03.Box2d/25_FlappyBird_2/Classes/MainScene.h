#ifndef __SceneTrans2_MAINSCENE__
#define __SceneTrans2_MAINSCENE__

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif

#include "cocos2d.h"

using namespace cocos2d;

class MainScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(MainScene);

	Size winSize;

	cocos2d::Sprite* Bird;
	cocos2d::Sprite* StartButton;
	cocos2d::Sprite* GradeButton;
	cocos2d::Sprite* RateButton;

	cocos2d::Vec2 position1;
	cocos2d::Vec2 position2;
	cocos2d::Vec2 position3;

	void createBird();

	virtual void onEnter();
	virtual void onExit();
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

};
#endif // __SceneTrans2_MAINSCENE__