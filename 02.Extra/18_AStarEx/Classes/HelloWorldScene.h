#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif

#include "cocos2d.h"
//#include "Astar.h"
#include "AstarItem.h"

class HelloWorld : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(HelloWorld);

	cocos2d::Size		winSize;

	cocos2d::TMXTiledMap*	tmap;
	cocos2d::TMXLayer*		metainfo;

	cocos2d::Sprite*		tamara;

	void setViewpointCenter(cocos2d::Vec2 position);
	cocos2d::Vec2 tileCoordForPosition(cocos2d::Vec2 position);
	cocos2d::Vec2 positionForTileCoord(cocos2d::Vec2 position);

	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);

	// Astar Start --------------------------------------------------
	cocos2d::Vec2			pCoordS;
	cocos2d::Vec2			pCoordE;

	std::vector<AstarItem*>* openPath;
	std::vector<AstarItem*>* closePath;
	std::vector<Vec2>* myPath;

	void AStarPathFind();
	void isRoad(Vec2 mPos, Vec2 pPos, int cost1, int cost2);
	int getHCost(Vec2 pos);
	void makePass();
	void movePass();
	void moveCamera();
	// Astar End ------------------------------------------------------
};

#endif // __HELLOWORLD_SCENE_H__