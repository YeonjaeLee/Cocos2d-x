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

	cocos2d::Sprite* Bckg;
	cocos2d::Sprite* Fish_001;
	cocos2d::Sprite* Fish_002;
	cocos2d::Sprite* Lighting_Background;
	cocos2d::Sprite* Flash_004;
	cocos2d::Sprite* Flash_005;
	cocos2d::Sprite* All_Light;
	cocos2d::Sprite* Logo_Light;
	cocos2d::Sprite* Title_Bubble_001;
	cocos2d::Sprite* Title_Bubble_002;
	cocos2d::Sprite* Title_Bubble_003;
	cocos2d::Sprite* BubbleLogo;
	cocos2d::Sprite* Play_Button_01;
	cocos2d::Sprite* Vibration_ON;
	cocos2d::Sprite* Base;
	cocos2d::Sprite* Create_Button_01;
	cocos2d::Sprite* Create_base;
	cocos2d::Sprite* Blue_Star;
	cocos2d::Sprite* Gold_Star;
	cocos2d::Sprite* Purple_Star;
	cocos2d::Sprite* Lighting;

	void doClick_Play_Button(Ref* pSender);
	void doClick_Vibration_ON(Ref* pSender);
	void doClick_Create_Button(Ref* pSender);

	void doAction_Fish_001(Ref* pSender);
	void ActionRepeatForever_Fish_001(Ref* pSender);
	void doAction_Fish_002(Ref* pSender);
	void ActionRepeatForever_Fish_002(Ref* pSender);
	void doAction_Lighting_Background(Ref* pSender);
	void ActionRepeatForever_Lighting_Background(Ref* pSender);
	void doAction_Lighting(Ref* pSender);
	void ActionRepeatForever_Lighting(Ref* pSender);
	void doAction_All_Light(Ref* pSender);
	void ActionRepeatForever_Flash_004(Ref* pSender);
	void doAction_Flash_004(Ref* pSender);
	void ActionRepeatForever_Flash_005(Ref* pSender);
	void doAction_Flash_005(Ref* pSender);
	void ActionRepeatForever_All_Light(Ref* pSender);
	void doAction_Logo_Light(Ref* pSender);
	void ActionRepeatForever_Logo_Light(Ref* pSender);
	void doAction_Title_Bubble_001(Ref* pSender);
	void ActionRepeatForever_Title_Bubble_001(Ref* pSender);
	void doAction_Title_Bubble_002(Ref* pSender);
	void ActionRepeatForever_Title_Bubble_002(Ref* pSender);
	void doAction_Title_Bubble_003(Ref* pSender);
	void ActionRepeatForever_Title_Bubble_003(Ref* pSender);
	void doAction_BubbleLogo(Ref* pSender);
	void ActionRepeatForever_BubbleLogo(Ref* pSender);
	void doAction_Base(Ref* pSender);
	void ActionRepeatForever_Base(Ref* pSender);
	void doAction_Create_base(Ref* pSender);
	void ActionRepeatForever_Create_base(Ref* pSender);
	void doAction_Blue_Star(Ref* pSender);
	void ActionRepeatForever_Blue_Star(Ref* pSender);
	void doAction_Gold_Star(Ref* pSender);
	void ActionRepeatForever_Gold_Star(Ref* pSender);
	void doAction_Purple_Star(Ref* pSender);
	void ActionRepeatForever_Purple_Star(Ref* pSender);
};

#endif // __HELLOWORLD_SCENE_H__