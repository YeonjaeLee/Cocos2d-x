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

	int state = 1;
	int can_W_Sword001 = 0;
	int can_W_Mace008 = 0;
	int can_W_Sword015 = 0;
	int can_I_Key = 0;

	cocos2d::Size		winSize;

	cocos2d::LabelTTF*	pLabel1;
	cocos2d::Sprite*	pHero;
	cocos2d::Sprite*	pDemon;
	cocos2d::Sprite*	pJelly;
	cocos2d::Sprite*	pWolf;
	cocos2d::Sprite*	pI_Chest;
	cocos2d::Sprite*	pW_Sword001;
	cocos2d::Sprite*	pW_Mace008;
	cocos2d::Sprite*	pW_Sword015;
	cocos2d::Sprite*	pI_Key;
	cocos2d::ParticleSystem *emitter;

	cocos2d::Sprite*	SideUi;
	cocos2d::Sprite*	ItemBox;
	cocos2d::Sprite*	pItemState;

	void doClick_ResetButton(Ref* pSender);

	cocos2d::Vec2		moveposition;
	cocos2d::Vec2		HeroPosition;
	cocos2d::Vec2		DemonPosition;
	cocos2d::Vec2		JellyPosition;
	cocos2d::Vec2		WolfPosition;
	cocos2d::Vec2		I_ChestPosition;
	cocos2d::Vec2		W_Sword001Position;
	cocos2d::Vec2		W_Mace008Position;
	cocos2d::Vec2		W_Sword015Position;
	cocos2d::Vec2		I_KeyPosition;

	cocos2d::Vec2		ItemStatePosition;

	cocos2d::TMXTiledMap* tmap;

	cocos2d::TMXLayer*	background;
	cocos2d::TMXLayer*	metainfo;

	void doAction_Label1(Ref* pSender);
	void ActionRepeatForever_Label1(Ref* pSender);
	void createHero();
	void createW_Sword001();
	void createW_Mace008();
	void createW_Sword015();
	void createI_Key();
	void createDemon();
	void createJelly();
	void createWolf();
	void createI_Chest();
	void createItemState();
	void resetItemState();

	virtual void onEnter();
	virtual void onExit();
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void setViewpointCenter(cocos2d::Vec2 position);
	void setPlayerPosition(cocos2d::Vec2 position);
	cocos2d::Vec2 tileCoordForPosition(cocos2d::Vec2 position);
};

#endif // __HELLOWORLD_SCENE_H__