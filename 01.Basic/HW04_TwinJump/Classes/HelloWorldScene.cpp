#include "HelloWorldScene.h"

USING_NS_CC;

/*
추가사항 :
2단 점프만 되게 할 것 (3단 점프 안됨)
내려오는 중에는 터치에 의해 다시 점프되지 않게 할 것
.
응용 :
내려올 때라도 어느 높이 이상이면 점프가 될 수 있게 한다.

*/

Scene* HelloWorld::createScene()
{
	auto scene = Scene::create();
	auto layer = HelloWorld::create();
	scene->addChild(layer);
	return scene;
}

bool HelloWorld::init()
{
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}
	/////////////////////////////////////////////

	auto batch = SpriteBatchNode::create("animations/player2.png", 50);
	auto texture = batch->getTexture();
	
	auto animation = Animation::create();
	animation->setDelayPerUnit(0.05f);

	for (int i = 0; i < 19; i++)
	{
		int column = i % 19;
		int row = i / 19;

		animation->addSpriteFrameWithTexture(
			texture,
			Rect(column * 30, row * 30, 30, 30));
	}
	// ok
	// 스프라이트 생성 및 초기화
	pMan = Sprite::createWithTexture(texture, Rect(0, 0, 30, 30));
	pMan->setPosition(Vec2(100, 100));
//	pMan->setTag(1);
	pMan->setScale(1.7f);
	
	this->addChild(pMan);

	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);
	pMan->runAction(rep);

	yValue = 0;
	nJumpCount = 0;
	this->schedule(schedule_selector(HelloWorld::myTick), 1.0f / 60);

	return true;
}

void HelloWorld::onEnter()
{
	Layer::onEnter();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void HelloWorld::onExit()
{
	_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);

	Layer::onExit();
}
// ok
bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
	if (yValue < 0)
	{
		return false;
	}
	this->doJump();

	return true;
}
// ok
void HelloWorld::doJump()
{
	nJumpCount++;
	
	if (nJumpCount == 1 || nJumpCount == 2)
	{
		yValue = 10;
	}
}

void HelloWorld::onTouchMoved(Touch* touch, Event* event)
{
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{
}
// ok
void HelloWorld::myTick(float f)
{
	if (nJumpCount == 0)
	{
		return;
	}

	pMan->setPosition(Vec2(pMan->getPosition().x, pMan->getPosition().y + yValue));
	log("y: %f, yValue: %f", pMan->getPosition().y, yValue);
	if (pMan->getPosition().y > 100)
	{
		// y축이 100보다 높을때 yValue값을 0.5씩 뺀다.
		yValue = yValue - 0.5f;
		if (yValue == 0)
		{
			log("3. %f", pMan->getPosition().y);
		}
	}
	else
	{
		// y축이 100밑으로 떨어지지 않게 보정
		yValue = 0;
		nJumpCount = 0;
		pMan->setPosition(Vec2(pMan->getPosition().x, 100));
	}
}