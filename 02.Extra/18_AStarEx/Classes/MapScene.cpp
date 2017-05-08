#include "MapScene.h"

USING_NS_CC;

Scene* MapScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MapScene::create();
	scene->addChild(layer);
	return scene;
}

bool MapScene::init()
{
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}
	/////////////////////////////////////////////

	// ȭ�� ������ ���ϱ�
	winSize = Director::getInstance()->getVisibleSize();

	// Ÿ�ϸ� �о� ���� 1
	tmap = TMXTiledMap::create("TileMaps/astar1.tmx");
	metainfo = tmap->getLayer("MetaInfo");
	tmap->setPosition(Vec2(winSize.width / 2 - tmap->getContentSize().width / 2, winSize.height / 2 - tmap->getContentSize().height / 2));

	// Ÿ�ϸ� �о� ���� 2
	/*tmap = TMXTiledMap::create("TileMaps/TestDesert.tmx");
	metainfo = tmap->getLayer("MetaInfo");

	metainfo->setVisible(false);*/
	this->addChild(tmap, 0, 11);	// z-order�� -1�� �ϸ� ȭ���� ������ �ʴ´�.

	// Ÿ�ϸʿ��� Objects��� ������ ������Ʈ ���̾��� ��ü�� ��������
	TMXObjectGroup* objects = tmap->getObjectGroup("Objects");

	// ������Ʈ ���̾�� SpawnPoint��� ������ �Ӽ��� �о� ����
	ValueMap spawnPoint = objects->getObject("SpawnPoint");

	int x = spawnPoint["x"].asInt();
	int y = spawnPoint["y"].asInt();

	// ĳ���� �ʱ�ȭ
	tamara = Sprite::create("grossinis_sister1.png");
	tmap->addChild(tamara, (int)tmap->getChildren().size());
	tamara->setPosition(Vec2(x, y));
	tamara->setScale(0.3f);

	openPath = new std::vector<AstarItem*>();
	closePath = new std::vector<AstarItem*>();
	myPath = new std::vector<Vec2>();

	// �̱� ��ġ ���� ��ġ ������ ���
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void MapScene::setViewpointCenter(Vec2 position)
{
	if (tmap->getMapSize().width * tmap->getTileSize().width < winSize.width ||
		tmap->getMapSize().height * tmap->getTileSize().height < winSize.height)
	{
		return;
	}

	// �Ķ���ͷ� ������ ��ġ�� ���� ȭ���� �����δ�.
	// �Ķ���ͷ� ������ ��ġ�� ���� ȭ���� �����δ�.
	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);

	x = MIN(x, (tmap->getMapSize().width * tmap->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (tmap->getMapSize().height * tmap->getTileSize().height) - winSize.height / 2);

	Vec2 actualPosition = Vec2(x, y);
	Vec2 centerOfView = Vec2(winSize.width / 2, winSize.height / 2);
	Vec2 viewPoint = centerOfView - actualPosition;

	this->setPosition(viewPoint);
}

// ���� ������ ���õ� Ÿ���� ��ġ�� �����´�.
Vec2 MapScene::tileCoordForPosition(Vec2 position)
{
	int x = position.x / tmap->getTileSize().width;
	int y = ((tmap->getMapSize().height * tmap->getTileSize().height) - position.y) / tmap->getTileSize().height;
	return Vec2(x, y);
}

// ���� Ÿ���� ��ġ�� ȭ�� ��ǥ�� �����´�.
Vec2 MapScene::positionForTileCoord(Vec2 position)
{
	int x = position.x * tmap->getTileSize().width + tmap->getTileSize().width / 2;
	int y = (tmap->getMapSize().height * tmap->getTileSize().height) - position.y * tmap->getTileSize().height - tmap->getTileSize().height / 2;
	return Vec2(x, y);
}

bool MapScene::onTouchBegan(Touch* touch, Event* event)
{
	return true;
}

void MapScene::onTouchEnded(Touch* touch, Event* event)
{
	auto touchPoint = touch->getLocation();
	touchPoint = tmap->convertToNodeSpace(touchPoint);

	if (touchPoint.x >= (tmap->getMapSize().width * tmap->getTileSize().width) ||
		touchPoint.y >= (tmap->getMapSize().height* tmap->getTileSize().height) ||
		touchPoint.y <= 0 ||
		touchPoint.x <= 0)
	{
		//log("���� ������ ��� ���� Ŭ���Ͽ����ϴ�.");
		return;
	}

	// �ǵ� ��ġ ���ϱ�
	Vec2 tileCoord = this->tileCoordForPosition(touchPoint);
	log("%f..%f", tileCoord.x, tileCoord.y);

	// ���� ��ġ�� Tile GID ���ϱ�
	int tileGid = this->metainfo->getTileGIDAt(tileCoord);

	if (tileGid)
	{
		// Ÿ�ϸʿ��� GID�� �ش��ϴ� �κ��� �Ӽ� �о� ����
		Value& properties = tmap->getPropertiesForGID(tileGid);

		if (!properties.isNull())
		{
			int wall = properties.asValueMap()["Wall"].asInt();
			if (wall == 1)
			{
				log("1. �̵� �Ұ����� �����Դϴ�.");
				return;
			}
		}
	}
	log("tileaGid : %d", tileGid);

	// A* �˻�
	Vec2 tamaraPos = tamara->getPosition();
	pCoordS = this->tileCoordForPosition(tamaraPos);
	pCoordE = this->tileCoordForPosition(touchPoint);
	this->AStarPathFind();
}

