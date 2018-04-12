//
//  TowerFactory.h
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-12.
//
//
#pragma once
#ifndef __CarrotFantasy__TowerFactory__
#define __CarrotFantasy__TowerFactory__

#include "CommonDefine.h"

class TowerBase;

class TowerFactory
{
public:
	/**
	* @brief 创建塔
	* @param rTowerType 塔的种类
	* @param tPosition 位置坐标
	*/
	static TowerBase *createTower(const TowerType &rTowerType, Vec2 tPosition);
};

#endif /* defined(__CarrotFantasy__TowerFactory__) */
