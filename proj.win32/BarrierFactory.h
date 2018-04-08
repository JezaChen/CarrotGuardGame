
//
//  BarrierFactory.h
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-8.
//
//
#pragma once
#ifndef __CarrotFantasy__BarrierFactory__
#define __CarrotFantasy__BarrierFactory__

#include "CommonDefine.h"

class BarrierBase;

class BarrierFactory
{
public:
	/*
	* @brief 兄贵，目前障碍物只有三个，真真是高级程序员，赶工的劲头我学到了
	*/
	static BarrierBase *createBarrier(const BarrierType &rBarrierType);
};

#endif /* defined(__CarrotFantasy__BarrierFactory__) */
