//
//  TowerCuttle.cpp
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-19.
//  
//
#include "TowerCuttle.h"
#include "MonsterBase.h"
#include "BarrierBase.h"
#include "MonsterManager.h"
#include "BarrierManager.h"
#include "SoundUtil.h"
#include "BulletBase.h"
#include "CsvUtil.h"
#include "BulletFactory.h"


bool TowerCuttle::init()
{
	bool bRet = false;
	do
	{
		//确保塔的基类初始化
		CC_BREAK_IF(!TowerBase::init(rId));
		//大章鱼没有旋转效果，需要注销调度器
		unschedule(schedule_selector(TowerCuttle::doRotation));

		_doAnimationSprite = Sprite::create();
		//设置图层不可见；
		_doAnimationSprite->setVisible(false);
		addChild(_doAnimationSprite);

		bRet = true;
	} while (0);
	return bRet;
}
void TowerCuttle::fire(float dt) {
    if (!_pAtkTarget || _pAtkTarget->getIsDead()) return; //攻击目标没了的话就不要瞎攻击了

    fireAction(); //炮塔开火动画启动

                  //创建子弹，显示出来并发射
    auto createBulletCF = CallFunc::create([=]()
    {
        if (!_pAtkTarget) return;
        BulletFactory::createCuttleBullets(_iBulletId, this, _pAtkTarget);
    });

    //运行子弹流程动画
    this->runAction(Sequence::create(DelayTime::create(0.15), createBulletCF, NULL));
}
