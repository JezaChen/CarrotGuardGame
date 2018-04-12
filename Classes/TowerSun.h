//
//  TowerSun.h
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-12.
//  参数有鬼
//
#pragma once
#ifndef __CarrotFantasy__TowerSun__
#define __CarrotFantasy__TowerSun__
#include "TowerBase.h"
class TowerSun :public TowerBase {
private:

	int const rId = 22;
	/**
	* @brief 确保塔的基类init函数的实现
	* @see 创建动画执行精灵并加入树中
	*/
	virtual bool init();
	/**
	* @brief 太阳塔的燃烧效果
	* @param dt 并不知道这个参数干嘛的
	*/
	virtual void fire(float dt);
	//动画执行精灵；
	Sprite * _doAnimationSprite;

	void attack();

public:

	CREATE_FUNC(TowerSun);
};
#endif /* defined(__CarrotFantasy__TowerSun__) */