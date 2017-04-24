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

	// 메뉴 아이템 생성 및 초기화
	auto pMenuItem1 = MenuItemImage::create(
		"Images/btn-play-normal.png",
		"Images/btn-play-selected.png",
		CC_CALLBACK_1(HelloWorld::doClick1, this));	// CC_CALLBACK_1 필수 1파라미터

	auto pMenuItem2 = MenuItemImage::create(
		"Images/btn-play-normal.png",
		"Images/btn-play-selected.png",
		CC_CALLBACK_1(HelloWorld::doClick2, this));

	auto pMenuItem3 = MenuItemImage::create(
		"Images/btn-play-normal.png",
		"Images/btn-play-selected.png",
		CC_CALLBACK_1(HelloWorld::doClick3, this));

	// 메뉴 생성
	auto pMenu = Menu::create(pMenuItem1, pMenuItem2, pMenuItem3, NULL);

	// 메뉴 배치
	pMenu->alignItemsVertically();

	// 레이어에 메뉴 객체 추가
	this->addChild(pMenu);

	return true;
}

void HelloWorld::doClick1(Ref* pSender)
{
	log("첫번째 메뉴가 선택되었습니다.");
}

void HelloWorld::doClick2(Ref* pSender)
{
	log("두번째 메뉴가 선택되었습니다.");
}

void HelloWorld::doClick3(Ref* pSender)
{
	log("세번째 메뉴가 선택되었습니다.");
}