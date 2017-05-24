#include "IntroScene.h"
#include "MainScene.h"

USING_NS_CC;

Scene* IntroScene::createScene()
{
	auto scene = Scene::create();
	auto layer = IntroScene::create();
	scene->addChild(layer);
	return scene;
}

bool IntroScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	/////////////////////////////////////////////
	// 윈도우 크기를 구한다.
	winSize = Director::getInstance()->getWinSize();

	Sprite* intrologo = Sprite::create("Images/intro.png");
	intrologo->setPosition(Vec2(winSize.width / 2, winSize.height / 2 + 60));
	intrologo->setScale(2.5);
	this->addChild(intrologo);

	this->schedule(schedule_selector(IntroScene::tick));

	return true;
}

void IntroScene::tick(float dt)
{
	count++;

	if (count == 100)
	{
		auto pScene = MainScene::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(3, pScene, Color3B::BLACK));
	}
}