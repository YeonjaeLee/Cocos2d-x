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
	if (!Layer::init())
	{
		return false;
	}
	/////////////////////////////////////////////
	// 4 * 5 
	position1 = Vec2(0 + 10, 240 + 10);		poses.push_back(position1);
	position2 = Vec2(60 + 10, 240 + 10);	poses.push_back(position2);
	position3 = Vec2(120 + 10, 240 + 10);	poses.push_back(position3);
	position4 = Vec2(180 + 10, 240 + 10);	poses.push_back(position4);
	position5 = Vec2(0 + 10, 180 + 10);		poses.push_back(position5);
	position6 = Vec2(60 + 10, 180 + 10);	poses.push_back(position6);
	position7 = Vec2(120 + 10, 180 + 10);	poses.push_back(position7);
	position8 = Vec2(180 + 10, 180 + 10);	poses.push_back(position8);
	position9 = Vec2(0 + 10, 120 + 10);		poses.push_back(position9);
	position10 = Vec2(60 + 10, 120 + 10);	poses.push_back(position10);
	position11 = Vec2(120 + 10, 120 + 10);	poses.push_back(position11);
	position12 = Vec2(180 + 10, 120 + 10);	poses.push_back(position12);
	position13 = Vec2(0 + 10, 60 + 10);		poses.push_back(position13);
	position14 = Vec2(60 + 10, 60 + 10);	poses.push_back(position14);
	position15 = Vec2(120 + 10, 60 + 10);	poses.push_back(position15);
	position16 = Vec2(180 + 10, 60 + 10);	poses.push_back(position16);
	position17 = Vec2(0 + 10, 0 + 10);		poses.push_back(position17);
	position18 = Vec2(60 + 10, 0 + 10);		poses.push_back(position18);
	position19 = Vec2(120 + 10, 0 + 10);	poses.push_back(position19);
	position20 = Vec2(180 + 10, 0 + 10);	poses.push_back(position20);

	auto pReplayItem = MenuItemImage::create(
		"Images/REPLAY.png",
		"Images/REPLAYSELECTED.png",
		CC_CALLBACK_1(HelloWorld::doClick, this));
	pMenu_pReplayItem = Menu::create(pReplayItem, nullptr);
	pMenu_pReplayItem->setPosition(Vec2(240, 160));
	pMenu_pReplayItem->setVisible(false);
	this->addChild(pMenu_pReplayItem, 3);

	this->sprcreate();
	this->boxcreate();
	this->settingrand();

	return true;
}

void HelloWorld::sprcreate()
{
	int a = 0;
	for (int i = 1; i < 21; i++)
	{
		auto string = String::createWithFormat("Images/card%02d.png", a + 1);
		auto sprite = Sprite::create(string->getCString());
		sprs.pushBack(sprite);

		if (i % 2 == 0)
			a++;
	}
	a = 0;
	for (int i = 1; i < 21; i++)
	{
		auto spriteex = (Sprite*)(sprs.at(i - 1));
		spriteex->setAnchorPoint(Vec2(0, 0));
		spriteex->setPosition(poses.at(i - 1));
		spriteex->setScale(0.7);
		this->addChild(spriteex, 1, i);
	}
}

