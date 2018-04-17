//
// BullePin.h
// CarrotFantasy
//
// Created by 何泓兵 on 18-4-11.
//
//
#pragma once
#include "BulletBase.h"
class  BulletPin :public BulletBase
{

	friend class TowerPin;

protected:
	/*
	* @brief 毒针的基本动作
	*/
	void doAction();
	/*
	* @brief 毒针毒液的移动
	*/
	void doMove()override;
	/*
	* @brief 保证子弹基类的init函数实现
	*/
	virtual bool init(const int &rId, VictimEntityBase *rVictimEntity);
	static BulletPin * create(const int &rId, VictimEntityBase * rVictimEntity);

};