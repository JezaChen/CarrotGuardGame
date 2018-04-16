//
//  MonsterFactory.cpp
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-9.
//
//

#include "MonsterFactory.h"
#include "MonsterBase.h"

MonsterBase *MonsterFactory::createMonster(const MonsterType &rMonsterType)
{
	MonsterBase *pMonster = nullptr;

	//根据怪物类型映射出不同的怪物Id
	int iMosterId = 0;
	switch (rMonsterType) {
	case en_Land_Pink:iMosterId = 2;
		break;
	case en_Land_Star:iMosterId = 1;
		break;
	case en_Land_Nima:iMosterId = 3;
		break;
	case en_Fly_Yellow:iMosterId = 7;
		break;
	case en_Fly_Blue:iMosterId = 8;
		break;
	case en_Fat_Green:iMosterId = 11;
		break;
	case en_Land_Boss_Pink:iMosterId = 5;
		break;
	case en_Land_Boss_Star:iMosterId = 4;
		break;
	case en_Land_Boss_Nima:iMosterId = 6;
		break;
	case en_Fly_Boss_Yellow:iMosterId = 9;
		break;
	case en_Fly_Boss_Blue:iMosterId = 10;
		break;
	case en_Fat_Boss_Green:iMosterId = 12;
		break;
	case en_Big_Oldboss:iMosterId = 14;
		break;
	case en_Fat_Oldboss:iMosterId = 15;
		break;
	case en_Fly_Oldboss:iMosterId = 16;
		break;
	case en_Land_Oldboss:iMosterId = 17;
		break;
	case en_Boss_Big:iMosterId = 13;
		break;
	default:
		break;
	}

	//生成并返回
	pMonster = MonsterBase::create(iMosterId);

	return pMonster;
}