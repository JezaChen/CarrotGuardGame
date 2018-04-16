//
//  BulletsLayer.cpp
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-10.
//
//

#include "BulletLayer.h"
#include "BulletManager.h"

bool BulletLayer::init()
{
	bool bRet = false;

	do
	{
		CC_BREAK_IF(!EntityLayerBase::init());
		//利用cocos的定时器，更新游戏动画；
		scheduleUpdate();

		bRet = true;
	} while (0);

	return bRet;
}

void BulletLayer::update(float dt)
{
	BulletManager::getInstance()->checkBulletIsDead();
}