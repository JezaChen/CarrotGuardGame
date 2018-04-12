//
//  TowerPin.h
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-12.
//  
//
#pragma once 
#include "TowerBase.h"
class TowerPin :public TowerBase
{
protected:
	int const rId = 28;
	/**
	* @brief 毒针的攻击效果
	*/
	void fire(float dt);
	/**
	* @brief 确保塔的基类init函数实现
	*/
	virtual bool init();
public:

	CREATE_FUNC(TowerPin);
};
