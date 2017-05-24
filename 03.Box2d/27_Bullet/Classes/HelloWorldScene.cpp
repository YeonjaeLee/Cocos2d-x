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

	if (!LayerColor::initWithColor(Color4B(0, 0, 0, 0)))
	{
		return false;
	}

	return true;
}
void HelloWorld::onEnter()//싱글터치모드
{
	Layer::onEnter(); //Layer에 터치기능을 추가한다


					  //   싱글 터치 모드로 터치 리스너 등록 
	auto listener = EventListenerTouchOneByOne::create(); //listener 라는 터치 변수를 선언한다


	listener->setSwallowTouches(true);//cut 용도


	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);// 클릭을 하면 onTouchBegan함수를 부른다
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);// 클릭한체로 움직이면 onTouchMoved함수를 부른다
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);// 클릭을 때면 onTouchMoved함수를 부른다


																		   //터치 리스너의 우선순위를 화면에 그려진 순서대로 한다.
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void HelloWorld::onExit()
{
	_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);

	Layer::onExit();
}

bool HelloWorld::onTouchBegan(Touch *touch, Event *unused_event)
{
	pos = touch->getLocation();
	//this->Shoot(pos);
	this->schedule(schedule_selector(HelloWorld::scheduleCallback), 1.0f / 60);

	return true;
}

void HelloWorld::onTouchMoved(Touch *touch, Event *unused_event)
{
	pos = touch->getLocation();
	this->schedule(schedule_selector(HelloWorld::scheduleCallback), 1.0f / 60);
	//this->touch = touch;
}

void HelloWorld::onTouchEnded(Touch *touch, Event *unused_event)
{
	this->unschedule(schedule_selector(HelloWorld::scheduleCallback));
}

void HelloWorld::scheduleCallback(float delta)
{
	Shoot(pos);
}

void HelloWorld::Shoot(Vec2 point)
{

	Point originPos;
	Point pos1;
	Point pos2;

	Size winSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	float angle;
	float speed = 1000.0f;

	auto bullet = Sprite::create("Bullet.png");

	originPos = { origin.x + winSize.width / 2, origin.y + winSize.height / 2 };

	//pos1 = this->touch->getLocation();

	bullet->setAnchorPoint(Vec2(0.5, 0.0));
	bullet->setPosition(originPos);
	bullet->setScaleX(0.2f);

	angle = (float)(atan2(point.y - originPos.y, point.x - originPos.x)); //atan2

	log("%f", float(atan(point.y)));

	//화면에 출력되는 스프라이트의 방향을 결정
	bullet->setRotation(-(angle * 180.0f / 3.141592) + 90.0f);

	pos2.x = (int)(cos(angle) * speed);
	pos2.y = (int)(sin(angle) * speed);

	auto shootAction = Sequence::create(MoveBy::create(1.0f, pos2), RemoveSelf::create(), NULL);

	bullet->runAction(shootAction);

	this->addChild(bullet);
	this->bullet_.pushBack(bullet);
}