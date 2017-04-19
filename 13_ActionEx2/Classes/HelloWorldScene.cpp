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
		CC_CALLBACK_1(HelloWorld::doReverse, this));
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
	this->ActionSequence(this);
}

void HelloWorld::ActionSequence(Ref* pSpender)
{
	auto action = Sequence::create(
		MoveBy::create(2, Vec2(400, 0)),
		RotateBy::create(2, 540),
		nullptr);

	pMan->runAction(action);
}

void HelloWorld::doReverse(Ref* pSender)
{
	// MoveTo	: 리버스 액션 동작 안함
	// JunpTo	: 리버스 액션 에러남
	// RotateTo	: 리버스 액션 에러남
	// ScaleTo	: 리버스 액션 에러남
	// TintTo	: 리버스 액션 에러남

//	auto myAction = MoveTo::create(2, Vec2(400, 0));
//	auto myAction = MoveBy::create(2, Vec2(400, 0));
//	auto myAction = JumpTo::create(2, Vec2(400, 0), 50, 3);
	auto myAction = JumpBy::create(2, Vec2(400, 0), 70, 3);

//	auto myAction = RotateTo::create(2, 270);
//	auto myAction = RotateBy::create(2, 270);

//	auto myAction = ScaleTo::create(2, 2.0);
//	auto myAction = ScaleBy::create(2, 2.0);

//	auto myAction = TintTo::create(2, 128, 128, 128);
//	auto myAction = TintBy::create(2, 0, -30, 30);

	auto myActionBack = myAction->reverse();
	pMan->runAction(myActionBack);
}