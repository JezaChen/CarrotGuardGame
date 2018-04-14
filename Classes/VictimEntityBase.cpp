//
//  VictimBase.cpp
//  CarrotFantasy
//
//  Created by 何泓兵 x 陈建彰 on 18-4-12.
//
//

#include "VictimEntityBase.h"
#include "HpSlot.h"
#include "TowerManager.h"
#include "TowerBase.h"
#include "SoundUtil.h"


VictimEntityBase::~VictimEntityBase()
{
    CC_SAFE_RELEASE_NULL(_pLockAtkTarget);
    CC_SAFE_RELEASE_NULL(_pHpSlot);
    CC_SAFE_RELEASE_NULL(_pLockFlagAnimate);
}

bool VictimEntityBase::init(const int &rIId, const std::string &rSCsvFileName)
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!Entity::init(rIId, rSCsvFileName));
        _iHp = CsvUtil::getInstance()->getInt(_iId, en_Hp, rSCsvFileName);
        _iState = en_Normal;
        _fSlowDuration = 0;
        _fStopDuration = 0;
        _fPoisonDuration = 0;
        _Pos = getPosition();
        _Size = getContentSize();
        this->schedule(schedule_selector(VictimEntityBase::checkAtkTarget));
        bRet = true;
    } while (0);

    return bRet;
}

void VictimEntityBase::beHurt(const AtkProperty tBeHurtValue)
{
    if (this->getIsDead())return; //若敌方死亡，返回

    //目前敌方实体的被攻击状态更新
    _iState |= tBeHurtValue._enAtkState;
    _iBulletStateType = tBeHurtValue._iBulletsType;

    //根据攻击属性的类型
    //设置攻击状态的持续时间
    switch (tBeHurtValue._enAtkState)
    {
        case en_Slow:
            _fSlowDuration = tBeHurtValue._iDuration;
            break;
        case en_Stop:
            _fStopDuration = tBeHurtValue._iDuration;
            break;
        case en_Poison:
            _fPoisonDuration = tBeHurtValue._iDuration;
            break;
        default:
            break;
    }
    auto tIHp = getIHp() - tBeHurtValue._iAtk; //生命值更新

    //受到新的攻击后，生命槽要显示并重新计时
    if (tIHp > 0)
    {
        unschedule(schedule_selector(VictimEntityBase::closeHpSlot));
        if (!_bHpSlotExsit)
        {
            hpSlotVisible(!_bHpSlotExsit);
            _bHpSlotExsit = true;
        }
        _pHpSlot->setVisible(true);
        schedule(schedule_selector(VictimEntityBase::closeHpSlot), _iHpCloseTime);
        setIHp(tIHp);
        _pHpSlot->setHp(getIHp());
        behurtAction();
    }

    else if (tIHp <= 0)
    {
        doDead(); //执行死亡动作
    }
}

void VictimEntityBase::closeHpSlot(float dt)
{
    _pHpSlot->setVisible(false);
}

void VictimEntityBase::deadAction(const std::string &rSDeadImageFile)
{
    auto tValue = std::make_tuple(getPosition(), _iValue);
    NOTIFY->postNotification("monsterDeadMoney", reinterpret_cast<Ref *>(&tValue)); //发出死亡通知，以更新金钱
    if (_pHpSlot) _pHpSlot->removeFromParent(); //若生命槽显示，关闭生命槽的显示
    if (_pLockAtkTarget) _pLockAtkTarget->removeFromParent(); //若锁定标识显示，关闭锁定标识的显示
    Entity::deadAction(); //执行实体死亡画面
}

void VictimEntityBase::createHpSlotSprite()
{
    _pHpSlot = HpSlot::create(this);
    _pHpSlot->retain();
    auto tPos = getPosition();
    auto tSpriteSize = getContentSize();
    auto tSlotSize = _pHpSlot->getContentSize();
    _pHpSlot->setPosition(Vec2(-tSlotSize.width / 2 - 3, tSpriteSize.height / 2 - 12));
    addChild(_pHpSlot);
}

void VictimEntityBase::createLockAtkSprite()
{
    createLockFlagAnimate();
    _pLockAtkTarget = Sprite::createWithSpriteFrame(
            SpriteFrameCache::getInstance()->getSpriteFrameByName("point01.png"));
    CC_SAFE_RETAIN(_pLockAtkTarget);
    _pLockAtkTarget->setPosition(Vec2(0, _Pos.y + _Size.height / 2 + 12));
    addChild(_pLockAtkTarget, 2);
}

void VictimEntityBase::createLockFlagAnimate()
{
    auto pAnimation = Animation::create();
    auto pSpriteFrameCache = SpriteFrameCache::getInstance();
    for (int i = 1; i <= 3; ++i)
        pAnimation->addSpriteFrame(pSpriteFrameCache->getSpriteFrameByName(StringUtils::format("point0%d.png", i)));
    pAnimation->setLoops(-1);
    pAnimation->setDelayPerUnit(0.1f);
    _pLockFlagAnimate = Animate::create(pAnimation);
    _pLockFlagAnimate->retain();
}

void VictimEntityBase::setAtkTarget(const bool &rBisAtkTarget)
{
    _bIsAtkTarget = rBisAtkTarget;
    if (_bIsAtkTarget)
    {
        if (!_pLockAtkTarget) createLockAtkSprite();
        _pLockAtkTarget->runAction(_pLockFlagAnimate); //_pLockAtkTarget以_pLockFlagAnimate方式进行运动
        _pLockAtkTarget->setVisible(true); //设置为可见状态
        SoundUtil::getInstance()->playEffectSound(SELECTVICTIMENTITYBASE); //播放音效
    }
    else
    {
        if (!_pLockAtkTarget) return;
        _pLockAtkTarget->stopAllActions(); //停止一切活动
        _pLockAtkTarget->setVisible(false); //设置为不可见
    }
}

void VictimEntityBase::hpSlotVisible(const bool &rBIsVisible)
{
    if (rBIsVisible) createHpSlotSprite();
    else _pHpSlot->setVisible(rBIsVisible);
}

void VictimEntityBase::checkAtkTarget(float dt)
{
    auto tTowerVec = TowerManager::getInstance()->getTowerVec();
    if (_bIsAtkTarget)
    {
        for (auto &towerItem : tTowerVec)
        {
            if (towerItem->isInAtkRange(this->getPosition())) //若是处于攻击范围
            {
                towerItem->setAtkTarget(this); //集体过来攻击
                towerItem->setIsHaveAtkTarget(true);
            }
        }
    }
}