void HelloWorld::boxcreate()
{
	box1 = Sprite::create("Images/box_normal.png");
	box1->setAnchorPoint(Vec2(0, 0));
	box1->setPosition(position1);
	box1->setScale(0.7);
	this->addChild(box1, 2);

	box2 = Sprite::create("Images/box_normal.png");
	box2->setAnchorPoint(Vec2(0, 0));
	box2->setPosition(position2);
	box2->setScale(0.7);
	this->addChild(box2, 2);

	box3 = Sprite::create("Images/box_normal.png");
	box3->setAnchorPoint(Vec2(0, 0));
	box3->setPosition(position3);
	box3->setScale(0.7);
	this->addChild(box3, 2);

	box4 = Sprite::create("Images/box_normal.png");
	box4->setAnchorPoint(Vec2(0, 0));
	box4->setPosition(position4);
	box4->setScale(0.7);
	this->addChild(box4, 2);

	box5 = Sprite::create("Images/box_normal.png");
	box5->setAnchorPoint(Vec2(0, 0));
	box5->setPosition(position5);
	box5->setScale(0.7);
	this->addChild(box5, 2);

	box6 = Sprite::create("Images/box_normal.png");
	box6->setAnchorPoint(Vec2(0, 0));
	box6->setPosition(position6);
	box6->setScale(0.7);
	this->addChild(box6, 2);

	box7 = Sprite::create("Images/box_normal.png");
	box7->setAnchorPoint(Vec2(0, 0));
	box7->setPosition(position7);
	box7->setScale(0.7);
	this->addChild(box7, 2);

	box8 = Sprite::create("Images/box_normal.png");
	box8->setAnchorPoint(Vec2(0, 0));
	box8->setPosition(position8);
	box8->setScale(0.7);
	this->addChild(box8, 2);

	box9 = Sprite::create("Images/box_normal.png");
	box9->setAnchorPoint(Vec2(0, 0));
	box9->setPosition(position9);
	box9->setScale(0.7);
	this->addChild(box9, 2);

	box10 = Sprite::create("Images/box_normal.png");
	box10->setAnchorPoint(Vec2(0, 0));
	box10->setPosition(position10);
	box10->setScale(0.7);
	this->addChild(box10, 2);

	box11 = Sprite::create("Images/box_normal.png");
	box11->setAnchorPoint(Vec2(0, 0));
	box11->setPosition(position11);
	box11->setScale(0.7);
	this->addChild(box11, 2);

	box12 = Sprite::create("Images/box_normal.png");
	box12->setAnchorPoint(Vec2(0, 0));
	box12->setPosition(position12);
	box12->setScale(0.7);
	this->addChild(box12, 2);

	box13 = Sprite::create("Images/box_normal.png");
	box13->setAnchorPoint(Vec2(0, 0));
	box13->setPosition(position13);
	box13->setScale(0.7);
	this->addChild(box13, 2);

	box14 = Sprite::create("Images/box_normal.png");
	box14->setAnchorPoint(Vec2(0, 0));
	box14->setPosition(position14);
	box14->setScale(0.7);
	this->addChild(box14, 2);

	box15 = Sprite::create("Images/box_normal.png");
	box15->setAnchorPoint(Vec2(0, 0));
	box15->setPosition(position15);
	box15->setScale(0.7);
	this->addChild(box15, 2);

	box16 = Sprite::create("Images/box_normal.png");
	box16->setAnchorPoint(Vec2(0, 0));
	box16->setPosition(position16);
	box16->setScale(0.7);
	this->addChild(box16, 2);

	box17 = Sprite::create("Images/box_normal.png");
	box17->setAnchorPoint(Vec2(0, 0));
	box17->setPosition(position17);
	box17->setScale(0.7);
	this->addChild(box17, 2);

	box18 = Sprite::create("Images/box_normal.png");
	box18->setAnchorPoint(Vec2(0, 0));
	box18->setPosition(position18);
	box18->setScale(0.7);
	this->addChild(box18, 2);

	box19 = Sprite::create("Images/box_normal.png");
	box19->setAnchorPoint(Vec2(0, 0));
	box19->setPosition(position19);
	box19->setScale(0.7);
	this->addChild(box19, 2);

	box20 = Sprite::create("Images/box_normal.png");
	box20->setAnchorPoint(Vec2(0, 0));
	box20->setPosition(position20);
	box20->setScale(0.7);
	this->addChild(box20, 2);
}

void HelloWorld::settingrand()
{
	int a, b, temp = 0;
	srand((int)time(NULL));

	for (int i = 0; i < 20; i++)
	{
		nNum[i] = i + 1;
	}

	for (int i = 0; i < 40; i++)
	{
		a = rand() % 20;
		b = rand() % 20;
		temp = nNum[a];
		nNum[a] = nNum[b];
		nNum[b] = temp;
	}
	// 확인
	//nNum[0] = 1;	nNum[1] = 2;	nNum[2] = 3;	nNum[3] = 4;	nNum[4] = 5;	nNum[5] = 6;	nNum[6] = 7;	nNum[7] = 8;	nNum[8] = 9;	nNum[9] = 10;	nNum[10] = 11;	nNum[11] = 12;	nNum[12] = 13;	nNum[13] = 14;	nNum[14] = 15;	nNum[15] = 16;	nNum[16] = 17;	nNum[17] = 18;	nNum[18] = 19;	nNum[19] = 20;
	log("%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", nNum[0], nNum[1], nNum[2], nNum[3], nNum[4], nNum[5], nNum[6], nNum[7], nNum[8], nNum[9], nNum[10], nNum[11], nNum[12], nNum[13], nNum[14], nNum[15], nNum[16], nNum[17], nNum[18], nNum[19]);
	for (int i = 0; i < 20; i++)
	{
		pmovespr = (Sprite *)getChildByTag(nNum[i]);
		pmovespr->setPosition(poses.at(i));
	}
}

