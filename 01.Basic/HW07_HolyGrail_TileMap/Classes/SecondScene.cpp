#include "SecondScene.h"
#include "ThirdScene.h"

using namespace cocos2d;

Scene* SecondScene::createScene()
{
	auto scene = Scene::create();
	auto layer = SecondScene::create();
	scene->addChild(layer);
	return scene;
}

bool SecondScene::init()
{
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}
	/////////////////////////////////////////////
	// 화면 사이즈 구하기
	winSize = Director::getInstance()->getWinSize();

	// 타일맵 읽어오기
	tmap = TMXTiledMap::create("TileMaps/HolyGrail_Stage2.tmx");
	background = tmap->getLayer("Background");
	metainfo = tmap->getLayer("MetaInfo");
	metainfo->setVisible(false);
	this->addChild(tmap, 0, 11);// z-order를 -1로 지정하면 화면이 나오지 않는다.

	// 타일앱에서 Object라고 지정한 오브젝트 레이어의 객체들 가져오기
	TMXObjectGroup* objects = tmap->getObjectGroup("Objects");

	// 오브젝트 레이어에서 SpqwnPoint 라고 지정한 속성값 읽어오기
	ValueMap HeroPoint = objects->getObject("HeroPoint");
	ValueMap DemonPoint1 = objects->getObject("DemonPoint_1");
	ValueMap DemonPoint2 = objects->getObject("DemonPoint_2");
	ValueMap DemonPoint3 = objects->getObject("DemonPoint_3");
	ValueMap JellyPoint1 = objects->getObject("JellyPoint_1");
	ValueMap JellyPoint2 = objects->getObject("JellyPoint_2");
	ValueMap JellyPoint3 = objects->getObject("JellyPoint_3");
	ValueMap JellyPoint4 = objects->getObject("JellyPoint_4");
	ValueMap JellyPoint5 = objects->getObject("JellyPoint_5");
	ValueMap WolfPoint1 = objects->getObject("WolfPoint_1");
	ValueMap WolfPoint2 = objects->getObject("WolfPoint_2");
	ValueMap WolfPoint3 = objects->getObject("WolfPoint_3");
	ValueMap WolfPoint4 = objects->getObject("WolfPoint_4");
	ValueMap I_ChestPoint = objects->getObject("I_ChestPoint");

	ValueMap W_Sword001Point1 = objects->getObject("W_Sword001Point_1");
	ValueMap W_Sword001Point2 = objects->getObject("W_Sword001Point_2");
	ValueMap W_Sword001Point3 = objects->getObject("W_Sword001Point_3");
	ValueMap W_Mace008Point1 = objects->getObject("W_Mace008Point_1");
	ValueMap W_Mace008Point2 = objects->getObject("W_Mace008Point_2");
	ValueMap W_Mace008Point3 = objects->getObject("W_Mace008Point_3");
	ValueMap W_Mace008Point4 = objects->getObject("W_Mace008Point_4");
	ValueMap W_Sword015Point1 = objects->getObject("W_Sword015Point_1");
	ValueMap W_Sword015Point2 = objects->getObject("W_Sword015Point_2");
	ValueMap I_KeyPoint = objects->getObject("I_KeyPoint");

	ValueMap ItemStatePoint = objects->getObject("ItemStatePoint");
	
	float xHero = HeroPoint["x"].asFloat();
	float yHero = HeroPoint["y"].asFloat();
	float xDemon1 = DemonPoint1["x"].asFloat();
	float yDemon1 = DemonPoint1["y"].asFloat();
	float xDemon2 = DemonPoint2["x"].asFloat();
	float yDemon2 = DemonPoint2["y"].asFloat();
	float xDemon3 = DemonPoint3["x"].asFloat();
	float yDemon3 = DemonPoint3["y"].asFloat();
	int xJelly1 = JellyPoint1["x"].asInt();
	int yJelly1 = JellyPoint1["y"].asInt();
	int xJelly2 = JellyPoint2["x"].asInt();
	int yJelly2 = JellyPoint2["y"].asInt();
	int xJelly3 = JellyPoint3["x"].asInt();
	int yJelly3 = JellyPoint3["y"].asInt();
	int xJelly4 = JellyPoint4["x"].asInt();
	int yJelly4 = JellyPoint4["y"].asInt();
	int xJelly5 = JellyPoint5["x"].asInt();
	int yJelly5 = JellyPoint5["y"].asInt();
	int xWolf1 = WolfPoint1["x"].asInt();
	int yWolf1 = WolfPoint1["y"].asInt();
	int xWolf2 = WolfPoint2["x"].asInt();
	int yWolf2 = WolfPoint2["y"].asInt();
	int xWolf3 = WolfPoint3["x"].asInt();
	int yWolf3 = WolfPoint3["y"].asInt();
	int xWolf4 = WolfPoint4["x"].asInt();
	int yWolf4 = WolfPoint4["y"].asInt();
	float xI_Chest = I_ChestPoint["x"].asFloat();
	float yI_Chest = I_ChestPoint["y"].asFloat();
	int xW_Sword0011 = W_Sword001Point1["x"].asInt();
	int yW_Sword0011 = W_Sword001Point1["y"].asInt();
	int xW_Sword0012 = W_Sword001Point2["x"].asInt();
	int yW_Sword0012 = W_Sword001Point2["y"].asInt();
	int xW_Sword0013 = W_Sword001Point3["x"].asInt();
	int yW_Sword0013 = W_Sword001Point3["y"].asInt();
	int xW_Mace0081 = W_Mace008Point1["x"].asInt();
	int yW_Mace0081 = W_Mace008Point1["y"].asInt();
	int xW_Mace0082 = W_Mace008Point2["x"].asInt();
	int yW_Mace0082 = W_Mace008Point2["y"].asInt();
	int xW_Mace0083 = W_Mace008Point3["x"].asInt();
	int yW_Mace0083 = W_Mace008Point3["y"].asInt();
	int xW_Mace0084 = W_Mace008Point4["x"].asInt();
	int yW_Mace0084 = W_Mace008Point4["y"].asInt();
	float xW_Sword0151 = W_Sword015Point1["x"].asFloat();
	float yW_Sword0151 = W_Sword015Point1["y"].asFloat();
	float xW_Sword0152 = W_Sword015Point2["x"].asFloat();
	float yW_Sword0152 = W_Sword015Point2["y"].asFloat();
	float xI_Key = I_KeyPoint["x"].asFloat();
	float yI_Key = I_KeyPoint["y"].asFloat();
	float xItemState = ItemStatePoint["x"].asFloat();
	float yItemState = ItemStatePoint["y"].asFloat();

	// SpawnPoint의 위치로 생성할 Hero의 위치 지정하기
	HeroPosition = Vec2(xHero, yHero);

	// 위치로 생성할 monster 위치 지정하기
	DemonPosition1 = Vec2(xDemon1, yDemon1);
	DemonPosition2 = Vec2(xDemon2, yDemon2);
	DemonPosition3 = Vec2(xDemon3, yDemon3);
	JellyPosition1 = Vec2(xJelly1, yJelly1);
	JellyPosition2 = Vec2(xJelly2, yJelly2);
	JellyPosition3 = Vec2(xJelly3, yJelly3);
	JellyPosition4 = Vec2(xJelly4, yJelly4);
	JellyPosition5 = Vec2(xJelly5, yJelly5);
	WolfPosition1 = Vec2(xWolf1, yWolf1);
	WolfPosition2 = Vec2(xWolf2, yWolf2);
	WolfPosition3 = Vec2(xWolf3, yWolf3);
	WolfPosition4 = Vec2(xWolf4, yWolf4);
	I_ChestPosition = Vec2(xI_Chest, yI_Chest);

	// 위치로 생성할 MetaInfo - Items 위치 지정하기
	W_Sword001Position1 = Vec2(xW_Sword0011, yW_Sword0011);
	W_Sword001Position2 = Vec2(xW_Sword0012, yW_Sword0012);
	W_Sword001Position3 = Vec2(xW_Sword0013, yW_Sword0013);
	W_Mace008Position1 = Vec2(xW_Mace0081, yW_Mace0081);
	W_Mace008Position2 = Vec2(xW_Mace0082, yW_Mace0082);
	W_Mace008Position3 = Vec2(xW_Mace0083, yW_Mace0083);
	W_Mace008Position4 = Vec2(xW_Mace0084, yW_Mace0084);
	W_Sword015Position1 = Vec2(xW_Sword0151, yW_Sword0151);
	W_Sword015Position2 = Vec2(xW_Sword0152, yW_Sword0152);
	I_KeyPosition = Vec2(xI_Key, yI_Key);

	// 위치로 아이템창 위치 지정하기
	ItemStatePosition = Vec2(xItemState, yItemState);

	SideUi = Sprite::create("Images/SideUi.png");
	SideUi->setPosition(Vec2(453, 140));
	SideUi->setOpacity(100.0);
	this->addChild(SideUi);

	ItemBox = Sprite::create("Images/SideB1.png");
	ItemBox->setPosition(Vec2(449, 285));
	ItemBox->setOpacity(80.0);
	this->addChild(ItemBox);

	LabelTTF* pLabel = LabelTTF::create("Stage 2", "Thonburi", 15);
	pLabel->setColor(Color3B::WHITE);
	pLabel->setPosition(Vec2(449, 65));
	this->addChild(pLabel, 1);

	auto pMenuItem_ResetButton = MenuItemImage::create(
		"Images/SideB2.png",
		"Images/SideB2.png",
		CC_CALLBACK_1(SecondScene::doClick_ResetButton, this));
	auto pMenu_ResetButton = Menu::create(pMenuItem_ResetButton, nullptr);
	pMenu_ResetButton->setPosition(Vec2(449, 33));
	this->addChild(pMenu_ResetButton);

	// 만든다.
	this->createHero();
	this->createDemon();
	this->createJelly();
	this->createWolf();
	this->createI_Chest();
	this->createW_Sword001();
	this->createW_Mace008();
	this->createW_Sword015();
	this->createI_Key();

	return true;
}

