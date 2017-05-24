#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif

#include "cocos2d.h"

using namespace cocos2d;

class HelloWorld : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(HelloWorld);

	virtual void onEnter();
	virtual void onExit();
	virtual bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event);
	virtual void onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * event);
	virtual void onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * event);
	//virtual void onTouchCancelled(cocos2d::Touch * touch, cocos2d::Event * event);

	void scheduleCallback(float f);

	void Shoot(Vec2 point);

	Vec2 pos;
	Vector<Sprite*> bullet_;
};

#endif // __HELLOWORLD_SCENE_H__