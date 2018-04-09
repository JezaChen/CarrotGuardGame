//
//  VictimBase.h
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-7.
//
//
#pragma once
#ifndef __CarrotFantasy__VictimEntityBase__
#define __CarrotFantasy__VictimEntityBase__

#include "Entity.h"
class HpSlot;

class VictimEntityBase :public Entity
{
public:

	virtual ~VictimEntityBase();

	/**
	*  @brief 实体被伤害并运行被伤害func
	*  @param rBeHurtValue 等于攻击力
	*/
	virtual void beHurt(const AtkProperty tBeHurtValue);
	/*
	* @brief 设置攻击目标
	*/
	virtual void setAtkTarget(const bool &rBisAtkTarget);
	/*
	* @brief 获取攻击目标
	*/
	virtual bool getAtkTarget()const { return _bIsAtkTarget; };
	/*
	* @被攻击后的可见生命
	*/
	virtual void hpSlotVisible(const bool &rBIsVisible);

protected:
	/*
	* @brief 关闭生命值显示
	*/
	virtual void closeHpSlot(float dt);
	/*
	* @brief 检查攻击目标
	*/
	virtual void checkAtkTarget(float dt);
	/*
	* @
	*/
	virtual bool init(const int &rIId, const std::string &rSCsvFileName);
	/*
	* @brief 创建锁定标志动画
	*/
	virtual void createLockFlagAnimate();
	/*
	* @brief 把精灵和生命值插槽绑定并创建
	*/
	virtual void createHpSlotSprite();
	/*
	* @brief 把精灵和锁定攻击目标绑定并创建
	*/
	virtual void createLockAtkSprite();
	/*
	* @brief 执行死亡动画
	*/
	virtual void deadAction(const std::string &rSDeadImageFile = "")override;
	/*
	* @brief 受伤动画（抽象函数）
	*/
	virtual void behurtAction() = 0;
	/*
	* @brief 障碍物和怪物的hp
	*/
	CC_SYNTHESIZE_PASS_BY_REF(int, _iHp, IHp);
	/*
	* @brief 怪物位
	*/
	CC_SYNTHESIZE_PASS_BY_REF(int, _iState, IState);
	/*
	* @brief 状态保持时间
	*/
	CC_SYNTHESIZE_PASS_BY_REF(float, _fSlowDuration, FSlowDuration);
	CC_SYNTHESIZE_PASS_BY_REF(float, _fStopDuration, fStopDuration);
	CC_SYNTHESIZE_PASS_BY_REF(float, _fPoisonDuration, fPoisonDuration);

	CC_SYNTHESIZE_PASS_BY_REF(float, _iBulletStateType, IBulletStateType);
	/*
	*  @brief 生命槽关闭时间
	*/
	const int _iHpCloseTime = 3;

private:

	bool _bHpSlotExsit = false;

	/*
	* @brief 生命槽精灵
	*/
	HpSlot *_pHpSlot = nullptr;
	/*
	* @brief 锁定攻击标志精灵
	*/
	Sprite *_pLockAtkTarget = nullptr;
	/*
	* @brief 锁定标志动画
	*/
	Animate *_pLockFlagAnimate = nullptr;

	/*
	* @brief 标志受害者是攻击目标
	*/
	bool _bIsAtkTarget = false;

	Vec2 _Pos;

	Size _Size;
};

#endif /* defined(__CarrotFantasy__VictimBase__) */
