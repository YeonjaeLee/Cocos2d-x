﻿#include "HelloWorldScene.h"

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

	// 메뉴의 위치는 Point::ZERO로 지정해두고
	// 각 메뉴 아이템의 위치를 지정하는 방법

	// 메뉴레이어 <-- 눈에 보이지 않는다.
	// 디폴트포인트 : (240, 160)  --> (0, 0)으로 바꾼다.

	// 메뉴 아이템 생성 및 초기화
	auto pMenuItem = MenuItemImage::create(
		"Images/btn-play-normal.png",
		"Images/btn-play-selected.png",
		CC_CALLBACK_1(HelloWorld::menuSelect, this));

	// 메뉴 아이템 위치 지정
	pMenuItem->setPosition(Vec2(100, 100));
	pMenuItem->setAnchorPoint(Vec2(0, 0));

	// 메뉴 생성
	auto pMenu = Menu::create(pMenuItem, nullptr);

	// 메뉴 위치 지정
	pMenu->setPosition(Vec2::ZERO);
	pMenu->setAnchorPoint(Vec2(0, 0));

	//pMenu->setPosition(Vec2(0, 0));

	// 레이어에 메뉴 객체 추가
	this->addChild(pMenu);

	return true;
}

void HelloWorld::menuSelect(Object* pSender)
{
	log("메뉴가 선택되었습니다.");
}