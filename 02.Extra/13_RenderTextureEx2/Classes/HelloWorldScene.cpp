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
	winSize = Director::getInstance()->getWinSize();

	// Render Texture 만들기
	m_pTarget = RenderTexture::create(winSize.width / 2 + 40,
		winSize.height / 2 + 30,
		Texture2D::PixelFormat::RGBA8888);

	m_pTarget->retain();
	m_pTarget->setPosition(Vec2(winSize.width / 2, winSize.height / 2 + 50));

	this->addChild(m_pTarget, 1);

	// 메뉴 만들기
	MenuItemFont::setFontSize(16);
	auto item1 = MenuItemFont::create("Save Image", CC_CALLBACK_1(HelloWorld::saveImage, this));
	item1->setColor(Color3B::BLACK);
	auto item2 = MenuItemFont::create("Clear", CC_CALLBACK_1(HelloWorld::clearImage, this));
	item2->setColor(Color3B::BLACK);
	auto menu = Menu::create(item1, item2, nullptr);
	menu->alignItemsVertically();
	menu->setPosition(Vec2(winSize.width - 50, winSize.height - 30));
	this->addChild(menu, 3);

	TableView* tableView2 = TableView::create(this, Size(290, 100));
	tableView2->setDirection(ScrollView::Direction::HORIZONTAL);
	tableView2->setPosition(Vec2(90, 10));
	tableView2->setDelegate(this);
	tableView2->setTag(100);
	this->addChild(tableView2);
	tableView2->reloadData();

	Sprite* image01 = Sprite::create("Images/image01.png");
	image01->setPosition(Vec2(240, 210));
	this->addChild(image01, 3);

	return true;
}

HelloWorld::~HelloWorld()
{
	m_pTarget->release();
	Director::getInstance()->getTextureCache()->removeUnusedTextures();
}

void HelloWorld::onEnter()
{
	Layer::onEnter();

	listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesMoved = CC_CALLBACK_2(HelloWorld::onTouchesMoved, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void HelloWorld::onExit()
{
	_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);

	Layer::onExit();
}

void HelloWorld::onTouchesMoved(const std::vector<Touch*>& touches, Event *Event)
{
	auto touch = touches[0];
	Vec2 start = touch->getLocation();
	Vec2 end = touch->getPreviousLocation();

	m_pTarget->begin();

	// for extra points, we'll draw this smoothly from the last position and vary the sprite's
	// scale/rotation/offset
	float distance = start.getDistance(end);
	if (distance > 1)
	{
		int d = (int)distance;
		m_pBrush.clear();
		for (int i = 0; i < d; ++i)
		{
			Sprite* sprite = Sprite::create("Images/brush.png");

			sprite->setColor(brushColor);
			//sprite->setOpacity(20);
			//sprite->setOpacity(150);
			m_pBrush.pushBack(sprite);
		}
		for (int i = 0; i < d; i++)
		{
			float difx = end.x - start.x;
			float dify = end.y - start.y;
			float delta = (float)i / distance;
			m_pBrush.at(i)->setPosition(Vec2(start.x + (difx * delta) - 100, start.y + (dify * delta) - 120));
			m_pBrush.at(i)->setRotation(rand() % 360);
			float r = (float)(rand() % 50 / 50.f) + 0.25f;
			m_pBrush.at(i)->setScale(r);

			//m_pBrush.at(i)->setColor(Color3B(rand() % 127 + 128, 255, 255));

			// Call visit to draw the brush, don't call draw..
			m_pBrush.at(i)->visit();
		}
	}
	m_pTarget->end();
}

void HelloWorld::saveImage(Ref* sender)
{
	static int counter = 0;

	char png[20];
	sprintf(png, "image-%d.png", counter);

	// Type 2
	m_pTarget->saveToFile(png, Image::Format::PNG, true, nullptr);

	auto image = m_pTarget->newImage();
	auto tex = Director::getInstance()->getTextureCache()->addImage(image, png);

	CC_SAFE_DELETE(image);

	auto sprite = Sprite::createWithTexture(tex);

	sprite->setScale(0.3f);
	sprite->setPosition(Vec2(40, 40));
	sprite->setRotation(counter * 3);

	addChild(sprite);
	//-----------------------------------------------------------------------

	// Add this function to avoid crash if we switch to a new scene.
	Director::getInstance()->getRenderer()->render();
	std::string fullpath = FileUtils::getInstance()->getWritablePath() + png;
	log("Image saved %s", fullpath.c_str());

	counter++;

}

void HelloWorld::clearImage(Ref* sender)
{
	m_pTarget->clear(255, 255, 255, 255);
}

void HelloWorld::tableCellTouched(TableView* table, TableViewCell* cell)
{
	for (int i = 0; i < 13; i++)
	{
		TableViewCell* tcell = table->cellAtIndex(i);
		if (tcell) {
			auto tsprite = (Sprite*)(tcell->getChildByTag(100));
			tsprite->setPosition(Vec2(0, 0));
		}
	}

	auto sprite1 = (Sprite*)(cell->getChildByTag(100));
	sprite1->setPosition(Vec2(0, 17));

	log("Tag : %d\nCell touched at indec: %ld",
		table->getTag(),
		cell->getIdx());
	if (cell->getIdx() == 0)
	{
		brushColor = cocos2d::Color3B::RED;
	}
	else if (cell->getIdx() == 1)
	{
		brushColor = cocos2d::Color3B::ORANGE;
	}
	else if (cell->getIdx() == 2)
	{
		brushColor = cocos2d::Color3B::YELLOW;
	}
	else if (cell->getIdx() == 3)
	{
		brushColor = cocos2d::Color3B::GREEN;
	}
	else if (cell->getIdx() == 4)
	{
		brushColor = cocos2d::Color3B(0, 154, 255);
	}
	else if (cell->getIdx() == 5)
	{
		brushColor = cocos2d::Color3B(255, 101, 222);
	}
	else if (cell->getIdx() == 6)
	{
		brushColor = cocos2d::Color3B(181, 0, 255);
	}
	else if (cell->getIdx() == 7)
	{
		brushColor = cocos2d::Color3B::WHITE;
	}
	else if (cell->getIdx() == 8)
	{
		brushColor = cocos2d::Color3B::BLACK;
	}
	else if (cell->getIdx() == 9)
	{
		brushColor = cocos2d::Color3B::GRAY;
	}
	else if (cell->getIdx() == 10)
	{
		brushColor = cocos2d::Color3B(115, 65, 0);
	}
	else if (cell->getIdx() == 11)
	{
		brushColor = cocos2d::Color3B(255, 207, 156);
	}
	else if (cell->getIdx() == 12)
	{
		brushColor = cocos2d::Color3B(255, 231, 214);
	}
}

Size HelloWorld::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
	/*if (idx == 2)
	{
		return Size(100, 100);
	}*/
	return Size(36, 100);
}

