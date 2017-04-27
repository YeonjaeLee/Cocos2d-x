﻿#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#define RANDOM_INT(MIN, MAX) ((MIN) + rand() % ((MAX + 1) - (MIN)))
USING_NS_CC;

#define MAX_MISSILE		2



class HelloWorld : public cocos2d::LayerColor
{
public:
	HelloWorld();

	static cocos2d::Scene* createScene();

	virtual bool init();
	void menuCloseCallback(Ref* pSender);

	CREATE_FUNC(HelloWorld);

	//void ccregisterWithTouchDispatcher();
	virtual void onEnter();
	virtual void onExit();
	virtual bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
	virtual void onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
	virtual void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);

	void Update(float time);
	void RegenEnemy(float time);
	void Shooting(float time);
	void PutCrashEffect(const cocos2d::Vec2 &pos);
	void AddEnemy(const Vec2& position);
	void UserLife(int LifeCount);

	cocos2d::Sprite* UserLife1;
	cocos2d::Sprite* UserLife2;
	cocos2d::Sprite* UserLife3;
	cocos2d::Sprite* GameOver;

	int LifeCount = 3;

private:
	Sprite *player_;//주인공 플레이어
	Vector<Sprite*> missile_[MAX_MISSILE];
	Vector<Sprite*> enemy_;//적비행기 CCArray(배열, 리스트 구조)

	Vec2 distance_;
	Size size_;
	int playerLife = 3;

	float regenCheckTime_;
};

#endif // __HELLOWORLD_SCENE_H__