void MapScene::AStarPathFind()
{
	for (int i = 0; i < openPath->size(); i++)
	{
		auto tNode = (AstarItem*)(openPath->at(i));
		delete tNode;
	}
	openPath->clear();

	for (int i = 0; i < closePath->size(); i++)
	{
		auto tNode = (AstarItem*)(closePath->at(i));
		delete tNode;
	}
	closePath->clear();

	myPath->clear();
	AstarItem* temp1 = new AstarItem();
	temp1->mPos = pCoordS;

	closePath->push_back(temp1);

	int nMax = tmap->getMapSize().width * tmap->getMapSize().height;
	bool bFind = false;
	for (int i = 0; i < nMax; i++)
	{
		Vec2 tmp1 = temp1->mPos;

		// �̵��� ���� ��ġ(���Ͱ�) ���ϱ�
		Vec2 topLeft = Vec2(tmp1.x - 1, tmp1.y - 1);
		Vec2 topCenter = Vec2(tmp1.x, tmp1.y - 1);
		Vec2 topRight = Vec2(tmp1.x + 1, tmp1.y - 1);
		Vec2 left = Vec2(tmp1.x - 1, tmp1.y);
		Vec2 right = Vec2(tmp1.x + 1, tmp1.y);
		Vec2 bottomLeft = Vec2(tmp1.x - 1, tmp1.y + 1);
		Vec2 bottomCenter = Vec2(tmp1.x, tmp1.y + 1);
		Vec2 bottomRight = Vec2(tmp1.x + 1, tmp1.y + 1);

		// �̵� ������ ������ üũ�ϰ� ���Ϳ� �� �߰�
		isRoad(topLeft, tmp1, temp1->g, 14);
		isRoad(topCenter, tmp1, temp1->g, 10);
		isRoad(topRight, tmp1, temp1->g, 14);
		isRoad(left, tmp1, temp1->g, 10);
		isRoad(right, tmp1, temp1->g, 10);
		isRoad(bottomLeft, tmp1, temp1->g, 14);
		isRoad(bottomCenter, tmp1, temp1->g, 10);
		isRoad(bottomRight, tmp1, temp1->g, 14);

		// log("size1 .. %ld", openPath->size());

		// ��� ��� : F = G + H
		int cost1 = 100000000;
		Vec2 tmp2;
		int nErase = 0;
		for (int j = 0; j < openPath->size(); j++)
		{
			auto tNode = (AstarItem*)(openPath->at(j));
			int cost2 = tNode->f;
			if (cost2 < cost1)
			{
				cost1 = cost2;
				tmp2 = tNode->mPos;
				nErase = j;
			}
		}
		//log("Cost : %f .. %f", tmp2.x, tmp2.y);

		auto tNode = (AstarItem*)(openPath->at(nErase));
		closePath->push_back(tNode);

		openPath->erase(openPath->begin() + nErase);

		if (tmp2.equals(pCoordE))
		{
			//log("size3 .. %ld", closePath->size());
			bFind = true;
			this->makePass();
			break;
		}

		if (openPath->size() == 0)
		{
			break;
		}
		//log("size2 .. %ld .. (%d, %d)", openPath->size(), (int)tNode->mPos.x, (int)tNode->mPos..y);

		temp1 = new AstarItem();
		temp1 = tNode;
	}

	if (!bFind)
	{
		log("���� ã�� �� �����ϴ�.");
	}
}

