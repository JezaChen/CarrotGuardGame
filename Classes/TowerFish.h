/**
* @brief 鱼骨头炮塔类
* @extends TowerBase
* @details 鱼骨头具有旋转效果，具有概率冻结(即眩晕)作用
* @authors 何泓兵
* @date 20180422
* */

#pragma once

#ifndef __CarrotFantasy__TowerFish__
#define __CarrotFantasy__TowerFish__

#include "TowerBase.h"

class TowerFish : public TowerBase
{

	int const rId = 43;

	/**
	* @brief 重写初始化函数
	* @extends TowerBase
	*/
	virtual bool init();

	/**
	* @brief 重写鱼骨头开炮函数
	* @details 处理一下开火间歇时间
	* @todo
	*/
	virtual void fire(float dt);

public:

	CREATE_FUNC(TowerFish);
};

#endif /* defined(__CarrotFantasy__TowerFish__) */
