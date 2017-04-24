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
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}
	/////////////////////////////////////////////

	// 람다 함수 타입
	auto pLabel = LabelTTF::create(
		"블럭을 터치해서 드래그 하세요",
		"Arial",
		20);
	pLabel->setPosition(Vec2(240, 280));
	pLabel->setFontFillColor(Color3B(0, 0, 0));
	this->addChild(pLabel, 101);

	sprite1 = Sprite::create("Images/CyanSquare.png");
	sprite1->setPosition(Vec2(240, 160) + Vec2(-80, 80));
	this->addChild(sprite1);

	return true;
}

void HelloWorld::onEnter()
{
	Layer::onEnter();

	// 싱글 터치 모드로 등록
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	/*listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);*/

	// 람다 함수 형식을 이용해 터치에 타깃을 지정할 수 있다.
	listener->onTouchBegan = [=](Touch* touch, Event* event)
	{
		log("touch began...");

		auto target = static_cast<Sprite*>(event->getCurrentTarget());

		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);

		if (rect.containsPoint(locationInNode))
		{
			reZorder(target);

			log("sprite onTouchBegan... x = %f, y = %f", locationInNode.x, locationInNode.y);
			target->setOpacity(180);
			return true;
		}
		return false;
	};
	listener->onTouchMoved = [](Touch* touch, Event* event)
	{
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		target->setPosition(target->getPosition() + touch->getDelta());
	};

	listener->onTouchEnded = [](Touch* touch, Event* event)
	{
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		log("sprite onTouchesEnded...");
		target->setOpacity(255);
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, sprite1);
}

void HelloWorld::onExit()
{
	_eventDispatcher->removeAllEventListeners();

	Layer::onExit();
}

void HelloWorld::reZorder(Sprite* pSender)
{
	sprite1->setZOrder(0);

	pSender->setZOrder(1);
}
