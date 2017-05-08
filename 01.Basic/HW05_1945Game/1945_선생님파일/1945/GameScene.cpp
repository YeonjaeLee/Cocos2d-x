#include "GameScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CGameScene::CGameScene() :
regenCheckTime_(-1.f)
{
}

CCScene* CGameScene::scene()
{
    CCScene *scene = CCScene::create();
    CGameScene *layer = CGameScene::create();
    scene->addChild(layer);
    return scene;
}

bool CGameScene::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }

    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(CGameScene::menuCloseCallback) );
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );

    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);

    size_ = CCDirector::sharedDirector()->getWinSize();

    CCLabelTTF* pLabel = CCLabelTTF::create("1945", "Thonburi", 34);
	pLabel->setColor(ccRED);
    pLabel->setPosition( ccp(size_.width / 2, size_.height - 20) );
    this->addChild(pLabel, 1);

    CCSprite* pSprite = CCSprite::create("bg.png");
    pSprite->setPosition( ccp(size_.width/2, size_.height/2) );
    this->addChild(pSprite, 0);

    player_ = CCSprite::create("airplain_01.png");
    player_->setPosition( ccp(size_.width/2, 50) );
    this->addChild(player_, 1);
	
	setTouchEnabled(true);
	
	schedule(schedule_selector(CGameScene::Update));
	schedule(schedule_selector(CGameScene::RegenEnemy), 1.f);
	schedule(schedule_selector(CGameScene::Shooting), 0.2f);
	
	//enemy 배열 생성
	enemy_ = CCArray::create();
	enemy_->retain();

	//missile 배열 생성
	for (int a = 0; a < MAX_MISSILE; ++a)
	{
		missile_[a] = CCArray::create();
		missile_[a]->retain();
	}

    return true;
}

void CGameScene::AddEnemy(const CCPoint& position)
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();

	//적비행기 하나를 Scene에 추가
	CCSprite *enemy = CCSprite::create("enemy_01.png");
	enemy->setPosition(position);
	addChild(enemy);
	
	//화면 아래로 내려가는 액션 등록
	CCActionInterval *move = CCMoveBy::create(3.f, ccp(0, -size.height));
	enemy->runAction(move);
	
	//배열에 방금 생성된 적비행기 스프라이트 포인터를 배열 요소로 추가
	enemy_->addObject(enemy);
}

void CGameScene::Update(float time)
{
    CCObject *obj = NULL;
	CCARRAY_FOREACH(enemy_, obj)
	{
		//적 비행기 스프라이트를 캐스팅(형변환)하여 얻어옴
		CCSprite *spr = (CCSprite*)obj;
		
		//적 비행기가 화면 아래로 사라졌을 경우 메모리에서 삭제합니다
		if (spr->getPosition().y <= 0)
		{
			//화면(Scene)에 적 비행기 스프라이트를 삭제
			removeChild(spr, false);
			
			//addObject로 추가했던 스프라이트 포인터를 배열에서 지웁니다
			enemy_->removeObject(spr);
			continue;
		}

		//모든 미사일 배열을 반복하여 충돌검사
		for (int a = 0; a < MAX_MISSILE; ++a)
		{
			CCARRAY_FOREACH(missile_[a], obj)
			{
				CCSprite *missile = (CCSprite*)obj;
				
				//미사일이 화면 위쪽으로 사라졌을 때
				if (missile->getPosition().y >= size_.height)
				{
					//미사일 삭제
					removeChild(missile, false);
					missile_[a]->removeObject(missile);
					continue;
				}

				if (missile->boundingBox().intersectsRect(spr->boundingBox()))
				{
					//미사일과 적 비행기가 부딪혔을 때
					PutCrashEffect(spr->getPosition());

					//적 비행기 삭제
					removeChild(spr, false);
					enemy_->removeObject(spr);
					
					//미사일 삭제
					removeChild(missile, false);
					missile_[a]->removeObject(missile);
				}
			}
		}

		if (player_)
		{
			//intersectsRect함수 리턴값이 충돌하면 true를 리턴
			if (player_->boundingBox().intersectsRect(spr->boundingBox()))
			{
				//충돌했을때 처리
				
				//1.폭파 이펙트 출력
				PutCrashEffect(player_->getPosition());
				PutCrashEffect(spr->getPosition());
				
				//2.적 비행기를 화면에서 없애준다
				
				//Scene에서 적비행기 스프라이트를 Remove한다
				removeChild(spr, false);
				enemy_->removeObject(spr);
				
				removeChild(player_, false);
				player_ = NULL;
				
				regenCheckTime_ = 0.f;
			}
		}
	}
	
	//유저 비행기가 죽었을때만 체크하여 부활처리
	if (!player_ &&
		regenCheckTime_ != -1.f)
	{
		//시간을 누적시켜서 3초 이상 경과되었을 때만 부활시킨다
		regenCheckTime_ += time;
		if (regenCheckTime_ >= 3.f)
		{
			//유저 비행기 부활처리
			player_ = CCSprite::create("airplain_01.png");
			player_->setPosition( ccp(size_.width/2, 50) );
			this->addChild(player_, 1);
		}
	}
	
	//현재 배열의 크기 = 적 비행기 갯수
	CCLog("%d", enemy_->count());
}

