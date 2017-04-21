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
	if (!LayerColor::initWithColor(Color4B(0, 0, 0, 0)))
	{
		return false;
	}
	/////////////////////////////////////////////

	srand((int)time(NULL));
	nRanNum = rand() % 3 + 1;

	grass_upper = Sprite::create("Images/grass_upper.png");
	grass_upper->setAnchorPoint(Vec2(1, 1));
	grass_upper->setPosition(Vec2(480, 320));
	grass_upper->setTag(99);
	this->addChild(grass_upper);

	mole_1 = Sprite::create("Images/mole_1.png");
	mole_1->setVisible(false);
	mole_1->setTag(1);
	this->addChild(mole_1);

	mole_2 = Sprite::create("Images/mole_1.png");
	mole_2->setVisible(false);
	mole_2->setTag(2);
	this->addChild(mole_2);

	mole_3 = Sprite::create("Images/mole_1.png");
	mole_3->setVisible(false);
	mole_3->setTag(3);
	this->addChild(mole_3);

	this->schedule(schedule_selector(HelloWorld::callEveryFrame), 2.0f);

	grass_lower = Sprite::create("Images/grass_lower.png");
	grass_lower->setAnchorPoint(Vec2(0, 0));
	grass_lower->setPosition(Vec2(0, 0));
	grass_lower->setTag(98);
	this->addChild(grass_lower, 2);

	return true;
}

void HelloWorld::callEveryFrame(float f)
{
	// ox = 0: 작동안함, ox = 1: 일어남
	do
	{
		ox1 = rand() % 2;
		ox2 = rand() % 2;
		ox3 = rand() % 2;
	} while (ox1 == ox2 && ox1 == ox3);
	log("ox1: %d, ox2: %d, ox3: %d", ox1, ox2, ox3);

	if (ox1 == 1)
	{
		this->doAction_mole_1(this);
	}
	if (ox2 == 1)
	{
		this->doAction_mole_2(this);
	}
	if (ox3 == 1)
	{
		this->doAction_mole_3(this);
	}

}

void HelloWorld::doAction_mole_1(Ref* pSender)
{
	mole_1->removeAllChildrenWithCleanup(true);

	mole_1 = Sprite::create("Images/mole_1.png");
	mole_1->setPosition(Vec2(93, 50));
	this->addChild(mole_1);

	this->ActionRepeatForever_mole_1(this);
}

void HelloWorld::ActionRepeatForever_mole_1(Ref* pSender)
{
	//nRanNum = rand() % 3 + 1;

	auto myActionForward = MoveBy::create(0.5, Vec2(0, 130));
	auto myActionBack = myActionForward->reverse();
	auto myAction = Sequence::create(myActionForward, myActionBack, Hide::create(), nullptr);

	mole_1->runAction(myAction);
}

void HelloWorld::doAction_mole_2(Ref* pSender)
{
	mole_2->removeAllChildrenWithCleanup(true);

	mole_2 = Sprite::create("Images/mole_1.png");
	mole_2->setPosition(Vec2(240, 50));
	this->addChild(mole_2);

	this->ActionRepeatForever_mole_2(this);
}

void HelloWorld::ActionRepeatForever_mole_2(Ref* pSender)
{
	//nRanNum = rand() % 3 + 1;

	auto myActionForward = MoveBy::create(0.5, Vec2(0, 130));
	auto myActionBack = myActionForward->reverse();
	auto myAction = Sequence::create(myActionForward, myActionBack, Hide::create(), nullptr);

	mole_2->runAction(myAction);
}

void HelloWorld::doAction_mole_3(Ref* pSender)
{
	mole_3->removeAllChildrenWithCleanup(true);

	mole_3 = Sprite::create("Images/mole_1.png");
	mole_3->setPosition(Vec2(384, 50));
	this->addChild(mole_3);

	this->ActionRepeatForever_mole_3(this);
}

void HelloWorld::ActionRepeatForever_mole_3(Ref* pSender)
{
	//nRanNum = rand() % 3 + 1;

	auto myActionForward = MoveBy::create(0.5, Vec2(0, 130));
	auto myActionBack = myActionForward->reverse();
	auto myAction = Sequence::create(myActionForward, myActionBack, Hide::create(), nullptr);

	mole_3->runAction(myAction);
}
