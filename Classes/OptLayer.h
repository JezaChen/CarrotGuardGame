//
//  OptLayer.h
//  CarrotFantasy
//
//  Created by ºÎãü±ø on 18-4-16.
//
//
#pragma once
#ifndef __CarrotFantasy__OptLayer__
#define __CarrotFantasy__OptLayer__

#include "cocos2d.h"

class TowerOptBtn;

using namespace cocos2d;

/**
*  OptLayer use to add,delete,upgrade Tower
*/

class OptLayer :public Layer
{
public:

	CREATE_FUNC(OptLayer);

protected:
	virtual bool init();

	virtual void listener();

protected:
	TowerOptBtn* towerOptBtn;
	bool _KeyOptBtn;
	Sprite* _pforbiddenSp;

};

#endif /* defined(__CarrotFantasy__OptLayer__) */
