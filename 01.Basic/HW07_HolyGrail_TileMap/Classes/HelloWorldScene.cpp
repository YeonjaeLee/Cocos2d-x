#include "HelloWorldScene.h"
#include "SecondScene.h"

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
	// 화면 사이즈 구하기
	winSize = Director::getInstance()->getWinSize();

	// 타일맵 읽어오기
	tmap = TMXTiledMap::create("TileMaps/HolyGrail_Stage1.tmx");
	background = tmap->getLayer("Background");
	metainfo = tmap->getLayer("MetaInfo");
	metainfo->setVisible(false);
	this->addChild(tmap, 0, 11);// z-order를 -1로 지정하면 화면이 나오지 않는다.

	// 타일앱에서 Object라고 지정한 오브젝트 레이어의 객체들 가져오기
	TMXObjectGroup* objects = tmap->getObjectGroup("Objects");

	// 오브젝트 레이어에서 SpqwnPoint 라고 지정한 속성값 읽어오기
	ValueMap HeroPoint = objects->getObject("HeroPoint");

	ValueMap DemonPoint = objects->getObject("DemonPoint");
	ValueMap JellyPoint = objects->getObject("JellyPoint");
	ValueMap WolfPoint = objects->getObject("WolfPoint");
	ValueMap I_ChestPoint = objects->getObject("I_ChestPoint");

	ValueMap W_Sword001Point = objects->getObject("W_Sword001Point");
	ValueMap W_Mace008Point = objects->getObject("W_Mace008Point");
	ValueMap W_Sword015Point = objects->getObject("W_Sword015Point");
	ValueMap I_KeyPoint = objects->getObject("I_KeyPoint");

	ValueMap ItemStatePoint = objects->getObject("ItemStatePoint");

	int xHero = HeroPoint["x"].asInt();
	int yHero = HeroPoint["y"].asInt();
	int xDemon = DemonPoint["x"].asInt();
	int yDemon = DemonPoint["y"].asInt();
	int xJelly = JellyPoint["x"].asInt();
	int yJelly = JellyPoint["y"].asInt();
	int xWolf = WolfPoint["x"].asInt();
	int yWolf = WolfPoint["y"].asInt();
	int xI_Chest = I_ChestPoint["x"].asInt();
	int yI_Chest = I_ChestPoint["y"].asInt();
	int xW_Sword001 = W_Sword001Point["x"].asInt();
	int yW_Sword001 = W_Sword001Point["y"].asInt();
	int xW_Mace008 = W_Mace008Point["x"].asInt();
	int yW_Mace008 = W_Mace008Point["y"].asInt();
	int xW_Sword015 = W_Sword015Point["x"].asInt();
	int yW_Sword015 = W_Sword015Point["y"].asInt();
	int xI_Key = I_KeyPoint["x"].asInt();
	int yI_Key = I_KeyPoint["y"].asInt();
	int xItemState = ItemStatePoint["x"].asInt();
	int yItemState = ItemStatePoint["y"].asInt();

	// SpawnPoint의 위치로 생성할 Hero의 위치 지정하기
	HeroPosition = Vec2(xHero, yHero);

	// 위치로 생성할 monster 위치 지정하기
	DemonPosition = Vec2(xDemon, yDemon);
	JellyPosition = Vec2(xJelly, yJelly);
	WolfPosition = Vec2(xWolf, yWolf);
	I_ChestPosition = Vec2(xI_Chest, yI_Chest);

	// 위치로 생성할 MetaInfo - Items 위치 지정하기
	W_Sword001Position = Vec2(xW_Sword001, yW_Sword001);
	W_Mace008Position = Vec2(xW_Mace008, yW_Mace008);
	W_Sword015Position = Vec2(xW_Sword015, yW_Sword015);
	I_KeyPosition = Vec2(xI_Key, yI_Key);

	// 위치로 아이템창 위치 지정하기
	ItemStatePosition = Vec2(xItemState, yItemState);

	pLabel1 = LabelTTF::create("칼은 늑대를 처치할 수 있으며, 메이스는 젤리를 처치할 수 있고, 성검으로 악마를 처치할 수 있습니다. 열쇠로 상자를 열면 클리어입니다.단, 한번에 하나의 아이템만을 가질 수 있습니다.", "Thonburi", 15);
	pLabel1->setVisible(false);
	this->addChild(pLabel1);
	this->doAction_Label1(this);

	SideUi = Sprite::create("Images/SideUi.png");
	SideUi->setPosition(Vec2(453, 140));
	SideUi->setOpacity(100.0);
	this->addChild(SideUi);

	ItemBox = Sprite::create("Images/SideB1.png");
	ItemBox->setPosition(Vec2(449, 285));
	ItemBox->setOpacity(80.0);
	this->addChild(ItemBox);

	LabelTTF* pLabel2 = LabelTTF::create("Stage 1", "Thonburi", 15);
	pLabel2->setColor(Color3B::WHITE);
	pLabel2->setPosition(Vec2(449, 65));
	this->addChild(pLabel2, 1);

	auto pMenuItem_ResetButton = MenuItemImage::create(
		"Images/SideB2.png",
		"Images/SideB2.png",
		CC_CALLBACK_1(HelloWorld::doClick_ResetButton, this));
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

