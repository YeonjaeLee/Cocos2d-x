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

	// Grossini 씨 스프라이트 추가
	pMan = Sprite::create("Images/grossini.png");
	pMan->setPosition(Vec2(50, 160));
	this->addChild(pMan);

	return true;
}

void HelloWorld::doAction(Ref* pSender)
{
	// Grossini 씨 스프라이트 제거
	pMan->removeFromParentAndCleanup(true);

	// 태그로 레이블 제거
	this->removeChildByTag(1, true);
	this->removeChildByTag(2, true);
	this->removeChildByTag(3, true);

	// Grossini 씨 스프라이트 추가
	pMan = Sprite::create("Images/grossini.png");
	pMan->setPosition(Vec2(50, 160));
	pMan->setTag(5);
	this->addChild(pMan);

	pMan->setVisible(false);
	
	auto action = Sequence::create(
		Place::create(Vec2(200, 200)),
		DelayTime::create(1.0),
		Show::create(),
		MoveBy::create(1, Vec2(200, 0)),
		CallFunc::create(CC_CALLBACK_0(HelloWorld::callback1, this)),
		CallFunc::create(CC_CALLBACK_0(HelloWorld::callback2, this, pMan)),
		CallFunc::create(CC_CALLBACK_0(HelloWorld::callback3, this, pMan, 42)),
		nullptr);

	pMan->runAction(action);
}

#pragma mark -
#pragma mark Callback Functions

void HelloWorld::callback1()
{
	auto label = LabelTTF::create("callback 1 called", "Marker Felt", 16);
	label->setPosition(Vec2(120, 160));
	label->setColor(Color3B::BLACK);
	label->setTag(1);

	this->addChild(label);
}

void HelloWorld::callback2(Node* sender)
{
	auto label = LabelTTF::create("callback 2 called", "Marker Felt", 16);
	label->setPosition(Vec2(240, 140));
	label->setColor(Color3B::RED);
	label->setTag(2);

	this->addChild(label);

	auto tItem = (Sprite *)sender;
	int i = tItem->getTag();
	log("tag num : %d", i);
}

void HelloWorld::callback3(Node* sender, long data)
{
	auto label = LabelTTF::create("callback 3 called", "Marker Felt", 16);
	label->setPosition(Vec2(360, 120));
	label->setColor(Color3B::BLUE);
	label->setTag(3);

	this->addChild(label);

	log("param data : %d", data);
}