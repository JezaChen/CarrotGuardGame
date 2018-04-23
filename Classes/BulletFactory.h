/**
* @brief 子弹工厂类
* @details 1-根据子弹类型、塔的类型和被害怪物实体创建各类子弹
* @details 2-设置子弹跟随怪物旋转以及子弹的初末位置
* @author 何泓兵
* @date 20180410
* */
#pragma once
#ifndef __CarrotFantasy__BulletFactory__
#define __CarrotFantasy__BulletFactory__

#include "CommonDefine.h"

class VictimEntityBase;

class BulletFactory
{
public:
	/**
	* @brief 创建各种子弹
	* @param rBulletId 子弹的id
	* @param rTower 塔基类的指针
	* @param rVictimEntity 受伤实体，等同于攻击目标
	*/
	static BulletBase *createBullet(const int &rBulletId, TowerBase* rTower, VictimEntityBase *rVictimEntity);

    /**
     * @brief 创建章鱼子弹
     * @param rCuttleBulletId 章鱼子弹的ID
     * @param rTower 塔基类的指针
     * @param level 章鱼子弹的等级，因为不同等级的子弹数不太一样
     */
    static void createCuttleBullets(const int& rCuttleBulletId, TowerBase* rTower, VictimEntityBase *rVictimEntity);
};

#endif /* defined(__CarrotFantasy__BulletFactory__) */