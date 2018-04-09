//
//  MoveControllerBase.h
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-9.
//
//
#pragma once
#ifndef CarrotFantasy_MoveControllerBase_h
#define CarrotFantasy_MoveControllerBase_h

#include "MonsterBase.h"

class MoveControllerBase : public Node
{
	friend class MonsterBase;
public:

	virtual ~MoveControllerBase();
	/*
	* @brief 控制怪物动作
	*/
	virtual void listenerMonster(float t);


private:
	/*
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
