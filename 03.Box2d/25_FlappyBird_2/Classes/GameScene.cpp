#include "GameScene.h"
#include "GameoverScene.h"

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
	// ������ ũ�⸦ ���Ѵ�.
	winSize = Director::getInstance()->getWinSize();
	srand((int)time(NULL));

	// �̹����� �ؽ�ó�� ���Ѵ�.
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/flappy_packer.plist");
	texture = Director::getInstance()->getTextureCache()->addImage("blocks.png");

	// ���� ����
	if (this->createBox2dWorld(true))
	{
		// ���忡 �浹�Լ� Ŭ������ �����ʿ� �߰���
		_world->SetContactListener((b2ContactListener*)this);

		this->schedule(schedule_selector(GameScene::tick));
	}

	_filename = "";

	return true;
}

bool GameScene::createBox2dWorld(bool debug)
{
	// ���� ���� ���� ----------------------------------------------------

	// �߷��� ������ �����Ѵ�.
	//b2Vec2 gravity = b2Vec2(0.0f, -30.0f);
	b2Vec2 gravity = b2Vec2(0.0f, 0.0f);

	_world = new b2World(gravity);
	_world->SetAllowSleeping(true);
	_world->SetContinuousPhysics(true);

	// ����� ����� ����
	if (debug)
	{
		// ���� : ���� ���� ��� �ϴ� ��
		// ȸ�� : ���� ���� ����� ���� ��
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

	// �����ڸ�(�׵θ�)�� ������ ����(Ground Box)�� �����.

	// �ٵ����� ��ǥ�� �����Ѵ�.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0);

	// ���忡 �ٵ����� ����(��ǥ)�� �ٵ� �����.
	b2Body *groundBody = _world->CreateBody(&groundBodyDef);

	// �����ڸ�(�׵θ�) ��輱�� �׸� �� �ִ� ����� ��ü�� �����.
	b2EdgeShape groundEdge;
	b2FixtureDef boxShapeDef;
	boxShapeDef.shape = &groundEdge;

	// ���� ����� ��ü�� Set(��1, ��2)�� ���� �����.
	// �׸��� �ٵ�(groundBody)�� ���(groundEdge)�� ������Ų��.

	// �Ʒ���
	groundEdge.Set(b2Vec2(0, 0), b2Vec2(winSize.width / PTM_RATIO, 0));
	groundBody->CreateFixture(&boxShapeDef);

	// ����
	groundEdge.Set(b2Vec2(0, 0), b2Vec2(0, winSize.height / PTM_RATIO));
	groundBody->CreateFixture(&boxShapeDef);

	// ����
	groundEdge.Set(b2Vec2(0, winSize.height / PTM_RATIO), b2Vec2(winSize.width / PTM_RATIO, winSize.height / PTM_RATIO));
	groundBody->CreateFixture(&boxShapeDef);

	// �Ʒ���
	groundEdge.Set(b2Vec2(winSize.width / PTM_RATIO, winSize.height / PTM_RATIO), b2Vec2(winSize.width / PTM_RATIO, 0));
	groundBody->CreateFixture(&boxShapeDef);

	// ���� ���� �� -----------------------------------------------------------
	/*Sprite* bg = Sprite::create("Images/bg.png");
	bg->setPosition(Vec2(0, 0));
	bg->setAnchorPoint(Vec2(0, 0));
	this->addChild(bg);*/

	Ground = Sprite::create("Images/ground.png");
	Ground->setPosition(Vec2(0, 0));
	Ground->setAnchorPoint(Vec2(0, 0));
	auto forward = MoveBy::create(1.0f, Vec2(-120, 0));
	auto myActionReplay = Place::create(Vec2(0, 0));
	auto myAction = Sequence::create(forward, myActionReplay, nullptr);
	auto rep = RepeatForever::create(myAction);
	Ground->runAction(rep);
	this->addChild(Ground);

	bird = this->createBirdAt(Vec2(winSize.width / 2 - 200, winSize.height * 2 / 3 - 50), true);

	groundbody = this->addNewSprite(Vec2(winSize.width / 2, winSize.height / 7 - 10), Size(720, 200), b2_staticBody, nullptr, 0);

	// ��ֹ�1 ����
	/*srand((int)time(NULL));
	int posy = rand() % 531;*/

	//this->createHoldBackAt(posy);



	//bDrag = false;

	//// ���콺 ����Ʈ �ٵ� �����ؼ� ���忡 �߰��Ѵ�.
	//gbody = this->addNewSprite(Vec2(0, 0), Size(0, 0), b2_staticBody, nullptr, 0);

	//// �ٵ� �����ؼ� ���忡 �߰��Ѵ�.
	//this->addNewSprite(Vec2(240, 160), Size(32, 32), b2_dynamicBody, "test", 0);
	return true;
}

GameScene::~GameScene()
{
	// ���带 C++�� new�� ���������Ƿ� ���⼭ �����ش�.
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
	hbcount++;

	// Step : ���� ���踦 �ùķ��̼��Ѵ�.
	_world->Step(dt, velocityIterations, positionIterations);

	// ������� ��ü��ŭ ������ �����鼭 �ٵ� ���� ��������Ʈ�� ���⼭ �����Ѵ�.
	for (b2Body *b = _world->GetBodyList(); b; b = b->GetNext())
	{
		if (b->GetUserData() != nullptr)
		{
			Sprite* spriteData = (Sprite *)b->GetUserData();
			spriteData->setPosition(Vec2(b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO));
			spriteData->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
		}
	}

	// �� Ŭ��
	if (playerIsFlying)
	{
		//log("GetLinearVelocity: %f, %f", bird->GetLinearVelocity().x, bird->GetLinearVelocity().y);
		//log("playerVelocity: %f", playerVelocity);

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
		if (flycount == 0)
		{
			playerIsFlying = false;
			flycount = 80;
		}
	}

	// ��� ����
	if (hbcount > 100)
	{
		if (hbcount % 300 == 0)
		{
			int posy = rand() % 531;
			log("%d", posy);
			this->createHoldBackAt1(posy);
			this->createHoldBackAt2(posy);
		}
	}
}

b2Body* GameScene::addNewSprite(Vec2 point, Size size, b2BodyType bodytype, const char* spriteName, int type)
{
	// �ٵ����� ����� �Ӽ����� �����Ѵ�.
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
	// ���忡 �ٵ����� ������ �ٵ� �����.
	b2Body *body = _world->CreateBody(&bodyDef);

	// �ٵ� ������ ���� �Ӽ��� �ٵ��� ����� �����.
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

b2Body* GameScene::createHoldBackAt1(int posy)
{
	Vec2 hbposition1 = Vec2(winSize.width + 200, posy);

	// ��ֹ�1 kinematicBody ��������Ʈ�� �߰��Ѵ�.
	holdback1 = Sprite::createWithSpriteFrameName("holdback1.png");
	holdback1->setPosition(hbposition1);
	this->addChild(holdback1);

	// �ٵ����� ����� �Ӽ����� �����Ѵ�.
	b2BodyDef bodyDef1;
	bodyDef1.type = b2_kinematicBody;
	bodyDef1.position.Set(hbposition1.x / PTM_RATIO, hbposition1.y / PTM_RATIO);
	bodyDef1.linearVelocity = b2Vec2(-3.5f, 0);
	bodyDef1.userData = holdback1;

	b2Body* body1 = _world->CreateBody(&bodyDef1);

	// �ٵ� ������ ���� �Ӽ��� �ٵ��� ����� �����.
	b2PolygonShape kinematicBox;

	// �ٵ��� ũ�� ���� - ������ ũ�⿡�� ��� ��ġ�� �����Ѵ�.
	kinematicBox.SetAsBox((holdback1->getContentSize().width / 2) / PTM_RATIO, (holdback1->getContentSize().height / 2 - 20) / PTM_RATIO);
	b2FixtureDef fixtureDef1;
	fixtureDef1.shape = &kinematicBox;
	fixtureDef1.density = 1.0f;

	body1->CreateFixture(&fixtureDef1);

	return body1;
}

b2Body* GameScene::createHoldBackAt2(int posy)
{
	Vec2 hbposition2 = Vec2(winSize.width + 200, posy + 830 + 260);

	// ��ֹ�2 kinematicBody ��������Ʈ�� �߰��Ѵ�.
	holdback2 = Sprite::createWithSpriteFrameName("holdback2.png");
	holdback2->setPosition(hbposition2);
	this->addChild(holdback2);

	// �ٵ����� ����� �Ӽ����� �����Ѵ�.
	b2BodyDef bodyDef2;
	bodyDef2.type = b2_kinematicBody;
	bodyDef2.position.Set(hbposition2.x / PTM_RATIO, hbposition2.y / PTM_RATIO);
	bodyDef2.linearVelocity = b2Vec2(-3.5f, 0);
	bodyDef2.userData = holdback2;

	b2Body* body2 = _world->CreateBody(&bodyDef2);

	// �ٵ� ������ ���� �Ӽ��� �ٵ��� ����� �����.
	b2PolygonShape kinematicBox;

	// �ٵ��� ũ�� ���� - ������ ũ�⿡�� ��� ��ġ�� �����Ѵ�.
	kinematicBox.SetAsBox((holdback2->getContentSize().width / 2) / PTM_RATIO, (holdback2->getContentSize().height / 2) / PTM_RATIO);
	b2FixtureDef fixtureDef2;
	fixtureDef2.shape = &kinematicBox;
	fixtureDef2.density = 1.0f;

	body2->CreateFixture(&fixtureDef2);

	return body2;
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

void GameScene::BeginContact(b2Contact *contact)
{
	log("Contact:Begin");

	b2Fixture *fixA = contact->GetFixtureA();
	b2Fixture *fixB = contact->GetFixtureB();

	b2Body *bodyA = fixA->GetBody();
	b2Body *bodyB = fixB->GetBody();

	if (bodyA->GetType() == b2_dynamicBody || bodyB->GetType() == b2_staticBody)
	{
		log("�浹");
		Bird->setVisible(false);
		Director::getInstance()->getTextureCache()->removeTextureForKey(_filename);
		removeChildByTag(childTag);
		_filename = "D:/YeonjaeLee/Cocos2d-x/03.Box2d/25_FlappyBird_2/Resources/Images/CaptureScreenTest.png";
		//utils::captureScreen(CC_CALLBACK_2(GameScene::afterCaptured, this), _filename);

		//this->pause();
		//Ground->pause();
		b2Vec2 gravity = b2Vec2(0.0f, -90.0f);
		_world->SetGravity(gravity);
	}
}

void GameScene::EndContact(b2Contact *contact)
{
	log("Contact:End");
}

void GameScene::PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
{
	log("Contact:PreSolve");
}

void GameScene::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse)
{
	log("Contact:PostSolve .. 1");

	b2Fixture *fixA = contact->GetFixtureA();
	b2Fixture *fixB = contact->GetFixtureB();

	b2Body *bodyA = fixA->GetBody();
	b2Body *bodyB = fixB->GetBody();

	if (bodyA->GetType() == b2_dynamicBody || bodyB->GetType() == b2_staticBody)
	{
		log("Contact:impulse .. %f", impulse->normalImpulses[0]);
		//Bird->pause();
		auto pScene = GameoverScene::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(0.5, pScene, Color3B::WHITE));

	}
}

//void GameScene::afterCaptured(bool succeed, const std::string& outputFile)
//{
//	if (succeed)
//	{
//		auto sp = Sprite::create(outputFile);
//		addChild(sp, 1, childTag);
//		sp->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
//		sp->setScale(3);
//
//		_filename = outputFile;
//	}
//	else
//	{
//		log("Capture screen failed.");
//	}
//}