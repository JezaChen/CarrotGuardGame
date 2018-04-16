//
//  TowerAnchor.h
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-12.
//  
//
#pragma once
#include "TowerBase.h"
class TowerAnchor :public TowerBase
{
private:
	Sprite * _doActionSprite;
	int const rId = 37;
	/**
	* @brief 锚的攻击效果
	*/
	void fire(float dt);
	/**
	* @brief 确保塔的基类init函数实现
	*/
	virtual bool init();
public:
	CREATE_FUNC(TowerAnchor);
};
