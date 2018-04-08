#pragma once
//
//  GameManager.h
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-8.
//  莫名显示红了？为什么
//

#ifndef __CarrotFantasy__GameManager__
#define __CarrotFantasy__GameManager__

#include "CommonDefine.h"

class GameManager :public Ref
{
public:

	CREATE_INSTANCE_FUNC(GameManager);

	DESTROY_INSTANCE_FUNC();

protected:
	/*
	* @brief 不暂停？你在干嘛呢
	*/
	virtual bool init();

	CC_SYNTHESIZE_PASS_BY_REF(int, _iCarrotHp, ICarrotHp);

	CC_SYNTHESIZE_PASS_BY_REF(int, _iMonsterBatch, IMonsterBatch);

	CC_SYNTHESIZE_PASS_BY_REF(bool, _bIsPause, IsPause);

private:

	GameManager() {}

	GameManager(const GameManager&) = delete;

	GameManager &operator=(const GameManager&) = delete;

};

#endif /* defined(__CarrotFantasy__GameManager__) */
