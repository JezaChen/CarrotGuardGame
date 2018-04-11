//
//  BulletsLayer.cpp
//  CarrotFantasy
//
//  Created by ºÎãü±ø on 18-4-10.
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

		scheduleUpdate();

		bRet = true;
	} while (0);

	return bRet;
}

void BulletLayer::update(float dt)
{
	BulletManager::getInstance()->checkBulletIsDead();
}