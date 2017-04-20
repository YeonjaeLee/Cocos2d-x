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
	Bckg = Sprite::create("Images/Bckground/Background.png");
	Bckg->setAnchorPoint(Vec2(0, 0));
	Bckg->setPosition(Vec2(0, 0));
	this->addChild(Bckg);

	Fish_001 = Sprite::create("Images/Fish_Effect/Fish_001.png");
	Fish_001->setVisible(false);
	this->addChild(Fish_001);
	this->doAction_Fish_001(this);

	Fish_002 = Sprite::create("Images/Fish_Effect/Fish_002.png");
	Fish_002->setVisible(false);
	this->addChild(Fish_002);
	this->doAction_Fish_002(this);

	Lighting = Sprite::create("Images/Flash_Effect/Lighting.png");
	Lighting->setVisible(false);
	this->addChild(Lighting);
	this->doAction_Lighting(this);

	Blue_Star = Sprite::create("Images/Background_Effect/Blue_Star.png");
	Blue_Star->setVisible(false);
	this->addChild(Blue_Star);
	this->doAction_Blue_Star(this);

	Gold_Star = Sprite::create("Images/Background_Effect/Gold_Star.png");
	Gold_Star->setVisible(false);
	this->addChild(Gold_Star);
	this->doAction_Gold_Star(this);

	Purple_Star = Sprite::create("Images/Background_Effect/Purple_Star.png");
	Purple_Star->setVisible(false);
	this->addChild(Purple_Star);
	this->doAction_Purple_Star(this);

	Lighting_Background = Sprite::create("Images/Bubble_Effect/Lighting_Background.png");
	Lighting_Background->setVisible(false);
	this->addChild(Lighting_Background);
	this->doAction_Lighting_Background(this);

	Flash_004 = Sprite::create("Images/Flash_Effect/Flash_004.png");
	Flash_004->setVisible(false);
	this->addChild(Flash_004);
	this->doAction_Flash_004(this);

	Flash_005 = Sprite::create("Images/Flash_Effect/Flash_005.png");
	Flash_005->setVisible(false);
	this->addChild(Flash_005);
	this->doAction_Flash_005(this);

	All_Light = Sprite::create("Images/Flash_Effect/All_Light.png");
	All_Light->setVisible(false);
	this->addChild(All_Light);
	this->doAction_All_Light(this);

	Logo_Light = Sprite::create("Images/Flash_Effect/Logo_Light.png");
	Logo_Light->setVisible(false);
	this->addChild(Logo_Light);
	this->doAction_Logo_Light(this);

	Title_Bubble_001 = Sprite::create("Images/Bubble_Effect/Title_Bubble_001.png");
	Title_Bubble_001->setVisible(false);
	this->addChild(Title_Bubble_001);
	this->doAction_Title_Bubble_001(this);

	Title_Bubble_002 = Sprite::create("Images/Bubble_Effect/Title_Bubble_002.png");
	Title_Bubble_002->setVisible(false);
	this->addChild(Title_Bubble_002);
	this->doAction_Title_Bubble_002(this);

	Title_Bubble_003 = Sprite::create("Images/Bubble_Effect/Title_Bubble_003.png");
	Title_Bubble_003->setVisible(false);
	this->addChild(Title_Bubble_003);
	this->doAction_Title_Bubble_003(this);

	BubbleLogo = Sprite::create("Images/Game_Logo/Bubble_Logo.png");
	BubbleLogo->setVisible(false);
	this->addChild(BubbleLogo);
	this->doAction_BubbleLogo(this);

	auto pMenuItem_Play_Button = MenuItemImage::create(
		"Images/Bubble_Button/Play_Button/Play_Button_01.png",
		"Images/Bubble_Button/Play_Button/Play_Button_02.png",
		CC_CALLBACK_1(HelloWorld::doClick_Play_Button, this));
	auto pMenu_Play_Button = Menu::create(pMenuItem_Play_Button, nullptr);
	pMenu_Play_Button->setPosition(Vec2(320, 320));
	this->addChild(pMenu_Play_Button);

	auto pMenuItem_Vibration_ON = MenuItemImage::create(
		"Images/Bubble_Button/Setting_Button/Vibration_ON.png",
		"Images/Bubble_Button/Setting_Button/Vibration_OFF.png",
		CC_CALLBACK_1(HelloWorld::doClick_Vibration_ON, this));
	auto pMenu_Vibration_ON = Menu::create(pMenuItem_Vibration_ON, nullptr);
	pMenu_Vibration_ON->setPosition(Vec2(450, 200));
	this->addChild(pMenu_Vibration_ON);

	Base = Sprite::create("Images/Bubble_Button/Base.png");
	Base->setVisible(false);
	this->addChild(Base);
	this->doAction_Base(this);

	auto pMenuItem_Create_Button = MenuItemImage::create(
		"Images/Bubble_Button/Create_Button/Create_Button_01.png",
		"Images/Bubble_Button/Create_Button/Create_Button_02.png",
		CC_CALLBACK_1(HelloWorld::doClick_Create_Button, this));
	auto pMenu_Create_Button = Menu::create(pMenuItem_Create_Button, nullptr);
	pMenu_Create_Button->setPosition(Vec2(590, 50));
	this->addChild(pMenu_Create_Button);

	Create_base = Sprite::create("Images/Bubble_Button/Create_Button/Create_base.png");
	Create_base->setVisible(false);
	this->addChild(Create_base);
	this->doAction_Create_base(this);
	
	return true;
}

