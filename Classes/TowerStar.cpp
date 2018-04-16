//
//  TowerStar.cpp
//  CarrotFantasy
//
//  Created by 何泓兵 x 陈建彰 on 18-4-12.
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
		unschedule(schedule_selector(TowerStar::doRotation));

		bRet = true;
	} while (0);
	return bRet;
}

void TowerStar::fire(float dt){
	if (!_pAtkTarget || _pAtkTarget->getIsDead()) return;
	auto fireActionCF = CallFunc::create([=](){ fireAction(); });

	auto createBulletCF = CallFunc::create([=](){
		if (!_pAtkTarget) return;
        //创建子弹并发射
		BulletStar * pBullet = BulletStar::create(getIBulletId(), _pAtkTarget);
		pBullet->setPosition(this->getPosition());
		pBullet->doMove();
	});

	this->runAction(Sequence::create(fireActionCF, DelayTime::create(0.35), createBulletCF, nullptr));
}