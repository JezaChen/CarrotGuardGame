
//
//  BarriersLayer.h
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-8.
//
//
#pragma once
#ifndef __CarrotFantasy__BarriersLayer__
#define __CarrotFantasy__BarriersLayer__

#include "EntityLayerBase.h"

/**
 *  @brief 障碍物层用以显示障碍物
 */

class BarriersLayer : public EntityLayerBase
{

public:

	CREATE_FUNC(BarriersLayer);

protected:
	/*
	 * @brief 执行障碍物实体层基类的初始化；
	 */
	virtual bool init();
	/**
	* @brief 显示障碍物被清空时出现的图层
	*/
	void DeleteBarrierLayer(Ref* rBarrierVec);

};

#endif /* defined(__CarrotFantasy__BarriersLayer__) */