void HelloWorld::doAction_Label1(Ref* pSender)
{
	pLabel1->removeAllChildrenWithCleanup(true);

	pLabel1 = LabelTTF::create("칼은 늑대를 처치할 수 있으며, 메이스는 젤리를 처치할 수 있고, 성검으로 악마를 처치할 수 있습니다. 열쇠로 상자를 열면 클리어입니다.단, 한번에 하나의 아이템만을 가질 수 있습니다.", "Thonburi", 15);
	pLabel1->setColor(Color3B::BLACK);
	pLabel1->setPosition(Vec2(1500, 12));
	this->addChild(pLabel1);
	
	this->ActionRepeatForever_Label1(this);
}

void HelloWorld::ActionRepeatForever_Label1(Ref* pSender)
{
	auto myActionForward = MoveBy::create(20, Vec2(-3000, 0));
	auto myActionReplay = Place::create(Vec2(1500, 12));
	auto myAction = Sequence::create(myActionForward, myActionReplay, nullptr);
	auto rep2 = RepeatForever::create(myAction);

	pLabel1->runAction(rep2);
}

void HelloWorld::doClick_ResetButton(Ref* pSender)
{
	log("play 버튼 클릭. ");
	state = 1;
	can_I_Key = 0;
	can_W_Mace008 = 0;
	can_W_Sword001 = 0;
	can_W_Sword015 = 0;
	init();
}

void HelloWorld::onEnter()
{
	Layer::onEnter();

	// 싱글 터치 모드로 터치 리스너 등록
	auto listener = EventListenerTouchOneByOne::create();
	// Swallow touches only available in OneByOne mode.
	// 핸들링된 터치 이벤트를 터치 이벤트 array에서 지우겠다는 의미다.
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

	// The priority of the touch listener is based on the draw order of sprite
	// 터치 리스너의 우선순위를 (노드가) 화면에 그려진 순서대로 한다.
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void HelloWorld::onExit()
{
	//_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
	Layer::onExit();
}

void HelloWorld::createHero()
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

void HelloWorld::createDemon()
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
	pDemon = Sprite::createWithSpriteFrameName("Demon1.png");
	pDemon->setPosition(DemonPosition);
	this->addChild(pDemon);

	pDemon->setScale(0.7);

	auto animation = Animation::createWithSpriteFrames(animFrams, 0.3f);
	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);
	pDemon->runAction(rep);
	animFrams.clear();
}

void HelloWorld::createJelly()
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
	pJelly = Sprite::createWithSpriteFrameName("Jelly1.png");
	pJelly->setPosition(JellyPosition);
	this->addChild(pJelly);

	pJelly->setScale(0.7);

	auto animation = Animation::createWithSpriteFrames(animFrams, 0.3f);
	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);
	pJelly->runAction(rep);
	animFrams.clear();
}

