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

	// 다양한 방법으로 스프라이트시트 텍스처를 만든다.

	// --------------------------------------------------------------------
	// Type 1 : from Sprite
	// --------------------------------------------------------------------
	auto sprite = Sprite::create("Images/grossini_dance_atlas.png");
	auto texture1 = sprite->getTexture();

	// --------------------------------------------------------------------
	// Type 2 : from Texture
	// --------------------------------------------------------------------
	auto texture2 = Director::getInstance()->getTextureCache()->addImage("Images/grossini_dance_arlas.png");

	// --------------------------------------------------------------------
	// Type 3 : from BatchNode
	// --------------------------------------------------------------------

	// small capacity. Testing resizing.
	// Don't use capacity=1 in your real game. It is expensive to resize the capacity
	auto batch = SpriteBatchNode::create("Images/grossini_dance_atlas.png", 10);
	auto texture3 = batch->getTexture();
	// --------------------------------------------------------------------


	auto animation = Animation::create();
	animation->setDelayPerUnit(0.3f);

	for (int i = 0; i < 14; i++)
	{
		// 첫째 줄에 5개의 프레임이 있고, 6번째부터는 두 번째 줄에 있으므로
		// 6번째 (idx==5)부터는 y 좌표의 값을 증가시켜야 한다.
		int column = i % 5;
		int row = i / 5;

		animation->addSpriteFrameWithTexture(
			texture3,
			Rect(column * 85, row * 121, 85, 121));
	}

	// 스프라이트 생성 및 초기화
	auto pMan = Sprite::createWithTexture(texture3, Rect(0, 0, 85, 121));
	pMan->setPosition(Vec2(240, 160));
	this->addChild(pMan);

	// 애니메이션 액션 실행
	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);
	pMan->runAction(rep);
		
	return true;
}