void MapScene::isRoad(Vec2 mPos, Vec2 pPos, int cost1, int cost2)
{
	// log("Vec2(%d, %d) %d", (int)mPos.x, (int)mPos.y, cost1);

	// �̵� ������ ������ üũ 1 : �ʹ��� �� Ŭ�� üũ
	if (mPos.x >= tmap->getMapSize().width ||
		mPos.y >= tmap->getMapSize().height ||
		mPos.y < 0 ||
		mPos.x < 0)
	{
		return;
	}

	// �̵� ������ ������ üũ 2 : ���� closePath �ȿ� �ִ� ������� üũ
	for (int i = 0; i < closePath->size(); i++)
	{
		auto tNode = (AstarItem*)(closePath->at(i));

		if (mPos == tNode->mPos)
		{
			return;
		}
	}

	// �̵� ������ ������ üũ 3 : ���� openPath �ȿ� �ִ� ������� üũ
	for (int i = 0; i < openPath->size(); i++)
	{
		auto tNode = (AstarItem*)(openPath->at(i));

		if (mPos == tNode->mPos)
		{
			return;
		}
	}

	// �̵� ������ ������ üũ 4 : �ʾ��� ��ֹ� üũ

	// Ÿ�� ��ġ�� Tile GID ���ϱ�
	int tileGid = this->metainfo->getTileGIDAt(mPos);

	if (tileGid)
	{
		// Ÿ�ϸʿ��� GID�� �ش��ϴ� �κ��� �Ӽ� �о� ����
		Value properties = tmap->getPropertiesForGID(tileGid);

		if (!properties.isNull())
		{
			int wall = properties.asValueMap()["Wall"].asInt();
			if (wall == 1)
			{
				log("2.�̵� �Ұ����� �����Դϴ�.");
				return;
			}
		}
	}

	// �̵� ������ ������ üũ 5 : �̵��� �浹�� �ִٸ� �� ����
	if (cost2 == 14)
	{
		// (2, 2) --> (3, 1) : (2, 1)
		// (2, 2) --> (3, 1) : (3, 2)
		Vec2 pos1 = Vec2(pPos.x, mPos.y);
		int tileGid1 = this->metainfo->getTileGIDAt(pos1);
		if (tileGid1)
		{
			// Ÿ�ϸʿ��� GID�� �ش��ϴ� �κ��� �Ӽ� �о� ����
			Value properties = tmap->getPropertiesForGID(tileGid1);

			if (!properties.isNull())
			{
				int wall = properties.asValueMap()["Wall"].asInt();
				if (wall == 1)
				{
					return;
				}
			}
		}
		Vec2 pos2 = Vec2(mPos.x, pPos.y);
		int tileGid2 = this->metainfo->getTileGIDAt(pos2);
		if (tileGid2)
		{
			// Ÿ�ϸʿ��� GID�� �ش��ϴ� �κ��� �Ӽ� �о� ����
			Value properties = tmap->getPropertiesForGID(tileGid2);

			if (!properties.isNull())
			{
				int wall = properties.asValueMap()["Wall"].asInt();
				if (wall == 1)
				{
					return;
				}
			}
		}
	}

	// ���Ϳ� �̵��� ������ ���� �߰�
	AstarItem* temp2 = new AstarItem();
	temp2->mPos = mPos;
	temp2->pPos = pPos;
	temp2->g = cost1 + cost2;
	temp2->h = this->getHCost(mPos);
	temp2->f = temp2->g + temp2->h;

	//log("Vec2(%d, %d) %d .. %d", (int)temp2->mPos.x, (int)temp2->mPos.y, temp2->g, temp2->);
	openPath->push_back(temp2);

	return;
}

int MapScene::getHCost(Vec2 pos)
{
	return std::abs(pCoordE.x - pos.x) * 10 + std::abs(pCoordE.y - pos.y) * 10;
}

// �������κ��� ��������� �Ųٷ� �θ� ã�Ƽ� �̵� ��ο� �־� �ش�.
void MapScene::makePass()
{
	int nLast = (int)closePath->size() - 1;

	auto tNode1 = (AstarItem*)(closePath->at(nLast));
	myPath->push_back(tNode1->mPos);
	Vec2 pos1 = tNode1->pPos;

	while (1)
	{
		for (int j = nLast; j >= 0; j--)
		{
			auto tNode2 = (AstarItem*)(closePath->at(j));
			Vec2 pos2 = tNode2->mPos;
			if (pos1 == pos2)
			{
				myPath->push_back(pos2);
				pos1 = tNode2->pPos;
				break;
			}
		}
		if (pos1 == pCoordS)
		{
			break;
		}
	}
	this->movePass();
}

// ĳ���� �̵���Ű��
void MapScene::movePass()
{
	Vector<FiniteTimeAction*>* actions = new Vector<FiniteTimeAction*>();

	int nLast2 = (int)myPath->size() - 1;

	for (int i = nLast2; i >= 0; i--)
	{
		//log("MyPath1 : Vec2(%d, %d)", (int)myPath->at(i).x, (int)myPath->at(i).y);
		Vec2 pos = positionForTileCoord(myPath->at(i));
		//log("MyPath2 : Vec2(%d, %d)", (int)pos.x, (int)pos.y);
		auto act = MoveTo::create(0.5, pos);
		actions->pushBack(act);

		auto callback = CallFunc::create(CC_CALLBACK_0(MapScene::moveCamera, this));
		actions->pushBack(callback);
	}

	const Vector<FiniteTimeAction*> xyz = *actions;
	auto seq = Sequence::create(xyz);
	tamara->runAction(seq);

	delete actions;
}

void MapScene::moveCamera()
{
	//ĳ������ ��ġ�� ���� ȭ�� ��ġ ����
	log("1 : %d .. %d", (int)tamara->getPosition().x, (int)tamara->getPosition().y);
	Vec2 pos = tmap->convertToWorldSpace(tamara->getPosition());
	log("2 : %d .. %d", (int)pos.x, (int)pos.y);
	Vec2 pos2 = tamara->getPosition() + tmap->getPosition();
	log("3 : %d .. %d", (int)pos2.x, (int)pos2.y);

	this->setViewpointCenter(pos);
}