/**
* @brief 子弹管理类
* @details 添加子弹到图层、将子弹加入向量统一管理监控
* @author 何泓兵
* @date 180410
* */
#pragma once
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
	/**
	* @brief 获取子弹vector的引用
	*/
	virtual BulletVec &getBulletVec();
	/*
	* @brief 添加子弹到图层的设置函数
	*/
	virtual void setFuncAddBulletLayer(const std::function<void(Entity*)> &rFuncAddBulletLayer);
	/*
	* @brief 检测子弹是否打出
	*/
	virtual void checkBulletIsDead();
	/*
	* @brief 清除管理类
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
	* @brief 给子弹vector指针分配内存空间
	*/
	virtual bool init();

private:
	//子弹vector的指针；
	BulletVec *_pBulletVec = nullptr;

	std::function<void(Entity*)> _funcAddBulletLayer;

private:

	BulletManager();

	virtual ~BulletManager();

	BulletManager(const BulletManager &) = delete;

	BulletManager &operator=(const BulletManager &) = delete;

};

#endif /* defined(__CarrotFantasy__BulletManager__) */
