#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace cocos2d;
using namespace CocosDenshion;

HelloWorld::HelloWorld() :
	regenCheckTime_(-1.f)
{
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

	MenuItemImage *pCloseItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		this,
		menu_selector(HelloWorld::menuCloseCallback));
	pCloseItem->setPosition(Vec2(20, Director::sharedDirector()->getWinSize().height - 20));
	Menu* pMenu = Menu::create(pCloseItem, NULL);
	pMenu->setPosition(Vec2(0, 0));
	this->addChild(pMenu, 1);

	SimpleAudioEngine::getInstance()->playBackgroundMusic("Sounds/mainMainMusic.mp3", true);

	SimpleAudioEngine::getInstance()->setEffectsVolume(1.0);
	size_ = Director::sharedDirector()->getWinSize();

	auto pReplayItem = MenuItemImage::create(
		"1945/REPLAY.png",
		"1945/REPLAYSELECTED.png",
		CC_CALLBACK_1(HelloWorld::doClick, this));
	pMenu_pReplayItem = Menu::create(pReplayItem, nullptr);
	pMenu_pReplayItem->setPosition(Vec2(size_.width / 2, size_.height / 2 - 40));
	pMenu_pReplayItem->setVisible(false);
	this->addChild(pMenu_pReplayItem, 3);

	////////////////////////////////////////////////////////////////////////

	LabelTTF* pLabel = LabelTTF::create("1945", "Thonburi", 34);
	pLabel->setColor(Color3B::RED);
	pLabel->setPosition(Vec2(size_.width / 2, size_.height - 20));
	this->addChild(pLabel, 1);

	Sprite* pSprite = Sprite::create("1945/bg.png");
	pSprite->setPosition(Vec2(size_.width / 2, size_.height / 2));
	this->addChild(pSprite, 0);

	player_ = Sprite::create("1945/airplain_01.png");
	player_->setPosition(Vec2(size_.width / 2, 50));
	this->addChild(player_, 1);

	UserLife1 = Sprite::create("1945/UserLife.png");
	UserLife1->setPosition(Vec2(size_.width - 80, 460));
	UserLife1->setScale(0.05);
	this->addChild(UserLife1);

	UserLife2 = Sprite::create("1945/UserLife.png");
	UserLife2->setPosition(Vec2(size_.width - 50, 460));
	UserLife2->setScale(0.05);
	this->addChild(UserLife2);

	UserLife3 = Sprite::create("1945/UserLife.png");
	UserLife3->setPosition(Vec2(size_.width - 20, 460));
	UserLife3->setScale(0.05);
	this->addChild(UserLife3);

	GameOver = Sprite::create("1945/GAMEOVER.png");
	GameOver->setPosition(Vec2(size_.width /2 + 5, size_.height / 2 + 50));
	GameOver->setScale(1.2);
	GameOver->setVisible(false);
	this->addChild(GameOver,3);

	setTouchEnabled(true);

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	schedule(schedule_selector(HelloWorld::Update));
	schedule(schedule_selector(HelloWorld::RegenEnemy), 1.f);
	schedule(schedule_selector(HelloWorld::Shooting), 0.2f);

	//enemy 배열 생성
	enemy_ = cocos2d::Vector<cocos2d::Sprite*>();

	//missile 배열 생성
	for (int a = 0; a < MAX_MISSILE; ++a)
	{
		missile_[a] = cocos2d::Vector<cocos2d::Sprite*>();
	}

	return true;
}

void HelloWorld::AddEnemy(const Vec2& position)
{
	Size size = Director::sharedDirector()->getWinSize();

	//적비행기 하나를 Scene에 추가
	Sprite *enemy = Sprite::create("1945/enemy_01.png");
	enemy->setPosition(position);
	addChild(enemy);

	//화면 아래로 내려가는 액션 등록
	ActionInterval *move = MoveBy::create(3.f, Vec2(0, -size.height));
	enemy->runAction(move);

	//배열에 방금 생성된 적비행기 스프라이트 포인터를 배열 요소로 추가
	enemy_.pushBack(enemy);
}

