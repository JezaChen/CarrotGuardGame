//
//  MonsterFactory.cpp
//  CarrotFantasy
//
//  Created by ºÎãü±ø on 18-4-9.
//
//

#include "MonsterFactory.h"
#include "MonsterBase.h"

MonsterBase *MonsterFactory::createMonster(const MonsterType &rMonsterType)
{
	MonsterBase *pMonster = nullptr;

	int iMonsterId = 0;
	switch (rMonsterType) {
	case en_Land_Pink:iMonsterId = 2;
		break;
	case en_Land_Star:iMonsterId = 1;
		break;
	case en_Land_Nima:iMonsterId = 3;
		break;
	case en_Fly_Yellow:iMonsterId = 7;
		break;
	case en_Fly_Blue:iMonsterId = 8;
		break;
	case en_Fat_Green:iMonsterId = 11;
		break;
	case en_Land_Boss_Pink:iMonsterId = 5;
		break;
	case en_Land_Boss_Star:iMonsterId = 4;
		break;
	case en_Land_Boss_Nima:iMonsterId = 6;
		break;
	case en_Fly_Boss_Yellow:iMonsterId = 9;
		break;
	case en_Fly_Boss_Blue:iMonsterId = 10;
		break;
	case en_Fat_Boss_Green:iMonsterId = 12;
		break;
	case en_Big_Oldboss:iMonsterId = 14;
		break;
	case en_Fat_Oldboss:iMonsterId = 15;
		break;
	case en_Fly_Oldboss:iMonsterId = 16;
		break;
	case en_Land_Oldboss:iMonsterId = 17;
		break;
	case en_Boss_Big:iMonsterId = 13;
		break;
    case en_Boss_Woowala:iMonsterId = 19;
        break;
    case en_Boss_PinkyNinja:iMonsterId = 20;
        break;
    case en_Boss_TwistyFork:iMonsterId = 21;
        break;
    case en_Boss_FlyDevils:iMonsterId = 22;
        break;
    case en_Boss_Cyclops:iMonsterId = 23;
        break;
    case en_Boss_Popbowling:iMonsterId = 24;
        break;
    case en_Boss_Gremlins:iMonsterId = 25;
        break;
    case en_Boss_Sadgeezer:iMonsterId = 26;
        break;
    case en_Boss_FireFeet:iMonsterId = 27;
        break;
    case en_Boss_Unicorn:iMonsterId = 28;
        break;
    case en_Boss_DarkAngle:iMonsterId = 29;
        break;
    case en_Boss_FatMummy:iMonsterId = 30;
        break;
    case en_Boss_ConchKing:iMonsterId = 31;
        break;
    case en_Boss_Hotstar:iMonsterId = 32;
        break;
    case en_Boss_DrOctopus:iMonsterId = 33;
        break;
    case en_Boss_HugeChela:iMonsterId = 34;
        break;

	default:
		break;
	}
	pMonster = MonsterBase::create(iMonsterId);

	return pMonster;
}