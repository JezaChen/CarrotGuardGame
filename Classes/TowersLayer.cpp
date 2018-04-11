//
//  TowersLayer.cpp
//  CarrotFantasy
//
//  Created by ºÎãü±ø on 18-4-11.
//
//
#include "TowersLayer.h"
#include "TowerManager.h"
#include "TowerBase.h"

bool TowersLayer::init()
{
	bool bRet = false;

	do
	{
		CC_BREAK_IF(!Layer::init());
		auto cache = SpriteFrameCache::getInstance();

		for (auto &iterSource : TOWERS) cache->addSpriteFramesWithFile(iterSource + PLISTPOSTFIX, iterSource + PHOTOPOSTFIX);

		schedule(schedule_selector(TowersLayer::checkTowerGrade));

		bRet = true;
	} while (0);

	return bRet;
}

void TowersLayer::checkTowerGrade(float dt) {
	for (auto &item : TowerManager::getInstance()->getTowerVec()) {
		if (item->getIUpgradeCount() <= 1) {
			if (item->getTowerGradeCost() <= TowerManager::getInstance()->getMoney()) item->showGradeMark();
			else  item->hideGradeMark();
		}
	}
}
