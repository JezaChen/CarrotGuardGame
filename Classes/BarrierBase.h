/**
 * @brief 障碍物基类
 * @details 说的是基类，其实它已经封装好障碍物一切的功能了
 * @author 何泓兵
 * @co_author 陈建彰
 * @date 20180408
 * */
#pragma once
#ifndef __CarrotFantasy__BarrierBase__
#define __CarrotFantasy__BarrierBase__


#include "VictimEntityBase.h"

class BarrierBase :public VictimEntityBase
{

public:

	/**
	 * @brief 静态函数，用于生产障碍物基类
	 * @method 设计模式中的工厂模式
	 * */
	static BarrierBase * create(const int &rId);

	/**
	 * @brief 声明一个友元，障碍物工厂
	 * @details 毕竟障碍物工厂负责生成障碍物，那它和障碍物基类是相互依存的，两者互为友元
	 * @todo 为了代码安全，可以不用友元
	 * */
	friend class BarrierFactory;

protected:
	/**
	 * @brief 初始化函数
	 * @details 用于给定的ID，初始化实例
	 * @param rId 障碍物ID
	 * @details 这个函数供create函数调用，属于工厂模式生产过程中的初始化阶段处理函数
	 * */
	virtual bool init(const int &rId);

	/**
	 * @brief 死亡操作
	 * @extends VictimEntityBase
	 * @details 根据给定的文件路径生成死亡动画，并进行一些清理操作
	 * @details 实质这个函数没有自己实现死亡动画，死亡动画调用父类的默认死亡动画
	 * @param rSDeadImageFile 死亡动画帧路径
	 * */
	virtual void deadAction(const std::string &rSDeadImageFile = "");
};

#endif /* defined(__CarrotFantasy__BarrierBase__) */
