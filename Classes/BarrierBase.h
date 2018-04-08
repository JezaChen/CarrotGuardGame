//
//  BarrierBase.h
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-7.
//
//
#pragma once
#ifndef __CarrotFantasy__BarrierBase__
#define __CarrotFantasy__BarrierBase__


#include "VictimEntityBase.h"

class BarrierBase :public VictimEntityBase
{

public:

	static BarrierBase * create(const int &rId);
	/*
	* @brief 友元障碍物工厂
	*/
	friend class BarrierFactory;

protected:
	/*
	* @brief 添加障碍物
	* @details 绑定受伤实体基类的init
	* @return true 添加成功，否则返回false
	*/
	virtual bool init(const int &rId);
	/*
	* @brief 死亡动画
	*/
	virtual void deadAction(const std::string &rSDeadImageFile = "");
	/*
	* @brief 受伤动画
	*/
	virtual void behurtAction();

};

#endif /* defined(__CarrotFantasy__BarrierBase__) */