void HelloWorld::createWolf()
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
	pWolf = Sprite::createWithSpriteFrameName("Wolf1.png");
	pWolf->setPosition(WolfPosition);
	this->addChild(pWolf);

	pWolf->setScale(0.7);

	auto animation = Animation::createWithSpriteFrames(animFrams, 0.3f);
	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);
	pWolf->runAction(rep);
	animFrams.clear();
}

void HelloWorld::createI_Chest()
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

void HelloWorld::createW_Sword001()
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
	pW_Sword001 = Sprite::createWithSpriteFrameName("W_Sword001.png");
	pW_Sword001->setPosition(W_Sword001Position);
	this->addChild(pW_Sword001);

	pW_Sword001->setScale(0.7);
	anim.clear();
}

void HelloWorld::createW_Mace008()
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
	pW_Mace008 = Sprite::createWithSpriteFrameName("W_Mace008.png");
	pW_Mace008->setPosition(W_Mace008Position);
	this->addChild(pW_Mace008);

	pW_Mace008->setScale(0.7);
	anim.clear();
}

void HelloWorld::createW_Sword015()
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
	pW_Sword015 = Sprite::createWithSpriteFrameName("W_Sword015.png");
	pW_Sword015->setPosition(W_Sword015Position);
	this->addChild(pW_Sword015);

	pW_Sword015->setScale(0.7);
	anim.clear();
}

void HelloWorld::createI_Key()
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

void HelloWorld::createItemState()
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

void HelloWorld::resetItemState()
{
	this->removeChild(pItemState);
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
	// 액션중에 다른액션이 실행되도록 하지못하게한다.(연타 방지)
	if (pHero->getNumberOfRunningActions())
	{
		log("광클 금지");
		return false;
	}
	return true;
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event)
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

void HelloWorld::setViewpointCenter(Vec2 position)
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
Vec2 HelloWorld::tileCoordForPosition(Vec2 position)
{
	int x = position.x / tmap->getTileSize().width;
	int y = ((tmap->getMapSize().height * tmap->getTileSize().height) - position.y) / tmap->getTileSize().height;
	return Vec2(x, y);
}

void HelloWorld::setPlayerPosition(Vec2 position)
{
	// 탭된 위치 구하기
	Vec2 tileCoord = this->tileCoordForPosition(position);
	// 현재 위치의 Tile GID 구하기
	int tileGid = this->metainfo->getTileGIDAt(tileCoord);

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
				if(can_W_Sword015 == 0)
				{ 
					return;
				}
				else
				{
					can_W_Sword015 = 0;
					this->metainfo->removeTileAt(tileCoord);
					//items->removeTileAt(tileCoord);
					pDemon->setVisible(false);
					log("Demon 처지!!!");
					resetItemState();
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
					pJelly->setVisible(false);
					log("Jelly 처지!!!");
					resetItemState();
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
					pWolf->setVisible(false);
					log("Wolf 처지!!!");
					resetItemState();
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

					auto pScene = SecondScene::createScene();
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
					pW_Sword001->setVisible(false);
					log("검 획득!!!");

					this->createItemState();
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
					pW_Mace008->setVisible(false);
					log("메이스 획득!!!");

					this->createItemState();
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
					pW_Sword015->setVisible(false);
					log("마법검 획득!!!");

					this->createItemState();
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
	if (state == 1)
	{
		moveposition = Vec2(0, 0 - tmap->getTileSize().height);
	}
	else if (state == 2)
	{
		moveposition = Vec2(0 - tmap->getTileSize().height, 0);
	}
	else if (state == 3)
	{
		moveposition = Vec2(tmap->getTileSize().height, 0);
	}
	else if (state == 4)
	{
		moveposition = Vec2(0, tmap->getTileSize().height);
	}
	auto myActionForward = MoveBy::create(0.1, moveposition);
	auto myActionDelay = DelayTime::create(0.5);
	auto myAction = Sequence::create(myActionForward, myActionDelay, nullptr);

	pHero->runAction(myAction);
}