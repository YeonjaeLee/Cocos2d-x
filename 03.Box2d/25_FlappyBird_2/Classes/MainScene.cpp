#include "MainScene.h"
#include "GameScene.h"

USING_NS_CC;

Scene* MainScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MainScene::create();
	scene->addChild(layer);
	return scene;
}

bool MainScene::init()
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

	Sprite* bg = Sprite::create("Images/bg.png");
	bg->setPosition(Vec2(0, 0));
	bg->setAnchorPoint(Vec2(0, 0));
	this->addChild(bg);

	auto Logo = Sprite::createWithSpriteFrameName("flappybird.png");
	Logo->setPosition(Vec2(winSize.width / 2 + 20, winSize.height / 2 + 200));
	this->addChild(Logo);

	auto Ground = Sprite::create("Images/ground.png");
	Ground->setPosition(Vec2(0, 0));
	Ground->setAnchorPoint(Vec2(0, 0));
	auto forward = MoveBy::create(1.0f, Vec2(-120, 0));
	auto myActionReplay = Place::create(Vec2(0, 0));
	auto myAction = Sequence::create(forward, myActionReplay, nullptr);
	auto rep = RepeatForever::create(myAction);
	Ground->runAction(rep);
	this->addChild(Ground);

	this->createBird();

	position1 = Vec2(winSize.width / 2 - 150, winSize.height / 2 - 300);
	StartButton = Sprite::createWithSpriteFrameName("start.png");
	StartButton->setPosition(position1);
	this->addChild(StartButton);

	position2 = Vec2(winSize.width / 2 + 150, winSize.height / 2 - 300);
	GradeButton = Sprite::createWithSpriteFrameName("grade.png");
	GradeButton->setPosition(position2);
	this->addChild(GradeButton);

	position3 = Vec2(winSize.width / 2, winSize.height / 2 - 90);
	RateButton = Sprite::createWithSpriteFrameName("rate.png");
	RateButton->setPosition(position3);
	this->addChild(RateButton);

	return true;
}

void MainScene::createBird()
{
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
}

void MainScene::onEnter()
{
	Layer::onEnter();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(MainScene::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(MainScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void MainScene::onExit()
{
	//_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
	Layer::onExit();
}

bool MainScene::onTouchBegan(Touch* touch, Event* event)
{
	log("클릭");
	return true;
}

void MainScene::onTouchEnded(Touch* touch, Event* event)
{
	auto touchPoint = touch->getLocation();
	touchPoint = this->convertToNodeSpace(touchPoint);
	log("클릭position(%f, %f)", touchPoint.x, touchPoint.y);

	if ((touchPoint.x > position1.x - 130 && touchPoint.x < position1.x + 120) && (touchPoint.y > position1.y - 60 && touchPoint.y < position1.y + 90))
	{
		log("play 버튼 클릭. ");
		auto myActionMove = MoveBy::create(0.1f, Vec2(0, -10));
		auto myActionBack = myActionMove->reverse();
		auto myAction = Sequence::create(myActionMove, myActionBack, nullptr);
		StartButton->runAction(myAction);

		auto pScene = GameScene::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(0.5, pScene, Color3B::WHITE));
	}
	else if ((touchPoint.x > position2.x - 130 && touchPoint.x < position2.x + 120) && (touchPoint.y > position2.y - 60 && touchPoint.y < position2.y + 90))
	{
		log("grade 버튼 클릭. ");
		auto myActionMove = MoveBy::create(0.1f, Vec2(0, -10));
		auto myActionBack = myActionMove->reverse();
		auto myAction = Sequence::create(myActionMove, myActionBack, nullptr);
		GradeButton->runAction(myAction);
	}
	else if ((touchPoint.x > position3.x - 80 && touchPoint.x < position3.x + 70) && (touchPoint.y > position3.y - 40 && touchPoint.y < position3.y + 40))
	{
		log("rate 버튼 클릭. ");
		auto myActionMove = MoveBy::create(0.1f, Vec2(0, -10));
		auto myActionBack = myActionMove->reverse();
		auto myAction = Sequence::create(myActionMove, myActionBack, nullptr);
		RateButton->runAction(myAction);
	}
}
