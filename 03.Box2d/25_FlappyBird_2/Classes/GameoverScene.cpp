#include "GameoverScene.h"

USING_NS_CC;

Scene* GameoverScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameoverScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameoverScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	/////////////////////////////////////////////
	// 윈도우 크기를 구한다.
	winSize = Director::getInstance()->getWinSize();

	Sprite* bg = Sprite::create("Images/CaptureScreenTest.png");
	bg->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	bg->setScale(2);
	this->addChild(bg);

	return true;
}