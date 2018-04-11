//
//  MonsterLayer.h
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-9.
//
//
#pragma once
#ifndef __CarrotFantasy__MonsterLayer__
#define __CarrotFantasy__MonsterLayer__

#include "EntityLayerBase.h"

class MonsterBase;

/*
* @brief 用于显示怪物
*/
class MonsterLayer :public EntityLayerBase
{
public:

	CREATE_FUNC(MonsterLayer);

protected:

	/*
	* @brief 添加怪物出口进图层
	*/
	virtual bool init();
	/*
	* @brief 注册怪物死亡事件
	* @details 怪物死后胡萝卜数增加
	*/
	virtual void registerMonsterDeadEvent();
	/*
	* @brief 怪物死亡过程
	* @details 怪物死亡胡萝卜数增加过程
	*/
	virtual void monsterDead(Ref *pData);
	/*
	* @brief 动画结束
	*/
	virtual void onExit()override;

};

#endif /* defined(__CarrotFantasy__MonsterLayer__) */
