//
//  MonsterFactory.h
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-9.
//
//
#pragma once
#ifndef __CarrotFantasy__MonsterFactory__
#define __CarrotFantasy__MonsterFactory__

#include "CommonDefine.h"

class MonsterFactory
{
public:
	/*
	* @brief 各种怪物哦，你怕不怕，长得超丑的
	*/
	static MonsterBase *createMonster(const MonsterType &rMonsterType);
};

#endif /* defined(__CarrotFantasy__MonsterFactory__) */