//
//  TowerSnow.cpp
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-12.
//  
//
#include "TowerSnow.h"
#include "MonsterBase.h"
#include "BarrierBase.h"
#include "MonsterManager.h"
#include "BarrierManager.h"
#include "SoundUtil.h"

bool TowerSnow::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!TowerBase::init(rId));
        unschedule(schedule_selector(TowerSnow::doRotation)); //雪花没有旋转效果，需要注销调度器

                                                              //开火动作精灵启动
        _doAnimationSprite = Sprite::create();
        _doAnimationSprite->setVisible(false);
        addChild(_doAnimationSprite); //加入到炮塔精灵中

        bRet = true;
    } while (0);
    return bRet;
}

void TowerSnow::fire(float dt) {
    if (!_pAtkTarget || _pAtkTarget->getIsDead()) return;

    //攻击效果精灵启动
    _doAnimationSprite->setVisible(true);
    //攻击动画启动
    Animation * pAnimation = Animation::create();
    for (int i = 1; i <= 5; i++)
    {
        std::string SpriteFrameName = "P" + _sModelName + StringUtils::format("%d.png", i);
        pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SpriteFrameName));
    }
    pAnimation->setDelayPerUnit(0.1);
    pAnimation->setLoops(1);
    SoundUtil::getInstance()->playEffectSound("Music/Towers/Snow.mp3"); //播放攻击声音

    CallFunc * pCallFunc = CallFunc::create([=]() {
        attack();
        _doAnimationSprite->setVisible(false);
    });

    _doAnimationSprite->runAction(Sequence::create(Animate::create(pAnimation), pCallFunc, NULL));
}

void TowerSnow::attack()
{
    AtkProperty atk;
    atk._enAtkState = 4;
    atk._iAtk = _iBulletId;
    atk._iDuration = 2;
    atk._iBulletsType = _iBulletId;

    Rect rect;
    //根据炮塔等级确定攻击范围
    //为了后面的块碰撞检测打下基础
    if (getIId() == 31) { rect = Rect(this->getPositionX() - 80, this->getPositionY() - 80, 160, 160); }
    if (getIId() == 32) { rect = Rect(this->getPositionX() - 100, this->getPositionY() - 100, 200, 200); }
    if (getIId() == 33) { rect = Rect(this->getPositionX() - 120, this->getPositionY() - 120, 240, 240); }

    /*************************************************************/
    /**-----------------------攻击游戏主逻辑-----------------------**/
    /*************************************************************/

    //todo 逻辑还是和飞机那么迷
    Vector<MonsterBase *>  MonsterVector = Vector<MonsterBase *>(MonsterManager::getInstance()->getMonsterVec());
    for (int i = MonsterVector.size() - 1; i >= 0; i--)
    {
        MonsterBase * pMonster = (MonsterBase *)(MonsterVector.at(i));
        if (rect.intersectsRect(pMonster->getBoundingBox()))
        {
            pMonster->beHurt(atk);
        }
        if (pMonster->getIHp() <= 0 || pMonster->getIsDead())
        {
            /*mIter =(auto)*/
            MonsterVector.eraseObject(pMonster);
        }
    }

    Vector<BarrierBase *> BarrierVector = Vector<BarrierBase *>(BarrierManager::getInstance()->getBarrierVec());
    for (int i = BarrierVector.size() - 1; i >= 0; i--)
    {
        BarrierBase * pBarrier = (BarrierBase *)(BarrierVector.at(i));
        if (rect.intersectsRect(pBarrier->getBoundingBox()))
        {
            pBarrier->beHurt(atk);
        }
        if (pBarrier->getIHp() <= 0 || pBarrier->getIsDead())
        {
            /*bIter =(auto)*/
            BarrierVector.eraseObject(pBarrier);
        }
    }
}