void CGameScene::Shooting(float time)
{
	if (!player_)
		return;
	
	for (int a = 0; a < MAX_MISSILE; ++a)
	{
		CCSprite *missile = CCSprite::create("missile.png");
		
		if (a == 0)
		{
			missile->setPosition(ccp(player_->getPosition().x - 16.f, player_->getPosition().y));
		}
		else if (a == 1)
		{
			missile->setPosition(ccp(player_->getPosition().x + 16.f, player_->getPosition().y));
		}
		
		addChild(missile);
		
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		CCActionInterval *move = CCMoveBy::create(0.75f, ccp(0, size.height));
		missile->runAction(move);
		
		missile_[a]->addObject(missile);
	}
}

void CGameScene::RegenEnemy(float time)
{
	for (int a = 0; a < RANDOM_INT(1, 5); ++a) {
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		AddEnemy(ccp(RANDOM_INT(0, (int)size.width), size.height));
	}
}

void CGameScene::PutCrashEffect(const cocos2d::CCPoint &pos)
{
	//맨첫번째 스프라이트가 로딩되어 베이스가 된다
	CCSprite *expBase = CCSprite::create("exp_01.png");
    expBase->setPosition(pos);
    
	//애니메이션 스프라이트 5프레임을 차례로 등록해줌
    CCAnimation *animation = CCAnimation::create();
    animation->addSpriteFrameWithFileName("exp_01.png");
    animation->addSpriteFrameWithFileName("exp_02.png");
    animation->addSpriteFrameWithFileName("exp_03.png");
    animation->addSpriteFrameWithFileName("exp_04.png");
    animation->addSpriteFrameWithFileName("exp_05.png");
    
	//0.1초 간격으로 애니메이션 처리 설정
    animation->setDelayPerUnit(0.1f);
	
	//애니메이션이 끝나고 시작 프레임(1번)으로 돌아간다
    animation->setRestoreOriginalFrame(true);
    
	//에니메이션 생성
    CCAnimate *animate = CCAnimate::create(animation);
	
	//애니메이션이 끝나면 removeChild를 자동으로 호출하여 메모리 삭제.. 이것도 일종의 액션이다
    CCCallFuncND *removeAction = CCCallFuncND::create(this, callfuncND_selector(CCNode::removeChild), expBase);
	
	//애니메이션과 리무브액션 2개의 액션을 하나의 시퀀스로 등록후 runAction 실행
    CCFiniteTimeAction *seq = CCSequence::create(animate, removeAction, NULL);
    this->addChild(expBase);//씬에 이펙트(베이스 스프라이트)를 추가
    expBase->runAction(seq);//베이스 스프라이트는 애니메이션 시퀀스를 실행한다
}

void CGameScene::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool CGameScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if (!player_)
		return true;
		
	CCPoint touchPoint = pTouch->getLocationInView();
    CCPoint touchGlPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
	
	CCPoint playerPos = player_->getPosition();
	distance_ = ccp(playerPos.x - touchGlPoint.x, playerPos.y - touchGlPoint.y);
	
	return true;
}

void CGameScene::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	if (!player_)
		return;

	CCPoint touchPoint = pTouch->getLocationInView();
    CCPoint touchGlPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
	
	CCPoint pos = ccp(touchGlPoint.x + distance_.x, touchGlPoint.y + distance_.y);
	
	if (pos.x < 0.f)
	{
		pos.x = 0.f;
		distance_ = ccp(pos.x - touchGlPoint.x, pos.y - touchGlPoint.y);
	}
	else if (pos.x > size_.width)
	{
		pos.x = size_.width;
		distance_ = ccp(pos.x - touchGlPoint.x, pos.y - touchGlPoint.y);
	}

	if (pos.y < 0.f)
	{
		pos.y = 0.f;
		distance_ = ccp(pos.x - touchGlPoint.x, pos.y - touchGlPoint.y);
	}
	else if (pos.y > size_.height)
	{
		pos.y = size_.height;
		distance_ = ccp(pos.x - touchGlPoint.x, pos.y - touchGlPoint.y);
	}
	
	player_->setPosition(pos);
}

void CGameScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
}

void CGameScene::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

