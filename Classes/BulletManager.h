#pragma once
//
//  BulletManager.h
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-10.
//
//

#ifndef __CarrotFantasy__BulletManager__
#define __CarrotFantasy__BulletManager__

#include "CommonDefine.h"
class Entity;
class BulletManager : public Ref
{
public:
	/*
	* @brief 单例设计模式
	* @details cocos里的宏定义
	*/
	CREATE_INSTANCE_FUNCTION(BulletManager);

	DESTROY_INSTANCE_FUNCTION();
	/*
	* @brief 获取子弹的vec
	*/
	virtual BulletVec &getBulletVec();
	/*
	* @brief 添加子弹到图层的函数
	* @param rFunAddBulletLayer 
	*/
	virtual void setFuncAddBulletLayer(const std::function<void(Entity*)> &rFuncAddBulletLayer);
	/*
	* @brief 检测子弹是否打出
	*/
	virtual void checkBulletIsDead();
	/*
	* @brief 清除manager
	*/
	virtual void clearManager();

protected:
	/*
	* @brief 定义友元子弹基类
	*/
	friend class BulletBase;
	/*
	* @brief 添加子弹
	* @param 子弹基类指针
	*/
	virtual void addBullet(BulletBase *pBullet);
	/*
	* @brief 给子弹vec的指针分配内存空间
	*/
	virtual bool init();

private:
	//子弹vec的指针；
	BulletVec *_pBulletVec = nullptr;

	std::function<void(Entity*)> _funcAddBulletLayer;

private:

	BulletManager();

	virtual ~BulletManager();

	BulletManager(const BulletManager &) = delete;

	BulletManager &operator=(const BulletManager &) = delete;

};

#endif /* defined(__CarrotFantasy__BulletManager__) */
