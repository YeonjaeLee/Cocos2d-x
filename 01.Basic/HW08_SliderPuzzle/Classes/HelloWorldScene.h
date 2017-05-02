#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(HelloWorld);

	cocos2d::Sprite* spr1;
	cocos2d::Sprite* spr2;
	cocos2d::Sprite* spr3;
	cocos2d::Sprite* spr4;
	cocos2d::Sprite* spr5;
	cocos2d::Sprite* spr6;
	cocos2d::Sprite* spr7;
	cocos2d::Sprite* spr8;
	cocos2d::Sprite* spr9;
	cocos2d::Sprite* clickspr;
	cocos2d::Sprite* pmovespr;

	cocos2d::Vec2 clickpos;
	cocos2d::Vec2 position1;
	cocos2d::Vec2 position2;
	cocos2d::Vec2 position3;
	cocos2d::Vec2 position4;
	cocos2d::Vec2 position5;
	cocos2d::Vec2 position6;
	cocos2d::Vec2 position7;
	cocos2d::Vec2 position8;
	cocos2d::Vec2 position9;

	void settingrand();
	void settingpos();
	void endok();
	virtual void onEnter();
	virtual void onExit();
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	int nNum[9];
	int hidesprtag;
};

#endif // __HELLOWORLD_SCENE_H__