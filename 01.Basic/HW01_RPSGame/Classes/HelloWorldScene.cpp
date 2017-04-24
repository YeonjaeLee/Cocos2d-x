#include "HelloWorldScene.h"

USING_NS_CC;

static int com = -1;
static int user = -1;
static int sCom = 0;
static int sUser = 0;
static int result = 0;

void HelloWorld::Userscoreprint(int num)
{
	auto pLabel = (Sprite *)getChildByTag(99);
	this->removeChild(pLabel, true);

	auto *pLabel1 = LabelTTF::create("Your score:0", "Thonburi", 20);
	pLabel1->setPosition(Vec2(100, 290));
	pLabel1->setColor(Color3B::BLUE);

	char UserScore[100] = { 0 };
	sprintf(UserScore, "Your Score : %d", sUser);
	pLabel1->setString(UserScore);
	pLabel1->setTag(99);

	this->addChild(pLabel1);
}

void HelloWorld::Comscoreprint(int num)
{
	auto pLabel = (Sprite *)getChildByTag(98);
	this->removeChild(pLabel, true);

	auto *pLabel2 = LabelTTF::create("Computer score:0", "Thonburi", 20);
	pLabel2->setPosition(Vec2(320, 290));
	pLabel2->setColor(Color3B::BLUE);

	char ComScore[100] = { 0 };
	sprintf(ComScore, "Computer Score : %d", sCom);
	pLabel2->setString(ComScore);
	pLabel2->setTag(98);

	this->addChild(pLabel2);
}

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
	auto *pLabel1 = LabelTTF::create("Your score:0", "Thonburi", 20);
	pLabel1->setPosition(Vec2(100, 290));
	pLabel1->setTag(99);
	pLabel1->setColor(Color3B::BLUE);
	this->addChild(pLabel1);

	auto *pLabel2 = LabelTTF::create("Computer score:0", "Thonburi", 20);
	pLabel2->setPosition(Vec2(320, 290));
	pLabel2->setTag(98);
	pLabel2->setColor(Color3B::BLUE);
	this->addChild(pLabel2);

	auto pMenuItem1 = MenuItemFont::create(
		" [ 가위 ] ",
		CC_CALLBACK_1(HelloWorld::doClick, this));
	pMenuItem1->setColor(Color3B(0, 0, 0));

	auto pMenuItem2 = MenuItemFont::create(
		" [ 바위 ] ",
		CC_CALLBACK_1(HelloWorld::doClick, this));
	pMenuItem2->setColor(Color3B(0, 0, 0));

	auto pMenuItem3 = MenuItemFont::create(
		" [  보  ] ",
		CC_CALLBACK_1(HelloWorld::doClick, this));
	pMenuItem3->setColor(Color3B(0, 0, 0));

	auto pMenuItem4 = MenuItemFont::create(
		" [ 다시하기 ] ",
		CC_CALLBACK_1(HelloWorld::doClick, this));
	pMenuItem4->setColor(Color3B(0, 0, 0));

	pMenuItem1->setTag(1);
	pMenuItem2->setTag(2);
	pMenuItem3->setTag(3);
	pMenuItem4->setTag(4);

	auto pMenu = Menu::create(pMenuItem1, pMenuItem2, pMenuItem3, nullptr);
	auto pMenu2 = Menu::create(pMenuItem4, nullptr);

	pMenu->alignItemsHorizontally();
	pMenu->setPosition(Vec2(240, 100));
	pMenu2->setPosition(Vec2(240, 50));

	this->addChild(pMenu);
	this->addChild(pMenu2);

	return true;
}

void HelloWorld::doClick(Ref* pSender)
{
	auto tItem = (MenuItem *)pSender;
	int i = tItem->getTag();

	if (com != -1)
	{
		auto pLabel3 = (Sprite *)getChildByTag(9);
		this->removeChild(pLabel3, true);

		auto pCom = (Sprite *)getChildByTag(11);
		this->removeChild(pCom, true);

		auto pUser = (Sprite *)getChildByTag(12);
		this->removeChild(pUser, true);
	}
	
	user = i;
	srand((int)time(NULL));
	com = rand() % 3 + 1;

	result = user - com;
	if (result == -1 || result == 2)
	{
		auto pLabel3 = LabelTTF::create("컴퓨터가 이겼습니다.", "Arial", 30);
		pLabel3->setPosition(Vec2(250, 270));
		pLabel3->setTag(9);
		pLabel3->setFontFillColor(Color3B::RED);
		this->addChild(pLabel3);

		sCom++;
		Comscoreprint(sCom);
	}
	else if (result == 0)
	{
		auto pLabel3 = LabelTTF::create("비겼습니다.", "Arial", 30);
		pLabel3->setPosition(Vec2(250, 270));
		pLabel3->setTag(9);
		pLabel3->setFontFillColor(Color3B::RED);
		this->addChild(pLabel3);
	}
	else
	{
		auto pLabel3 = LabelTTF::create("당신이 이겼습니다.", "Arial", 30);
		pLabel3->setPosition(Vec2(250, 270));
		pLabel3->setTag(9);
		pLabel3->setFontFillColor(Color3B::RED);
		this->addChild(pLabel3);

		sUser++;
		Userscoreprint(sUser);
	}

	if (com == 1)
	{
		auto pCom = Sprite::create("Images/img1.png");
		pCom->setPosition(Vec2(350, 190));
		pCom->setTag(11);
		this->addChild(pCom);
	}
	else if (com == 2)
	{
		auto pCom = Sprite::create("Images/img2.png");
		pCom->setPosition(Vec2(350, 190));
		pCom->setTag(11);
		this->addChild(pCom);
	}
	else if (com == 3)
	{
		auto pCom = Sprite::create("Images/img3.png");
		pCom->setPosition(Vec2(350, 190));
		pCom->setTag(11);
		this->addChild(pCom);
	}

	if (i == 1)
	{
		auto pUser = Sprite::create("Images/img1.png");
		pUser->setFlipX(true);
		pUser->setPosition(Vec2(100, 190));
		pUser->setTag(12);
		this->addChild(pUser);
	}
	else if (i == 2)
	{
		auto pUser = Sprite::create("Images/img2.png");
		pUser->setFlipX(true);
		pUser->setPosition(Vec2(100, 190));
		pUser->setTag(12);
		this->addChild(pUser);
	}
	else if (i == 3)
	{
		auto pUser = Sprite::create("Images/img3.png");
		pUser->setFlipX(true);
		pUser->setPosition(Vec2(100, 190));
		pUser->setTag(12);
		this->addChild(pUser);
	}
	else if (i == 4)
	{
		auto pLabel3 = (Sprite *)getChildByTag(9);
		this->removeChild(pLabel3, true);

		auto pCom = (Sprite *)getChildByTag(11);
		this->removeChild(pCom, true);

		auto pUser = (Sprite *)getChildByTag(12);
		this->removeChild(pUser, true);

		sUser = 0;
		sCom = 0;
		Comscoreprint(sCom);
		Userscoreprint(sUser);
	}
}
