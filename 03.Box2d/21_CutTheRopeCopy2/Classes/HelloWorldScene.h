#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include <GLES-Render.h>


//#define PTM_RATIO 32

using namespace cocos2d;

// 전방 선언. 뒤에 include 할테니 갖다 쓰라는 의미.
class VRope;

class HelloWorld : public cocos2d::LayerColor
	, public b2ContactListener
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(HelloWorld);

	~HelloWorld();
	bool createBox2dWorld(bool debug);
	virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags) override;
	
	virtual void onEnter();
	virtual void onExit();
	virtual bool onTouchBegan(Touch *touch, Event *event);
	virtual void onTouchMoved(Touch *touch, Event *event);

	b2Body* createCandyAt(Vec2 pt, bool userData);
	void createRope(b2Body* bodyA, b2Vec2 anchorA, b2Body* bodyB, b2Vec2 anchorB, float32 sag);
	void tick(float dt);
	bool checkLineIntersection(Vec2 p1, Vec2 p2, Vec2 p3, Vec2 p4);
	b2Body* createRopeTipBody();
	b2Body* addNewSprite(Vec2 point, Size size, b2BodyType bodytype, const char* spriteName, int type);

private:
	Size			winSize;
	Texture2D*		texture;
	b2World*		_world;
	// For debugging
	GLESDebugDraw*	m_debugDraw;

	std::vector<VRope *>*	ropes;
	std::vector<b2Body *>*	candies;

	SpriteBatchNode*		ropeSpriteSheet;

	Sprite*		sprite;

	Sprite*		croc_;
	b2Body*		crocMouth_;
	b2Fixture*	crocMouthBottom_;
	bool		crocMouthOpened;
	int			opencount = 0;
//	b2Body*					groundBody;

	virtual void BeginContact(b2Contact *contact);
	virtual void EndContact(b2Contact *contact);
	virtual void PreSolve(b2Contact *contact, const b2Manifold *oldManifold);
	virtual void PostSolve(b2Contact *contact, const b2ContactImpulse *impulse);

protected:
	void onDraw(const cocos2d::Mat4& transform, uint32_t flags);
	cocos2d::CustomCommand _customCmd;
};

#endif // __HELLOWORLD_SCENE_H__