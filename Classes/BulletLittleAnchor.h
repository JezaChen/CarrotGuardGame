//
// BulletLittleAnchor.h
// CarrotFantasy
//
// Created by 何泓兵 on 18-4-11.
//
//
#pragma once
#include "BulletAnchor.h"
class BulletLittleAnchor :public BulletAnchor
{

protected:
	/*
	* @brief 确保BulletAnchor的init函数实现
	*/
	virtual bool init(const int &rId, VictimEntityBase *rVictimEntity);

	static BulletLittleAnchor * create(const int &rId, VictimEntityBase * rVictimEntity);

};