void HelloWorld::doClick_Play_Button(Ref* pSender)
{
	log("play 버튼 클릭. ");
}

void HelloWorld::doClick_Vibration_ON(Ref* pSender)
{
	log("Setting 버튼 클릭. ");
}

void HelloWorld::doClick_Create_Button(Ref* pSender)
{
	log("Create 버튼 클릭. ");
}

void HelloWorld::doAction_Fish_001(Ref* pSender)
{
	Fish_001->removeAllChildrenWithCleanup(true);

	Fish_001 = Sprite::create("Images/Fish_Effect/Fish_001.png");
	Fish_001->setPosition(Vec2(-100, 500));
	Fish_001->setOpacity(100.0);
	this->addChild(Fish_001);

	this->ActionRepeatForever_Fish_001(this);
}

void HelloWorld::ActionRepeatForever_Fish_001(Ref* pSender)
{
	auto myActionForward = MoveBy::create(9, Vec2(800, -70));
	auto myActionBack = myActionForward->reverse();
	auto myAction = Sequence::create(myActionForward, Hide::create(), myActionBack, Show::create(), nullptr);
	auto rep2 = RepeatForever::create(myAction);

	Fish_001->runAction(rep2);
}

void HelloWorld::doAction_Fish_002(Ref* pSender)
{
	Fish_002->removeAllChildrenWithCleanup(true);

	Fish_002 = Sprite::create("Images/Fish_Effect/Fish_002.png");
	Fish_002->setPosition(Vec2(700, 550));
	Fish_002->setOpacity(100.0);
	this->addChild(Fish_002);

	this->ActionRepeatForever_Fish_002(this);
}

void HelloWorld::ActionRepeatForever_Fish_002(Ref* pSender)
{
	auto myActionForward = MoveBy::create(9, Vec2(-800, -70));
	auto myActionBack = myActionForward->reverse();
	auto myAction = Sequence::create(myActionForward, Hide::create(), myActionBack, Show::create(), nullptr);
	auto rep2 = RepeatForever::create(myAction);

	Fish_002->runAction(rep2);
}

