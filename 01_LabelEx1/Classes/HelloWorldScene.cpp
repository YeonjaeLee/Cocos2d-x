#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor(Color4B(255, 255, 255, 255)) )
    {
        return false;
    }

	//////////////////////////////////

	//레이블 생성 및 초기화 1
//	auto pLabel = LabelTTF::create("Hello World", "Arial", 64);

	// 레이블 생성 및 초기화 2
	// 내용이 길면 자동개행이 되지 않고 중앙정렬만 된다.
	// 34 vs 64
//	auto pLabel = LabelTTF::create("동해물과 백두산이 마르고 닳도록 하느님이 보우하사 우리나라 만세.", "Arial", 34);
	
	// 레이블 생성 및 초기화 3
	// 폰트 크기는 너무 크고 레이블의 크기가 상대적으로 작을 때 글자가 잘리는 현상이
	// 발생할 수 있다. 이럴 때는 레이블의 크기를 더 늘리거나 폰트 크기를 줄여 본다.
	// Size(300, 100) vs Size(300, 200)
	auto pLabel = LabelTTF::create("동해물과 백두산이 마르고 닳도록 하느님이 보우하사 우리나라 만세.",
		"Arial",
		34,
		Size(300, 200),
		TextHAlignment::CENTER,
		TextVAlignment::CENTER);

	// 레이블의 위치 지정
	pLabel->setPosition(Vec2(240, 160));

	// 레이블의 색 지정
	pLabel->setColor(Color3B(0, 0, 0));	// 255, 0, 0

	// 레이블의 투명도 지정
	pLabel->setOpacity(100.0f);

	// 레이블에 레이블 객체 추가
	this->addChild(pLabel);


    return true;
}
