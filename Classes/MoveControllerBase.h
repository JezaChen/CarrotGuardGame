/**
 * @brief 移动控制类
 * @details 怪物在地图上移动需要这个类来控制
 * @authors 陈建彰 x 何泓兵
 * @date 20180409
 * */
#pragma once
#ifndef CarrotFantasy_MoveControllerBase_h
#define CarrotFantasy_MoveControllerBase_h

#include "MonsterBase.h"

class MoveControllerBase : public Node
{
	friend class MonsterBase;
public:

	virtual ~MoveControllerBase();

	/**
	 * @brief 用于调度器使用的怪物移动调度函数
	 * @param t 调度时间
	 */
	virtual void listenerMonster(float t);


private:
	/**
	 * @brief 绑定怪物
	 * @param pMonster 待绑定的怪物
	 */
	void setMonster(MonsterBase * pMonster);

	/**
	 * @brief 擦除已走轨迹方法
	 * @details 当怪物移动之后，之前走过的轨迹要及时擦除
	 * */
	void erasePoint();

	virtual bool init(MonsterBase * pMonster);

	/**
	 * @brief 根据MonsterBase，生成对应的MonsterControllerBase
	 * @details 形成一种绑定关系
	 * @param pMonster 对应的MonsterBase
	 * */
	static MoveControllerBase * create(MonsterBase * pMonster);

	CC_SYNTHESIZE_PASS_BY_REF(int, _iMonsterSpeed, IMonsterSpeed);

	/**
	 * @brief 移动过程中特殊动画的显示函数
	 * @details 当怪物遭受到减速、停止、毒性攻击时，有一些特殊的动画显示，用这个函数娴熟出来
	 * @param iBulletType 子弹类型
	 * @param t 调度时间
	 * */
	Animation * AnimationMaker(int iBulletType, float t);

	MoveControllerBase() {}
private:

	MonsterBase *_pMonster = nullptr;

	std::vector<Vec2> * _pMapPoints;

};


#endif/* defined(CarrotFantasy_MoveControllerBase_h)*/
