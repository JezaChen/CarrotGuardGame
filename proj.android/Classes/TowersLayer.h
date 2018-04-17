//
//  TowersLayer.h
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-11.
//
//
#pragma once
#ifndef __CarrotFantasy__TowersLayer__
#define __CarrotFantasy__TowersLayer__

#include "EntityLayerBase.h"

/*
* @brief 用以显示塔
*/
class TowersLayer :public EntityLayerBase
{
public:

	CREATE_FUNC(TowersLayer);

protected:
	/*
	* @brief 显示并检查塔的级别
	*/
	virtual void checkTowerGrade(float dt);
	/*
	* @details 确保layer的init函数实现
	* @details 创建精灵帧缓存并赋值
	* @details 计时器检查塔的级别
	*/
	virtual bool init();


};

#endif /* defined(__CarrotFantasy__TowersLayer__) */
