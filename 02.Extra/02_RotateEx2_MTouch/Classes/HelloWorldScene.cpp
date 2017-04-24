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

	pMan = Sprite::create("Images/grossini.png");
	pMan->setPosition(Vec2(240, 160));
	pMan->setScale(1.5);
	this->addChild(pMan);

	pLabel1 = LabelTTF::create("0", "Arial", 64);
	pLabel1->setPosition(Vec2(100, 100));
	pLabel1->setColor(Color3B::BLACK);
	this->addChild(pLabel1);

	pLabel2 = LabelTTF::create("0", "Arial", 64);
	pLabel2->setPosition(Vec2(200, 100));
	pLabel2->setColor(Color3B::BLACK);
	this->addChild(pLabel2);

	bSelect = false;
	i = 0;

	return true;
}

void HelloWorld::onEnter()
{
	Layer::onEnter();

	// 멀티터치모드로 터치리스너 등록
	auto listener = EventListenerTouchAllAtOnce::create();

	listener->onTouchesBegan = CC_CALLBACK_2(HelloWorld::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(HelloWorld::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(HelloWorld::onTouchesEnded, this);

	// The priority of the touch listener is based on the draw order of sprite
	// 터치리스너의 우선순위를 (노드가) 화면에 그려진 순서대로 한다.
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void HelloWorld::onExit()
{
	_eventDispatcher->removeAllEventListeners();

	Layer::onExit();
}

void HelloWorld::onTouchesBegan(const std::vector<Touch*>& touches, Event *event)
{
	bSelect = false;

	char myNum1[20] = { 0 };
	sprintf(myNum1, "%lu", touches.size());
	pLabel1->setString(myNum1);

	//if ((int)touches.size() < 2)
	//{
	//	return;
	//}

	for (auto &item : touches)
	{
		auto touch = item;
		auto touchPoint = touch->getLocation();
		/*log("Touch x:%d y:%d", (int)touchPoint.x, (int)touchPoint.y);*/
	
		Rect rect = pMan->getBoundingBox();
		if (rect.containsPoint(touchPoint))
		{
			log("Touch x:%d y:%d", (int)touchPoint.x, (int)touchPoint.y);
			i++;
		}
	}

	char myNum2[20] = { 0 };
	sprintf(myNum2, "%d", i);
	pLabel2->setString(myNum2);

	if (i > 1)
	{
		bSelect = true;
	}

}

void HelloWorld::onTouchesMoved(const std::vector<Touch*>& touches, Event *event)
{
	if (bSelect)
	{
		auto touch = touches[0];

		Point oldPoint = touch->getPreviousLocation();
		Point nowPoint = touch->getLocation();

		Point firstVector = oldPoint - pMan->getPosition();
		float firstRotateAngle = -firstVector.getAngle();
		float previousTouch = CC_RADIANS_TO_DEGREES(firstRotateAngle);

		Point secondVector = nowPoint - pMan->getPosition();
		float secondRotateAngle = -secondVector.getAngle();
		float currentTouch = CC_RADIANS_TO_DEGREES(secondRotateAngle);
	
		gRotation += currentTouch - previousTouch;
		gRotation = fmod(gRotation, 360.0f);

		pMan->setRotation(gRotation);
	}
}

void HelloWorld::onTouchesEnded(const std::vector<Touch*>& touches, Event *event)
{
	pLabel1->setString("0");
	pLabel2->setString("0");

	i = 0;
	bSelect = false;
}