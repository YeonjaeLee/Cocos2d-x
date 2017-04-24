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

	// 메뉴 아이템 생성 및 초기화
	auto item1 = MenuItemFont::create(
		"start",
		CC_CALLBACK_1(HelloWorld::doStart, this));
	item1->setColor(Color3B(0, 0, 0));

	auto item2 = MenuItemFont::create(
		"pause",
		CC_CALLBACK_1(HelloWorld::doPause, this));
	item2->setColor(Color3B(0, 0, 0));

	auto item3 = MenuItemFont::create(
		"resume",
		CC_CALLBACK_1(HelloWorld::doResume, this));
	item3->setColor(Color3B(0, 0, 0));

	auto item4 = MenuItemFont::create(
		"change",
		CC_CALLBACK_1(HelloWorld::doChange, this));
	item4->setColor(Color3B(0, 0, 0));

	auto item5 = MenuItemFont::create(
		"stop",
		CC_CALLBACK_1(HelloWorld::doStop, this));
	item5->setColor(Color3B(0, 0, 0));

	// 메뉴 생성
	auto pMenu = Menu::create(item1, item2, item3, item4, item5, nullptr);

	// 세로로 정렬
	pMenu->alignItemsVertically();

	// 레이어에 메뉴 객체 추가
	this->addChild(pMenu);
	bChange = false;

	return true;
}

void HelloWorld::doStart(Ref* pSender)
{
	this->schedule(schedule_selector(HelloWorld::tick1), 1.0f);
	this->schedule(schedule_selector(HelloWorld::tick2), 2.0f);
}

void HelloWorld::doPause(Ref* pSender)
{
	Director::getInstance()->getScheduler()->pauseTarget(this);
}

void HelloWorld::doResume(Ref* pSender)
{
	Director::getInstance()->getScheduler()->resumeTarget(this);
}

void HelloWorld::doChange(Ref* pSender)
{
	if (bChange) {
		bChange = false;
		this->unschedule(schedule_selector(HelloWorld::tick2));
		this->schedule(schedule_selector(HelloWorld::tick2), 2.0f);
	}
	else {
		bChange = true;

		this->unschedule(schedule_selector(HelloWorld::tick2));
		this->schedule(schedule_selector(HelloWorld::tick2), 3.0f);
	}
}

void HelloWorld::doStop(Ref* pSender)
{
	this->unschedule(schedule_selector(HelloWorld::tick1));
	this->unschedule(schedule_selector(HelloWorld::tick2));
}

void HelloWorld::tick1(float f)
{
	log("tick1");
}

void HelloWorld::tick2(float f)
{
	log("tick2");
}