/**
* @brief 子弹图层类
* @details 1-名字起错了，这个不是图层类；
* @details 2-利用计时器(update())和(scheduleUpdate())更新检查子弹是否死亡；
* @author 何泓兵
* @date 20180411
* */
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
