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


	// 동그란 버튼 스프라이트 추가
	pBall = Sprite::create("Images/r1.png");
	pBall->setPosition(Vec2(50, 100));
	pBall->setScale(0.7f);
	this->addChild(pBall);

	// Grossini 씨의 스프라이트 추가
	pMan = Sprite::create("Images/grossini.png");
	pMan->setPosition(Vec2(50, 150));
	pMan->setScale(0.5f);
	this->addChild(pMan);

	// Grossini 씨의 sister1 스프라이트 추가
	pWoman1 = Sprite::create("Images/grossinis_sister1.png");
	pWoman1->setPosition(Vec2(50, 220));
	pWoman1->setScale(0.5f);
	this->addChild(pWoman1);

	// Grossini 씨의 sister2 스프라이트 추가
	pWoman2 = Sprite::create("Images/grossinis_sister2.png");
	pWoman2->setPosition(Vec2(50, 280));
	pWoman2->setScale(0.5f);
	this->addChild(pWoman2);

	return true;
}

void HelloWorld::doAction(Ref* pSender)
{
	doActionReset();
	// 정상 속도
	auto move = MoveBy::create(3.0f, Vec2(400, 0));

/*
	// 속도-------------------------------------------
	// 빨라지기 : 시작이 늦고 나중에 빠름
	auto ease_in	= EaseIn::create(move->clone(), 4.0f);
	// 느려지기 : 시작이 빠르고 나중에 늦음
	auto ease_out	= EaseOut::create(move->clone(), 4.0f);
	// 빨라졌다 느려지기 : 시작과 끝이 느리고 중간이 빠름
	auto ease_inout1 = EaseInOut::create(move->clone(), 4.0f);

//	auto ease_inout2 = EaseInOut::create(move->clone(), 3.0f);
//	auto ease_inout3 = EaseInOut::create(move->clone(), 1.0f);

	// 탄성---------------------------------------------
	// 시작 부분 탄성
	auto ease_in	= EaseElasticIn::create(move->clone(), 0.4f);
	// 끝 부분 탄성
	auto ease_out	= EaseElasticOut::create(move->clone(), 0.4f);
	// 시작 부분과 끝 부분 탄성
	auto ease_inout1 = EaseElasticInOut::create(move->clone(), 0.4f);

	// 바운스-------------------------------------------------
	// 시작 부분 바운스
	auto ease_in = EaseBounceIn::create(move->clone());
	// 끝 부분 바운스
	auto ease_out = EaseBounceOut::create(move->clone());
	// 시작 부분과 끝 부분 바운스
	auto ease_inout1 = EaseBounceInOut::create(move->clone());
*/
	// 1배 빠르게 - 같은 속도
	auto ease_in = Speed::create(move->clone(), 1.0f);
	// 2배 빠르게
	auto ease_out = Speed::create(move->clone(), 2.0f);
	// 3배 빠르게
	auto ease_inout1 = Speed::create(move->clone(), 3.0f);

	pBall->runAction(move);
	pMan->runAction(ease_in);
	pWoman1->runAction(ease_out);
	pWoman2->runAction(ease_inout1);
	
}

void HelloWorld::doActionReset()
{
	pBall->setPosition(Vec2(50, 100));
	pBall->setScale(0.7f);

	pMan->setPosition(Vec2(50, 150));
	pMan->setScale(0.5f);

	pWoman1->setPosition(Vec2(50, 220));
	pWoman1->setScale(0.5f);

	pWoman2->setPosition(Vec2(50, 280));
	pWoman2->setScale(0.5f);
}