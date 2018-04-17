/**
 * @brief 怪兽工厂类
 * @details 1-这名字起的..
 * @details 2-根据怪物类型(MonsterType)生成不同的怪物基类(MonsterBase)
 * @author 何泓兵
 * @co_author 陈建彰
 * @date 20180410
 * */
#pragma once
#ifndef __CarrotFantasy__MonsterFactory__
#define __CarrotFantasy__MonsterFactory__

#include "CommonDefine.h"

class MonsterFactory
{
public:
	/**
	 * @brief 生成怪物哦
	 * @details 长得超丑的哦
	 * @details 问你怕不怕
	 * @details 怕不怕!
	 * @param rMonsterType 怪物类型
	 * @return 怪物基类
	 * */
	static MonsterBase *createMonster(const MonsterType &rMonsterType);
};

#endif /* defined(__CarrotFantasy__MonsterFactory__) */