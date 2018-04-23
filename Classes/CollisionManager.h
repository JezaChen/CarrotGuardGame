/**
* @brief 风扇子弹碰撞检测类
* @authors 何泓兵 x 陈建彰
* @date 20180412
* */
#pragma once
#ifndef __CarrotFantasy__CollisionManager__
#define __CarrotFantasy__CollisionManager__

#include "CommonDefine.h"

class CollisionManager
{
public:
	/**
	* @brief 处理碰撞
	* @param rBarrierVec 障碍物vec
	* @param rMonsterVec 怪物vec
	* @param rBulletVec 子弹vec
	*/
	static void collision(Vector<BarrierBase *> &rBarrierVec, Vector<MonsterBase *> &rMonsterVec, Vector<BulletBase*> &rBulletVec);

protected:
	/**
	* @brief 子弹和怪物的碰撞
	* @param pBullet 子弹的指针
	* @param rMonSterVec 怪物vec
	*/
	static void MonsterAndBullet(BulletBase * pBullet, Vector<MonsterBase *> &rMonsterVec);
	/**
	* @brief 障碍物和子弹的碰撞
	* @param pBullet 子弹的指针
	* @param rBarrierVec 障碍物vec
	*/
	static void BarrierAndBullet(BulletBase * pBullet, Vector<BarrierBase *> &rBarrierVec);
	/**
	* @brief 创建动画
	* @param BulletName 子弹名称
	* @param SpriteFrameCount 精灵帧数目
	*/
	static Animation * AnimationMaker(std::string BulletName, int SpriteFrameCount);

};

#endif /* defined(__CarrotFantasy__CollisionManager__) */