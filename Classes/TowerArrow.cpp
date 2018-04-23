//
//  TowerArrow.cpp
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-23.
//
//
#include "TowerArrow.h"
#include "VictimEntityBase.h"
#include "BulletFactory.h"

bool TowerArrow::init()
{
    bool bRet = false;
    do
    {
        //确保塔的基类初始化
        CC_BREAK_IF(!TowerBase::init(rId));

        bRet = true;
    } while (0);
    return bRet;
}
void TowerArrow::fire(float dt) {
    if (!_pAtkTarget || _pAtkTarget->getIsDead()) return; //攻击目标没了的话就不要瞎攻击了

    fireAction(); //炮塔开火动画启动

                  //创建子弹，显示出来并发射
    auto createBulletCF = CallFunc::create([=]()
    {
        if (!_pAtkTarget) return;
        BulletFactory::createArrowBullets(_iBulletId, this, _pAtkTarget);
    });

    //运行子弹流程动画
    this->runAction(Sequence::create(DelayTime::create(_iAtkInterval), createBulletCF, NULL));
}
