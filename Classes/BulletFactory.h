
//
//  BulletFactory.h
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-10.
//
//
#pragma once
#ifndef __CarrotFantasy__BulletFactory__
#define __CarrotFantasy__BulletFactory__

#include "CommonDefine.h"

class VictimEntityBase;

class BulletFactory
{
public:
	/*
	* @brief 创建各种子弹
	* @param rBulletId 子弹的id
	* @param rTower
	* @param rVictimEntity 受伤实体，等同于攻击力
	*/
	static BulletBase *createBullet(const int &rBulletId, TowerBase* rTower, VictimEntityBase *rVictimEntity);
};

#endif /* defined(__CarrotFantasy__BulletFactory__) */