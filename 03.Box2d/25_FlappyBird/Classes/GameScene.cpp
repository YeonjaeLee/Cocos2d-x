#include "GameScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	/////////////////////////////////////////////
	// 윈도우 크기를 구한다.
	winSize = Director::getInstance()->getWinSize();

	// 이미지의 텍스처를 구한다.
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/flappy_packer.plist");
	texture = Director::getInstance()->getTextureCache()->addImage("bird1.png");

	// 월드 생성
	if (this->createBox2dWorld(true))
	{
		this->schedule(schedule_selector(GameScene::tick));
	}
	return true;
}

bool GameScene::createBox2dWorld(bool debug)
{
	// 월드 생성 시작 ----------------------------------------------------

	// 중력의 방향을 결정한다.
	//b2Vec2 gravity = b2Vec2(0.0f, -30.0f);
	b2Vec2 gravity = b2Vec2(0.0f, 0.0f);

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
	Sprite* bg = Sprite::create("Images/bg.png");
	bg->setPosition(Vec2(0, 0));
	bg->setAnchorPoint(Vec2(0, 0));
	this->addChild(bg);

	auto Ground = Sprite::create("Images/ground.png");
	Ground->setPosition(Vec2(0, 0));
	Ground->setAnchorPoint(Vec2(0, 0));
	auto forward = MoveBy::create(1.0f, Vec2(-120, 0));
	auto myActionReplay = Place::create(Vec2(0, 0));
	auto myAction = Sequence::create(forward, myActionReplay, nullptr);
	auto rep = RepeatForever::create(myAction);
	Ground->runAction(rep);
	this->addChild(Ground);

	bird = this->createBirdAt(Vec2(winSize.width / 2 - 200, winSize.height * 2 / 3 - 50), true);
	
	//bDrag = false;

	//// 마우스 조인트 바디를 생성해서 월드에 추가한다.
	//gbody = this->addNewSprite(Vec2(0, 0), Size(0, 0), b2_staticBody, nullptr, 0);

	//// 바디를 생성해서 월드에 추가한다.
	//this->addNewSprite(Vec2(240, 160), Size(32, 32), b2_dynamicBody, "test", 0);
	return true;
}

GameScene::~GameScene()
{
	// 월드를 C++의 new로 생성했으므로 여기서 지워준다.
	delete _world;
	_world = nullptr;
}

void GameScene::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	Layer::draw(renderer, transform, flags);

	_customCmd.init(_globalZOrder, transform, flags);
	_customCmd.func = CC_CALLBACK_0(GameScene::onDraw, this, transform, flags);
	renderer->addCommand(&_customCmd);
}

void GameScene::onEnter()
{
	Layer::onEnter();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void GameScene::onExit()
{
	//_eventDispatcher->removeAllEventListeners();
	Layer::onExit();
}

void GameScene::tick(float dt)
{
	int velocityIterations = 8;
	int positionIterations = 3;

	// Step : 물리 세계를 시뮬레이션한다.
	_world->Step(dt, velocityIterations, positionIterations);

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
		log("GetLinearVelocity: %f, %f", bird->GetLinearVelocity().x, bird->GetLinearVelocity().y);
		log("playerVelocity: %f", playerVelocity);
		
		if (bird->GetLinearVelocity().y > 5.0)
		{
			bird->ApplyLinearImpulse(b2Vec2(0, playerVelocity - bird->GetLinearVelocity().y - 40.0f),
				bird->GetWorldCenter(),
				true);
		}
		else if (bird->GetLinearVelocity().y < 0)
		{
			bird->ApplyLinearImpulse(b2Vec2(0, playerVelocity - bird->GetLinearVelocity().y),
				bird->GetWorldCenter(),
				true);
		}
		else
		{
			bird->ApplyLinearImpulse(b2Vec2(0, playerVelocity),
				bird->GetWorldCenter(),
				true);
		}

		playerVelocity -= 10.0f;

		if (playerVelocity < -40.0f)
			playerVelocity = 0.0f;

		flycount--;
		log("%d", flycount);
		if (flycount == 0)
		{
			playerIsFlying = false;
			flycount = 80;
		}
	}
}

b2Body* GameScene::addNewSprite(Vec2 point, Size size, b2BodyType bodytype, const char* spriteName, int type)
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

b2Body* GameScene::createBirdAt(Vec2 pt, bool userData)
{
	// Get the sprite from the sprite sheet
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("Images/flappy_packer.plist");

	Vector<SpriteFrame*> animFrams;

	char str[100] = { 0 };
	for (int i = 1; i < 4; i++)
	{
		sprintf(str, "bird%01d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		animFrams.pushBack(frame);
	}
	Bird = Sprite::createWithSpriteFrameName("bird1.png");
	Bird->setPosition(Vec2(winSize.width / 2, winSize.height / 2 + 50));
	this->addChild(Bird);

	auto animation = Animation::createWithSpriteFrames(animFrams, 0.1f);
	auto animate = Animate::create(animation);

	auto myActionForward = MoveBy::create(0.2, Vec2(0, 15));
	auto myActionBack = myActionForward->reverse();
	auto myAction = Sequence::create(myActionForward, myActionBack, nullptr);
	auto spawn = Spawn::create(animate, myAction, nullptr);
	auto rep = RepeatForever::create(spawn);

	Bird->runAction(rep);
	animFrams.clear();

	// Defines the body of your candy
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = b2Vec2(pt.x / PTM_RATIO, pt.y / PTM_RATIO);
	bodyDef.userData = Bird;
	//bodyDef.linearDamping = 0.3f;
	b2Body* body = _world->CreateBody(&bodyDef);
	// Define the fixture as a polygon
	b2FixtureDef fixtureDef;
	b2PolygonShape spriteShape;

	b2Vec2 verts[] =
	{
		b2Vec2(-31.6f / PTM_RATIO, -23.4f / PTM_RATIO),
		b2Vec2(-33.6f / PTM_RATIO, 15.0f / PTM_RATIO),
		b2Vec2(-15.3f / PTM_RATIO, 28.4f / PTM_RATIO),
		b2Vec2(21.3f / PTM_RATIO, 28.4f / PTM_RATIO),
		b2Vec2(40.0f / PTM_RATIO, -19.25f / PTM_RATIO),
		b2Vec2(25.25f / PTM_RATIO, -28.5f / PTM_RATIO),
		b2Vec2(-25.0f / PTM_RATIO, -28.5f / PTM_RATIO),
		b2Vec2(-30.55f / PTM_RATIO, 20.95f / PTM_RATIO)
	};
	spriteShape.Set(verts, 7);
	fixtureDef.shape = &spriteShape;
	fixtureDef.density = 30.0f;
	//fixtureDef.filter.categoryBits = 0x01;
	//fixtureDef.filter.maskBits = 0x01;

	body->CreateFixture(&fixtureDef);

	return body;
}

b2Body* GameScene::getBodyAtTab(Vec2 p)
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

bool GameScene::onTouchBegan(Touch* touch, Event* event)
{
	flycount = 80;
	playerVelocity = 200.0f;
	playerIsFlying = true;
	
	return true;
}

void GameScene::onTouchEnded(Touch *touch, Event *event)
{
	playerVelocity = 0.0f;
}

void GameScene::onDraw(const Mat4 &transform, uint32_t flags)
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
