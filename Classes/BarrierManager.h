//
//  BarrierManager.h
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-7.
//
//

#pragma once
#ifndef __CarrotFantasy__BarrierManager__
#define __CarrotFantasy__BarrierManager__

#include "CommonDefine.h"

class Entity;

class BarrierManager : public Ref
{
public:
	/*
	* @brief 单例设计模式
	* @see 来源于cocos的宏
	*/
	CREATE_INSTANCE_FUNCTION(BarrierManager);

	DESTROY_INSTANCE_FUNCTION();
	/*
	* @brief 获取障碍物vector
	*/
	BarrierVec &getBarrierVec();
	/*
	* @brief 设置添加障碍物到layer里
	* @param 
	*/
	virtual void setFuncAddBarrierToLayer(const std::function<void(Entity*)> &rFuncAddBarrierToLayer);
	/*
	* @brief 清理被攻击的锁定状态
	*/
	virtual void clearBeAtkLockState();
	/*
	* @brief 清理管理
	*/
	virtual void clearManager();

protected:

	friend class BarrierBase;
	/*
	* @brief 添加障碍物
	*/
	virtual void addBarrier(BarrierBase *pBarrier);
	/*
	* @brief 设置BarrierVec，并注册事件
	* @return true 搞定返回，否则返回false
	*/
	virtual bool init();
	/*
	* @brief 注册障碍物被干掉事件
	*/
	virtual void registerBarrierDeadEvent();
	/*
	* @brief 从manager中删去指定的障碍物
	*/
	virtual void removeBarrierFromManager(Ref *pBarrier);

private:
	//赋空vector；
	BarrierVec *_pBarrierVec = nullptr;

	std::function<void(Entity*)> _funcAddBarrierToLayer;

private:

	BarrierManager();

	virtual ~BarrierManager();

	BarrierManager(const BarrierManager &) = delete;

	BarrierManager &operator=(const BarrierManager &) = delete;
};

#endif /* defined(__CarrotFantasy__BarrierManager__) */