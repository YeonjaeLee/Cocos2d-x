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

	// 스프라이트의 색 지정은 그림이 흰색이거나 밝은색이어야 효과가 나타난다.
	auto parent = Sprite::create("Images/white-512x512.png");
	parent->setTextureRect(Rect(0, 0, 150, 150));
	parent->setPosition(Vec2(240, 160));	// 좌표 지정
	parent->setColor(Color3B(0, 0, 255));	// 칼라 설정 - 블루
	this->addChild(parent);

	// 부모 스프라이트에 자식 스프라이트 추가
	auto child = Sprite::create("Images/white-512x512.png");
	child->setTextureRect(Rect(0, 0, 50, 5));
	child->setColor(Color3B::RED);	// 칼라 설정 - 레드

	// 위치 지정
	//	child->setPosition(Vec2(0, 0));
	// 윗줄 삭제, 아래 코드 추가
	Size parentSize;
	parentSize = parent->getContentSize();
	child->setPosition(Vec2(parentSize.width / 2.0, parentSize.height + 10));

	parent->addChild(child);

	return true;
}