void HelloWorld::onEnter()
{
	Layer::onEnter();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void HelloWorld::onExit()
{
	//_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
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
	// 클릭지점 sprite 구하기
	if ((touchPoint.x > poses.at(0).x && touchPoint.x < poses.at(0).x + 60 - 5) && (touchPoint.y > poses.at(0).y && touchPoint.y < poses.at(0).y + 60 - 5))
	{
			if (count == 1 && state == 1)
			{
				log("중복선택");
				return;
			}
			count++;
			state = 1;
			clickspr = (Sprite*)getChildByTag(nNum[0]);
			clickpos = clickspr->getPosition();
			clickbox = box1;
			box1->setVisible(false);
			log("nNum[0]클릭! 현재 spr은 %d(%f, %f)", nNum[0], clickpos.x, clickpos.y);
	}
	else if ((touchPoint.x > poses.at(1).x && touchPoint.x < poses.at(1).x + 60 - 5) && (touchPoint.y > poses.at(1).y && touchPoint.y < poses.at(1).y + 60 - 5))
	{
		if (count == 1 && state == 2)
		{
			log("중복선택");
			return;
		}
		count++;
		state = 2;
		clickspr = (Sprite*)getChildByTag(nNum[1]);
		clickpos = clickspr->getPosition();
		clickbox = box2;
		box2->setVisible(false);
		log("nNum[1]클릭! 현재 spr은 %d(%f, %f)", nNum[1], clickpos.x, clickpos.y);
	}
	else if ((touchPoint.x > poses.at(2).x && touchPoint.x < poses.at(2).x + 60 - 5) && (touchPoint.y > poses.at(2).y && touchPoint.y < poses.at(2).y + 60 - 5))
	{
		if (count == 1 && state == 3)
		{
			log("중복선택");
			return;
		}
		count++;
		state = 3;
		clickspr = (Sprite*)getChildByTag(nNum[2]);
		clickpos = clickspr->getPosition();
		clickbox = box3;
		box3->setVisible(false);
		log("nNum[2]클릭! 현재 spr은 %d(%f, %f)", nNum[2], clickpos.x, clickpos.y);
	}
	else if ((touchPoint.x > poses.at(3).x && touchPoint.x < poses.at(3).x + 60 - 5) && (touchPoint.y > poses.at(3).y && touchPoint.y < poses.at(3).y + 60 - 5))
	{
		if (count == 1 && state == 4)
		{
			log("중복선택");
			return;
		}
		count++;
		state = 4;
		clickspr = (Sprite*)getChildByTag(nNum[3]);
		clickpos = clickspr->getPosition();
		clickbox = box4;
		box4->setVisible(false);
		log("nNum[3]클릭! 현재 spr은 %d(%f, %f)", nNum[3], clickpos.x, clickpos.y);
	}
	else if ((touchPoint.x > poses.at(4).x && touchPoint.x < poses.at(4).x + 60 - 5) && (touchPoint.y > poses.at(4).y && touchPoint.y < poses.at(4).y + 60 - 5))
	{
		if (count == 1 && state == 5)
		{
			log("중복선택");
			return;
		}
		count++;
		state = 5;
		clickspr = (Sprite*)getChildByTag(nNum[4]);
		clickpos = clickspr->getPosition();
		clickbox = box5;
		box5->setVisible(false);
		log("nNum[4]클릭! 현재 spr은 %d(%f, %f)", nNum[4], clickpos.x, clickpos.y);
	}
	else if ((touchPoint.x > poses.at(5).x && touchPoint.x < poses.at(5).x + 60 - 5) && (touchPoint.y > poses.at(5).y && touchPoint.y < poses.at(5).y + 60 - 5))
	{
		if (count == 1 && state == 6)
		{
			log("중복선택");
			return;
		}
		count++;
		state = 6;
		clickspr = (Sprite*)getChildByTag(nNum[5]);
		clickpos = clickspr->getPosition();
		clickbox = box6;
		box6->setVisible(false);
		log("nNum[5]클릭! 현재 spr은 %d(%f, %f)", nNum[5], clickpos.x, clickpos.y);
	}
	else if ((touchPoint.x > poses.at(6).x && touchPoint.x < poses.at(6).x + 60 - 5) && (touchPoint.y > poses.at(6).y && touchPoint.y < poses.at(6).y + 60 - 5))
	{
		if (count == 1 && state == 7)
		{
			log("중복선택");
			return;
		}
		count++;
		state = 7;
		clickspr = (Sprite*)getChildByTag(nNum[6]);
		clickpos = clickspr->getPosition();
		clickbox = box7;
		box7->setVisible(false);
		log("nNum[6]클릭! 현재 spr은 %d(%f, %f)", nNum[6], clickpos.x, clickpos.y);
	}
	else if ((touchPoint.x > poses.at(7).x && touchPoint.x < poses.at(7).x + 60 - 5) && (touchPoint.y > poses.at(7).y && touchPoint.y < poses.at(7).y + 60 - 5))
	{
		if (count == 1 && state == 8)
		{
			log("중복선택");
			return;
		}
		count++;
		state = 8;
		clickspr = (Sprite*)getChildByTag(nNum[7]);
		clickpos = clickspr->getPosition();
		clickbox = box8;
		box8->setVisible(false);
		log("nNum[7]클릭! 현재 spr은 %d(%f, %f)", nNum[7], clickpos.x, clickpos.y);
	}
	else if ((touchPoint.x > poses.at(8).x && touchPoint.x < poses.at(8).x + 60 - 5) && (touchPoint.y > poses.at(8).y && touchPoint.y < poses.at(8).y + 60 - 5))
	{
		if (count == 1 && state == 9)
		{
			log("중복선택");
			return;
		}
		count++;
		state = 9;
		clickspr = (Sprite*)getChildByTag(nNum[8]);
		clickpos = clickspr->getPosition();
		clickbox = box9;
		box9->setVisible(false);
		log("nNum[8]클릭! 현재 spr은 %d(%f, %f)", nNum[8], clickpos.x, clickpos.y);
	}
	else if ((touchPoint.x > poses.at(9).x && touchPoint.x < poses.at(9).x + 60 - 5) && (touchPoint.y > poses.at(9).y && touchPoint.y < poses.at(9).y + 60 - 5))
	{
		if (count == 1 && state == 10)
		{
			log("중복선택");
			return;
		}
		count++;
		state = 10;
		clickspr = (Sprite*)getChildByTag(nNum[9]);
		clickpos = clickspr->getPosition();
		clickbox = box10;
		box10->setVisible(false);
		log("nNum[9]클릭! 현재 spr은 %d(%f, %f)", nNum[9], clickpos.x, clickpos.y);
	}
	else if ((touchPoint.x > poses.at(10).x && touchPoint.x < poses.at(10).x + 60 - 5) && (touchPoint.y > poses.at(10).y && touchPoint.y < poses.at(10).y + 60 - 5))
	{
		if (count == 1 && state == 11)
		{
			log("중복선택");
			return;
		}
		count++;
		state = 11;
		clickspr = (Sprite*)getChildByTag(nNum[10]);
		clickpos = clickspr->getPosition();
		clickbox = box11;
		box11->setVisible(false);
		log("nNum[10]클릭! 현재 spr은 %d(%f, %f)", nNum[10], clickpos.x, clickpos.y);
	}
	else if ((touchPoint.x > poses.at(11).x && touchPoint.x < poses.at(11).x + 60 - 5) && (touchPoint.y > poses.at(11).y && touchPoint.y < poses.at(11).y + 60 - 5))
	{
		if (count == 1 && state == 12)
		{
			log("중복선택");
			return;
		}
		count++;
		state = 12;
		clickspr = (Sprite*)getChildByTag(nNum[11]);
		clickpos = clickspr->getPosition();
		clickbox = box12;
		box12->setVisible(false);
		log("nNum[11]클릭! 현재 spr은 %d(%f, %f)", nNum[11], clickpos.x, clickpos.y);
	}
	else if ((touchPoint.x > poses.at(12).x && touchPoint.x < poses.at(12).x + 60 - 5) && (touchPoint.y > poses.at(12).y && touchPoint.y < poses.at(12).y + 60 - 5))
	{
		if (count == 1 && state == 13)
		{
			log("중복선택");
			return;
		}
		count++;
		state = 13;
		clickspr = (Sprite*)getChildByTag(nNum[12]);
		clickpos = clickspr->getPosition();
		clickbox = box13;
		box13->setVisible(false);
		log("nNum[12]클릭! 현재 spr은 %d(%f, %f)", nNum[12], clickpos.x, clickpos.y);
	}
	else if ((touchPoint.x > poses.at(13).x && touchPoint.x < poses.at(13).x + 60 - 5) && (touchPoint.y > poses.at(13).y && touchPoint.y < poses.at(13).y + 60 - 5))
	{
		if (count == 1 && state == 14)
		{
			log("중복선택");
			return;
		}
		count++;
		state = 14;
		clickspr = (Sprite*)getChildByTag(nNum[13]);
		clickpos = clickspr->getPosition();
		clickbox = box14;
		box14->setVisible(false);
		log("nNum[13]클릭! 현재 spr은 %d(%f, %f)", nNum[13], clickpos.x, clickpos.y);
	}
	else if ((touchPoint.x > poses.at(14).x && touchPoint.x < poses.at(14).x + 60 - 5) && (touchPoint.y > poses.at(14).y && touchPoint.y < poses.at(14).y + 60 - 5))
	{
		if (count == 1 && state == 15)
		{
			log("중복선택");
			return;
		}
		count++;
		state = 15;
		clickspr = (Sprite*)getChildByTag(nNum[14]);
		clickpos = clickspr->getPosition();
		clickbox = box15;
		box15->setVisible(false);
		log("nNum[14]클릭! 현재 spr은 %d(%f, %f)", nNum[14], clickpos.x, clickpos.y);
	}
	else if ((touchPoint.x > poses.at(15).x && touchPoint.x < poses.at(15).x + 60 - 5) && (touchPoint.y > poses.at(15).y && touchPoint.y < poses.at(15).y + 60 - 5))
	{
		if (count == 1 && state == 16)
		{
			log("중복선택");
			return;
		}
		count++;
		state = 16;
		clickspr = (Sprite*)getChildByTag(nNum[15]);
		clickpos = clickspr->getPosition();
		clickbox = box16;
		box16->setVisible(false);
		log("nNum[15]클릭! 현재 spr은 %d(%f, %f)", nNum[15], clickpos.x, clickpos.y);
	}
	else if ((touchPoint.x > poses.at(16).x && touchPoint.x < poses.at(16).x + 60 - 5) && (touchPoint.y > poses.at(16).y && touchPoint.y < poses.at(16).y + 60 - 5))
	{
		if (count == 1 && state == 17)
		{
			log("중복선택");
			return;
		}
		count++;
		state = 17;
		clickspr = (Sprite*)getChildByTag(nNum[16]);
		clickpos = clickspr->getPosition();
		clickbox = box17;
		box17->setVisible(false);
		log("nNum[16]클릭! 현재 spr은 %d(%f, %f)", nNum[16], clickpos.x, clickpos.y);
	}
	else if ((touchPoint.x > poses.at(17).x && touchPoint.x < poses.at(17).x + 60 - 5) && (touchPoint.y > poses.at(17).y && touchPoint.y < poses.at(17).y + 60 - 5))
	{
		if (count == 1 && state == 18)
		{
			log("중복선택");
			return;
		}
		count++;
		state = 18;
		clickspr = (Sprite*)getChildByTag(nNum[17]);
		clickpos = clickspr->getPosition();
		clickbox = box18;
		box18->setVisible(false);
		log("nNum[17]클릭! 현재 spr은 %d(%f, %f)", nNum[17], clickpos.x, clickpos.y);
	}
	else if ((touchPoint.x > poses.at(18).x && touchPoint.x < poses.at(18).x + 60 - 5) && (touchPoint.y > poses.at(18).y && touchPoint.y < poses.at(18).y + 60 - 5))
	{
		if (count == 1 && state == 19)
		{
			log("중복선택");
			return;
		}
		count++;
		state = 19;
		clickspr = (Sprite*)getChildByTag(nNum[18]);
		clickpos = clickspr->getPosition();
		clickbox = box19;
		box19->setVisible(false);
		log("nNum[18]클릭! 현재 spr은 %d(%f, %f)", nNum[18], clickpos.x, clickpos.y);
	}
	else if ((touchPoint.x > poses.at(19).x && touchPoint.x < poses.at(19).x + 60 - 5) && (touchPoint.y > poses.at(19).y && touchPoint.y < poses.at(19).y + 60 - 5))
	{
		if (count == 1 && state == 20)
		{
			log("중복선택");
			return;
		}
		count++;
		state = 20;
		clickspr = (Sprite*)getChildByTag(nNum[19]);
		clickpos = clickspr->getPosition();
		clickbox = box20;
		box20->setVisible(false);
		log("nNum[19]클릭! 현재 spr은 %d(%f, %f)", nNum[19], clickpos.x, clickpos.y);
	}
	else
	{
		log("잘못클릭하셨습니다.");
	}

	if (count == 1)
	{
		clickspr1 = clickspr;
		clickbox1 = clickbox;
		state1 = state;
		log("1번째 %d", state);
	}
	else if (count == 2)
	{
		clickspr2 = clickspr;
		clickbox2 = clickbox;
		state2 = state;
		log("2번째 %d", state);
	}
	this->vsspr();
	this->endok();
}

void HelloWorld::vsspr()
{
	if (count == 2)
	{
		log("%d vs %d", clickspr1->getTag(), clickspr2->getTag());
		auto myActionForward1 = RotateTo::create(0.25, 30);
		auto myActionForward2 = RotateTo::create(0.5, -30);
		auto myActionForward3 = RotateTo::create(0.5, 30);
		auto myAction = Sequence::create(myActionForward1, myActionForward2, myActionForward3, Hide::create(), nullptr);

		if ((clickspr1->getTag() == 1 && clickspr2->getTag() == 2) || (clickspr1->getTag() == 2 && clickspr2->getTag() == 1))
		{
			clickspr1->setAnchorPoint(Vec2(0.5, 0.5));
			clickspr2->setAnchorPoint(Vec2(0.5, 0.5));
			clickspr1->setPosition(Vec2(clickspr1->getPosition().x + 29, clickspr1->getPosition().y + 29));
			clickspr2->setPosition(Vec2(clickspr2->getPosition().x + 29, clickspr2->getPosition().y + 29));
			clickspr1->runAction(myAction);
			clickspr2->runAction(myAction->clone());

			this->doParticles(Vec2(clickspr1->getPosition().x, clickspr1->getPosition().y));
			this->doParticles(Vec2(clickspr2->getPosition().x, clickspr2->getPosition().y));
			this->vsmovepos(state1);
			this->vsmovepos(state2);
		}
		else if ((clickspr1->getTag() == 3 && clickspr2->getTag() == 4) || (clickspr1->getTag() == 4 && clickspr2->getTag() == 3))
		{
			clickspr1->setAnchorPoint(Vec2(0.5, 0.5));
			clickspr2->setAnchorPoint(Vec2(0.5, 0.5));
			clickspr1->setPosition(Vec2(clickspr1->getPosition().x + 29, clickspr1->getPosition().y + 29));
			clickspr2->setPosition(Vec2(clickspr2->getPosition().x + 29, clickspr2->getPosition().y + 29));
			clickspr1->runAction(myAction);
			clickspr2->runAction(myAction->clone());

			this->doParticles(Vec2(clickspr1->getPosition().x, clickspr1->getPosition().y));
			this->doParticles(Vec2(clickspr2->getPosition().x, clickspr2->getPosition().y));
			this->vsmovepos(state1);
			this->vsmovepos(state2);
		}
		else if ((clickspr1->getTag() == 5 && clickspr2->getTag() == 6) || (clickspr1->getTag() == 6 && clickspr2->getTag() == 5))
		{
			clickspr1->setAnchorPoint(Vec2(0.5, 0.5));
			clickspr2->setAnchorPoint(Vec2(0.5, 0.5));
			clickspr1->setPosition(Vec2(clickspr1->getPosition().x + 29, clickspr1->getPosition().y + 29));
			clickspr2->setPosition(Vec2(clickspr2->getPosition().x + 29, clickspr2->getPosition().y + 29));
			clickspr1->runAction(myAction);
			clickspr2->runAction(myAction->clone());

			this->doParticles(Vec2(clickspr1->getPosition().x, clickspr1->getPosition().y));
			this->doParticles(Vec2(clickspr2->getPosition().x, clickspr2->getPosition().y));
			this->vsmovepos(state1);
			this->vsmovepos(state2);
		}
		else if ((clickspr1->getTag() == 7 && clickspr2->getTag() == 8) || (clickspr1->getTag() == 8 && clickspr2->getTag() == 7))
		{
			clickspr1->setAnchorPoint(Vec2(0.5, 0.5));
			clickspr2->setAnchorPoint(Vec2(0.5, 0.5));
			clickspr1->setPosition(Vec2(clickspr1->getPosition().x + 29, clickspr1->getPosition().y + 29));
			clickspr2->setPosition(Vec2(clickspr2->getPosition().x + 29, clickspr2->getPosition().y + 29));
			clickspr1->runAction(myAction);
			clickspr2->runAction(myAction->clone());

			this->doParticles(Vec2(clickspr1->getPosition().x, clickspr1->getPosition().y));
			this->doParticles(Vec2(clickspr2->getPosition().x, clickspr2->getPosition().y));
			this->vsmovepos(state1);
			this->vsmovepos(state2);
		}
		else if ((clickspr1->getTag() == 9 && clickspr2->getTag() == 10) || (clickspr1->getTag() == 10 && clickspr2->getTag() == 9))
		{
			clickspr1->setAnchorPoint(Vec2(0.5, 0.5));
			clickspr2->setAnchorPoint(Vec2(0.5, 0.5));
			clickspr1->setPosition(Vec2(clickspr1->getPosition().x + 29, clickspr1->getPosition().y + 29));
			clickspr2->setPosition(Vec2(clickspr2->getPosition().x + 29, clickspr2->getPosition().y + 29));
			clickspr1->runAction(myAction);
			clickspr2->runAction(myAction->clone());

			this->doParticles(Vec2(clickspr1->getPosition().x, clickspr1->getPosition().y));
			this->doParticles(Vec2(clickspr2->getPosition().x, clickspr2->getPosition().y));
			this->vsmovepos(state1);
			this->vsmovepos(state2);
		}
		else if ((clickspr1->getTag() == 11 && clickspr2->getTag() == 12) || (clickspr1->getTag() == 12 && clickspr2->getTag() == 11))
		{
			clickspr1->setAnchorPoint(Vec2(0.5, 0.5));
			clickspr2->setAnchorPoint(Vec2(0.5, 0.5));
			clickspr1->setPosition(Vec2(clickspr1->getPosition().x + 29, clickspr1->getPosition().y + 29));
			clickspr2->setPosition(Vec2(clickspr2->getPosition().x + 29, clickspr2->getPosition().y + 29));
			clickspr1->runAction(myAction);
			clickspr2->runAction(myAction->clone());

			this->doParticles(Vec2(clickspr1->getPosition().x, clickspr1->getPosition().y));
			this->doParticles(Vec2(clickspr2->getPosition().x, clickspr2->getPosition().y));
			this->vsmovepos(state1);
			this->vsmovepos(state2);
		}
		else if ((clickspr1->getTag() == 13 && clickspr2->getTag() == 14) || (clickspr1->getTag() == 14 && clickspr2->getTag() == 13))
		{
			clickspr1->setAnchorPoint(Vec2(0.5, 0.5));
			clickspr2->setAnchorPoint(Vec2(0.5, 0.5));
			clickspr1->setPosition(Vec2(clickspr1->getPosition().x + 29, clickspr1->getPosition().y + 29));
			clickspr2->setPosition(Vec2(clickspr2->getPosition().x + 29, clickspr2->getPosition().y + 29));
			clickspr1->runAction(myAction);
			clickspr2->runAction(myAction->clone());

			this->doParticles(Vec2(clickspr1->getPosition().x, clickspr1->getPosition().y));
			this->doParticles(Vec2(clickspr2->getPosition().x, clickspr2->getPosition().y));
			this->vsmovepos(state1);
			this->vsmovepos(state2);
		}
		else if ((clickspr1->getTag() == 15 && clickspr2->getTag() == 16) || (clickspr1->getTag() == 16 && clickspr2->getTag() == 15))
		{
			clickspr1->setAnchorPoint(Vec2(0.5, 0.5));
			clickspr2->setAnchorPoint(Vec2(0.5, 0.5));
			clickspr1->setPosition(Vec2(clickspr1->getPosition().x + 29, clickspr1->getPosition().y + 29));
			clickspr2->setPosition(Vec2(clickspr2->getPosition().x + 29, clickspr2->getPosition().y + 29));
			clickspr1->runAction(myAction);
			clickspr2->runAction(myAction->clone());

			this->doParticles(Vec2(clickspr1->getPosition().x, clickspr1->getPosition().y));
			this->doParticles(Vec2(clickspr2->getPosition().x, clickspr2->getPosition().y));
			this->vsmovepos(state1);
			this->vsmovepos(state2);
		}
		else if ((clickspr1->getTag() == 17 && clickspr2->getTag() == 18) || (clickspr1->getTag() == 18 && clickspr2->getTag() == 17))
		{
			clickspr1->setAnchorPoint(Vec2(0.5, 0.5));
			clickspr2->setAnchorPoint(Vec2(0.5, 0.5));
			clickspr1->setPosition(Vec2(clickspr1->getPosition().x + 29, clickspr1->getPosition().y + 29));
			clickspr2->setPosition(Vec2(clickspr2->getPosition().x + 29, clickspr2->getPosition().y + 29));
			clickspr1->runAction(myAction);
			clickspr2->runAction(myAction->clone());

			this->doParticles(Vec2(clickspr1->getPosition().x, clickspr1->getPosition().y));
			this->doParticles(Vec2(clickspr2->getPosition().x, clickspr2->getPosition().y));
			this->vsmovepos(state1);
			this->vsmovepos(state2);
		}
		else if ((clickspr1->getTag() == 19 && clickspr2->getTag() == 20) || (clickspr1->getTag() == 20 && clickspr2->getTag() == 19))
		{
			clickspr1->setAnchorPoint(Vec2(0.5, 0.5));
			clickspr2->setAnchorPoint(Vec2(0.5, 0.5));
			clickspr1->setPosition(Vec2(clickspr1->getPosition().x + 29, clickspr1->getPosition().y + 29));
			clickspr2->setPosition(Vec2(clickspr2->getPosition().x + 29, clickspr2->getPosition().y + 29));
			clickspr1->runAction(myAction);
			clickspr2->runAction(myAction->clone());
			
			this->doParticles(Vec2(clickspr1->getPosition().x, clickspr1->getPosition().y));
			this->doParticles(Vec2(clickspr2->getPosition().x, clickspr2->getPosition().y));
			this->vsmovepos(state1);
			this->vsmovepos(state2);
		}
		else
		{
			log("불일치");
			auto myActionMove1 = MoveBy::create(0.2, Vec2(5, 0));
			auto myActionMove2 = MoveBy::create(0.2, Vec2(-10, 0));
			auto myAction = Sequence::create(myActionMove1, myActionMove2, myActionMove1, nullptr);
			clickspr1->runAction(myAction);
			clickspr2->runAction(myAction->clone());

			clickbox1->setVisible(true);
			clickbox1->setOpacity(20.0);
			clickbox2->setVisible(true);
			clickbox2->setOpacity(20.0);
			auto myboxActionDelay = DelayTime::create(0.6);
			auto myboxActionFadeIn = FadeIn::create(0.3);
			auto myboxAction = Sequence::create(myboxActionDelay, myboxActionFadeIn, nullptr);
			clickbox1->runAction(myboxAction);
			clickbox2->runAction(myboxAction->clone());
		}
		count = 0;
		state = 0;
	}
}

void HelloWorld::vsmovepos(int state)
{
	for (int i = 0; i < 20; i++)
	{
		if (state == i + 1)
		{
			log("position%d -> 600, 600", i+1);
			poses.at(i) = Vec2(600, 600);
		}
	}
}

void HelloWorld::doParticles(Vec2 position)
{
	ParticleSystem* particleTest = ParticleFlower::create();
	auto texture = Director::getInstance()->getTextureCache()->addImage("Images/stars.png");
	particleTest->setTexture(texture);

	if (particleTest != NULL)
	{
		particleTest->setScale(0.7);
		particleTest->setDuration(0.1);
		particleTest->setPosition(position);
		this->addChild(particleTest,4);
	}
}

void HelloWorld::endok()
{
	int okstate = 0;
	for (int i = 0; i < 20; i++)
	{
		if (poses.at(i) != Vec2(600, 600))
		{
			okstate = 1;
		}
	}
	if (okstate == 0)
	{
		pMenu_pReplayItem->setVisible(true);
	}
}

void HelloWorld::doClick(Ref* pSender)
{
	log("Replay 버튼 클릭. ");
	pMenu_pReplayItem->setVisible(false);
	sprs.clear();
	poses.clear();

	auto pScene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1, pScene, Color3B::BLACK));
}