void HelloWorld::doAction_Lighting(Ref* pSender)
{
	Lighting->removeAllChildrenWithCleanup(true);

	Lighting = Sprite::create("Images/Flash_Effect/Lighting.png");
	Lighting->setPosition(Vec2(370, 90));
	this->addChild(Lighting);

	this->ActionRepeatForever_Lighting(this);
}

void HelloWorld::ActionRepeatForever_Lighting(Ref* pSender)
{
	auto myActionForward = FadeOut::create(1.0f);
	auto myActionBack = myActionForward->reverse();
	auto myAction = Sequence::create(myActionForward, myActionBack, nullptr);
	auto rep2 = RepeatForever::create(myAction);

	Lighting->runAction(rep2);
}

void HelloWorld::doAction_Blue_Star(Ref* pSender)
{
	Blue_Star->removeAllChildrenWithCleanup(true);

	Blue_Star = Sprite::create("Images/Background_Effect/Blue_Star.png");
	Blue_Star->setPosition(Vec2(100, 160));
	this->addChild(Blue_Star);

	this->ActionRepeatForever_Blue_Star(this);
}

void HelloWorld::ActionRepeatForever_Blue_Star(Ref* pSender)
{
	auto myActionForward = RotateBy::create(2.5, 360);
	auto myAction = Sequence::create(myActionForward, nullptr);
	auto rep2 = RepeatForever::create(myAction);

	Blue_Star->runAction(rep2);
}

void HelloWorld::doAction_Gold_Star(Ref* pSender)
{
	Gold_Star->removeAllChildrenWithCleanup(true);

	Gold_Star = Sprite::create("Images/Background_Effect/Gold_Star.png");
	Gold_Star->setPosition(Vec2(350, 60));
	Gold_Star->setOpacity(150.0);
	this->addChild(Gold_Star);

	this->ActionRepeatForever_Gold_Star(this);
}

void HelloWorld::ActionRepeatForever_Gold_Star(Ref* pSender)
{
	auto myActionForward = RotateBy::create(1.8, 360);
	auto myAction = Sequence::create(myActionForward, nullptr);
	auto rep2 = RepeatForever::create(myAction);

	Gold_Star->runAction(rep2);
}

void HelloWorld::doAction_Purple_Star(Ref* pSender)
{
	Purple_Star->removeAllChildrenWithCleanup(true);

	Purple_Star = Sprite::create("Images/Background_Effect/Purple_Star.png");
	Purple_Star->setPosition(Vec2(590, 100));
	Purple_Star->setOpacity(200.0);
	this->addChild(Purple_Star);

	this->ActionRepeatForever_Purple_Star(this);
}

void HelloWorld::ActionRepeatForever_Purple_Star(Ref* pSender)
{
	auto myActionForward = RotateBy::create(2, 360);
	auto myAction = Sequence::create(myActionForward, nullptr);
	auto rep2 = RepeatForever::create(myAction);

	Purple_Star->runAction(rep2);
}

void HelloWorld::doAction_Lighting_Background(Ref* pSender)
{
	Lighting_Background->removeAllChildrenWithCleanup(true);

	Lighting_Background = Sprite::create("Images/Bubble_Effect/Lighting_Background.png");
	Lighting_Background->setPosition(Vec2(330, 820));
	this->addChild(Lighting_Background);

	this->ActionRepeatForever_Lighting_Background(this);
}

void HelloWorld::ActionRepeatForever_Lighting_Background(Ref* pSender)
{
	auto myActionForward = FadeOut::create(1.5f);
	auto myActionBack = myActionForward->reverse();
	auto myAction = Sequence::create(myActionForward, myActionBack, nullptr);
	auto rep2 = RepeatForever::create(myAction);

	Lighting_Background->runAction(rep2);
}

void HelloWorld::doAction_Flash_004(Ref* pSender)
{
	Flash_004->removeAllChildrenWithCleanup(true);

	Flash_004 = Sprite::create("Images/Flash_Effect/Flash_004.png");
	Flash_004->setPosition(Vec2(490, 830));
	this->addChild(Flash_004);

	this->ActionRepeatForever_Flash_004(this);
}

