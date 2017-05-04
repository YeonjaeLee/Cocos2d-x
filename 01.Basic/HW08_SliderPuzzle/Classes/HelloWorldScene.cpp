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
	position1 = Vec2(0 + 10, 200 + 10);
	position2 = Vec2(100 + 10, 200 + 10);
	position3 = Vec2(200 + 10, 200 + 10);
	position4 = Vec2(0 + 10, 100 + 10);
	position5 = Vec2(100 + 10, 100 + 10);
	position6 = Vec2(200 + 10, 100 + 10);
	position7 = Vec2(0 + 10, 0 + 10);
	position8 = Vec2(100 + 10, 0 + 10);
	position9 = Vec2(200 + 10, 0 + 10);

	spr1 = Sprite::create("Images/sample.png", Rect(0, 0, 98, 98));
	spr1->setAnchorPoint(Vec2(0, 0));
	spr1->setPosition(position1);
	this->addChild(spr1, 1, 1);

	spr2 = Sprite::create("Images/sample.png", Rect(100, 0, 98, 98));
	spr2->setAnchorPoint(Vec2(0, 0));
	spr2->setPosition(position2);
	this->addChild(spr2, 1, 2);

	spr3 = Sprite::create("Images/sample.png", Rect(200, 0, 98, 98));
	spr3->setAnchorPoint(Vec2(0, 0));
	spr3->setPosition(position3);
	this->addChild(spr3, 1, 3);

	spr4 = Sprite::create("Images/sample.png", Rect(0, 100, 98, 98));
	spr4->setAnchorPoint(Vec2(0, 0));
	spr4->setPosition(position4);
	this->addChild(spr4, 1, 4);

	spr5 = Sprite::create("Images/sample.png", Rect(100, 100, 98, 98));
	spr5->setAnchorPoint(Vec2(0, 0));
	spr5->setPosition(position5);
	this->addChild(spr5, 1, 5);

	spr6 = Sprite::create("Images/sample.png", Rect(200, 100, 98, 98));
	spr6->setAnchorPoint(Vec2(0, 0));
	spr6->setPosition(position6);
	this->addChild(spr6, 1, 6);

	spr7 = Sprite::create("Images/sample.png", Rect(0, 200, 98, 98));
	spr7->setAnchorPoint(Vec2(0, 0));
	spr7->setPosition(position7);
	this->addChild(spr7, 1, 7);

	spr8 = Sprite::create("Images/sample.png", Rect(100, 200, 98, 98));
	spr8->setAnchorPoint(Vec2(0, 0));
	spr8->setPosition(position8);
	this->addChild(spr8, 1, 8);

	spr9 = Sprite::create("Images/sample.png", Rect(200, 200, 98, 98));
	spr9->setAnchorPoint(Vec2(0, 0));
	spr9->setPosition(position9);
	this->addChild(spr9, 1, 9);

	this->settingrand();
	hidesprtag = nNum[8];

	return true;
}

