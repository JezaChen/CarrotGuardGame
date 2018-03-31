//
//  GameScene.h
//  newCardDefence
//
//  Created by ºÎãü±ø on 18-3-30.
//
//
#pragma once
#ifndef __newCardDefence__GameScene__
#define __newCardDefence__GameScene__

#include "SceneBase.h"

class EntityLayerBase;
class Carrot;

class GameScene :public SceneBase
{
public:

	CREATE_FUNC(GameScene);

	virtual ~GameScene();

	virtual Carrot* getCarrot();

	virtual void clickChooseItem();
protected:

	virtual bool init();

	virtual void createLayers();

	virtual void addLayers();

	virtual void onEnter()override;

	virtual void onExit()override;

	virtual void preLoadSource();

	virtual void unLoadSource();

	virtual void collisionUpDate(float dt);

	virtual void createBarriers();

	virtual void clearAllManager();

	virtual void registerGameEvent();

	virtual void showGameEndLayer(Ref *pData);

	virtual void startBuildMonster(Ref *pData);

private:

	/**
	*  gamescene°üÀ¨Æß¸öÍ¼²ã£ºtiledMapLayer£¬barrierLayer£¬BulletsLayer£¬MonsterLayer£¬TowersLayer£¬ScoreAndControllerLayer£¬OptLayer
	*/

	std::vector<std::string> *_pSourceVec = nullptr;

	Layer *_pTiledMapLayer = nullptr;

	EntityLayerBase *_pBarriersLayer = nullptr;

	EntityLayerBase *_pBulletsLayer = nullptr;

	EntityLayerBase *_pMonsterLayer = nullptr;

	EntityLayerBase *_pTowersLayer = nullptr;

	Layer *_pScoreAndControllerLayer = nullptr;

	Layer *_pOptLayer = nullptr;

	Carrot *_pCarrot = nullptr;

	int _iSourceCount = 0;
};

#endif /* defined(__newCardDefence__GameScene__) */
