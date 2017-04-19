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

	MenuItemFont::setFontSize(28);

	auto pMenuItem = MenuItemFont::create(
		"Action",
		CC_CALLBACK_1(HelloWorld::doAction, this));
	pMenuItem->setColor(Color3B(0, 0, 0));

	// 메뉴 생성
	auto pMenu = Menu::create(pMenuItem, nullptr);

	// 메뉴 배치
	pMenu->alignItemsHorizontally();

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
	// 회전 목적지가 제자리이므로 회전하지 않는다.
	auto myAction = RotateTo::create(2, 360);

	//// 가까운 쪽으로 회전 방향이 자동으로 결정된다.
	//auto myAction = RotateTo::create(2, 90);
	//auto myAction = RotateTo::create(2, 180);
	//auto myAction = RotateTo::create(2, 270);

//	auto myAction = MoveBy::create(2, Vec2(400, 0));

	pMan->runAction(myAction);
}