void HelloWorld::settingrand()
{
	int a, b, temp = 0;
	srand((int)time(NULL));

	for (int i = 0; i < 9; i++)
	{
		nNum[i] = i + 1;
	}

	for (int i = 0; i < 18; i++)
	{
		a = rand() % 9;
		b = rand() % 9;
		temp = nNum[a];
		nNum[a] = nNum[b];
		nNum[b] = temp;
	}
	// 확인
	/*nNum[0] = 1;
	nNum[1] = 2;
	nNum[2] = 3;
	nNum[3] = 4;
	nNum[4] = 5;
	nNum[5] = 6;
	nNum[6] = 7;
	nNum[7] = 9;
	nNum[8] = 8;*/
	for (int i = 0; i < 9; i++)
	{
		pmovespr = (Sprite *)getChildByTag(nNum[i]);
		if (i == 0)
		{
			Vec2 onepoint = position1 - pmovespr->getPosition();
			auto myActionForward = MoveBy::create(2, onepoint);
			auto myAction = Sequence::create(myActionForward, nullptr);

			pmovespr->runAction(myAction);
		}
		else if (i == 1)
		{
			Vec2 onepoint = position2 - pmovespr->getPosition();
			auto myActionForward = MoveBy::create(2, onepoint);
			auto myAction = Sequence::create(myActionForward, nullptr);

			pmovespr->runAction(myAction);
		}
		else if (i == 2)
		{
			Vec2 onepoint = position3 - pmovespr->getPosition();
			auto myActionForward = MoveBy::create(2, onepoint);
			auto myAction = Sequence::create(myActionForward, nullptr);

			pmovespr->runAction(myAction);
		}
		else if (i == 3)
		{
			Vec2 onepoint = position4 - pmovespr->getPosition();
			auto myActionForward = MoveBy::create(2, onepoint);
			auto myAction = Sequence::create(myActionForward, nullptr);

			pmovespr->runAction(myAction);
		}
		else if (i == 4)
		{
			Vec2 onepoint = position5 - pmovespr->getPosition();
			auto myActionForward = MoveBy::create(2, onepoint);
			auto myAction = Sequence::create(myActionForward, nullptr);

			pmovespr->runAction(myAction);
		}
		else if (i == 5)
		{
			Vec2 onepoint = position6 - pmovespr->getPosition();
			auto myActionForward = MoveBy::create(2, onepoint);
			auto myAction = Sequence::create(myActionForward, nullptr);

			pmovespr->runAction(myAction);
		}
		else if (i == 6)
		{
			Vec2 onepoint = position7 - pmovespr->getPosition();
			auto myActionForward = MoveBy::create(2, onepoint);
			auto myAction = Sequence::create(myActionForward, nullptr);

			pmovespr->runAction(myAction);
		}
		else if (i == 7)
		{
			Vec2 onepoint = position8 - pmovespr->getPosition();
			auto myActionForward = MoveBy::create(2, onepoint);
			auto myAction = Sequence::create(myActionForward, nullptr);

			pmovespr->runAction(myAction);
		}
		else if (i == 8)
		{
			Vec2 onepoint = position9 - pmovespr->getPosition();
			auto myActionForward = MoveBy::create(2, onepoint);
			auto myActionFade = FadeOut::create(2.0f);
			auto myAction = Sequence::create(myActionForward, myActionFade, nullptr);

			pmovespr->runAction(myAction);
		}
	}
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
	// 액션중 터치 불가
	if (pmovespr->getNumberOfRunningActions() == 0)
	{
		return true;
	}
	log("클릭");
	return true;
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{
	auto touchPoint = touch->getLocation();
	touchPoint = this->convertToNodeSpace(touchPoint);
	log("클릭position(%f, %f)", touchPoint.x, touchPoint.y);
	
	// 클릭지점 sprite 구하기
	if ((touchPoint.x > position1.x && touchPoint.x < position1.x + 100) && (touchPoint.y > position1.y && touchPoint.y < position1.y + 100))
	{
		clickspr = (Sprite*)getChildByTag(nNum[0]);
		clickpos = clickspr->getPosition();
		log("nNum[0]클릭! 현재 spr은 %d(%f, %f)", nNum[0], clickpos.x, clickpos.y);
		if (nNum[1] == hidesprtag)
		{
			int temp;
			temp = nNum[0];
			nNum[0] = nNum[1];
			nNum[1] = temp;
		}
		else if (nNum[3] == hidesprtag)
		{
			int temp;
			temp = nNum[0];
			nNum[0] = nNum[3];
			nNum[3] = temp;
		}
	}
	else if((touchPoint.x > position2.x && touchPoint.x < position2.x + 100) && (touchPoint.y > position2.y && touchPoint.y < position2.y + 100))
	{
		clickspr = (Sprite*)getChildByTag(nNum[1]);
		clickpos = clickspr->getPosition();
		log("nNum[1]클릭! 현재 spr은 %d(%f, %f)", nNum[1], clickpos.x, clickpos.y);
		if (nNum[0] == hidesprtag)
		{
			int temp;
			temp = nNum[1];
			nNum[1] = nNum[0];
			nNum[0] = temp;
		}
		else if (nNum[2] == hidesprtag)
		{
			int temp;
			temp = nNum[1];
			nNum[1] = nNum[2];
			nNum[2] = temp;
		}
		else if (nNum[4] == hidesprtag)
		{
			int temp;
			temp = nNum[1];
			nNum[1] = nNum[4];
			nNum[4] = temp;
		}
	}
	else if ((touchPoint.x > position3.x && touchPoint.x < position3.x + 100) && (touchPoint.y > position3.y && touchPoint.y < position3.y + 100))
	{
		clickspr = (Sprite*)getChildByTag(nNum[2]);
		clickpos = clickspr->getPosition();
		log("nNum[2]클릭! 현재 spr은 %d(%f, %f)", nNum[2], clickpos.x, clickpos.y);
		if (nNum[1] == hidesprtag)
		{
			int temp;
			temp = nNum[2];
			nNum[2] = nNum[1];
			nNum[1] = temp;
		}
		else if (nNum[5] == hidesprtag)
		{
			int temp;
			temp = nNum[2];
			nNum[2] = nNum[5];
			nNum[5] = temp;
		}
	}
	else if ((touchPoint.x > position4.x && touchPoint.x < position4.x + 100) && (touchPoint.y > position4.y && touchPoint.y < position4.y + 100))
	{
		clickspr = (Sprite*)getChildByTag(nNum[3]);
		clickpos = clickspr->getPosition();
		log("nNum[3]클릭! 현재 spr은 %d(%f, %f)", nNum[3], clickpos.x, clickpos.y);
		if (nNum[0] == hidesprtag)
		{
			int temp;
			temp = nNum[3];
			nNum[3] = nNum[0];
			nNum[0] = temp;
		}
		else if (nNum[4] == hidesprtag)
		{
			int temp;
			temp = nNum[3];
			nNum[3] = nNum[4];
			nNum[4] = temp;
		}
		else if (nNum[6] == hidesprtag)
		{
			int temp;
			temp = nNum[3];
			nNum[3] = nNum[6];
			nNum[6] = temp;
		}
	}
	else if ((touchPoint.x > position5.x && touchPoint.x < position5.x + 100) && (touchPoint.y > position5.y && touchPoint.y < position5.y + 100))
	{
		clickspr = (Sprite*)getChildByTag(nNum[4]);
		clickpos = clickspr->getPosition();
		log("nNum[4]클릭! 현재 spr은 %d(%f, %f)", nNum[4], clickpos.x, clickpos.y);
		if (nNum[1] == hidesprtag)
		{
			int temp;
			temp = nNum[4];
			nNum[4] = nNum[1];
			nNum[1] = temp;
		}
		else if (nNum[3] == hidesprtag)
		{
			int temp;
			temp = nNum[4];
			nNum[4] = nNum[3];
			nNum[3] = temp;
		}
		else if (nNum[5] == hidesprtag)
		{
			int temp;
			temp = nNum[4];
			nNum[4] = nNum[5];
			nNum[5] = temp;
		}
		else if (nNum[7] == hidesprtag)
		{
			int temp;
			temp = nNum[4];
			nNum[4] = nNum[7];
			nNum[7] = temp;
		}
	}
	else if ((touchPoint.x > position6.x && touchPoint.x < position6.x + 100) && (touchPoint.y > position6.y && touchPoint.y < position6.y + 100))
	{
		clickspr = (Sprite*)getChildByTag(nNum[5]);
		clickpos = clickspr->getPosition();
		log("nNum[5]클릭! 현재 spr은 %d(%f, %f)", nNum[5], clickpos.x, clickpos.y);
		if (nNum[2] == hidesprtag)
		{
			int temp;
			temp = nNum[5];
			nNum[5] = nNum[2];
			nNum[2] = temp;
		}
		else if (nNum[4] == hidesprtag)
		{
			int temp;
			temp = nNum[5];
			nNum[5] = nNum[4];
			nNum[4] = temp;
		}
		else if (nNum[8] == hidesprtag)
		{
			int temp;
			temp = nNum[5];
			nNum[5] = nNum[8];
			nNum[8] = temp;
		}
	}
	else if ((touchPoint.x > position7.x && touchPoint.x < position7.x + 100) && (touchPoint.y > position7.y && touchPoint.y < position7.y + 100))
	{
		clickspr = (Sprite*)getChildByTag(nNum[6]);
		clickpos = clickspr->getPosition();
		log("nNum[6]클릭! 현재 spr은 %d(%f, %f)", nNum[6], clickpos.x, clickpos.y);
		if (nNum[3] == hidesprtag)
		{
			int temp;
			temp = nNum[6];
			nNum[6] = nNum[3];
			nNum[3] = temp;
		}
		else if (nNum[7] == hidesprtag)
		{
			int temp;
			temp = nNum[6];
			nNum[6] = nNum[7];
			nNum[7] = temp;
		}
	}
	else if ((touchPoint.x > position8.x && touchPoint.x < position8.x + 100) && (touchPoint.y > position8.y && touchPoint.y < position8.y + 100))
	{
		clickspr = (Sprite*)getChildByTag(nNum[7]);
		clickpos = clickspr->getPosition();
		log("nNum[7]클릭! 현재 spr은 %d(%f, %f)", nNum[7], clickpos.x, clickpos.y);
		if (nNum[4] == hidesprtag)
		{
			int temp;
			temp = nNum[7];
			nNum[7] = nNum[4];
			nNum[4] = temp;
		}
		else if (nNum[6] == hidesprtag)
		{
			int temp;
			temp = nNum[7];
			nNum[7] = nNum[6];
			nNum[6] = temp;
		}
		if (nNum[8] == hidesprtag)
		{
			int temp;
			temp = nNum[7];
			nNum[7] = nNum[8];
			nNum[8] = temp;
		}
	}
	else if ((touchPoint.x > position9.x && touchPoint.x < position9.x + 100) && (touchPoint.y > position9.y && touchPoint.y < position9.y + 100))
	{
		clickspr = (Sprite*)getChildByTag(nNum[8]);
		clickpos = clickspr->getPosition();
		log("nNum[8]클릭! 현재 spr은 %d(%f, %f)", nNum[8], clickpos.x, clickpos.y);
		if (nNum[5] == hidesprtag)
		{
			int temp;
			temp = nNum[8];
			nNum[8] = nNum[5];
			nNum[5] = temp;
		}
		else if (nNum[7] == hidesprtag)
		{
			int temp;
			temp = nNum[8];
			nNum[8] = nNum[7];
			nNum[7] = temp;
		}
	}
	else
	{
		log("잘못클릭하셨습니다.");
	}

	this->settingpos();
	this->endok();
}

void HelloWorld::settingpos()
{
	for (int i = 0; i < 9; i++)
	{
		auto pmovespr = (Sprite *)getChildByTag(nNum[i]);
		if (i == 0)
		{
			pmovespr->setPosition(position1);
		}
		else if (i == 1)
		{
			pmovespr->setPosition(position2);
		}
		else if (i == 2)
		{
			pmovespr->setPosition(position3);
		}
		else if (i == 3)
		{
			pmovespr->setPosition(position4);
		}
		else if (i == 4)
		{
			pmovespr->setPosition(position5);
		}
		else if (i == 5)
		{
			pmovespr->setPosition(position6);
		}
		else if (i == 6)
		{
			pmovespr->setPosition(position7);
		}
		else if (i == 7)
		{
			pmovespr->setPosition(position8);
		}
		else if (i == 8)
		{
			pmovespr->setPosition(position9);
		}
	}
}

void HelloWorld::endok()
{
	if (nNum[0] == 1 && nNum[1] == 2 && nNum[2] == 3 && nNum[3] == 4 && nNum[4] == 5 && nNum[5] == 6 && nNum[6] == 7 && nNum[7] == 8 && nNum[8] == 9)
	{
		auto myActionFadeout = FadeOut::create(1.0f);
		auto myAction1 = Sequence::create(myActionFadeout, nullptr);
		spr1->runAction(myAction1);
		spr2->runAction(myAction1->clone());
		spr3->runAction(myAction1->clone());
		spr4->runAction(myAction1->clone());
		spr5->runAction(myAction1->clone());
		spr6->runAction(myAction1->clone());
		spr7->runAction(myAction1->clone());
		spr8->runAction(myAction1->clone());
		spr9->runAction(myAction1->clone());

		auto allspr = Sprite::create("Images/sample.png", Rect(0, 0, 298, 298));
		allspr->setAnchorPoint(Vec2(0, 0));
		allspr->setPosition(Vec2(10, 10));
		allspr->setOpacity(20.0);
		this->addChild(allspr,1);

		auto myActionFadein = FadeIn::create(3.0f);
		auto myAction2 = Sequence::create(myActionFadein, nullptr);
		allspr->runAction(myAction2);
	}
}