void SecondScene::doClick_ResetButton(Ref* pSender)
{
	log("stage 2 버튼 클릭. ");
	state = 1;
	can_I_Key = 0;
	can_W_Mace008 = 0;
	can_W_Sword001 = 0;
	can_W_Sword015 = 0;
	init();
}

void SecondScene::onEnter()
{
	Layer::onEnter();

	// 싱글 터치 모드로 터치 리스너 등록
	auto listener = EventListenerTouchOneByOne::create();
	// Swallow touches only available in OneByOne mode.
	// 핸들링된 터치 이벤트를 터치 이벤트 array에서 지우겠다는 의미다.
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(SecondScene::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(SecondScene::onTouchEnded, this);

	// The priority of the touch listener is based on the draw order of sprite
	// 터치 리스너의 우선순위를 (노드가) 화면에 그려진 순서대로 한다.
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void SecondScene::onExit()
{
	//_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);

	Layer::onExit();
}

void SecondScene::createHero()
{
	// 움직이는 사용자 넣기 시작
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("Images/Holygrail.plist");

	Vector<SpriteFrame*> animFrams;

	char str[100] = { 0 };
	for (int i = 1; i < 13; i++)
	{
		sprintf(str, "Hero%02d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		if (i < 4)
		{
			animFrams.pushBack(frame);
			state = 1;
		}
	}
	pHero = Sprite::createWithSpriteFrameName("Hero01.png");
	pHero->setPosition(HeroPosition);
	this->addChild(pHero);
	pHero->setScale(0.7);
}

void SecondScene::createDemon()
{
	// 움직이는 Demon 넣기 시작
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("Images/Holygrail.plist");

	Vector<SpriteFrame*> animFrams;

	char str[100] = { 0 };
	for (int i = 1; i < 4; i++)
	{
		sprintf(str, "Demon%01d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		animFrams.pushBack(frame);
	}
	pDemon1 = Sprite::createWithSpriteFrameName("Demon1.png");
	pDemon1->setPosition(DemonPosition1);
	this->addChild(pDemon1);
	pDemon1->setScale(0.7);

	pDemon2 = Sprite::createWithSpriteFrameName("Demon1.png");
	pDemon2->setPosition(DemonPosition2);
	this->addChild(pDemon2);
	pDemon2->setScale(0.7);

	pDemon3 = Sprite::createWithSpriteFrameName("Demon1.png");
	pDemon3->setPosition(DemonPosition3);
	this->addChild(pDemon3);
	pDemon3->setScale(0.7);

	auto animation = Animation::createWithSpriteFrames(animFrams, 0.3f);
	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);
	pDemon1->runAction(rep);
	pDemon2->runAction(rep->clone());
	pDemon3->runAction(rep->clone());
	animFrams.clear();
}

void SecondScene::createJelly()
{
	// 움직이는 Jelly 넣기 시작
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("Images/Holygrail.plist");

	Vector<SpriteFrame*> animFrams;

	char str[100] = { 0 };
	for (int i = 1; i < 4; i++)
	{
		sprintf(str, "Jelly%01d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		animFrams.pushBack(frame);
	}
	pJelly1 = Sprite::createWithSpriteFrameName("Jelly1.png");
	pJelly1->setPosition(JellyPosition1);
	this->addChild(pJelly1);
	pJelly1->setScale(0.7);

	pJelly2 = Sprite::createWithSpriteFrameName("Jelly1.png");
	pJelly2->setPosition(JellyPosition2);
	this->addChild(pJelly2);
	pJelly2->setScale(0.7);

	pJelly3 = Sprite::createWithSpriteFrameName("Jelly1.png");
	pJelly3->setPosition(JellyPosition3);
	this->addChild(pJelly3);
	pJelly3->setScale(0.7);

	pJelly4 = Sprite::createWithSpriteFrameName("Jelly1.png");
	pJelly4->setPosition(JellyPosition4);
	this->addChild(pJelly4);
	pJelly4->setScale(0.7);

	pJelly5 = Sprite::createWithSpriteFrameName("Jelly1.png");
	pJelly5->setPosition(JellyPosition5);
	this->addChild(pJelly5);
	pJelly5->setScale(0.7);

	auto animation = Animation::createWithSpriteFrames(animFrams, 0.3f);
	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);
	pJelly1->runAction(rep);
	pJelly2->runAction(rep->clone());
	pJelly3->runAction(rep->clone());
	pJelly4->runAction(rep->clone());
	pJelly5->runAction(rep->clone());
	animFrams.clear();
}

void SecondScene::createWolf()
{
	// 움직이는 Wolf 넣기 시작
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("Images/Holygrail.plist");

	Vector<SpriteFrame*> animFrams;

	char str[100] = { 0 };
	for (int i = 1; i < 4; i++)
	{
		sprintf(str, "Wolf%01d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		animFrams.pushBack(frame);
	}
	pWolf1 = Sprite::createWithSpriteFrameName("Wolf1.png");
	pWolf1->setPosition(WolfPosition1);
	this->addChild(pWolf1);
	pWolf1->setScale(0.7);

	pWolf2 = Sprite::createWithSpriteFrameName("Wolf1.png");
	pWolf2->setPosition(WolfPosition2);
	this->addChild(pWolf2);
	pWolf2->setScale(0.7);

	pWolf3 = Sprite::createWithSpriteFrameName("Wolf1.png");
	pWolf3->setPosition(WolfPosition3);
	this->addChild(pWolf3);
	pWolf3->setScale(0.7);

	pWolf4 = Sprite::createWithSpriteFrameName("Wolf1.png");
	pWolf4->setPosition(WolfPosition4);
	this->addChild(pWolf4);
	pWolf4->setScale(0.7);

	auto animation = Animation::createWithSpriteFrames(animFrams, 0.3f);
	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);
	pWolf1->runAction(rep);
	pWolf2->runAction(rep->clone());
	pWolf3->runAction(rep->clone());
	pWolf4->runAction(rep->clone());

	animFrams.clear();
}

void SecondScene::createI_Chest()
{
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("Images/Holygrail.plist");

	Vector<SpriteFrame*> animFrams;

	char str[100] = { 0 };
	for (int i = 1; i < 3; i++)
	{
		sprintf(str, "I_Chest%02d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		animFrams.pushBack(frame);
	}
	pI_Chest = Sprite::createWithSpriteFrameName("I_Chest01.png");
	pI_Chest->setPosition(I_ChestPosition);
	this->addChild(pI_Chest);

	pI_Chest->setScale(0.7);
	animFrams.clear();
}

void SecondScene::createW_Sword001()
{
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("Images/Holygrail.plist");

	Vector<SpriteFrame*> anim;

	char str[100] = { 0 };
	for (int i = 1; i < 2; i++)
	{
		sprintf(str, "W_Sword%03d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);

		anim.pushBack(frame);
	}
	pW_Sword0011 = Sprite::createWithSpriteFrameName("W_Sword001.png");
	pW_Sword0011->setPosition(W_Sword001Position1);
	this->addChild(pW_Sword0011);
	pW_Sword0011->setScale(0.7);

	pW_Sword0012 = Sprite::createWithSpriteFrameName("W_Sword001.png");
	pW_Sword0012->setPosition(W_Sword001Position2);
	this->addChild(pW_Sword0012);
	pW_Sword0012->setScale(0.7);

	pW_Sword0013 = Sprite::createWithSpriteFrameName("W_Sword001.png");
	pW_Sword0013->setPosition(W_Sword001Position3);
	this->addChild(pW_Sword0013);
	pW_Sword0013->setScale(0.7);

	anim.clear();
}

void SecondScene::createW_Mace008()
{
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("Images/Holygrail.plist");

	Vector<SpriteFrame*> anim;

	char str[100] = { 0 };
	for (int i = 1; i < 2; i++)
	{
		sprintf(str, "W_Mace%03d.png", 8);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);

		anim.pushBack(frame);
	}
	pW_Mace0081 = Sprite::createWithSpriteFrameName("W_Mace008.png");
	pW_Mace0081->setPosition(W_Mace008Position1);
	this->addChild(pW_Mace0081);
	pW_Mace0081->setScale(0.7);

	pW_Mace0082 = Sprite::createWithSpriteFrameName("W_Mace008.png");
	pW_Mace0082->setPosition(W_Mace008Position2);
	this->addChild(pW_Mace0082);
	pW_Mace0082->setScale(0.7);

	pW_Mace0083 = Sprite::createWithSpriteFrameName("W_Mace008.png");
	pW_Mace0083->setPosition(W_Mace008Position3);
	this->addChild(pW_Mace0083);
	pW_Mace0083->setScale(0.7);

	pW_Mace0084 = Sprite::createWithSpriteFrameName("W_Mace008.png");
	pW_Mace0084->setPosition(W_Mace008Position4);
	this->addChild(pW_Mace0084);
	pW_Mace0084->setScale(0.7);

	anim.clear();
}

void SecondScene::createW_Sword015()
{
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("Images/Holygrail.plist");

	Vector<SpriteFrame*> anim;

	char str[100] = { 0 };
	for (int i = 1; i < 2; i++)
	{
		sprintf(str, "W_Sword%03d.png", 15);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);

		anim.pushBack(frame);
	}
	pW_Sword0151 = Sprite::createWithSpriteFrameName("W_Sword015.png");
	pW_Sword0151->setPosition(W_Sword015Position1);
	this->addChild(pW_Sword0151);
	pW_Sword0151->setScale(0.7);

	pW_Sword0152 = Sprite::createWithSpriteFrameName("W_Sword015.png");
	pW_Sword0152->setPosition(W_Sword015Position2);
	this->addChild(pW_Sword0152);
	pW_Sword0152->setScale(0.7);
	anim.clear();
}

void SecondScene::createI_Key()
{
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("Images/Holygrail.plist");

	Vector<SpriteFrame*> anim;

	char str[100] = { 0 };
	for (int i = 1; i < 2; i++)
	{
		sprintf(str, "I_Key%02d.png", 2);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);

		anim.pushBack(frame);
	}
	pI_Key = Sprite::createWithSpriteFrameName("I_Key02.png");
	pI_Key->setPosition(I_KeyPosition);
	this->addChild(pI_Key);

	pI_Key->setScale(0.7);

	const char* Holly = "Images/holly.plist";

	emitter = ParticleSystemQuad::create(Holly);
	emitter->setPosition(I_KeyPosition);
	emitter->setScale(0.7f);
	emitter->setDuration(-1.0f);
	emitter->setAutoRemoveOnFinish(true);

	this->addChild(emitter);
	anim.clear();
}

void SecondScene::createItemState()
{
	if (can_I_Key == 1)
	{
		auto cache = SpriteFrameCache::getInstance();
		cache->addSpriteFramesWithFile("Images/Holygrail.plist");

		Vector<SpriteFrame*> anim;

		char str[100] = { 0 };
		for (int i = 1; i < 2; i++)
		{
			sprintf(str, "I_Key%02d.png", 2);
			SpriteFrame* frame = cache->getSpriteFrameByName(str);

			anim.pushBack(frame);
		}
		pItemState = Sprite::createWithSpriteFrameName("I_Key02.png");
		pItemState->setPosition(ItemStatePosition);
		this->addChild(pItemState);
		anim.clear();
	}
	else if (can_W_Sword001 == 1)
	{
		auto cache = SpriteFrameCache::getInstance();
		cache->addSpriteFramesWithFile("Images/Holygrail.plist");

		Vector<SpriteFrame*> anim;

		char str[100] = { 0 };
		for (int i = 1; i < 2; i++)
		{
			sprintf(str, "W_Sword%03d.png", i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str);

			anim.pushBack(frame);
		}
		pItemState = Sprite::createWithSpriteFrameName("W_Sword001.png");
		pItemState->setPosition(ItemStatePosition);
		this->addChild(pItemState);
		anim.clear();
	}
	else if (can_W_Sword015 == 1)
	{
		auto cache = SpriteFrameCache::getInstance();
		cache->addSpriteFramesWithFile("Images/Holygrail.plist");

		Vector<SpriteFrame*> anim;

		char str[100] = { 0 };
		for (int i = 1; i < 2; i++)
		{
			sprintf(str, "W_Sword%03d.png", 15);
			SpriteFrame* frame = cache->getSpriteFrameByName(str);

			anim.pushBack(frame);
		}
		pItemState = Sprite::createWithSpriteFrameName("W_Sword015.png");
		pItemState->setPosition(ItemStatePosition);
		this->addChild(pItemState);
		anim.clear();
	}
	else if (can_W_Mace008 == 1)
	{
		auto cache = SpriteFrameCache::getInstance();
		cache->addSpriteFramesWithFile("Images/Holygrail.plist");

		Vector<SpriteFrame*> anim;

		char str[100] = { 0 };
		for (int i = 1; i < 2; i++)
		{
			sprintf(str, "W_Mace%03d.png", 8);
			SpriteFrame* frame = cache->getSpriteFrameByName(str);

			anim.pushBack(frame);
		}
		pItemState = Sprite::createWithSpriteFrameName("W_Mace008.png");
		pItemState->setPosition(ItemStatePosition);
		this->addChild(pItemState);
		anim.clear();
	}
}

void SecondScene::resetItemState()
{
	this->removeChild(pItemState);
}

bool SecondScene::onTouchBegan(Touch* touch, Event* event)
{
	if (pHero->getNumberOfRunningActions() == 0)
	{
		return true;
	}
	return true;
}

void SecondScene::onTouchEnded(Touch* touch, Event* event)
{
	auto touchPoint = touch->getLocation();
	touchPoint = this->convertToNodeSpace(touchPoint);

	Vec2 playerPos = pHero->getPosition();

	Vec2 diff = touchPoint - playerPos;

	if (abs(diff.x) > abs(diff.y))
	{
		if (diff.x > 0)
		{
			playerPos.x += tmap->getTileSize().width;

			auto cache = SpriteFrameCache::getInstance();
			cache->addSpriteFramesWithFile("Images/Holygrail.plist");

			Vector<SpriteFrame*> animFrams;

			char str[100] = { 0 };
			for (int i = 1; i < 13; i++)
			{
				sprintf(str, "Hero%02d.png", i);
				SpriteFrame* frame = cache->getSpriteFrameByName(str);
				if (i > 6 && i < 10)
				{
					animFrams.pushBack(frame);
					state = 3;
				}
			}
			auto animation = Animation::createWithSpriteFrames(animFrams, 0.3f);
			auto animate = Animate::create(animation);
			auto rep = Repeat::create(animate, 1);
			pHero->runAction(rep);
			animFrams.clear();
		}
		else
		{
			playerPos.x -= tmap->getTileSize().width;

			auto cache = SpriteFrameCache::getInstance();
			cache->addSpriteFramesWithFile("Images/Holygrail.plist");

			Vector<SpriteFrame*> animFrams;

			char str[100] = { 0 };
			for (int i = 1; i < 13; i++)
			{
				sprintf(str, "Hero%02d.png", i);
				SpriteFrame* frame = cache->getSpriteFrameByName(str);
				if (i > 3 && i < 7)
				{
					animFrams.pushBack(frame);
					state = 2;
				}
			}
			auto animation = Animation::createWithSpriteFrames(animFrams, 0.3f);
			auto animate = Animate::create(animation);
			auto rep = Repeat::create(animate, 1);
			pHero->runAction(rep);
			animFrams.clear();
		}
	}
	else
	{
		if (diff.y > 0)
		{
			playerPos.y += tmap->getTileSize().height;

			auto cache = SpriteFrameCache::getInstance();
			cache->addSpriteFramesWithFile("Images/Holygrail.plist");

			Vector<SpriteFrame*> animFrams;

			char str[100] = { 0 };
			for (int i = 1; i < 13; i++)
			{
				sprintf(str, "Hero%02d.png", i);
				SpriteFrame* frame = cache->getSpriteFrameByName(str);
				if (i > 9 && i < 13)
				{
					animFrams.pushBack(frame);
					state = 4;
				}
			}
			auto animation = Animation::createWithSpriteFrames(animFrams, 0.3f);
			auto animate = Animate::create(animation);
			auto rep = Repeat::create(animate, 1);
			pHero->runAction(rep);
			animFrams.clear();
		}
		else
		{
			playerPos.y -= tmap->getTileSize().height;

			auto cache = SpriteFrameCache::getInstance();
			cache->addSpriteFramesWithFile("Images/Holygrail.plist");

			Vector<SpriteFrame*> animFrams;

			char str[100] = { 0 };
			for (int i = 1; i < 13; i++)
			{
				sprintf(str, "Hero%02d.png", i);
				SpriteFrame* frame = cache->getSpriteFrameByName(str);
				if (i < 4)
				{
					animFrams.pushBack(frame);
					state = 1;
				}
			}
			auto animation = Animation::createWithSpriteFrames(animFrams, 0.3f);
			auto animate = Animate::create(animation);
			auto rep = Repeat::create(animate, 1);
			pHero->runAction(rep);
			animFrams.clear();
		}
	}

	if (playerPos.x <= (tmap->getMapSize().width * tmap->getTileSize().width) &&
		playerPos.y <= (tmap->getMapSize().height * tmap->getTileSize().height) &&
		playerPos.y >= 0 &&
		playerPos.x >= 0)
	{
		// Hero의 새로운 위치 지정
		this->setPlayerPosition(playerPos);
	}

	// Hero의 위치에 맞춰 화면 위치 조정
	//this->setViewpointCenter(pHero->getPosition());
}

void SecondScene::setViewpointCenter(Vec2 position)
{
	// 파라미터로 들어오는 위치에 맞춰 화면을 움직인다.
	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);

	x = MIN(x, (tmap->getMapSize().width * tmap->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (tmap->getMapSize().height * tmap->getTileSize().height) - winSize.height / 2);

	Vec2 actualPosition = Vec2(x, y);
	Vec2 centerOfView = Vec2(winSize.width / 2, winSize.height / 2);
	Vec2 viewPoint = centerOfView - actualPosition;

	this->setPosition(viewPoint);
}

// 현재 탭으로 선택된 타일의 위치를 가져온다.
Vec2 SecondScene::tileCoordForPosition(Vec2 position)
{
	int x = position.x / tmap->getTileSize().width;
	int y = ((tmap->getMapSize().height * tmap->getTileSize().height) - position.y) / tmap->getTileSize().height;
	return Vec2(x, y);
}

void SecondScene::setPlayerPosition(Vec2 position)
{
	// 탭된 위치 구하기
	Vec2 tileCoord = this->tileCoordForPosition(position);
	// 현재 위치의 Tile GID 구하기
	int tileGid = this->metainfo->getTileGIDAt(tileCoord);
	if (state == 1)
	{
		moveposition = Vec2(0, -32);
	}
	else if (state == 2)
	{
		moveposition = Vec2(-32, 0);
	}
	else if (state == 3)
	{
		moveposition = Vec2(32, 0);
	}
	else if (state == 4)
	{
		moveposition = Vec2(0, 32);
	}
	auto myActionForward = MoveBy::create(0.1, moveposition);
	auto myActionDelay = DelayTime::create(0.5);
	auto myAction = Sequence::create(myActionForward, myActionDelay, nullptr);
	willposition = moveposition + pHero->getPosition();

	if (tileGid)
	{
		// 타일맵에서 GID에 해당하는 부분의 속성 읽어 오기
		Value& properties = tmap->getPropertiesForGID(tileGid);

		if (!properties.isNull())
		{
			std::string wall = properties.asValueMap()["Wall"].asString();
			if (wall == "YES")
			{
				log("Wall...");
				return;
			}

			std::string monster1 = properties.asValueMap()["Monster"].asString();
			if (monster1 == "Demon")
			{
				if (can_W_Sword015 == 0)
				{
					return;
				}
				else
				{
					can_W_Sword015 = 0;
					this->metainfo->removeTileAt(tileCoord);
					//items->removeTileAt(tileCoord);
					if ((willposition.x > DemonPosition1.x- 1 && willposition.x < DemonPosition1.x + 1) && (willposition.y > DemonPosition1.y - 1 && willposition.y < DemonPosition1.y + 1))
					{
						pDemon1->setVisible(false);
						log("Demon1 처지!!!");
						resetItemState();
					}
					else if ((willposition.x > DemonPosition2.x - 1 && willposition.x < DemonPosition2.x + 1) && (willposition.y > DemonPosition2.y - 1 && willposition.y < DemonPosition2.y + 1))
					{
						pDemon2->setVisible(false);
						log("Demon2 처지!!!");
						resetItemState();
					}
					else if ((willposition.x > DemonPosition3.x - 1 && willposition.x < DemonPosition3.x + 1) && (willposition.y > DemonPosition3.y - 1 && willposition.y < DemonPosition3.y + 1))
					{
						pDemon3->setVisible(false);
						log("Demon3 처지!!!");
						resetItemState();
					}
				}
			}

			std::string monster2 = properties.asValueMap()["Monster"].asString();
			if (monster2 == "Jelly")
			{
				if (can_W_Mace008 == 0)
				{
					return;
				}
				else
				{
					can_W_Mace008 = 0;
					this->metainfo->removeTileAt(tileCoord);
					//items->removeTileAt(tileCoord);
					if ((willposition.x > JellyPosition1.x - 1 && willposition.x < JellyPosition1.x + 1) && (willposition.y > JellyPosition1.y - 1 && willposition.y < JellyPosition1.y + 1))
					{
						pJelly1->setVisible(false);
						log("Jelly1 처지!!!");
						resetItemState();
					}
					else if ((willposition.x > JellyPosition2.x - 1 && willposition.x < JellyPosition2.x + 1) && (willposition.y > JellyPosition2.y - 1 && willposition.y < JellyPosition2.y + 1))
					{
						pJelly2->setVisible(false);
						log("Jelly2 처지!!!");
						resetItemState();
					}
					else if ((willposition.x > JellyPosition3.x - 1 && willposition.x < JellyPosition3.x + 1) && (willposition.y > JellyPosition3.y - 1 && willposition.y < JellyPosition3.y + 1))
					{
						pJelly3->setVisible(false);
						log("Jelly3 처지!!!");
						resetItemState();
					}
					else if ((willposition.x > JellyPosition4.x - 1 && willposition.x < JellyPosition4.x + 1) && (willposition.y > JellyPosition4.y - 1 && willposition.y < JellyPosition4.y + 1))
					{
						pJelly4->setVisible(false);
						log("Jelly4 처지!!!");
						resetItemState();
					}
					else if ((willposition.x > JellyPosition5.x - 1 && willposition.x < JellyPosition5.x + 1) && (willposition.y > JellyPosition5.y - 1 && willposition.y < JellyPosition5.y + 1))
					{
						pJelly5->setVisible(false);
						log("Jelly5 처지!!!");
						resetItemState();
					}
				}
			}

			std::string monster3 = properties.asValueMap()["Monster"].asString();
			if (monster3 == "Wolf")
			{
				if (can_W_Sword001 == 0)
				{
					return;
				}
				else
				{
					can_W_Sword001 = 0;
					this->metainfo->removeTileAt(tileCoord);
					//items->removeTileAt(tileCoord);
					if ((willposition.x > WolfPosition1.x - 1 && willposition.x < WolfPosition1.x + 1) && (willposition.y > WolfPosition1.y - 1 && willposition.y < WolfPosition1.y + 1))
					{
						pWolf1->setVisible(false);
						log("Wolf1 처지!!!");
						resetItemState();
					}
					else if ((willposition.x > WolfPosition2.x - 1 && willposition.x < WolfPosition2.x + 1) && (willposition.y > WolfPosition2.y - 1 && willposition.y < WolfPosition2.y + 1))
					{
						pWolf2->setVisible(false);
						log("Wolf2 처지!!!");
						resetItemState();
					}
					else if ((willposition.x > WolfPosition3.x - 1 && willposition.x < WolfPosition3.x + 1) && (willposition.y > WolfPosition3.y - 1 && willposition.y < WolfPosition3.y + 1))
					{
						pWolf3->setVisible(false);
						log("Wolf3 처지!!!");
						resetItemState();
					}
					else if ((willposition.x > WolfPosition4.x - 1 && willposition.x < WolfPosition4.x + 1) && (willposition.y > WolfPosition4.y - 1 && willposition.y < WolfPosition4.y + 1))
					{
						pWolf4->setVisible(false);
						log("Wolf4 처지!!!");
						resetItemState();
					}
				}
			}

			std::string exit1 = properties.asValueMap()["Exit"].asString();
			if (exit1 == "I_Chest")
			{
				if (can_I_Key == 0)
				{
					return;
				}
				else
				{
					can_I_Key = 0;
					this->metainfo->removeTileAt(tileCoord);
					//items->removeTileAt(tileCoord);
					pI_Chest->setVisible(false);
					log("성공!!!");
					resetItemState();
					auto cache = SpriteFrameCache::getInstance();
					cache->addSpriteFramesWithFile("Images/Holygrail.plist");

					Vector<SpriteFrame*> animFrams;

					char str[100] = { 0 };
					for (int i = 1; i < 3; i++)
					{
						sprintf(str, "I_Chest%02d.png", i);
						SpriteFrame* frame = cache->getSpriteFrameByName(str);
						animFrams.pushBack(frame);
					}
					auto pI_Chestopen = Sprite::createWithSpriteFrameName("I_Chest02.png");
					pI_Chestopen->setPosition(I_ChestPosition);
					this->addChild(pI_Chestopen);
					pI_Chestopen->setScale(0.7);

					auto pScene = ThirdScene::createScene();
					Director::getInstance()->replaceScene(TransitionFade::create(1, pScene, Color3B::WHITE));
				}
			}

			std::string item1 = properties.asValueMap()["Items"].asString();
			if (item1 == "W_Sword001")
			{
				if (can_I_Key == 1 || can_W_Sword001 == 1 || can_W_Sword015 == 1 || can_W_Mace008 == 1)
				{
					return;
				}
				else
				{
					can_W_Sword001 = 1;
					this->metainfo->removeTileAt(tileCoord);
					//items->removeTileAt(tileCoord);
					if ((willposition.x > W_Sword001Position1.x - 1 && willposition.x < W_Sword001Position1.x + 1) && (willposition.y > W_Sword001Position1.y - 1 && willposition.y < W_Sword001Position1.y + 1))
					{
						pW_Sword0011->setVisible(false);
						log("검1 획득!!!");
						this->createItemState();
					}
					else if ((willposition.x > W_Sword001Position2.x - 1 && willposition.x < W_Sword001Position2.x + 1) && (willposition.y > W_Sword001Position2.y - 1 && willposition.y < W_Sword001Position2.y + 1))
					{
						pW_Sword0012->setVisible(false);
						log("검2 획득!!!");
						this->createItemState();
					}
					else if ((willposition.x > W_Sword001Position3.x - 1 && willposition.x < W_Sword001Position3.x + 1) && (willposition.y > W_Sword001Position3.y - 1 && willposition.y < W_Sword001Position3.y + 1))
					{
						pW_Sword0013->setVisible(false);
						log("검3 획득!!!");
						this->createItemState();
					}
				}
			}

			std::string item2 = properties.asValueMap()["Items"].asString();
			if (item2 == "W_Mace008")
			{
				if (can_I_Key == 1 || can_W_Sword001 == 1 || can_W_Sword015 == 1 || can_W_Mace008 == 1)
				{
					return;
				}
				else
				{
					can_W_Mace008 = 1;
					this->metainfo->removeTileAt(tileCoord);
					//items->removeTileAt(tileCoord);
					if ((willposition.x > W_Mace008Position1.x - 1 && willposition.x < W_Mace008Position1.x + 1) && (willposition.y > W_Mace008Position1.y - 1 && willposition.y < W_Mace008Position1.y + 1))
					{
						pW_Mace0081->setVisible(false);
						log("메이스1 획득!!!");
						this->createItemState();
					}
					else if ((willposition.x > W_Mace008Position2.x - 1 && willposition.x < W_Mace008Position2.x + 1) && (willposition.y > W_Mace008Position2.y - 1 && willposition.y < W_Mace008Position2.y + 1))
					{
						pW_Mace0082->setVisible(false);
						log("메이스2 획득!!!");
						this->createItemState();
					}
					else if ((willposition.x > W_Mace008Position3.x - 1 && willposition.x < W_Mace008Position3.x + 1) && (willposition.y > W_Mace008Position3.y - 1 && willposition.y < W_Mace008Position3.y + 1))
					{
						pW_Mace0083->setVisible(false);
						log("메이스3 획득!!!");
						this->createItemState();
					}
					else if ((willposition.x > W_Mace008Position4.x - 1 && willposition.x < W_Mace008Position4.x + 1) && (willposition.y > W_Mace008Position4.y - 1 && willposition.y < W_Mace008Position4.y + 1))
					{
						pW_Mace0084->setVisible(false);
						log("메이스4 획득!!!");
						this->createItemState();
					}
				}
			}

			std::string item3 = properties.asValueMap()["Items"].asString();
			if (item3 == "W_Sword015")
			{
				if (can_I_Key == 1 || can_W_Sword001 == 1 || can_W_Sword015 == 1 || can_W_Mace008 == 1)
				{
					return;
				}
				else
				{
					can_W_Sword015 = 1;
					this->metainfo->removeTileAt(tileCoord);
					//items->removeTileAt(tileCoord);
					if ((willposition.x > W_Sword015Position1.x - 1 && willposition.x < W_Sword015Position1.x + 1) && (willposition.y > W_Sword015Position1.y - 1 && willposition.y < W_Sword015Position1.y + 1))
					{
						pW_Sword0151->setVisible(false);
						log("마법검1 획득!!!");
						this->createItemState();
					}
					else if ((willposition.x > W_Sword015Position2.x - 1 && willposition.x < W_Sword015Position2.x + 1) && (willposition.y > W_Sword015Position2.y - 1 && willposition.y < W_Sword015Position2.y + 1))
					{
						pW_Sword0152->setVisible(false);
						log("마법검2 획득!!!");
						this->createItemState();
					}
				}
			}

			std::string item4 = properties.asValueMap()["Items"].asString();
			if (item4 == "I_Key")
			{
				if (can_I_Key == 1 || can_W_Sword001 == 1 || can_W_Sword015 == 1 || can_W_Mace008 == 1)
				{
					return;
				}
				else
				{
					can_I_Key = 1;
					this->metainfo->removeTileAt(tileCoord);
					//items->removeTileAt(tileCoord);
					pI_Key->setVisible(false);
					emitter->setVisible(false);
					log("키 획득!!!");
					this->createItemState();
				}
			}
		}
	}
	// 파라미터로 들어온 위치에 Hero 위치 조정하기
	pHero->runAction(myAction);
}