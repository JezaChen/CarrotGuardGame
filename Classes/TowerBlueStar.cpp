//
//  TowerBlueStar.cpp
//  CarrotFantasy
//
//  Created by ������ x �½��� on 18-4-12.
//  
//
#include "TowerBlueStar.h"
#include "BulletBlueStar.h"
#include "VictimEntityBase.h"

bool TowerBlueStar::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!TowerBase::init(rId));
		unschedule(schedule_selector(TowerBlueStar::doRotation));

		bRet = true;
	} while (0);
	return bRet;
}

void TowerBlueStar::fire(float dt) {
	if (!_pAtkTarget || _pAtkTarget->getIsDead()) return;
	auto fireActionCF = CallFunc::create([=]() { fireAction(); });

	auto createBulletCF = CallFunc::create([=]() {
		if (!_pAtkTarget) return;
		BulletBlueStar * pBullet = BulletBlueStar::create(getIBulletId(), _pAtkTarget);
		pBullet->setPosition(this->getPosition());
		pBullet->doMove();
	});

	this->runAction(Sequence::create(fireActionCF, DelayTime::create(0.35), createBulletCF, NULL));
}