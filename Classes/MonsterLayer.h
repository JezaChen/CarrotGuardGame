/**
 * @brief 怪物死后的金钱显示图层类
 * @todo 这文件名起的不对
 * @author 何泓兵
 * @date 20180409
 * */
#pragma once
#ifndef __CarrotFantasy__MonsterLayer__
#define __CarrotFantasy__MonsterLayer__

#include "EntityLayerBase.h"

class MonsterBase;

class MonsterLayer :public EntityLayerBase
{
public:

	CREATE_FUNC(MonsterLayer);

protected:

	/**
	 * @brief 初始化函数
	 * */
	virtual bool init();

	/**
	 * @breif 注册怪物死亡事件后的处理函数
	 * @details 怪物死亡之后，会加上金钱图层
	 * */
	virtual void registerMonsterDeadEvent();

	/*
	* @brief 怪物死亡加钱画面的图层显示
	* @details 怪物死亡胡金钱数增加过程
	* @details 准确来说，是死掉之后那个金钱的框框上升的动画
	*/
	virtual void monsterDead(Ref *pData);

	virtual void onExit()override;

};

#endif /* defined(__CarrotFantasy__MonsterLayer__) */
