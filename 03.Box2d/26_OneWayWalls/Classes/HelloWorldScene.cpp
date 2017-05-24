#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	auto scene = Scene::create();
	auto layer = HelloWorld::create();
	scene->addChild(layer);
	return scene;
}

bool HelloWorld::init()
{
	if (!Layer::init())
	{
		return false;
	}
	/////////////////////////////////////////////
	// 윈도우 크기를 구한다.
	winSize = Director::getInstance()->getWinSize();

	// 이미지의 텍스처를 구한다.
	texture = Director::getInstance()->getTextureCache()->addImage("blocks.png");

	// 월드 생성
	if (this->createBox2dWorld(true))
	{
		// 월드에 충돌함수 클래스를 리스너에 추가함

		_world->SetContactListener((b2ContactListener*)this);
		this->schedule(schedule_selector(HelloWorld::tick));
	}
	return true;
}

bool HelloWorld::createBox2dWorld(bool debug)
{
	// 월드 생성 시작 ----------------------------------------------------

	// 중력의 방향을 결정한다.
	b2Vec2 gravity = b2Vec2(0.0f, -30.0f);

	_world = new b2World(gravity);
	_world->SetAllowSleeping(true);
	_world->SetContinuousPhysics(true);

	// 디버그 드로잉 설정
	if (debug)
	{
		// 적색 : 현재 물리 운동을 하는 것
		// 회색 : 현재 물리 운동량이 없는 것
		m_debugDraw = new GLESDebugDraw(PTM_RATIO);
		_world->SetDebugDraw(m_debugDraw);

		uint32 flags = 0;
		flags += b2Draw::e_shapeBit;
		flags += b2Draw::e_jointBit;
		//flags += b2Draw::e_aabbBit;
		//flags += b2Draw::e_pairBit;
		//flags += b2Draw::e_centerOfMassBit;
		m_debugDraw->SetFlags(flags);

	}

	// 가장자리(테두리)를 지정해 공간(Ground Box)을 만든다.

	// 바디데프에 좌표를 설정한다.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0);

	// 월드에 바디데프의 정보(좌표)로 바디를 만든다.
	b2Body *groundBody = _world->CreateBody(&groundBodyDef);

	// 가장자리(테두리) 경계선을 그릴 수 있는 모양의 객체를 만든다.
	b2EdgeShape groundEdge;
	b2FixtureDef boxShapeDef;
	boxShapeDef.shape = &groundEdge;

	// 에지 모양의 객체에 Set(점1, 점2)로 선을 만든다.
	// 그리고 바디(groundBody)에 모양(groundEdge)을 고정시킨다.

	// 아래쪽
	groundEdge.Set(b2Vec2(0, 0), b2Vec2(winSize.width / PTM_RATIO, 0));
	groundBody->CreateFixture(&boxShapeDef);

	// 왼쪽
	groundEdge.Set(b2Vec2(0, 0), b2Vec2(0, winSize.height / PTM_RATIO));
	groundBody->CreateFixture(&boxShapeDef);

	// 위쪽
	groundEdge.Set(b2Vec2(0, winSize.height / PTM_RATIO), b2Vec2(winSize.width / PTM_RATIO, winSize.height / PTM_RATIO));
	groundBody->CreateFixture(&boxShapeDef);

	// 아래쪽
	groundEdge.Set(b2Vec2(winSize.width / PTM_RATIO, winSize.height / PTM_RATIO), b2Vec2(winSize.width / PTM_RATIO, 0));
	groundBody->CreateFixture(&boxShapeDef);

	// 월드 생성 끝 -----------------------------------------------------------
	//setup platform shape for reuse
	b2PolygonShape polygonShape;
	b2Vec2 verts[5];
	verts[0].Set(0, -0.75);
	verts[1].Set(2.5, -0.5);
	verts[2].Set(2.5, 0.5);
	verts[3].Set(-2.5, 0.5);
	verts[4].Set(-2.5, -0.5);
	polygonShape.Set(verts, 5);

	//kinematic platform
	/*{
		b2BodyDef bodyDef;
		bodyDef.type = b2_kinematicBody;
		bodyDef.position.Set(6, 5);
		m_platformBody = _world->CreateBody(&bodyDef);
		m_platformFixture = m_platformBody->CreateFixture(&polygonShape, 0);
	}*/

	//dynamic box
	/*{
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(6, 10);
		body = _world->CreateBody(&bodyDef);

		polygonShape.SetAsBox(0.5, 0.5);
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &polygonShape;
		_world->CreateBody(&bodyDef)->CreateFixture(&polygonShape, 1);
	}*/

	//바디를 생성 후
	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	bodyDef.position.Set(6, 7);
	b2Body* pBody = _world->CreateBody(&bodyDef);
	//픽스쳐를 생성 후에 UserData에 (void*)1을 세팅            
	b2Fixture* pFixture = pBody->CreateFixture(&polygonShape, 0);
	pFixture->SetUserData((void*)1);
	//이 세팅을 안하면 바디의 픽스쳐의 UserData가 NULL이 됩니다.
	//이렇게 1이라고 설정한 바디들은 충돌함수에서 원웨이 플래폼으로 인식하게 됩니다. 일종의 태그 입니다.

	//
	myBall = this->addNewSprite(Vec2(200, 20), Size(32, 32), b2_dynamicBody, nullptr, 1);
	Sprite* myBallSprite = (Sprite*)myBall->GetUserData();

	/*bDrag = false;
	gbody = this->addNewSprite(Vec2(0, 0), Size(0, 0), b2_staticBody, nullptr, 0);

	this->addNewSprite(Vec2(240, 160), Size(32, 32), b2_dynamicBody, "test", 0);
	*/
	return true;
}

