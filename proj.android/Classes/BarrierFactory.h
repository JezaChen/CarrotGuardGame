/**
 * @brief 障碍物工厂类
 * @details 根据障碍物类型，生成对应的障碍物基类
 * @author 何泓兵
 * @date 20180408
 * @todo 不会被弃用了吧？？
 * */
#pragma once
#ifndef __CarrotFantasy__BarrierFactory__
#define __CarrotFantasy__BarrierFactory__

#include "CommonDefine.h"

class BarrierBase;

class BarrierFactory
{
public:
	/**
	 * @brief 生成障碍物基类静态方法
	 * @details 根据给定的障碍物类型，生成对应的障碍物基类
	 * @param rBarrierType 障碍物类型
	 * */
	static BarrierBase *createBarrier(const BarrierType &rBarrierType);
};

#endif /* defined(__CarrotFantasy__BarrierFactory__) */
