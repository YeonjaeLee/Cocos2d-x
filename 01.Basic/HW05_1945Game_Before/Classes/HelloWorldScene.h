#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif

#include "cocos2d.h"

#define RANDOM_INT(MIN, MAX) ((MIN) + arc4random() % ((MAX + 1) - (MIN)))

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

	void ccregisterWithTouchDispatcher();

	bool TouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
	void TouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
	void TouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);

	void Update(float time);
	void RegenEnemy(float time);
	void Shooting(float time);

	void PutCrashEffect(const cocos2d::CCPoint &pos);

	void AddEnemy(const CCPoint& position);

private:
	Sprite *player_;//주인공 플레이어
	Array *missile_[MAX_MISSILE];
	Array *enemy_;//적비행기 CCArray(배열, 리스트 구조)

	Point distance_;
	Size size_;

	float regenCheckTime_;
};

#endif // __HELLOWORLD_SCENE_H__