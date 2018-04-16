//
//  BulletBase.h
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-10.
//  存在不懂；
//
#pragma once
#ifndef __CarrotFantasy__BulletBase__
#define __CarrotFantasy__BulletBase__

#include "Entity.h"
#include "DynamicPropertyInterface.h"

class BulletBase :public Entity, public DynamicPropertyInterface
{

public:
	std::set<int>& getIdMap();

	virtual void doMove();

	static BulletBase *create(const int &rIId, VictimEntityBase *rVictimEntity);
	/*
	* @brief 子弹攻击力
	*/
	virtual AtkProperty getAtkPro();
	/*
	* @brief 死亡动画
	*/
	virtual void deadAction(const std::string &rSDeadImageFile = "");

	/*
	* @brief 动画
	* @param rDt 延迟时间
	*/
	virtual void doAction(const float &rDt);

protected:
	/*
	* @brief 确认实体类和动态性能类的init的实现
	* @retails 获取子弹攻击状态，子弹类型，死亡动画数目，并把设计好的子弹加入树中
	* @param rId
	* @param rVictimEntity 受伤害实体等同于攻击目标
	*/
	virtual bool init(const int &rId, VictimEntityBase *rVictimEntity);
	/*
	* @brief 如果塔防是防御类，那么攻速变低
	*/
	CC_SYNTHESIZE_PASS_BY_REF(int, _iAtkState, IAtkState);

	CC_SYNTHESIZE_PASS_BY_REF(int, _iBulletType, IBulletType);

	CC_SYNTHESIZE_PASS_BY_REF(int, _iDeadActCount, IDeadActCount);
	//攻击目标指针；
	VictimEntityBase *_pAtkTarget = nullptr;

	std::set<int> *_IdMap = nullptr;
};

#endif /* defined(__CarrotFantasy__BulletBase__) */