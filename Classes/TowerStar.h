//
//  TowerStar.h
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-12.
//  
//
#pragma once
#ifndef __CarrotFantasy__TowerStar__
#define __CarrotFantasy__TowerStar__
#include "TowerBase.h"
class TowerStar :public TowerBase {

	int const rId = 13;
	/**
	* @brief 确保塔的基类init函数实现
	* @see 计时器监控回转
	*/
	virtual bool init();
	/**
	* @brief 星星的作用效果
	*/
	virtual void fire(float dt);

public:

	CREATE_FUNC(TowerStar);
};
#endif /* defined(__CarrotFantasy__TowerStar__) */