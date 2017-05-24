#ifndef __Box2dEx18__ContactListener__
#define __Box2dEx18__ContactListener__

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif

#include "cocos2d.h"
#include "Box2D/Box2D.h"

using namespace cocos2d;

class ContactListener : public b2ContactListener
{
public:
	ContactListener();
	~ContactListener();

	virtual void BeginContact(b2Contact *contact);
	virtual void EndContact(b2Contact *contact);
	virtual void PreSolve(b2Contact *contact, const b2Manifold *oldManifold);
	virtual void PostSolve(b2Contact *contact, const b2ContactImpulse *impulse);
};

#endif // defined(__Box2dEx18__ContactListener__)


