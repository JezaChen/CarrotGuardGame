//
//  TowerRocket.h
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-12.
//  
//
#pragma once
#ifndef __CarrotFantasy__TowerRocket__
#define __CarrotFantasy__TowerRocket__
#include "TowerBase.h"
class TowerRocket :public TowerBase {

	int const rId = 25;
	/**
	* @brief 确保塔的基类init函数实现
	*/
	virtual bool init();
	/**
	* @brief 火箭攻击效果
	*/
	virtual void fire(float dt);

public:

	CREATE_FUNC(TowerRocket);
};
#endif /* defined(__CarrotFantasy__TowerRocket__) */