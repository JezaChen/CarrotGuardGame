/**
* @brief 大章鱼炮塔类
* @extends TowerBase
* @details 大章鱼不具有旋转效果，具有范围攻击效果
* @authors 何泓兵
* @date 20180419
* */
#pragma once
#ifndef __CarrotFantasy__TowerCuttle__
#define __CarrotFantasy__TowerCuttle__

#include "TowerBase.h"

class TowerCuttle :public TowerBase
{
private:
	const int rId = 40;

	AtkProperty atk;

	//动画执行精灵；
	Sprite *_doAnimationSprite;

	/**
	* @brief 重写基类的初始化函数
	* @details 要注销旋转检测调度器
	* @see 计时器监控旋转
	*/
	virtual bool init();

	/**
	* @brief 重写开火函数
	* @details 开火函数供调度器调用
	* @param dt 调度器要求引入的参数
	*/
	virtual void fire(float dt);

public:

	CREATE_FUNC(TowerCuttle);
};
#endif /* defined(__CarrotFantasy__TowerCuttle__) */