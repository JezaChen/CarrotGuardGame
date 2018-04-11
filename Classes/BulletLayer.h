//
//  BulletsLayer.h
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-10.
//
//
#pragma once
#ifndef __CarrotFantasy__BulletsLayer__
#define __CarrotFantasy__BulletsLayer__

#include "EntityLayerBase.h"

/**
*  BulletsLayer use to show Bullet
*/

class BulletLayer :public EntityLayerBase
{
public:

	CREATE_FUNC(BulletLayer);

protected:

	virtual bool init();
	/*
	* @brief 检查子弹是否正常打出
	*/
	virtual void update(float dt);
};

#endif /* defined(__CarrotFantasy__BulletsLayer__) */
