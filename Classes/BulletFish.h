//
// BulletFish.h
// CarrotFantasy
//
// Created by 何泓兵 on 18-4-22.
//
//
#pragma once
#ifndef __CarrotFantasy__BulletFish__
#define __CarrotFantasy__BulletFish__
#include "BulletBase.h"
class VictimEntityBase;

class BulletFish :public BulletBase 
{

	friend class TowerFish;

protected:
	/*
	* @brief 鱼骨头的瞄准；
	*/
	void doAction();
	/*
	* @brief 鱼骨头射出子弹的移动
	*/
	void doMove()override;
	/*
	* @brief 保证子弹基类的init函数实现
	*/
	virtual bool init(const int &rId, VictimEntityBase *rVictimEntity);
	/**
	* @子弹创建
	*/
	static BulletFish * create(const int &rId, VictimEntityBase *rVictimEntity);
	/**
	* @brief 暴击效果随机数
	*/
    int _iCrit_Effect_Random_Number;


};
#endif /* defined(__CarrotFantasy__BulletFish__) */