void HelloWorld::ActionRepeatForever_Flash_004(Ref* pSender)
{
	auto myActionForward = FadeOut::create(1.0f);
	auto myActionBack = myActionForward->reverse();
	auto myAction = Sequence::create(myActionForward, myActionBack, nullptr);
	auto rep2 = RepeatForever::create(myAction);

	Flash_004->runAction(rep2);
}

void HelloWorld::doAction_Flash_005(Ref* pSender)
{
	Flash_005->removeAllChildrenWithCleanup(true);

	Flash_005 = Sprite::create("Images/Flash_Effect/Flash_005.png");
	Flash_005->setPosition(Vec2(550, 800));
	this->addChild(Flash_005);

	this->ActionRepeatForever_Flash_005(this);
}

void HelloWorld::ActionRepeatForever_Flash_005(Ref* pSender)
{
	auto myActionForward = FadeOut::create(1.0f);
	auto myActionBack = myActionForward->reverse();
	auto myAction = Sequence::create(myActionForward, myActionBack, nullptr);
	auto rep2 = RepeatForever::create(myAction);

	Flash_005->runAction(rep2);
}

void HelloWorld::doAction_All_Light(Ref* pSender)
{
	All_Light->removeAllChildrenWithCleanup(true);

	All_Light = Sprite::create("Images/Flash_Effect/All_Light.png");
	All_Light->setPosition(Vec2(340, 500));
	this->addChild(All_Light);

	this->ActionRepeatForever_All_Light(this);
}

void HelloWorld::ActionRepeatForever_All_Light(Ref* pSender)
{
	auto myActionForward = FadeOut::create(5.0f);
	auto myActionBack = myActionForward->reverse();
	auto myAction = Sequence::create(myActionForward, myActionBack, nullptr);
	auto rep2 = RepeatForever::create(myAction);

	All_Light->runAction(rep2);
}

void HelloWorld::doAction_Logo_Light(Ref* pSender)
{
	Logo_Light->removeAllChildrenWithCleanup(true);

	Logo_Light = Sprite::create("Images/Flash_Effect/Logo_Light.png");
	Logo_Light->setPosition(Vec2(320, 710));
	this->addChild(Logo_Light);

	this->ActionRepeatForever_Logo_Light(this);
}

void HelloWorld::ActionRepeatForever_Logo_Light(Ref* pSender)
{
	auto myActionForward = FadeOut::create(1.0f);
	auto myActionBack = myActionForward->reverse();
	auto myAction = Sequence::create(myActionForward, myActionBack, nullptr);
	auto rep2 = RepeatForever::create(myAction);

	Logo_Light->runAction(rep2);
}

void HelloWorld::doAction_Title_Bubble_001(Ref* pSender)
{
	Title_Bubble_001->removeAllChildrenWithCleanup(true);

	Title_Bubble_001 = Sprite::create("Images/Bubble_Effect/Title_Bubble_001.png");
	Title_Bubble_001->setPosition(Vec2(400, -400));
	Title_Bubble_001->setOpacity(150.0);
	this->addChild(Title_Bubble_001);

	this->ActionRepeatForever_Title_Bubble_001(this);
}

void HelloWorld::ActionRepeatForever_Title_Bubble_001(Ref* pSender)
{
	auto myActionForward = MoveBy::create(2, Vec2(0, 1500));
	auto myActionReplay = Place::create(Vec2(400, -400));
	auto myAction = Sequence::create(myActionForward, myActionReplay, nullptr);
	auto rep2 = RepeatForever::create(myAction);

	Title_Bubble_001->runAction(rep2);
}

