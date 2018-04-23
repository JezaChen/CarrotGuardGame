//
//  TowerFish.cpp
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-22.
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

        srand(time(nullptr));
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
        pBullet->setPosition(this->getPosition()); //确定发射位置
                                                   //确定发射角度，公式还是一样的
        pBullet->getSprite()->setRotation(90 - 180 * (_pAtkTarget->getPosition() - this->getPosition()).getAngle() / M_PI);
        pBullet->doMove(); //子弹发射启动
	});

	this->runAction(Sequence::create(fireActionCF, DelayTime::create(0.35), createBulletCF, NULL));
}