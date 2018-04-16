//
// BulletBlueStar.h
// CarrotFantasy
//
// Created by 何泓兵 on 18-4-11.
//
//
#pragma once
#ifndef __CarrotFantasy__BulletBlueStar__
#define __CarrotFantasy__BulletBlueStar__
#include "BulletBase.h"
class VictimEntityBase;

class BulletBlueStar :public BulletBase {

	friend class TowerBlueStar;

protected:
	/*
	* @brief 蓝星星的瞄准；
	*/
	void doAction();
	/*
	* @brief 蓝星星射出子弹的移动
	*/
	void doMove()override;
	/*
	* @brief 保证子弹基类的init函数实现
	*/
	virtual bool init(const int &rId, VictimEntityBase *rVictimEntity);

	static BulletBlueStar * create(const int &rId, VictimEntityBase *rVictimEntity);
};
#endif /* defined(__CarrotFantasy__BulletBlueStar__) */