/**
 * @brief 怪物基类
 * @details 怪物的公共父类
 * @authors 何泓兵 x 陈建彰
 * @date 20180409
 * */
#pragma once
#ifndef __CarrotFantasy__MonsterBase__
#define __CarrotFantasy__MonsterBase__

#include "VictimEntityBase.h"
#include "DynamicPropertyInterface.h"

class MoveControllerBase;

class MonsterBase : public VictimEntityBase, public DynamicPropertyInterface
{
	friend class MonsterFactory;

public:
	/**
	 * @brief 根据怪物id创建怪物
     * @method 设计模式中的工厂模式
	 * @param rIId 怪物Id
	 * @return 怪物ID对应的实例
	 */
	static MonsterBase * create(const int &rIId);

	/**
	 * @brief 设置最大速度
	 * @param iSpeed 怪物的最大速度
	 */
	void setMaxSpeed(const int &iSpeed);

protected:
	/**
	 * @brief 执行死亡动画
	 * @extends VictimEntityBase
	 * @param rSDeadImageFile 死亡动画帧图片
	 * @see 实质可见的死亡动画是用Entity类的方法执行
	 * @todo 参数没什么用
	 */
	virtual void deadAction(const std::string &rSDeadImageFile = "")override;

	/**
	 * @brief 模型精灵做动作
	 * @extends DynamicPropertyInterface
	 * @param rDt 调度器需要的参数，延迟时间
	 */
	virtual void doAction(const float &rDt);

	/**
	 * @brief 怪物初始化函数
	 * @param rIId 怪物的ID
	 */
	virtual bool init(const int &rIId);

	/**
	 * @brief 创建怪物动画
	 */
	virtual void createAnimation();

	/**
 	 * @brief 怪物的怪叫声，你怕不怕
	 */
	virtual void MonsterSound();

	/**
	 * @brief 判断怪物的方向
	 */
	CC_SYNTHESIZE_PASS_BY_REF(bool, _bIsLeft, IsLeft);

	MoveControllerBase * _pMoveController = nullptr;
};

#endif /* defined(__CarrotFantasy__MonsterBase__) */
