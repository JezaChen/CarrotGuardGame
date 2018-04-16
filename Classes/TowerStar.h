/**
 * @brief 普通星星炮塔类
 * @extends TowerBase
 * @details 普通星星不具有旋转效果，具有附带攻击周围怪物效果
 * @authors 陈建彰 x 何泓兵
 * @date 20180412
 * */
#pragma once
#ifndef __CarrotFantasy__TowerStar__
#define __CarrotFantasy__TowerStar__
#include "TowerBase.h"
class TowerStar :public TowerBase {

	int const rId = 13;
	/**
	 * @brief 重写基类的初始化函数
	 * @details 要注销旋转检测调度器
	 * @see 计时器监控回转
	 */
	virtual bool init();
	/**
	 * @brief 重写父类的开火函数
	 * @details 星星炮塔有星星子弹，所以攻击逻辑交由子弹类实现，因而不需要写额外的attack()函数来实现攻击逻辑
	 */
	virtual void fire(float dt);

public:

	CREATE_FUNC(TowerStar);
};
#endif /* defined(__CarrotFantasy__TowerStar__) */