TableViewCell * HelloWorld::tableCellAtIndex(TableView *table, ssize_t idx)
{
	for (int i = 0; i < 13; i++)
	{
		TableViewCell* tcell = table->cellAtIndex(i);
		if (tcell) {
			auto tsprite = (Sprite*)(tcell->getChildByTag(100));
			tsprite->setPosition(Vec2(0, 0));
		}
	}

	char str[100] = { 0 };
	for (int i = 0; i < 13; i++)
	{
		sprintf(str, "Images/crayon_%02d.png", i + 1);
		auto push = Sprite::create(str);
		crayons.pushBack(push);
		/*auto str = String::createWithFormat("Images/crayon_%02d.png", i + 1);
		auto sprite = Sprite::create(str->getCString());
		crayons.pushBack(sprite);*/
	}
	
	auto string = String::createWithFormat("%d", idx);
	TableViewCell *cell = table->dequeueCell();

	if (!cell)
	{
		cell = new CustomTableViewCell();
		cell->autorelease();

		log("idx 1 .. %d", idx);

		auto str = String::createWithFormat("Images/crayon_%02d.png", idx + 1);
		log("%s", str->getCString());
		auto sprite = Sprite::create(str->getCString());
		sprite->setAnchorPoint(Vec2::ZERO);
		sprite->setPosition(0, 0);
		sprite->setTag(100);
		sprite->setScale(0.5f);
		cell->addChild(sprite);

		auto label = LabelTTF::create(string->getCString(), "Helvetica", 20.0f);
		label->setPosition(Vec2::ZERO);
		label->setAnchorPoint(Vec2::ZERO);
		label->setTag(123);
		label->setColor(Color3B(0, 0, 0));
		cell->addChild(label);
	}
	else
	{
		log("idx 2 .. %d", idx);

		auto sprite1 = (Sprite*)(cell->getChildByTag(100));
		auto sprite2 = (Sprite*)(crayons.at(idx));
		sprite1->setTexture(sprite2->getTexture());

		auto label = (LabelTTF*)cell->getChildByTag(123);
		label->setString(string->getCString());
	}

	/*auto string = String::createWithFormat("%d", idx);
	TableViewCell *cell = table->dequeueCell();

	if (!cell)
	{
		cell = new CustomTableViewCell();
		cell->autorelease();

		if (count == 1)
		{
			auto sprite = Sprite::create("Images/crayon_01.png");
			sprite->setAnchorPoint(Vec2::ZERO);
			sprite->setPosition(Vec2(0, 0));
			sprite->setScale(0.5);
			cell->addChild(sprite);
		}
		else if (count == 2)
		{
			auto sprite = Sprite::create("Images/crayon_02.png");
			sprite->setAnchorPoint(Vec2::ZERO);
			sprite->setPosition(Vec2(0, 0));
			sprite->setScale(0.5);
			cell->addChild(sprite);
		}
		else if (count == 3)
		{
			auto sprite = Sprite::create("Images/crayon_03.png");
			sprite->setAnchorPoint(Vec2::ZERO);
			sprite->setPosition(Vec2(0, 0));
			sprite->setScale(0.5);
			cell->addChild(sprite);
		}
		else if (count == 4)
		{
			auto sprite = Sprite::create("Images/crayon_04.png");
			sprite->setAnchorPoint(Vec2::ZERO);
			sprite->setPosition(Vec2(0, 0));
			sprite->setScale(0.5);
			cell->addChild(sprite);
		}
		else if (count == 5)
		{
			auto sprite = Sprite::create("Images/crayon_05.png");
			sprite->setAnchorPoint(Vec2::ZERO);
			sprite->setPosition(Vec2(0, 0));
			sprite->setScale(0.5);
			cell->addChild(sprite);
		}
		else if (count == 6)
		{
			auto sprite = Sprite::create("Images/crayon_06.png");
			sprite->setAnchorPoint(Vec2::ZERO);
			sprite->setPosition(Vec2(0, 0));
			sprite->setScale(0.5);
			cell->addChild(sprite);
		}
		else if (count == 7)
		{
			auto sprite = Sprite::create("Images/crayon_07.png");
			sprite->setAnchorPoint(Vec2::ZERO);
			sprite->setPosition(Vec2(0, 0));
			sprite->setScale(0.5);
			cell->addChild(sprite);
		}
		else if (count == 8)
		{
			auto sprite = Sprite::create("Images/crayon_08.png");
			sprite->setAnchorPoint(Vec2::ZERO);
			sprite->setPosition(Vec2(0, 0));
			sprite->setScale(0.5);
			cell->addChild(sprite);
		}
		else if (count == 9)
		{
			auto sprite = Sprite::create("Images/crayon_09.png");
			sprite->setAnchorPoint(Vec2::ZERO);
			sprite->setPosition(Vec2(0, 0));
			sprite->setScale(0.5);
			cell->addChild(sprite);
		}
		else if (count == 10)
		{
			auto sprite = Sprite::create("Images/crayon_10.png");
			sprite->setAnchorPoint(Vec2::ZERO);
			sprite->setPosition(Vec2(0, 0));
			sprite->setScale(0.5);
			cell->addChild(sprite);
		}
		else if (count == 11)
		{
			auto sprite = Sprite::create("Images/crayon_11.png");
			sprite->setAnchorPoint(Vec2::ZERO);
			sprite->setPosition(Vec2(0, 0));
			sprite->setScale(0.5);
			cell->addChild(sprite);
		}
		else if (count == 12)
		{
			auto sprite = Sprite::create("Images/crayon_12.png");
			sprite->setAnchorPoint(Vec2::ZERO);
			sprite->setPosition(Vec2(0, 0));
			sprite->setScale(0.5);
			cell->addChild(sprite);
		}
		else
		{
			auto sprite = Sprite::create("Images/crayon_13.png");
			sprite->setAnchorPoint(Vec2::ZERO);
			sprite->setPosition(Vec2(0, 0));
			sprite->setScale(0.5);
			cell->addChild(sprite);
		}

		
		count++;
		auto label = LabelTTF::create(string->getCString(), "Helvetica", 20.0);
		label->setPosition(Vec2::ZERO);
		label->setAnchorPoint(Vec2::ZERO);
		label->setTag(123);
		label->setColor(Color3B::BLACK);
		cell->addChild(label);
	}
	else
	{
		auto label = (LabelTTF*)cell->getChildByTag(123);
		label->setString(string->getCString());
	}*/

	return cell;
}

ssize_t HelloWorld::numberOfCellsInTableView(TableView *table)
{
	return 13;
}