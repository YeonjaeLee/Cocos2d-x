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

	cocos2d::Sprite* grass_upper;
	cocos2d::Sprite* mole_1;
	cocos2d::Sprite* mole_2;
	cocos2d::Sprite* mole_3;
	cocos2d::Sprite* grass_lower;

	void callEveryFrame(float f);

	void doAction_mole_1(Ref* pSender);
	void ActionRepeatForever_mole_1(Ref* pSender);
	void doAction_mole_2(Ref* pSender);
	void ActionRepeatForever_mole_2(Ref* pSender);
	void doAction_mole_3(Ref* pSender);
	void ActionRepeatForever_mole_3(Ref* pSender);

	int ox1, ox2, ox3;
	int nRanNum;
};

#endif // __HELLOWORLD_SCENE_H__