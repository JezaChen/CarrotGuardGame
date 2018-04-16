/**
 * @brief 带毒针筒炮塔类
 * @extends TowerBase
 * @details 带毒针筒具有旋转，具有发射毒药功能，而且毒药可以持续一段时间
 * @authors 陈建彰 x 何泓兵
 * @date 20180412
 * */
#pragma once 
#include "TowerBase.h"
class TowerPin :public TowerBase
{
protected:
	int const rId = 28;
	/**
	* @brief 毒针的攻击效果
	*/
	void fire(float dt);
	/**
	* @brief 确保塔的基类init函数实现
	*/
	virtual bool init();
public:

	CREATE_FUNC(TowerPin);
};
