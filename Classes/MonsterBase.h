//
//  MonsterBase.h
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-9.
//
//
#pragma once
#ifndef __CarrotFantasy__MonsterBase__
#define __CarrotFantasy__MonsterBase__

#include "VictimEntityBase.h"
#include "DynamicPropertyInterFace.h"

class MoveControllerBase;

class MonsterBase : public VictimEntityBase, public DynamicPropertyInterFace
{
	friend class MonsterFactory;

public:
	/*
	* @brief 根据怪物id创建怪物
	*/
	static MonsterBase * create(const int &rIId);
	/*
	* @brief 设置最大速度
	*/
	void setMaxSpeed(const int &iSpeed);

protected:
	/*
	* @brief 执行死亡动画
	*/
	virtual void deadAction(const std::string &rSDeadImageFile = "")override;
	/*
	* @brief 模型精灵做动作
	*/
	virtual void doAction(const float &rDt);
	/*
	* @brief 怪物init
	*/
	virtual bool init(const int &rIId);
	/*
	* @brief 受伤动画
	*/
	virtual void behurtAction();
	/*
	* @brief 创建怪物动画
	*/
	virtual void createAnimation();
	/*
	* @brief 怪物的怪叫声，你怕不怕
	*/
	virtual void MonsterSound();
	/*
	* @brief 判断怪物的方向
	*/
	CC_SYNTHESIZE_PASS_BY_REF(bool, _bIsLeft, IsLeft);

	MoveControllerBase * _pMoveController = nullptr;
};

#endif /* defined(__CarrotFantasy__MonsterBase__) */
