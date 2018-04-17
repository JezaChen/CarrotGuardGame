//
// BulletAnchor.h
// CarrotFantasy
//
// Created by 何泓兵 on 18-4-11.
//
//
#pragma once
#include "BulletBase.h"
class BulletAnchor :public BulletBase
{

	friend class TowerAnchor;

protected:
	/**
	* @brief 锚子弹的基本动作
	*/
	void doAction();
	/**
	* @brief 锚子弹的运动
	*/
	void doMove()override;
	/**
	* @brief 保证子弹基类的成功初始化
	*/
	virtual bool init(const int &rId, VictimEntityBase *rVictimEntity);
	/**
	* @brief 创建锚的子弹
	*/
	static BulletAnchor * create(const int &rId, VictimEntityBase * rVictimEntity);

};