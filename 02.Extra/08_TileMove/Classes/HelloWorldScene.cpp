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
	// 화면 사이즈 구하기
	winSize = Director::getInstance()->getWinSize();

	// 타일맵 읽어오기
	tmap = TMXTiledMap::create("TileMaps/TestDesert_2.tmx");
	background = tmap->getLayer("Background");
	items = tmap->getLayer("Items");
	metainfo = tmap->getLayer("MetaInfo");
	metainfo->setVisible(false);
	this->addChild(tmap, 0, 11);// z-order를 -1로 지정하면 화면이 나오지 않는다.

	// 타일앱에서 Object라고 지정한 오브젝트 레이어의 객체들 가져오기
	TMXObjectGroup* objects = tmap->getObjectGroup("Objects");

	// 오브젝트 레이어에서 SpqwnPoint 라고 지정한 속성값 읽어오기
	ValueMap spawnPoint = objects->getObject("SpawnPoint");

	int x = spawnPoint["x"].asInt();
	int y = spawnPoint["y"].asInt();

	return true;
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
	_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);

	Layer::onExit();
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
	return true;
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{
	auto touchPoint = touch->getLocation();
	touchPoint = this->convertToNodeSpace(touchPoint);
	this->setPlayerPosition(touchPoint);
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
			std::string item1 = properties.asValueMap()["Items"].asString();
			if (item1 == "apple")
			{
				int nVecX = rand() % 10;
				int nVecY = rand() % 10;

				int tileGid2 = this->items->getTileGIDAt(tileCoord);
				int tileGid3 = this->metainfo->getTileGIDAt(tileCoord);

				items->setTileGID(tileGid2, Vec2(nVecX, nVecY));
				metainfo->setTileGID(tileGid3, Vec2(nVecX, nVecY));
				this->metainfo->removeTileAt(tileCoord);
				items->removeTileAt(tileCoord);

				log("APPLE 아이템 획득!!!");

				this->metainfo->removeTileAt(tileCoord);
				this->items->removeTileAt(tileCoord);
			}
			if (item1 == "banana")
			{
				/*this->metainfo->removeTileAt(tileCoord);
				items->removeTileAt(tileCoord);*/

				log("BANANA 아이템 획득!!!");
			}
		}
	}
}