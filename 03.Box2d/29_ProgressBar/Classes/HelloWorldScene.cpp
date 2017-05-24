#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

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
	auto pMenuItem1 = MenuItemFont::create(" SpriteProgressToRadial ",
		CC_CALLBACK_1(HelloWorld::SpriteProgressToRadial, this));
	pMenuItem1->setColor(Color3B(255, 255, 255));

	auto pMenuItem2 = MenuItemFont::create(" SpriteProgressToHorizontal ",
		CC_CALLBACK_1(HelloWorld::SpriteProgressToHorizontal, this));
	pMenuItem2->setColor(Color3B(255, 255, 255));

	auto pMenuItem3 = MenuItemFont::create(" SpriteProgressToVertical ",
		CC_CALLBACK_1(HelloWorld::SpriteProgressToVertical, this));
	pMenuItem3->setColor(Color3B(255, 255, 255));

	auto pMenuItem4 = MenuItemFont::create(" SpriteProgressToRadialMidpointChanged ",
		CC_CALLBACK_1(HelloWorld::SpriteProgressToRadialMidpointChanged, this));
	pMenuItem4->setColor(Color3B(255, 255, 255));

	auto pMenuItem5 = MenuItemFont::create(" SpriteProgressBarVarious ",
		CC_CALLBACK_1(HelloWorld::SpriteProgressBarVarious, this));
	pMenuItem5->setColor(Color3B(255, 255, 255));

	auto pMenuItem6 = MenuItemFont::create(" SpriteProgressBarTintAndFade ",
		CC_CALLBACK_1(HelloWorld::SpriteProgressBarTintAndFade, this));
	pMenuItem6->setColor(Color3B(255, 255, 255));

	auto pMenu = Menu::create(pMenuItem1, pMenuItem2, pMenuItem3, pMenuItem4, pMenuItem5, pMenuItem6, NULL);

	pMenu->alignItemsVertically();

	this->addChild(pMenu);

	return true;
}

void HelloWorld::SpriteProgressToRadial(Ref* pSender)
{
	//	this->removeAllChildrenWithCleanup(true);

	this->removeChildByTag(1);
	this->removeChildByTag(2);
	this->removeChildByTag(3);

	pWoman1 = Sprite::create("bar.png");
	pWoman2 = Sprite::create("bar.png");

	auto to1 = ProgressTo::create(2, 100);
	auto to2 = ProgressTo::create(2, 100);

	auto left = ProgressTimer::create(pWoman1);
	left->setTag(1);
	left->setType(ProgressTimer::Type::RADIAL);
	this->addChild(left);
	left->setPosition(Point(140, 160));
	left->runAction(RepeatForever::create(to1));

	auto right = ProgressTimer::create(pWoman2);
	right->setTag(2);
	right->setType(ProgressTimer::Type::RADIAL);

	//Makes the ridial CCW
	right->setReverseProgress(true);
	this->addChild(right);
	right->setPosition(Point(340, 160));
	right->runAction(RepeatForever::create(to2));
}

void HelloWorld::SpriteProgressToHorizontal(Ref* pSender)
{
	//	this->removeAllChildrenWithCleanup(true);

	this->removeChildByTag(1);
	this->removeChildByTag(2);
	this->removeChildByTag(3);

	pWoman1 = Sprite::create("bar.png");
	pWoman2 = Sprite::create("bar.png");

	auto to1 = ProgressTo::create(2, 100);
	auto to2 = ProgressTo::create(2, 100);

	auto left = ProgressTimer::create(pWoman1);
	left->setTag(1);
	left->setType(ProgressTimer::Type::BAR);

	left->setMidpoint(Point(0, 0));
	left->setBarChangeRate(Point(1, 0));

	this->addChild(left);

	left->setPosition(Point(140, 160));
	left->runAction(RepeatForever::create(to1));

	auto right = ProgressTimer::create(pWoman2);
	right->setTag(2);
	right->setType(ProgressTimer::Type::BAR);

	right->setMidpoint(Point(1, 0));
	right->setBarChangeRate(Point(1, 0));

	this->addChild(right);
	right->setPosition(Point(340, 160));
	right->runAction(RepeatForever::create(to2));
}

void HelloWorld::SpriteProgressToVertical(Ref* pSender)
{
	//	this->removeAllChildrenWithCleanup(true);

	this->removeChildByTag(1);
	this->removeChildByTag(2);
	this->removeChildByTag(3);

	pWoman1 = Sprite::create("bar.png");
	pWoman2 = Sprite::create("bar.png");

	auto to1 = ProgressTo::create(2, 100);
	auto to2 = ProgressTo::create(2, 100);

	auto left = ProgressTimer::create(pWoman1);
	left->setTag(1);
	left->setType(ProgressTimer::Type::BAR);

	left->setMidpoint(Point(0, 0));
	left->setBarChangeRate(Point(0, 1));

	this->addChild(left);

	left->setPosition(Point(140, 160));
	left->runAction(RepeatForever::create(to1));

	auto right = ProgressTimer::create(pWoman2);
	right->setTag(2);
	right->setType(ProgressTimer::Type::BAR);

	right->setMidpoint(Point(0, 1));
	right->setBarChangeRate(Point(0, 1));

	this->addChild(right);
	right->setPosition(Point(340, 160));
	right->runAction(RepeatForever::create(to2));
}

