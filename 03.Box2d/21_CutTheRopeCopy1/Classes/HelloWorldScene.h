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
	void tick(float dt);

	b2Body* addNewSpriteAt(Vec2 point);
	void createRope(b2Body* bodyA, b2Vec2 anchorA, b2Body* bodyB, b2Vec2 anchorB, float32 sag);
	virtual bool onTouchBegan(Touch *touch, Event *event);
	
	Size			winSize;
	Texture2D*		texture;
	b2World*		_world;
	// For debugging
	GLESDebugDraw*	m_debugDraw;

	b2Body*					groundBody;
	std::vector<VRope *>*	ropes;
	SpriteBatchNode*		ropeSpriteSheet;

protected:
	void onDraw(const cocos2d::Mat4& transform, uint32_t flags);
	cocos2d::CustomCommand _customCmd;
};

#endif // __HELLOWORLD_SCENE_H__