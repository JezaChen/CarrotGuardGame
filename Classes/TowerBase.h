//
//  TowerBase.h
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-9.
//  存在不懂问题
//
#pragma once
#ifndef __CarrotFantasy__TowerBase__
#define __CarrotFantasy__TowerBase__

#include "Entity.h"

class VictimEntityBase;


class TowerBase :public Entity
{
public:

	static TowerBase* create(const int &rId);

	/*
	*  Tower rocate
	* @妈耶，这是干嘛的
	*/
	virtual void doRocation(float dt);

	virtual ~TowerBase();
	/*
	* @brief 获取塔的升级成本
	*/
	virtual int getTowerGradeCost();

	/*
	* @brief 设定当前攻击目标
	* @param pVictimEntity 目标点
	*/
	virtual void setAtkTarget(VictimEntityBase *pVictimEntity);
	/*
	* @brief 显示等级标志
	*/
	virtual void showGradeMark();
	/*
	* @brief 隐藏等级标志
	*/
	virtual void hideGradeMark();

	/*
	* @brief 检查怪物是否在攻击范围
	* @param rPos 攻击目标位置
	* @return true 在返回内，否则返回false
	*/
	virtual bool isInAtkRange(const Vec2 &rPos);
	/*
	* @brief 升级塔
	*/
	virtual void upGrade();
protected:
	/*
	* @brief 死亡动画函数执行
	*/
	virtual void deadAction(const std::string &rSDeadImageFile = "")override;
	/*
	* @brief 检查攻击目标
	* @param rDt 帧数
	*/
	virtual void checkAtkTarget(float dt);
	/*
	* @brief 选择攻击目标
	*/
	virtual void chooseAtkTarget();
	/*
	* @brief 检查攻击目标是否出了范围
	*/
	virtual void checkTargetIsOutOfRange();
	/*
	* @brief 错过攻击目标
	*/
	virtual void missAtkTarget();
	/*
	* @brief 子弹发射
	*/
	virtual void fire(float dt);
	/*
	* @brief 塔防init
	*/
	virtual void initTower();
	/*
	* @brief 确保实体init和塔init函数的实现
	* @details 设置计时器监控塔攻击的全过程
	*/
	virtual bool init(const int &rId);
	/*
	* @brief 塔攻击的效果
	*/
	virtual void fireAction();
	/*
	* @brief 塔关联子弹的id
	*/
	CC_SYNTHESIZE_PASS_BY_REF(int, _iBulletId, IBulletId);
	/*
	* @brief 子弹攻速
	*/
	CC_SYNTHESIZE_PASS_BY_REF(int, _iAtkRange, IAtkRange);
	/*
	* @brief 塔的攻击空间
	*/
	CC_SYNTHESIZE_PASS_BY_REF(double, _iAtkSpace, IAtkSpace);
	/*
	* @brief 塔升级的成本费用
	*/
	CC_SYNTHESIZE_PASS_BY_REF(std::string, _sUpgradeCost, SUpgradeCose);
	/*
	* @brief 塔的级别数
	*/
	CC_SYNTHESIZE_PASS_BY_REF(int, _iUpgradeCount, IUpgradeCount);
	/*
	* @brief 是否回转
	*/
	CC_SYNTHESIZE_PASS_BY_REF(bool, _bIsRotation, BIsRotation);
	/*
	* @brief 各塔防花费成本
	*/
	CC_SYNTHESIZE_PASS_BY_REF(int, _iCreateCost, ICreateCost);

	/*
	* @brief 攻击目标是否拥有
	*/
	CC_SYNTHESIZE_PASS_BY_REF(bool, _bIsHaveAtkTarget, IsHaveAtkTarget);

protected:
	/*
	* @brief 等级标志
	*/
	Sprite* _pGradeMark = nullptr;
	/*
	* @brief 塔的面板
	*/
	Sprite *_pTowerPanel = nullptr;
	/*
	* @brief 攻击目标效果
	*/
	VictimEntityBase *_pAtkTarget = nullptr;
};

#endif /* defined(__CarrotFantasy__TowerBase__) */
