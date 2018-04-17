//
//  TowerFireBottle.cpp
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-12.
//  
//
#include "TowerFireBottle.h"
#include "MonsterManager.h"
#include "MonsterBase.h"
#include "BarrierManager.h"
#include "BarrierBase.h"
#include "TowerManager.h"
#include "SoundUtil.h"

bool TowerFireBottle::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!TowerBase::init(rId));

        _doActionSprite = Sprite::create();
        addChild(_doActionSprite, -100);

        bRet = true;
    } while (0);
    return bRet;
}

void TowerFireBottle::chooseAtkTarget()
{

    auto tMonsterVec = MonsterManager::getInstance()->getMonsterVec();

    for (auto &iterMonster : tMonsterVec)
    {
        if (isInAtkRange(iterMonster->getPosition()))
        {
            fireAction();
            setAtkTarget(iterMonster);
            break;
        }
    }
}

void TowerFireBottle::fire(float dt)
{
    if (!_pAtkTarget || _pAtkTarget->getIsDead()) return;

    //先创建开火的子弹(严格说是火)动画
    Animation *pAnimation = Animation::create();
    for (int i = 1; i <= 2; i++)
    {
        //_sModelName实际上已经包含了该炮塔的等级
        std::string SpriteFrameName = "P" + _sModelName + StringUtils::format("%d.png", i);
        pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SpriteFrameName));
    }
    pAnimation->setDelayPerUnit(0.05);
    pAnimation->setLoops(1); //因为使用了调度器，因而每次调度之开火一次就可以了

    SoundUtil::getInstance()->playEffectSound("Music/Towers/FireBottle.mp3"); //播放开火声音

    //创建一个子精灵用于显示开火动画
    _doActionSprite->setVisible(true);
    //只要y轴变动就可以了
    _doActionSprite->setScaleY(
            this->getPosition().distance(_pAtkTarget->getPosition()) / _doActionSprite->getContentSize().height);
    _doActionSprite->setPosition((this->getPosition() + _pAtkTarget->getPosition()) / 2 - this->getPosition());
    //火的角度要和炮塔面对怪物的角度是一致的，所以用同样的公式就可以了
    _doActionSprite->setRotation(90 - 180 * (_pAtkTarget->getPosition() - this->getPosition()).getAngle() / M_PI);
    _doActionSprite->runAction(Animate::create(pAnimation)); //二营长，开炮!!!

    //创建攻击属性
    AtkProperty atk;
    atk._enAtkState = 1;
    atk._iAtk = int(_iBulletId * 0.8);
    atk._iDuration = 0;

    //创建攻击后怪物受伤画面
    Animation *pHurtAction = Animation::create();
    pHurtAction->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PFBottle01.png"));
    pHurtAction->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PFBottle02.png"));
    pHurtAction->setDelayPerUnit(0.06);
    pHurtAction->setLoops(1);

    Rect rect = Rect(_pAtkTarget->getPositionX() - 60, _pAtkTarget->getPositionY() - 60, 120, 120); //确定攻击方块，用于碰撞检测

    if (_pAtkTarget->getAnimationFrameCount() != 0) //有多个帧，说明是个怪物
    {
        for (auto &mIter : MonsterManager::getInstance()->getMonsterVec())
        {
            MonsterBase *pMonster = (MonsterBase *) mIter;
            //为什么要遍历向量检测碰撞呢，因为汽油桶的攻击会对周围怪物有攻击效果
            if (rect.intersectsRect(pMonster->getBoundingBox())) //若发生了碰撞，就激发攻击
            {
                pMonster->beHurt(atk);
                Sprite *pMonsterHurt = Sprite::create();
                pMonster->addChild(pMonsterHurt); //碰撞到的怪兽会加一个受伤精灵

                CallFunc *pClear = CallFunc::create([=]()
                                                    { pMonsterHurt->removeFromParentAndCleanup(true); });
                pMonsterHurt->runAction(Sequence::create(Animate::create(pHurtAction), pClear, nullptr)); //受伤精灵显示动画
            }
            if (pMonster->getIHp() <= 0 || pMonster->getIsDead()) //没命了就不要开火了
            {
                break;
            }
        }
    }
    else //否则，是个障碍物
    {
        //同样的处理方式
        for (auto &bIter : BarrierManager::getInstance()->getBarrierVec())
        {
            BarrierBase *pBarrier = (BarrierBase *) bIter;
            if (rect.intersectsRect(pBarrier->getBoundingBox()))
            {
                pBarrier->beHurt(atk);
                Sprite *pBarrierHurt = Sprite::create();
                pBarrier->addChild(pBarrierHurt);
                CallFunc *pClear = CallFunc::create([=]()
                                                    { pBarrierHurt->removeFromParentAndCleanup(true); });
                pBarrierHurt->runAction(Sequence::create(Animate::create(pHurtAction), pClear, nullptr));
            }
            if (pBarrier->getIHp() <= 0 || pBarrier->getIsDead())
            {
                break;
            }
        }
    }
}

void TowerFireBottle::missAtkTarget()
{
    CC_SAFE_RELEASE_NULL(_pAtkTarget);
    _doActionSprite->setVisible(false);
}
