//
//  TowerBlueStar.h
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-12.
//  
//
#pragma once
#ifndef __CarrotFantasy__TowerBlueStar__
#define __CarrotFantasy__TowerBlueStar__
#include "TowerBase.h"
class TowerBlueStar :public TowerBase {

	int const rId = 19;
	/**
	* @brief 确保塔的基类init函数实现
	* @see 计时器监控回转
	*/
	virtual bool init();
	/**
	* @brief 蓝星星的攻击效果
	*/
	virtual void fire(float dt);

public:

	CREATE_FUNC(TowerBlueStar);
};
#endif /* defined(__CarrotFantasy__TowerBlueStar__) */