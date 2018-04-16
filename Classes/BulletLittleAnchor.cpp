//
// BulletLittleAnchor.cpp
// CarrotFantasy
//
// Created by ºÎãü±ø on 18-4-11.
//
//
#include "BulletLittleAnchor.h"

bool BulletLittleAnchor::init(const int & rId, VictimEntityBase *rVictimEntity)
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!BulletAnchor::init(rId, rVictimEntity));

		bRet = true;
	} while (0);
	return bRet;
}

BulletLittleAnchor * BulletLittleAnchor::create(const int & rId, VictimEntityBase *rVictimEntity)
{
	BulletLittleAnchor * pBullet = new BulletLittleAnchor();
	if (pBullet && pBullet->init(rId, rVictimEntity))
	{
		pBullet->autorelease();
		return pBullet;
	}
	CC_SAFE_DELETE(pBullet);
	return nullptr;
}


