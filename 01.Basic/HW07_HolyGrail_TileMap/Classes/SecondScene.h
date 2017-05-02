#ifndef __SceneTrans1__SecondScene__
#define __SceneTrans1__SecondScene__

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif

#include "cocos2d.h"

class SecondScene : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(SecondScene);

	int state = 1;
	int can_W_Sword001 = 0;
	int can_W_Mace008 = 0;
	int can_W_Sword015 = 0;
	int can_I_Key = 0;

	cocos2d::Size		winSize;

	cocos2d::Sprite*	pHero;
	cocos2d::Sprite*	pDemon1;
	cocos2d::Sprite*	pDemon2;
	cocos2d::Sprite*	pDemon3;
	cocos2d::Sprite*	pJelly1;
	cocos2d::Sprite*	pJelly2;
	cocos2d::Sprite*	pJelly3;
	cocos2d::Sprite*	pJelly4;
	cocos2d::Sprite*	pJelly5;
	cocos2d::Sprite*	pWolf1;
	cocos2d::Sprite*	pWolf2;
	cocos2d::Sprite*	pWolf3;
	cocos2d::Sprite*	pWolf4;
	cocos2d::Sprite*	pI_Chest;
	cocos2d::Sprite*	pW_Sword0011;
	cocos2d::Sprite*	pW_Sword0012;
	cocos2d::Sprite*	pW_Sword0013;
	cocos2d::Sprite*	pW_Mace0081;
	cocos2d::Sprite*	pW_Mace0082;
	cocos2d::Sprite*	pW_Mace0083;
	cocos2d::Sprite*	pW_Mace0084;
	cocos2d::Sprite*	pW_Sword0151;
	cocos2d::Sprite*	pW_Sword0152;
	cocos2d::Sprite*	pI_Key;
	cocos2d::ParticleSystem *emitter;

	cocos2d::Sprite*	SideUi;
	cocos2d::Sprite*	ItemBox;
	cocos2d::Sprite*	pItemState;

	void doClick_ResetButton(Ref* pSender);

	cocos2d::Vec2		moveposition;
	cocos2d::Vec2		willposition;
	cocos2d::Vec2		HeroPosition;
	cocos2d::Vec2		DemonPosition1;
	cocos2d::Vec2		DemonPosition2;
	cocos2d::Vec2		DemonPosition3;
	cocos2d::Vec2		JellyPosition1;
	cocos2d::Vec2		JellyPosition2;
	cocos2d::Vec2		JellyPosition3;
	cocos2d::Vec2		JellyPosition4;
	cocos2d::Vec2		JellyPosition5;
	cocos2d::Vec2		WolfPosition1;
	cocos2d::Vec2		WolfPosition2;
	cocos2d::Vec2		WolfPosition3;
	cocos2d::Vec2		WolfPosition4;
	cocos2d::Vec2		I_ChestPosition;
	cocos2d::Vec2		W_Sword001Position1;
	cocos2d::Vec2		W_Sword001Position2;
	cocos2d::Vec2		W_Sword001Position3;
	cocos2d::Vec2		W_Mace008Position1;
	cocos2d::Vec2		W_Mace008Position2;
	cocos2d::Vec2		W_Mace008Position3;
	cocos2d::Vec2		W_Mace008Position4;
	cocos2d::Vec2		W_Sword015Position1;
	cocos2d::Vec2		W_Sword015Position2;
	cocos2d::Vec2		I_KeyPosition;

	cocos2d::Vec2		ItemStatePosition;

	cocos2d::TMXTiledMap* tmap;

	cocos2d::TMXLayer*	background;
	cocos2d::TMXLayer*	metainfo;

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

#endif // defind(__SceneTrans1__SecondScene__)