void HelloWorld::SpriteProgressToRadialMidpointChanged(Ref* pSender)
{
	//	this->removeAllChildrenWithCleanup(true);

	this->removeChildByTag(1);
	this->removeChildByTag(2);
	this->removeChildByTag(3);

	pWoman1 = Sprite::create("bar.png");
	pWoman2 = Sprite::create("bar.png");

	auto to1 = ProgressTo::create(2, 100);
	auto to2 = ProgressTo::create(2, 100);

	auto left = ProgressTimer::create(pWoman1);
	left->setTag(1);
	left->setType(ProgressTimer::Type::RADIAL);

	left->setMidpoint(Point(0.25f, 0.75f));

	this->addChild(left);

	left->setPosition(Point(140, 160));
	left->runAction(RepeatForever::create(to1));

	auto right = ProgressTimer::create(pWoman2);
	right->setTag(2);
	right->setType(ProgressTimer::Type::RADIAL);

	right->setMidpoint(Point(0.75f, 0.25f));

	this->addChild(right);
	right->setPosition(Point(340, 160));
	right->runAction(RepeatForever::create(to2));
}

void HelloWorld::SpriteProgressBarVarious(Ref* pSender)
{
	//	this->removeAllChildrenWithCleanup(true);

	this->removeChildByTag(1);
	this->removeChildByTag(2);
	this->removeChildByTag(3);

	pWoman1 = Sprite::create("bar.png");
	pWoman2 = Sprite::create("bar.png");

	auto to1 = ProgressTo::create(2, 100);
	auto to2 = ProgressTo::create(2, 100);
	auto to3 = ProgressTo::create(2, 100);

	auto left = ProgressTimer::create(pWoman1);
	left->setTag(1);
	left->setType(ProgressTimer::Type::BAR);

	left->setMidpoint(Point(0.5f, 0.5f));
	left->setBarChangeRate(Point(1, 0));
	this->addChild(left);

	left->setPosition(Point(140, 160));
	left->runAction(RepeatForever::create(to1));

	auto middle = ProgressTimer::create(pWoman2);
	middle->setTag(2);
	middle->setType(ProgressTimer::Type::BAR);

	middle->setMidpoint(Point(0.5f, 0.5f));
	middle->setBarChangeRate(Point(1, 1));

	this->addChild(middle);
	middle->setPosition(Point(240, 160));
	middle->runAction(RepeatForever::create(to2));

	auto right = ProgressTimer::create(pWoman1);
	right->setTag(3);
	right->setType(ProgressTimer::Type::BAR);

	right->setMidpoint(Point(0.5f, 0.5f));
	right->setBarChangeRate(Point(0, 1));

	this->addChild(right);
	right->setPosition(Point(340, 160));
	right->runAction(RepeatForever::create(to3));
}

void HelloWorld::SpriteProgressBarTintAndFade(Ref* pSender)
{
	//	this->removeAllChildrenWithCleanup(true);

	this->removeChildByTag(1);
	this->removeChildByTag(2);
	this->removeChildByTag(3);

	pWoman1 = Sprite::create("bar.png");
	pWoman2 = Sprite::create("bar.png");

	auto to = ProgressTo::create(6, 100);

	auto tint = Sequence::create(TintTo::create(1, 255, 0, 0), TintTo::create(1, 0, 255, 0), TintTo::create(1, 0, 0, 255), NULL);

	auto fade = Sequence::create(FadeTo::create(1.0f, 0), FadeTo::create(1.0f, 255), NULL);

	auto left = ProgressTimer::create(pWoman1);
	left->setTag(1);
	left->setType(ProgressTimer::Type::BAR);

	left->setMidpoint(Point(0.5f, 0.5f));
	left->setBarChangeRate(Point(1, 0));
	this->addChild(left);

	left->setPosition(Point(140, 160));
	left->runAction(RepeatForever::create(to->clone()));
	left->runAction(RepeatForever::create(tint->clone()));

	left->addChild(Label::createWithTTF("Tint", "NanumPen.ttf", 20, Size(0, 0), TextHAlignment::CENTER, TextVAlignment::CENTER));

	auto middle = ProgressTimer::create(pWoman2);
	middle->setTag(2);
	middle->setType(ProgressTimer::Type::BAR);

	middle->setMidpoint(Point(0.5f, 0.5f));
	middle->setBarChangeRate(Point(1, 1));

	this->addChild(middle);
	middle->setPosition(Point(240, 160));
	middle->runAction(RepeatForever::create(to->clone()));
	middle->runAction(RepeatForever::create(fade->clone()));

	middle->addChild(Label::createWithTTF("Fade", "NanumPen.ttf", 20, Size(0, 0), TextHAlignment::CENTER, TextVAlignment::CENTER));

	auto right = ProgressTimer::create(pWoman1);
	right->setTag(3);
	right->setType(ProgressTimer::Type::BAR);

	right->setMidpoint(Point(0.5f, 0.5f));
	right->setBarChangeRate(Point(0, 1));

	this->addChild(right);
	right->setPosition(Point(340, 160));
	right->runAction(RepeatForever::create(to->clone()));
	right->runAction(RepeatForever::create(tint->clone()));
	right->runAction(RepeatForever::create(fade->clone()));

	right->addChild(Label::createWithTTF("Tint and Fade", "NanumPen.ttf", 20, Size(0, 0), TextHAlignment::CENTER, TextVAlignment::CENTER));
}