void HelloWorld::Update(float time)
{
	Sprite *missile = Sprite::create("1945/missile.png");

	// 적과 미사일을 지울 백터를 만든다.
	Vector<Sprite*> eraseEnemy;
	Vector<Sprite*> eraseMissile;
	for (auto enemy : enemy_)
	{
		// 적 비행기가 화면 아래로 사라졌을 경우 메모리에서 삭제합니다
		if (enemy->getPosition().y <= 0)
		{
			// 적을 지울 백터에 넣는다.
			eraseEnemy.pushBack(enemy);
		}
		//모든 미사일 백터를 반복하여 충돌검사
		for (int a = 0; a < MAX_MISSILE; a++)
		{
			for(auto missile :missile_[a])
			{
				//미사일이 화면 위쪽으로 사라졌을 때
				if (missile->getPosition().y >= size_.height)
				{
					//미사일 삭제
					eraseMissile.pushBack(missile);
				}

				if (missile->boundingBox().intersectsRect(enemy->boundingBox()))
				{
					//미사일과 적 비행기가 부딪혔을 때
					PutCrashEffect(enemy->getPosition());

					//적 비행기 삭제
					eraseEnemy.pushBack(enemy);

					//미사일 삭제
					eraseMissile.pushBack(missile);
				}
			}
		}
		if (player_)
		{
			//intersectsRect함수 리턴값이 충돌하면 true를 리턴
			if (player_->boundingBox().intersectsRect(enemy->boundingBox()))
			{
				//충돌했을때 처리
				LifeCount--;
				UserLife(LifeCount);

				//1.폭파 이펙트 출력
				PutCrashEffect(player_->getPosition());
				PutCrashEffect(enemy->getPosition());

				//2.적 비행기를 화면에서 없애준다

				//Scene에서 적비행기 스프라이트를 Remove한다
				eraseEnemy.pushBack(enemy);

				regenCheckTime_ = 0.f;	
			}
		}
	}
	// 적 비행기와 미사일을 지워준다.
	for (auto eraseAllEnemy : eraseEnemy)
	{
		removeChild(eraseAllEnemy, false);
		enemy_.eraseObject(eraseAllEnemy);
	}
	for (auto eraseAllMissile : eraseMissile)
	{
		removeChild(eraseAllMissile, false);
		enemy_.eraseObject(eraseAllMissile);
	}

	eraseEnemy.clear();
	eraseMissile.clear();

	//// 유저 비행기가 죽었을때만 체크하여 부활처리
	//if (!player_ && regenCheckTime_ != -1.f && playerLife > 0)
	//{
	//	//시간을 누적시켜서 3초 이상 경과되었을 때만 부활시킨다
	//	regenCheckTime_ += time;
	//	if (regenCheckTime_ >= 3.f)
	//	{
	//		//유저 비행기 부활처리
	//		player_ = CCSprite::create("1945/airplain_01.png");
	//		player_->setPosition(ccp(size_.width / 2, 50));
	//		this->addChild(player_, 1);
	//	}
	//}

	// 현재 배열의 크기 = 적 비행기 갯수
	log("%d", enemy_.size());
}

void HelloWorld::UserLife(int LifeCount)
{
	if (LifeCount == 3)
	{
		UserLife1->setVisible(true);
		UserLife2->setVisible(true);
		UserLife3->setVisible(true);
	}
	else if (LifeCount == 2)
	{
		UserLife1->setVisible(false);
		UserLife2->setVisible(true);
		UserLife3->setVisible(true);
	}
	else if (LifeCount == 1)
	{
		UserLife1->setVisible(false);
		UserLife2->setVisible(false);
		UserLife3->setVisible(true);
	}
	else
	{
		UserLife1->setVisible(false);
		UserLife2->setVisible(false);
		UserLife3->setVisible(false);

		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		SimpleAudioEngine::getInstance()->playEffect("Sounds/shipDestroyEffect.mp3");
		Director::getInstance()->pause();
//		this->removeChild(player_, true);
		player_->setVisible(false);
		GameOver->setVisible(true);
		pMenu_pReplayItem->setVisible(true);
	}
}

void HelloWorld::Shooting(float time)
{
	if (!player_)
		return;
	for (int a = 0; a < MAX_MISSILE; ++a)
	{
		Sprite *missile = Sprite::create("1945/missile.png");

		if (a == 0)
		{
			missile->setPosition(Vec2(player_->getPosition().x - 16.f, player_->getPosition().y));
		}
		else if (a == 1)
		{
			missile->setPosition(Vec2(player_->getPosition().x + 16.f, player_->getPosition().y));
		}
		SimpleAudioEngine::getInstance()->playEffect("Sounds/fireEffect.mp3");
		SimpleAudioEngine::getInstance()->setEffectsVolume(0.5);
		this->addChild(missile);

		Size size = Director::sharedDirector()->getWinSize();
		ActionInterval *move = MoveBy::create(0.75f, Vec2(0, size.height));
		missile->runAction(move);

		missile_[a].pushBack(missile);
	}
}

