//
//  TowerManager.h
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-11.
//
//
#pragma once
#ifndef __CarrotFantasy__TowerManager__
#define __CarrotFantasy__TowerManager__

#include "CommonDefine.h"

class Entity;

class TowerManager :public Ref
{
public:

	CREATE_INSTANCE_FUNCTION(TowerManager);

	DESTROY_INSTANCE_FUNCTION();
	/*
	* @brief 获取塔的vec
	*/
	virtual TowerVec &getTowerVec();
	/*
	* @brief 添加塔到layer里
	*/
	virtual void setFuncAddTowerLayer(const std::function<void(Entity*)> &rFuncAddEntityLayer);
	/*
	* @brief 清理manager
	*/
	virtual void clearManager();
	/*
	* @brief 检查塔的金钱的设置函数
	*/
	virtual void setFuncCheckMoney(const std::function<int()> &rFuncCheckMoney);
	/*
	* @brief 获取现在的金币
	*/
	virtual int getMoney();
protected:
	/*
	* @brief 声明友元塔基类
	*/
	friend class TowerBase;
	/*
	* @brief 添加塔的函数
	*/
	virtual void addTower(TowerBase *pTower);
	/*
	* @注册塔的死亡事件
	*/
	virtual void registerTowerDeadEvent();
	/*
	* @brief 分配塔vec指针内存，并注册事件
	*/
	virtual bool init();
	/*
	* @brief 从manager中清除该塔
	*/
	virtual void removeTowerFromManager(Ref *pSender);

private:
	//塔的vec指针；
	TowerVec *_pTowerVec = nullptr;

	std::function<void(Entity*)> _funcAddTowerToLayer;

	std::function<int()> _funcCheckMoney;


private:

	TowerManager();

	virtual ~TowerManager();

	TowerManager(const TowerManager &) = delete;

	TowerManager &operator=(const TowerManager &) = delete;

};


#endif /* defined(__CarrotFantasy__TowerManager__) */
