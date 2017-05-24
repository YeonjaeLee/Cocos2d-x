#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif

#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include <GLES-Render.h>

#define PTM_RATIO 32

using namespace cocos2d;

class HelloWorld : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(HelloWorld);

	~HelloWorld();
	bool createBox2dWorld(bool debug);
	virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags) override;
	void tick(float dt);
	void addNewSpriteAtPosition(Vec2 location);

	virtual void onTouchEnded(Set *touch, Event *event);

	Size winSize;
	Texture2D* texture;
	b2World* _world;
	GLESDebugDraw* m_debugDraw;

protected:
	void onDraw(const cocos2d::Mat4& transform, uint32_t flags);
	cocos2d::CustomCommand _customCmd;
};

#endif // __HELLOWORLD_SCENE_H__