void HelloWorld::doAction_Title_Bubble_002(Ref* pSender)
{
	Title_Bubble_002->removeAllChildrenWithCleanup(true);

	Title_Bubble_002 = Sprite::create("Images/Bubble_Effect/Title_Bubble_002.png");
	Title_Bubble_002->setPosition(Vec2(400, -300));
	this->addChild(Title_Bubble_002);

	this->ActionRepeatForever_Title_Bubble_002(this);
}

void HelloWorld::ActionRepeatForever_Title_Bubble_002(Ref* pSender)
{
	auto myActionForward = MoveBy::create(1.7, Vec2(0, 2000));
	auto myActionReplay = Place::create(Vec2(400, -300));
	auto myAction = Sequence::create(myActionForward, myActionReplay, nullptr);
	auto rep2 = RepeatForever::create(myAction);

	Title_Bubble_002->runAction(rep2);
}

void HelloWorld::doAction_Title_Bubble_003(Ref* pSender)
{
	Title_Bubble_003->removeAllChildrenWithCleanup(true);

	Title_Bubble_003 = Sprite::create("Images/Bubble_Effect/Title_Bubble_003.png");
	Title_Bubble_003->setPosition(Vec2(400, -500));
	Title_Bubble_003->setOpacity(100.0);
	this->addChild(Title_Bubble_003);

	this->ActionRepeatForever_Title_Bubble_003(this);
}

void HelloWorld::ActionRepeatForever_Title_Bubble_003(Ref* pSender)
{
	auto myActionForward = MoveBy::create(3, Vec2(0, 1500));
	auto myActionReplay = Place::create(Vec2(400, -500));
	auto myAction = Sequence::create(myActionForward, myActionReplay, nullptr);
	auto rep2 = RepeatForever::create(myAction);

	Title_Bubble_003->runAction(rep2);
}

void HelloWorld::doAction_BubbleLogo(Ref* pSender)
{
	BubbleLogo->removeAllChildrenWithCleanup(true);

	BubbleLogo = Sprite::create("Images/Game_Logo/Bubble_Logo.png");
	BubbleLogo->setPosition(Vec2(320, 690));
	this->addChild(BubbleLogo);

	this->ActionRepeatForever_BubbleLogo(this);
}

void HelloWorld::ActionRepeatForever_BubbleLogo(Ref* pSender)
{
	auto myActionForward = MoveBy::create(2, Vec2(0, 30));
	auto myActionBack = myActionForward->reverse();
	auto myAction = Sequence::create(myActionForward, myActionBack, nullptr);
	auto rep2 = RepeatForever::create(myAction);

	BubbleLogo->runAction(rep2);
}

void HelloWorld::doAction_Base(Ref* pSender)
{
	Base->removeAllChildrenWithCleanup(true);

	Base = Sprite::create("Images/Bubble_Button/Base.png");
	Base->setPosition(Vec2(348, 296));
	this->addChild(Base);

	this->ActionRepeatForever_Base(this);
}

void HelloWorld::ActionRepeatForever_Base(Ref* pSender)
{
	auto myActionForward = FadeOut::create(0.7f);
	auto myActionBack = myActionForward->reverse();
	auto myAction = Sequence::create(myActionForward, myActionBack, nullptr);
	auto rep2 = RepeatForever::create(myAction);

	Base->runAction(rep2);
}

void HelloWorld::doAction_Create_base(Ref* pSender)
{
	Create_base->removeAllChildrenWithCleanup(true);

	Create_base = Sprite::create("Images/Bubble_Button/Create_Button/Create_base.png");
	Create_base->setPosition(Vec2(590, 50));
	this->addChild(Create_base);

	this->ActionRepeatForever_Create_base(this);
}

void HelloWorld::ActionRepeatForever_Create_base(Ref* pSender)
{
	auto myActionForward = RotateBy::create(2, 360);
	auto myActionBack = myActionForward->reverse();
	auto myAction = Sequence::create(myActionForward, myActionBack, nullptr);
	auto rep2 = RepeatForever::create(myAction);

	Create_base->runAction(rep2);
}