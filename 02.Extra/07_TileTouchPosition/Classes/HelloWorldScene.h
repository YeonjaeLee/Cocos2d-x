#ifndef __HELLOWORLD_SCENE_H__
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

	void onEnter();
	void onExit();
	bool onTouchBegan(cocos2d::Touch * pTouch, cocos2d::Event * pEvent);
	void onTouchMoved(cocos2d::Touch * pTouch, cocos2d::Event * pEvent);
	void onTouchEnded(cocos2d::Touch * pTouch, cocos2d::Event * pEvent);

	cocos2d::Vec2 touchToXY(cocos2d::Vec2 touch);
	cocos2d::TMXTiledMap* map;
	cocos2d::Vec2 pos;

};

#endif // __HELLOWORLD_SCENE_H__