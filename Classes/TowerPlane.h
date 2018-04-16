//
//  TowerPlane.h
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-12.
//
//
#pragma once
#ifndef __CarrotFantasy__TowerPlane__
#define __CarrotFantasy__TowerPlane__

#include "TowerBase.h"
class TowerPlane :public TowerBase {

	int const rId = 34;
	/**
	* @brief 确保塔的基类init函数实现
	* @see 创建动画精灵并加入树中
	*/
	virtual bool init();
	/**
	* @brief 飞机的攻击效果
	*/
	virtual void fire(float dt);
	//动画精灵；
	Sprite * _doAnimationSprite;

public:
	void attack();
	CREATE_FUNC(TowerPlane);
};

#endif /* defined(__CarrotFantasy__TowerPlane__) */