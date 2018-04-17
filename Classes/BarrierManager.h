/**
 * @brief 障碍物管理类
 * @details 管理游戏过程中的障碍物，比如注册、去除等等操作
 * @authors 何泓兵 x 陈建彰
 * @date 20180408
 * */
#pragma once
#ifndef __CarrotFantasy__BarrierManager__
#define __CarrotFantasy__BarrierManager__

#include "CommonDefine.h"
//为了减少头文件包含；
class Entity;

class BarrierManager : public Ref
{
public:
	/**
	 * @brief 创建函数
	 * @details 设计模式中的单例模式
	 * @see 来源于cocos的宏
	 */
	CREATE_INSTANCE_FUNCTION(BarrierManager);

	DESTROY_INSTANCE_FUNCTION();

	/**
     * @brief 获取障碍物向量
     * @return 障碍物向量的引用
	 */
	BarrierVec& getBarrierVec();

	/**
	 * @brief 设置用于添加障碍物到图层的处理函数
	 * @param rFuncAddBarrierToLayer 用于添加障碍物到图层的函数
	 */
	virtual void setFuncAddBarrierToLayer(const std::function<void(Entity*)> &rFuncAddBarrierToLayer);

	/**
	 * @brief 清理被攻击的锁定状态
	 */
	virtual void clearBeAtkLockState();

	/**
	 * @brief 清理管理
	 */
	virtual void clearManager();

protected:

	/**
	 * @brief 声明一个友元，障碍物基类
	 * */

	friend class BarrierBase;

	/**
	 * @brief 添加(注册)障碍物
	 * @param pBarrier 要注册的障碍物基类
	 */
	virtual void addBarrier(BarrierBase *pBarrier);

	/**
	 * @brief 初始化函数
	 * @return true 初始化成功，否则返回false
	 */
	virtual bool init();

	/**
	 * @brief 注册障碍物被干掉事件
	 */
	virtual void registerBarrierDeadEvent();

	/**
	 * @brief 从manager中删去指定的障碍物
	 */
	virtual void removeBarrierFromManager(Ref *pBarrier);

private:
	//赋空vector；
	BarrierVec *_pBarrierVec = nullptr; //管理障碍物用的向量
	//用于添加障碍物到图层的函数；
	std::function<void(Entity*)> _funcAddBarrierToLayer;

private:

	BarrierManager();

	virtual ~BarrierManager();

	BarrierManager(const BarrierManager &) = delete;

	BarrierManager &operator=(const BarrierManager &) = delete;
};

#endif /* defined(__CarrotFantasy__BarrierManager__) */