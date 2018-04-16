//
//  TowerFireBottle.h
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-12.
//  
//
#pragma once
#ifndef __CarrotFantasy__TowerFireBottle__
#define __CarrotFantasy__TowerFireBottle__
#include "TowerBase.h"

class TowerFireBottle :public TowerBase {
protected:
	/**
	* @brief 确保塔的基类init函数实现
	* @see 创建动画精灵并加入树中
	*/
	virtual bool init();
	/**
	* @brief 获取攻击目标
	*/
	void  chooseAtkTarget();
	/**
	* @brief 失去攻击目标
	*/
	void missAtkTarget();
	/**
	* @brief 汽油桶的攻击效果
	*/
	void fire(float dt);

	int const rId = 16;
	//动画精灵；
	Sprite * _doActionSprite;

public:

	CREATE_FUNC(TowerFireBottle);

};
#endif/* defined(__CarrotFantasy__TowerFireBottle__)*/