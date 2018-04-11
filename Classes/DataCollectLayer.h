
//  DataCollectLayer.h
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-8.
//
//
#pragma once
#ifndef __CarrotFantasy__DataCollectLayer__
#define __CarrotFantasy__DataCollectLayer__

#include "cocos2d.h"

using namespace cocos2d;

class DataCollectLayer : public Layer
{
public:

	CREATE_FUNC(DataCollectLayer);

protected:
	/*
	* @brief 成就汇总图层添加
	*/
	virtual bool init();
	/*
	* @brief 兄贵，成就汇总图，你看看你才消灭几个怪物啊
	*/
	virtual void loadSource();

};

#endif /* defined(__CarrotFantasy__DataCollectLayer__) */