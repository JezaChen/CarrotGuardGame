//
//  TowerSnow.h
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-12.
//  
//
#pragma once
#ifndef __CarrotFantasy__TowerSnow__
#define __CarrotFantasy__TowerSnow__
#include "TowerBase.h"
class TowerSnow :public TowerBase {

	int const rId = 31;
	/**
	* @brief 确保塔的基类init函数实现
	* @see 计时器监控回转
	* @see 创建动画精灵并加入树中
	*/
	virtual bool init();
	/**
	* @brief 雪花的攻击效果
	*/
	virtual void fire(float dt);
	//动画精灵；
	Sprite * _doAnimationSprite;

	void attack();

public:

	CREATE_FUNC(TowerSnow);
};
#endif /* defined(__CarrotFantasy__TowerSnow__) */