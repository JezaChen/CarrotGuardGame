/**
 * @brief 敌方实体基类
 * @details 怪物类和障碍物类的共同父类，该类封装了它们两种敌方类的共同属性
 * @extends 继承于Entity
 * @see Entity是游戏中一切运动实体的公共基类
 * @authors 陈建彰 x 何泓兵
 * @date 20180411
 * @update 注释全新更新，这是你从来没有看到的全新版本
 * */
#pragma once
#ifndef VICTIMENTITY_BASE_H
#define VICTIMENTITY_BASE_H

#include "Entity.h"

class HpSlot;

class VictimEntityBase : public Entity
{
public:

    virtual ~VictimEntityBase();

    /**
     * @brief 敌方实体被(子弹)伤害后的处理函数
     * @param rBeHurtValue 攻击属性
     * @details 攻击属性里面有
     */
    virtual void beHurt(const AtkProperty tBeHurtValue);

    /**
     * @brief 设置炮塔的攻击目标
     * @details 选中某个怪物，附近的炮塔就专门打这个怪物
     * @param rBisAtkTarget 是否选中了它
     */
    virtual void setAtkTarget(const bool &rBisAtkTarget);

    /**
     * @brief 获知是否被选中了
     * @return 返回是否该伤害敌方实体被玩家选中了
     */
    virtual bool getAtkTarget() const
    { return _bIsAtkTarget; };

    /**
     * @brief 设置该敌方实体的生命槽是否可见
     * @param rBIsVisible 是否设置为可见
     * @see 玩过游戏的都知道，如果不攻击的话，生命槽过一会就会消失了，因而需要写一个函数来控制生命槽的可见性
     * */
    virtual void hpSlotVisible(const bool &rBIsVisible);

protected:
    /**
     * @brief 关闭生命槽
     * @todo 参数好像没啥用，那写个啥
     * */
    virtual void closeHpSlot(float dt);

    /**
     * @brief 检查该敌方实体是否被设置为攻击目标，并另所有炮塔的攻击目标指向它
     */
    virtual void checkAtkTarget(float dt);

    /**
     * @brief 初始化函数
     * @param rIId 实体ID
     * @param rSCsvFileName CSV表格的路径
     * @see 计时器监控检查攻击目标
     */
    virtual bool init(const int &rIId, const std::string &rSCsvFileName);

    /**
     * @brief 创建锁定标志动画
     */
    virtual void createLockFlagAnimate();

    /**
     * @brief 把精灵和生命值插槽绑定并创建
     */
    virtual void createHpSlotSprite();

    /**
     * @brief 把精灵和锁定攻击目标绑定并创建
     */
    virtual void createLockAtkSprite();

    /**
     * @brief 执行死亡动画
     */
    virtual void deadAction(const std::string &rSDeadImageFile = "") override;

    /**
     * @brief 受伤动画（抽象函数）
     */
    //virtual void behurtAction() = 0;
    /**
     * @brief 敌方实体的hp
     */
CC_SYNTHESIZE_PASS_BY_REF(int, _iHp, IHp);
    /**
    * @brief 怪物位
    */
CC_SYNTHESIZE_PASS_BY_REF(int, _iState, IState);
    /**
    * @brief 状态保持时间
    */
CC_SYNTHESIZE_PASS_BY_REF(float, _fSlowDuration, FSlowDuration);
CC_SYNTHESIZE_PASS_BY_REF(float, _fStopDuration, fStopDuration);
CC_SYNTHESIZE_PASS_BY_REF(float, _fPoisonDuration, fPoisonDuration);

CC_SYNTHESIZE_PASS_BY_REF(float, _iBulletStateType, IBulletStateType);
    /**
    *  @brief 生命槽关闭时间
    */
    const int _iHpCloseTime = 3;

private:

    bool _bHpSlotExsit = false;

    /**
    * @brief 生命槽精灵
    */
    HpSlot *_pHpSlot = nullptr;
    /**
    * @brief 锁定攻击标志精灵
    */
    Sprite *_pLockAtkTarget = nullptr;
    /**
    * @brief 锁定标志动画
    */
    Animate *_pLockFlagAnimate = nullptr;

    /**
    * @brief 标志受害者是攻击目标
    */
    bool _bIsAtkTarget = false;

    Vec2 _Pos;

    Size _Size;
};

#endif
