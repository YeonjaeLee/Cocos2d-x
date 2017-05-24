#ifndef __SceneTrans2_GAMESCENE__
#define __SceneTrans2_GAMESCENE__

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include <GLES-Render.h>

#define PTM_RATIO 32

using namespace cocos2d;

class GameScene : public cocos2d::Layer
	, public b2ContactListener
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
	b2Body* createBirdAt(Vec2 pt, bool userData);
	b2Body* createHoldBackAt1(int posy);
	b2Body* createHoldBackAt2(int posy);

	b2Body* getBodyAtTab(Vec2 p);
	virtual bool onTouchBegan(Touch *touch, Event *event);
	virtual void onTouchEnded(Touch *touch, Event *event);

private:
	Size winSize;
	Texture2D* texture;
	b2World* _world;
	// For debugging
	GLESDebugDraw* m_debugDraw;

	b2Body* bird;
	cocos2d::Sprite* Bird;
	bool playerIsFlying = false;
	float playerVelocity = 0.0f;

	int flycount = 80;
	int hbcount = 0;

	b2Body*		groundbody;

	Sprite* Ground;
	Sprite* holdback1;
	Sprite* holdback2;

	void afterCaptured(bool succeed, const std::string& outputFile);
	std::string _filename;
	static const int childTag = 119;

	/*bool bDrag;
	b2Body *dragBody;
	b2MouseJoint *mouseJoint;
	b2Body *gbody;*/

	virtual void BeginContact(b2Contact *contact);
	virtual void EndContact(b2Contact *contact);
	virtual void PreSolve(b2Contact *contact, const b2Manifold *oldManifold);
	virtual void PostSolve(b2Contact *contact, const b2ContactImpulse *impulse);

protected:
	void onDraw(const cocos2d::Mat4& transform, uint32_t flags);
	cocos2d::CustomCommand _customCmd;
};

#endif // __SceneTrans2_GAMESCENE__