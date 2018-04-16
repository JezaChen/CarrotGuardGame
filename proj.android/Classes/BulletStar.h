//
//BulletStar.h
//CarrotFantasy
//
//Created by 何泓兵 on 18-4-11
//
//
#pragma once
#ifndef __CarrotFantasy__BulletStar__
#define __CarrotFantasy__BulletStar__
#include "BulletBase.h"
class VictimEntityBase;

class BulletStar :public BulletBase {

	friend class TowerStar;

protected:
	/*
	* @brief 星星塔防的基本动作
	*/
	void doAction();
	/*
	* @brief 星星的子弹的移动
	*/
	void doMove()override;
	/*
	* @brief 保证子弹基类的init函数实现
	*/
	virtual bool init(const int &rId, VictimEntityBase *rVictimEntity);

	static BulletStar * create(const int &rId, VictimEntityBase *rVictimEntity);
};
#endif /* defined(__CarrotFantasy__BulletStar__) */