//
//  TowerFish.cpp
//  CarrotFantasy
//
//  Created by ºÎãü±ø on 18-4-22.
//  
//
#include "TowerFish.h"
#include "BulletFish.h"
#include "VictimEntityBase.h"

bool TowerFish::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!TowerBase::init(rId));

		bRet = true;
	} while (0);
	return bRet;
}

void TowerFish::fire(float dt) 
{
	if (!_pAtkTarget || _pAtkTarget->getIsDead()) return;
	auto fireActionCF = CallFunc::create([=]() { fireAction(); });

	auto createBulletCF = CallFunc::create([=]() {
		if (!_pAtkTarget) return;
		BulletFish * pBullet = BulletFish::create(getIBulletId(), _pAtkTarget);
		pBullet->setPosition(this->getPosition());
		pBullet->doMove();
	});

	this->runAction(Sequence::create(fireActionCF, DelayTime::create(0.35), createBulletCF, NULL));
}