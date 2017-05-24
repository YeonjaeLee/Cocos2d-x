#ifndef __SceneTrans2_GameSCENE__
#define __SceneTrans2_GameSCENE__

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include <GLES-Render.h>

#define PTM_RATIO 32

using namespace cocos2d;

class GameScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(GameScene);

	bool createBox2dWorld(bool debug);
	~GameScene();
	virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags) override;

	virtual void onEnter();
	virtual void onExit();
	void tick(float dt);
	b2Body* addNewSprite(Vec2 point, Size size, b2BodyType bodytype, const char* spriteName, int type);
	b2Body* getBodyAtTab(Vec2 p);
	virtual bool onTouchBegan(Touch *touch, Event *event);
	virtual void onTouchEnded(Touch *touch, Event *event);

	b2Body* createBirdAt(Vec2 pt, bool userData);

	Size winSize;
	Texture2D* texture;
	b2World* _world;
	GLESDebugDraw* m_debugDraw;

	b2Body* bird;
	cocos2d::Sprite* Bird;
	bool playerIsFlying = false;
	float playerVelocity = 0.0f;

	int flycount = 80;

	/*bool bDrag;
	b2Body *dragBody;
	b2MouseJoint *mouseJoint;
	b2Body *gbody;*/

protected:
	void onDraw(const cocos2d::Mat4& transform, uint32_t flags);
	cocos2d::CustomCommand _customCmd;
	// For debugging

};

#endif // __SceneTrans2_GameSCENE__