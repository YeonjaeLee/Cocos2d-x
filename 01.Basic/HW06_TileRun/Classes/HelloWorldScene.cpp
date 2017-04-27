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

	tmap = TMXTiledMap::create("TileMaps/TileRun3.tmx");
	background = tmap->getLayer("Background");
	metainfo = tmap->getLayer("MetaInfo");
	metainfo->setVisible(false);
	this->addChild(tmap, 0, 11);

	TMXObjectGroup* objects = tmap->getObjectGroup("Objects");
	ValueMap spawnPoint = objects->getObject("SpawnPoint");

	int x = spawnPoint["x"].asInt();
	int y = spawnPoint["y"].asInt();

	womanPosition = Vec2(x, y);
	this->createWoman();
	
	this->schedule(schedule_selector(HelloWorld::myTick), 1.0f / 60);

	return true;
}

void HelloWorld::createWoman()
{
	woman = Sprite::create("Images/grossinis_sister1.png");
	woman->setPosition(womanPosition);
	woman->setScale(0.5);
	this->addChild(woman);
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
			std::string cliff = properties.asValueMap()["Cliff"].asString();
			if (cliff == "YES")
			{
				log("낭떨어지...");
				return;
			}
		}
	}
}

void HelloWorld::myTick(float f)
{
	tmap->setPosition(Vec2(0 + i, 0));
	this->setPlayerPosition(Vec2(womanPosition.x - i, womanPosition.y));
	i--;
	if (i == -704)
	{
		i = 0;
	}
}