void HelloWorld::RegenEnemy(float time)
{
	for (int a = 0; a < RANDOM_INT(1, 5); ++a) {
		Size size = Director::sharedDirector()->getWinSize();
		AddEnemy(ccp(RANDOM_INT(0, (int)size.width), size.height));
	}
}

void HelloWorld::PutCrashEffect(const cocos2d::Vec2 &pos)
{
	SimpleAudioEngine::getInstance()->playEffect("Sounds/explodeEffect.mp3");
	SimpleAudioEngine::getInstance()->setEffectsVolume(1.5);

	//맨첫번째 스프라이트가 로딩되어 베이스가 된다
	Sprite *expBase = Sprite::create("exps/exp_01.png");
	expBase->setPosition(pos);

	//애니메이션 스프라이트 5프레임을 차례로 등록해줌
	Animation *animation = Animation::create();
	animation->addSpriteFrameWithFileName("exps/exp_01.png");
	animation->addSpriteFrameWithFileName("exps/exp_02.png");
	animation->addSpriteFrameWithFileName("exps/exp_03.png");
	animation->addSpriteFrameWithFileName("exps/exp_04.png");
	animation->addSpriteFrameWithFileName("exps/exp_05.png");

	//0.1초 간격으로 애니메이션 처리 설정
	animation->setDelayPerUnit(0.1f);

	//애니메이션이 끝나고 시작 프레임(1번)으로 돌아간다
	animation->setRestoreOriginalFrame(true);

	//에니메이션 생성
	Animate *animate = Animate::create(animation);

	//애니메이션이 끝나면 removeChild를 자동으로 호출하여 메모리 삭제.. 이것도 일종의 액션이다
	CallFunc *removeAction = CallFunc::create(expBase, CC_CALLFUNC_SELECTOR(Node::removeFromParent));

	//애니메이션과 리무브액션 2개의 액션을 하나의 시퀀스로 등록후 runAction 실행
	FiniteTimeAction *seq = Sequence::create(animate, removeAction, nullptr);

	this->addChild(expBase);//씬에 이펙트(베이스 스프라이트)를 추가
	expBase->runAction(seq);//베이스 스프라이트는 애니메이션 시퀀스를 실행한다
}

void HelloWorld::onEnter()
{
	Layer::onEnter();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void HelloWorld::onExit()
{
	_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);

	Layer::onExit();
}

bool HelloWorld::onTouchBegan(Touch *pTouch, Event *pEvent)
{
	return true;
}

void HelloWorld::onTouchMoved(Touch *pTouch, Event *pEvent)
{
	if (!player_)
		return;

	Vec2 touchPoint = pTouch->getLocationInView();
	Vec2 touchGlPoint = Director::sharedDirector()->convertToGL(touchPoint);

	Vec2 pos = Vec2(touchGlPoint.x + distance_.x, touchGlPoint.y + distance_.y);

	if (pos.x < 0.f)
	{
		pos.x = 0.f;
		distance_ = Vec2(pos.x - touchGlPoint.x, pos.y - touchGlPoint.y);
	}
	else if (pos.x > size_.width)
	{
		pos.x = size_.width;
		distance_ = Vec2(pos.x - touchGlPoint.x, pos.y - touchGlPoint.y);
	}

	if (pos.y < 0.f)
	{
		pos.y = 0.f;
		distance_ = Vec2(pos.x - touchGlPoint.x, pos.y - touchGlPoint.y);
	}
	else if (pos.y > size_.height)
	{
		pos.y = size_.height;
		distance_ = Vec2(pos.x - touchGlPoint.x, pos.y - touchGlPoint.y);
	}

	player_->setPosition(pos);
}

void HelloWorld::onTouchEnded(Touch *pTouch, Event *pEvent)
{
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
	Director::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void HelloWorld::doClick(Ref* pSender)
{
	log("Replay 버튼 클릭. ");
	LifeCount = 3;
	pMenu_pReplayItem->setVisible(false);
	GameOver->setVisible(false);
	SimpleAudioEngine::getInstance()->playBackgroundMusic("Sounds/mainMainMusic.mp3", true);
	Director::getInstance()->resume();
	init();
}