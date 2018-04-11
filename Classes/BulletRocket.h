//
// BulletRocket.h
// CarrotFantasy
//
// Created by 何泓兵 on 18-4-11.
//
//
#pragma once
#ifndef __CarrotFantasy__BulletRocket__
#define __CarrotFantasy__BulletRocket__
#include "BulletBase.h"
class VictimEntityBase;

class BulletRocket :public BulletBase {

	friend class TowerRocket;

protected:
	/*
	* @brief 火箭子弹的基本动作
	*/
	void doAction();
	/*
	* @brief 火箭弹的移动
	*/
	void doMove()override;
	/*
	* @brief 保证子弹基类的init函数实现
	*/
	virtual bool init(const int &rId, VictimEntityBase *rVictimEntity);

	static BulletRocket * create(const int &rId, VictimEntityBase *rVictimEntity);
};
#endif /* defined(__CarrotFantasy__BulletRocket__) */