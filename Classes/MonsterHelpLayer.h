//
//  MonsterHelpLayer.h
//  CarrotFantasy
//
//  Created by ºÎãü±ø on 18-4-9.
//
//
#pragma once
#ifndef __CarrotFantasy__MonsterHelpLayer__
#define __CarrotFantasy__MonsterHelpLayer__

#include "CommonDefine.h"

class MonsterHelpLayer :public Layer
{
public:

	CREATE_FUNC(MonsterHelpLayer);

protected:
	/*
	* @brief Ìí¼Ó¹ÖÎï°ïÖú½øÍ¼²ã
	*/
	virtual bool init()override;
};

#endif /* defined(__CarrotFantasy__MonsterHelpLayer__) */