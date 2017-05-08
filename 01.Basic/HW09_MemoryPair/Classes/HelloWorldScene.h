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

	cocos2d::Sprite* box1;
	cocos2d::Sprite* box2;
	cocos2d::Sprite* box3;
	cocos2d::Sprite* box4;
	cocos2d::Sprite* box5;
	cocos2d::Sprite* box6;
	cocos2d::Sprite* box7;
	cocos2d::Sprite* box8;
	cocos2d::Sprite* box9;
	cocos2d::Sprite* box10;
	cocos2d::Sprite* box11;
	cocos2d::Sprite* box12;
	cocos2d::Sprite* box13;
	cocos2d::Sprite* box14;
	cocos2d::Sprite* box15;
	cocos2d::Sprite* box16;
	cocos2d::Sprite* box17;
	cocos2d::Sprite* box18;
	cocos2d::Sprite* box19;
	cocos2d::Sprite* box20;
	cocos2d::Sprite* clickbox;
	cocos2d::Sprite* clickbox1;
	cocos2d::Sprite* clickbox2;

	cocos2d::Sprite* pmovespr;
	cocos2d::Sprite* clickspr;
	cocos2d::Sprite* clickspr1;
	cocos2d::Sprite* clickspr2;

	cocos2d::Vec2 position1;
	cocos2d::Vec2 position2;
	cocos2d::Vec2 position3;
	cocos2d::Vec2 position4;
	cocos2d::Vec2 position5;
	cocos2d::Vec2 position6;
	cocos2d::Vec2 position7;
	cocos2d::Vec2 position8;
	cocos2d::Vec2 position9;
	cocos2d::Vec2 position10;
	cocos2d::Vec2 position11;
	cocos2d::Vec2 position12;
	cocos2d::Vec2 position13;
	cocos2d::Vec2 position14;
	cocos2d::Vec2 position15;
	cocos2d::Vec2 position16;
	cocos2d::Vec2 position17;
	cocos2d::Vec2 position18;
	cocos2d::Vec2 position19;
	cocos2d::Vec2 position20;
	cocos2d::Vec2 clickpos;

//	cocos2d::Vector<Sprite*> boxes;
	cocos2d::Vector<cocos2d::Sprite*> sprs;
	std::vector<cocos2d::Vec2> poses;

	cocos2d::Menu* pMenu_pReplayItem;

	void sprcreate();
	void boxcreate();
	void settingrand();
	void vsspr();
	void vsmovepos(int state);
	void endok();

	virtual void onEnter();
	virtual void onExit();
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void doClick(Ref * pSender);
	void doParticles(cocos2d::Vec2 position);

	int nNum[20] = { 0 };
	int count = 0;
	int state = 0;
	int state1 = 0;
	int state2 = 0;
};

#endif // __HELLOWORLD_SCENE_H__