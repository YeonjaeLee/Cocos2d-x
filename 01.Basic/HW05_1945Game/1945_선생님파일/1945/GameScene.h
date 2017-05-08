#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

#define RANDOM_INT(MIN, MAX) ((MIN) + arc4random() % ((MAX + 1) - (MIN)))

USING_NS_CC;

#define MAX_MISSILE		2

class CGameScene : public cocos2d::CCLayer
{
public:
	CGameScene();
	
    virtual bool init();
    static cocos2d::CCScene* scene();
    void menuCloseCallback(CCObject* pSender);
    CREATE_FUNC(CGameScene);

	void registerWithTouchDispatcher();
	
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	
	void Update(float time);
	void RegenEnemy(float time);
	void Shooting(float time);

	void PutCrashEffect(const cocos2d::CCPoint &pos);
	
	void AddEnemy(const CCPoint& position);
	
private:
	CCSprite *player_;//주인공 플레이어
	CCArray *missile_[MAX_MISSILE];
	CCArray *enemy_;//적비행기 CCArray(배열, 리스트 구조)
	
	CCPoint distance_;
	CCSize size_;
	
	float regenCheckTime_;
};

#endif // __HELLOWORLD_SCENE_H__
