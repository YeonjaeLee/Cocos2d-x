#include "HelloWorldScene.h"

static std::string fontList[]=
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	// info.plist에 사용자가 추가한 ttf를 정의해야 한다.
	"A Damn Mess",
		"Abberancy",
		"Abduction",
		"Paint Boy",
		"Schwarzwald Regular",
		"Scissor Cuts",
#else
	"fonts/A Damn Mess.ttf",
		"fonts/Abberancy.ttf",
		"fonts/Abduction.ttf",
		"fonts/Paint Boy.ttf",
		"fonts/Schwarzwald Regular.ttf",
		"fonts/Scissor Cuts.ttf",
#endif
};

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

	// 레이블 생성 및 초기화
	auto pLabel1 = LabelTTF::create("Hello Gikimi", "Arial", 34);

	// 레이블의 위치 지정
	pLabel1->setPosition(Vec2(240, 200));

	// 레이블의 색 지정
	pLabel1->setColor(Color3B(0, 0, 0));

	// 레이어에 레이블 객체 추가
	this->addChild(pLabel1);

	//레이블 생성 및 초기화

	auto pLabel2 = LabelTTF::create("Hello Gikimi", fontList[5].c_str(), 34);

	// 레이블의 위치 지정
	pLabel2->setPosition(Vec2(240, 100));

	// 레이블의 색 지정
	pLabel2->setColor(Color3B(0, 0, 0));

	// 레이어에 레이블 객체 추가
	this->addChild(pLabel2);
    
    return true;
}
