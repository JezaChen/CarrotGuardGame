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
	 * @brief 控制怪物动作
	 */
	virtual void listenerMonster(float t);


private:
	/**
	 * @brief 设置怪物移动
	 */
	void setMonster(MonsterBase * pMonster);

	/**
	 * erase the vector's Point
	 */
	void erasePoint();

	virtual bool init(MonsterBase * pMonster);

	static MoveControllerBase * create(MonsterBase * pMonster);

	CC_SYNTHESIZE_PASS_BY_REF(int, _iMonsterSpeed, IMonsterSpeed);

	Animation * AnimationMaker(int iBulletType, float t);

	MoveControllerBase() {}
private:

	MonsterBase *_pMonster = nullptr;

	std::vector<Vec2> * _pMapPoints;

};


#endif/* defined(CarrotFantasy_MoveControllerBase_h)*/
