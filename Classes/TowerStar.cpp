//
//  TowerStar.cpp
//  CarrotFantasy
//
//  Created by ºÎãü±ø on 18-4-12.
//  
//
#include "TowerStar.h"
#include "BulletStar.h"
#include "VictimEntityBase.h"

bool TowerStar::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!TowerBase::init(rId));
		unschedule(schedule_selector(TowerStar::doRocation));

		bRet = true;
	} while (0);
	return bRet;
}

void TowerStar::fire(float dt){
	if (!_pAtkTarget || _pAtkTarget->getIsDead()) return;
	auto fireActionCF = CallFunc::create([=](){ fireAction(); });

	auto createBulletCF = CallFunc::create([=](){
		if (!_pAtkTarget) return;
		BulletStar * pBullet = BulletStar::create(getIBulletId(), _pAtkTarget);
		pBullet->setPosition(this->getPosition());
		pBullet->doMove();
	});

	this->runAction(Sequence::create(fireActionCF, DelayTime::create(0.35), createBulletCF, NULL));
}