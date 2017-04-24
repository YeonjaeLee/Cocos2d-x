#include "TestScene3.h"
#include "HelloWorldScene.h"	// 추가

using namespace cocos2d;

Scene* TestScene3::createScene()
{
	auto scene = Scene::create();
	auto layer = TestScene3::create();
	scene->addChild(layer);
	return scene;
}

bool TestScene3::init()
{
	if (!LayerColor::initWithColor(Color4B(255, 255, 0, 255)))
	{
		return false;
	}
	/////////////////////////////////////////////

	// 메뉴 아이템 생성 및 초기화

	auto item1 = MenuItemFont::create(
		"Close Scene 3",
		CC_CALLBACK_1(TestScene3::doClose, this));
	item1->setColor(Color3B(0, 0, 0));

	// 메뉴 생성
	auto pMenu = Menu::create(item1, nullptr);

	// 메뉴 정렬
	pMenu->setPosition(Vec2(240, 50));

	// 레이어에 메뉴 객체 추가
	this->addChild(pMenu);

	return true;
}

void TestScene3::doClose(Ref* pSender)
{
	auto pScene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(pScene);
}