b2Body* HelloWorld::addNewSprite(Vec2 point, Size size, b2BodyType bodytype, const char* spriteName, int type)
{
	// 바디데프를 만들고 속성들을 지정한다.
	b2BodyDef bodyDef;
	bodyDef.type = bodytype;
	bodyDef.position.Set(point.x / PTM_RATIO, point.y / PTM_RATIO);

	if (spriteName)
	{
		if (strcmp(spriteName, "test") == 0)
		{
			int idx = (CCRANDOM_0_1() > .5 ? 0 : 1);
			int idy = (CCRANDOM_0_1() > .5 ? 0 : 1);
			Sprite* sprite = Sprite::createWithTexture(texture, Rect(32 * idx, 32 * idy, 32, 32));
			sprite->setPosition(point);
			this->addChild(sprite);

			bodyDef.userData = sprite;
		}
		else
		{
			Sprite* sprite = Sprite::create(spriteName);
			sprite->setPosition(point);
			this->addChild(sprite);

			bodyDef.userData = sprite;
		}
	}
	// 월드에 바디데프의 정보로 바디를 만든다.
	b2Body *body = _world->CreateBody(&bodyDef);

	// 바디에 적용할 물리 속성용 바디의 모양을 만든다.
	b2FixtureDef fixtureDef;
	b2PolygonShape dynamicBox;
	b2CircleShape circle;

	if (type == 0)
	{
		dynamicBox.SetAsBox(size.width / 2 / PTM_RATIO, size.height / 2 / PTM_RATIO);

		fixtureDef.shape = &dynamicBox;
	}
	else
	{
		circle.m_radius = (size.width / 2) / PTM_RATIO;

		fixtureDef.shape = &circle;
	}

	// Define the dynamic body fixture.
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.0f;

	body->CreateFixture(&fixtureDef);

	return body;
}

HelloWorld::~HelloWorld()
{
	// 월드를 C++의 new로 생성했으므로 여기서 지워준다.
	//delete myContactListener;
	delete _world;
	_world = nullptr;
}

void HelloWorld::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	Layer::draw(renderer, transform, flags);

	_customCmd.init(_globalZOrder, transform, flags);
	_customCmd.func = CC_CALLBACK_0(HelloWorld::onDraw, this, transform, flags);
	renderer->addCommand(&_customCmd);
}

