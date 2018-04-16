//
//  TowerBall.h
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-12.
//  
//
#pragma once
#ifndef __CarrotFantasy__TowerBall__
#define __CarrotFantasy__TowerBall__
#include "TowerBase.h"

class TowerBall :public TowerBase {
protected:
	/**
	* @brief 确保塔的基类init函数实现
	* @see 创建动画精灵并加入树中
	* @see 计时器监控回转
	*/
	virtual bool init();
	/**
	* @brief 选择攻击目标
	*/
	void  chooseAtkTarget();
	/**
	* @brief 魔法球的攻击效果
	*/
	void fire(float dt);
	/**
	* @brief 失去攻击目标
	*/
	void missAtkTarget();

	int const rId = 10;
	//动画精灵；
	Sprite * _doActionSprite;

public:

	CREATE_FUNC(TowerBall);

};
#endif/* defined (__CarrotFantasy__TowerBall__)*/
