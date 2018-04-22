//
//  TowerPin.cpp
//  CarrotFantasy
//
//  Created by ºÎãü±ø on 18-4-12.
//  
//
#include "TowerPin.h"
#include "MonsterManager.h"
#include "MonsterBase.h"
#include "BarrierManager.h"
#include "TowerManager.h"
#include "BulletPin.h"

bool TowerPin::init() {
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!TowerBase::init(rId));
		bRet = true;

	} while (0);
	return bRet;
}
void TowerPin::fire(float dt) 
{
	if (!_pAtkTarget || _pAtkTarget->getIsDead()) return;
	auto fireActionCF = CallFunc::create([=]() { fireAction(); });

	auto createBulletCF = CallFunc::create([=]() 
	{
		if (!_pAtkTarget) return;
		BulletPin * pBullet = BulletPin::create(_iBulletId, _pAtkTarget);
		pBullet->setPosition(this->getPosition());
		pBullet->setRotation(90 - 180 * (_pAtkTarget->getPosition() - this->getPosition()).getAngle() / M_PI);
		pBullet->doMove();
	});

	this->runAction(Sequence::create(fireActionCF, DelayTime::create(0.35), createBulletCF, NULL));

}