void HelloWorld::onEnter()
{
	Layer::onEnter();

	// 싱글 터치 모드로 터치리스너 등록
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	//listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void HelloWorld::onExit()
{
	_eventDispatcher->removeAllEventListeners();
	Layer::onExit();
}

void HelloWorld::tick(float dt)
{
	int velocityIterations = 8;
	int positionIterations = 3;

	// Step : 물리 세계를 시뮬레이션한다.
	_world->Step(dt, velocityIterations, positionIterations);

	// 모든 물리 객체들은 링크드 리스트에 저장되어 참조해 볼 수 있게 구현돼 있다.
	// 만들어진 객체만큼 루프를 돌리면서 바디에 붙인 스프라이트를 여기서 제어한다.
	for (b2Body *b = _world->GetBodyList(); b; b = b->GetNext())
	{
		if (b->GetUserData() != nullptr)
		{
			Sprite* spriteData = (Sprite *)b->GetUserData();
			spriteData->setPosition(Vec2(b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO));
			spriteData->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
		}
	}

	if (playerIsFlying)
	{
		myBall->ApplyLinearImpulse(b2Vec2(0, playerVelocity),
			myBall->GetWorldCenter(),
			true);

		playerVelocity += 0.01f;

		if (playerVelocity > 1.5f)
			playerVelocity = 1.5f;
	}
}

b2Body* HelloWorld::getBodyAtTab(Vec2 p)
{
	b2Fixture *fix;
	for (b2Body *b = _world->GetBodyList(); b; b = b->GetNext())
	{
		if (b->GetUserData() != nullptr)
		{
			if (b->GetType() == b2_staticBody)	continue;
			fix = b->GetFixtureList();
			if (fix->TestPoint(b2Vec2(p.x / PTM_RATIO, p.y / PTM_RATIO)))
			{
				return b;
			}
		}
	}
	return nullptr;
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
	playerVelocity = 0.5f;
	playerIsFlying = true;
	/*Vec2 touchPoint = touch->getLocation();
	
	if (b2Body *b = this->getBodyAtTab(touchPoint))
	{
		dragBody = b;
		bDrag = true;

		b2MouseJointDef md;
		md.bodyA = gbody;
		md.bodyB = dragBody;
		md.target.Set(dragBody->GetPosition().x, dragBody->GetPosition().y);
		md.maxForce = 300.0 * dragBody->GetMass();

		mouseJoint = (b2MouseJoint *)_world->CreateJoint(&md);
	}*/

	// 테두리 사이즈
	//this->addNewSprite(touchPoint, Size(64, 64), b2_dynamicBody, "test", 0);

	return true;
}

//void HelloWorld::onTouchMoved(Touch *touch, Event *event)
//{
//	Vec2 touchPoint = touch->getLocation();
//	if (bDrag)
//	{
//		mouseJoint->SetTarget(b2Vec2(touchPoint.x / PTM_RATIO, touchPoint.y / PTM_RATIO));
//	}
//}

void HelloWorld::onTouchEnded(Touch *touch, Event *event)
{
	playerVelocity = 0.0f;
	playerIsFlying = false;
	/*if (bDrag)
	{
		_world->DestroyJoint(mouseJoint);
		mouseJoint = nullptr;

		dragBody->SetAwake(true);
	}
	bDrag = false;*/
}

void HelloWorld::onDraw(const Mat4 &transform, uint32_t flags)
{
	Director* director = Director::getInstance();
	CCASSERT(nullptr != director, "Director is null when seting matrix stack");
	director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);

	GL::enableVertexAttribs(cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION);
	_world->DrawDebugData();
	CHECK_GL_ERROR_DEBUG();

	director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

void HelloWorld::BeginContact(b2Contact *contact)
{
	log("Contact:Begin");
	//충돌한 두 물체의 픽스쳐를 받아온다.
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	b2Fixture* platformFixture = NULL;
	b2Fixture* otherFixture = NULL;

	//둘 중 어떤 픽스쳐가 원웨이 플레폼인지 판단한다.
	//UserData를 받아와서 이게 널인지 아닌지 체크를 하는데 우린 앞서 원웨이 플레폼의 UserData를 (void*)1로 설정했으므로
	//UserData가 널이 아닌 것이 'platformFixture'가 되고 다른 것이 'otherFicture'가 된다.
	//만약 다른 충돌 관련 코드를 사용중인 경우, 이부분에 대해 반드시 확인, 수정이 필요하다.
	if (fixtureA->GetUserData()) {
		platformFixture = fixtureA;
		otherFixture = fixtureB;
		log("fixtureA = platform");
	}
	else if (fixtureB->GetUserData()) {
		platformFixture = fixtureB;
		otherFixture = fixtureA;
		log("fixtureB = platform");
	}

	//플레폼 픽스쳐가 없으면 리턴, 정상적인 충돌 활동 수행
	if (!platformFixture)
	{
		log("플레폼 픽스쳐 없음. 정상적 충돌 활동 수행");
		return;
	}

	int numPoints = contact->GetManifold()->pointCount;
	b2WorldManifold worldManifold;
	contact->GetWorldManifold(&worldManifold);

	b2Body* platformBody = platformFixture->GetBody();
	b2Body* otherBody = otherFixture->GetBody();

	for (int i = 0; i < numPoints; i++) {
		b2Vec2 pointVelPlatform =
			platformBody->GetLinearVelocityFromWorldPoint(worldManifold.points[i]);

		b2Vec2 pointVelOther =
			otherBody->GetLinearVelocityFromWorldPoint(worldManifold.points[i]);

		b2Vec2 relativeVel = platformBody->GetLocalVector(pointVelOther - pointVelPlatform);

		//다른 픽스쳐의 속도 - 원웨이 플레폼 픽스쳐의 속도의 y벡터 값이 -1보다 작으면 충돌
		//즉, 캐릭터가 플레폼과 충돌을 했을 때, 캐릭터의 속도가 플레폼보다 아래 방향으로 가해지는 경우 충돌이라고 판단
		//왜 굳이 캐릭터가 아래로 이동하면 충돌이라고 단순하게 하지 않는 걸까? - 플레폼이 위 방향으로 움직이고 캐릭터는 가만히 있을 수 있기 때문에.
		if (relativeVel.y < -1)
		{
			return;
		}

	}
	//그것이 아니면 충돌이 아님. 픽스쳐와 픽스쳐는 서로 충돌이 아니라고 인식해서 통과된다.
	contact->SetEnabled(false);
}

void HelloWorld::EndContact(b2Contact *contact)
{
	log("Contact:End");
	//reset the default state of the contact in case it comes back for more
	contact->SetEnabled(true);
}

void HelloWorld::PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
{
	log("Contact:PreSolve");
	//log("-----------%f---------------", gbody->GetLinearVelocity());
}

void HelloWorld::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse)
{
	log("Contact:PostSolve .. 1");

	b2Fixture *fixA = contact->GetFixtureA();
	b2Fixture *fixB = contact->GetFixtureB();

	b2Body *bodyA = fixA->GetBody();
	b2Body *bodyB = fixB->GetBody();

	if (bodyA->GetType() == b2_kinematicBody || bodyB->GetType() == b2_dynamicBody)
	{
		log("Contact:impulse .. %f", impulse->normalImpulses[0]);
	}
}
