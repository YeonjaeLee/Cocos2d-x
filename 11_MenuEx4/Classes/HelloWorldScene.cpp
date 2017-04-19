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
	auto pMenuItem1 = MenuItemFont::create(
		"Menu-1",
		CC_CALLBACK_1(HelloWorld::doClick, this));
	pMenuItem1->setColor(Color3B::BLACK);

	auto pMenuItem2 = MenuItemFont::create(
		"Menu-2",
		CC_CALLBACK_1(HelloWorld::doClick, this));
	pMenuItem2->setColor(Color3B::BLACK);

	pMenuItem1->setTag(1);
	pMenuItem2->setTag(2);

	// 메뉴 생성
	auto pMenu = Menu::create(pMenuItem1, pMenuItem2, nullptr);

	// 메뉴 배치
	pMenu->alignItemsVertically();

	// 레이어에 메뉴 객체 추가
	this->addChild(pMenu);

	return true;
}

void HelloWorld::doClick(Ref* pSender)
{
	// 두 번 연속 눌리는 것에 대한 방지 코드는 추가해야 한다.

	auto tItem = (MenuItem *)pSender;
	int i = tItem->getTag();

	if (i == 1)
	{
		// 1번 메뉴가 눌렸고, child 스프라이트를 추가한다
		auto pMan = Sprite::create("Images/grossini.png");

		pMan->setPosition(Vec2(100, 160));	// 좌표 지정
		pMan->setTag(11);					// 태그 지정

		this->addChild(pMan);
	}
	else
	{
		// 2번 메뉴가 눌렸고 추가했던 차일드 스프라이트를 제거한다.
		// 태그로 스프라이트 찾기
		auto pMan = (Sprite*)getChildByTag(11);

		// 스프라이트 제거
		this->removeChild(pMan, true);

		// 스프라이트 제거 by 태그
		// this->removeChildByTag(11, true);
	}
}