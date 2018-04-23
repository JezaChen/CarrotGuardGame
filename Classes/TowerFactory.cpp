//
//  TowerFactory.cpp
//  CarrotFantasy
//
//  Created by ºÎãü±ø on 18-4-12.
//
//
#include "TowerFactory.h"
#include "TowerBase.h"
#include "TowerBall.h"
#include "TowerFireBottle.h"
#include "TowerStar.h"
#include "TowerBlueStar.h"
#include "TowerSun.h"
#include "TowerPin.h"
#include "TowerSnow.h"
#include "TowerRocket.h"
#include "TowerPlane.h"
#include "TowerAnchor.h"
TowerBase *TowerFactory::createTower(const TowerType &rTowerType, Vec2 tposition)
{
	TowerBase *pTower = nullptr;
	int towerId = 0;
	switch (rTowerType)
	{
	case en_GreenTower: towerId = 1; break;
	case en_FanTower:towerId = 4; break;
	case en_ShitTower: towerId = 7; break;
	case en_BallTower: towerId = 10; pTower = TowerBall::create(); break;
	case en_StarTower: towerId = 13; pTower = TowerStar::create(); break;
	case en_FireBottleTower: towerId = 16; pTower = TowerFireBottle::create(); break;
	case en_BlueStarTower:towerId = 19; pTower = TowerBlueStar::create(); break;
	case en_SunTower:towerId = 22; pTower = TowerSun::create(); break;
	case en_RocketTower:towerId = 25; pTower = TowerRocket::create(); break;
	case en_PinTower:towerId = 28; pTower = TowerPin::create(); break;
	case en_SnowTower:towerId = 31; pTower = TowerSnow::create(); break;
	case en_PlaneTower:towerId = 34; pTower = TowerPlane::create(); break;
	case en_AnchorTower:towerId = 37; pTower = TowerAnchor::create(); break;
	default:
		break;
	}
	if (towerId < 8) pTower = TowerBase::create(towerId);
	pTower->setPosition(tposition);
	return pTower;
}
