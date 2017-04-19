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

	auto pMenuItem = MenuItemFont::create(
		"Action",
		CC_CALLBACK_1(HelloWorld::doAction, this));
	pMenuItem->setColor(Color3B(0, 0, 0));

	// 메뉴 생성
	auto pMenu = Menu::create(pMenuItem, nullptr);

	// 메뉴 위치 지정
	pMenu->setPosition(Vec2(240, 50));

	// 레이어에 메뉴 객체 추가
	this->addChild(pMenu);

	// Groosini 씨 스프라이트 추가
	pMan = Sprite::create("Images/grossini.png");
	pMan->setPosition(Vec2(50, 200));	// 좌표 지정
	this->addChild(pMan);

	return true;
}

void HelloWorld::doAction(Ref* pSender)
{
	// Grossini 씨 스프라이트 제거
	pMan->removeFromParentAndCleanup(true);

	// Grossini 씨 스프라이트 추가
	pMan = Sprite::create("Images/grossini.png");
	pMan->setPosition(Vec2(50, 160));	// 좌표 지정
	this->addChild(pMan);

	// 다음 함수 호출
	this->ActionSpawn(this);
}

void HelloWorld::ActionSequence(Ref* pSpender)
{
	auto action = Sequence::create(
		MoveBy::create(2, Vec2(400, 0)),
		RotateBy::create(2, 540),
		nullptr);

	pMan->runAction(action);
}

void HelloWorld::ActionSpawn(Ref* pSender)
{
	// 4초에 4번 점프(초당 1번 점프)
	// 회전은 2초만.
	// 그러므로 점프를 두 번 하는 동안 회전, 나머지는 그냥 점프만 한다.

	auto action = Spawn::create(
		JumpBy::create(4, Vec2(400, 0), 50, 4),
		RotateBy::create(2, 720),
		nullptr);

	pMan->runAction(action);
}

void HelloWorld::ActionReverse(Ref* pSender)
{
	auto action = MoveBy::create(2, Vec2(400, 0));
	auto reverseAction = action->reverse();

	pMan->runAction(reverseAction);
}

void HelloWorld::ActionRepeat(Ref* pSender)
{
	auto myActionForward = MoveBy::create(2, Vec2(400, 0));
	auto myActionBack = myActionForward->reverse();
	auto myAction = Sequence::create(myActionForward, myActionBack, nullptr);

	auto rep1 = Repeat::create(myAction, 3);

	pMan->runAction(rep1);
}

void HelloWorld::ActionRepeatForever(Ref* pSender)
{
	auto myActionForward = MoveBy::create(2, Vec2(400, 0));
	auto myActionBack = myActionForward->reverse();
	auto myAction = Sequence::create(myActionForward, myActionBack, nullptr);

	auto rep2 = RepeatForever::create(myAction);

	pMan->runAction(rep2);
}

void HelloWorld::ActionDelayTime(Ref* pSender)
{
	auto act1 = RotateTo::create(1, 150));
	auto act2 = RotateTo::create(1, 0));

	auto myAction = Sequence::create(
		act1, 
		DelayTime::create(2),
		act2,
		DelayTime::create(1),
		nullptr);

	auto rep2 = RepeatForever::create(myAction);

	pMan->runAction(rep1);
}