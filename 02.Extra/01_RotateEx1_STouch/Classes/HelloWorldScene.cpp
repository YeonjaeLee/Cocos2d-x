﻿#include "HelloWorldScene.h"

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

	pMan = Sprite::create("Images/grossini.png");
	pMan->setPosition(Vec2(240, 160));
	this->addChild(pMan);

	bSelect = false;

	return true;
}

void HelloWorld::onEnter()
{
	Layer::onEnter();

	// 싱글터치모드로 터치리스너 등록
	auto listener = EventListenerTouchOneByOne::create();
	// Swallow touches only available in OneByOne mode.
	// 핸들링된 터치 이벤트를 터치 이벤트 array에서 지우겠다는 의미이다.
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

	// The priority of the touch listener is based on the draw order of sprite
	// 터치리스너의 우선순위를 (노드가) 화면에 그려진 순서대로 한다.
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void HelloWorld::onExit()
{
	_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);

	Layer::onExit();
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
	auto touchPoint = touch->getLocation();
	bSelect = pMan->getBoundingBox().containsPoint(touchPoint);

	return true;
}

void HelloWorld::onTouchMoved(Touch* touch, Event* event)
{
	if (bSelect)
	{
		Point oldPoint = touch->getPreviousLocation();
		Point nowPoint = touch->getLocation();

		Point firstVector = oldPoint - pMan->getPosition();
		float firstRotateAngle = -firstVector.getAngle();
		float previousTouch = CC_RADIANS_TO_DEGREES(firstRotateAngle);

		Point secondVector = nowPoint - pMan->getPosition();
		float secondRotateAngle = -secondVector.getAngle();
		float currentTouch = CC_RADIANS_TO_DEGREES(secondRotateAngle);

		gRotation = gRotation + currentTouch - previousTouch;
		gRotation = fmod(gRotation, 360.0f);

		pMan->setRotation(gRotation);
	}
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{
	bSelect = false;
}