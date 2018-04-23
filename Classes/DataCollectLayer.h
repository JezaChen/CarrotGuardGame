/**
* @brief 成就汇总图层类
* @details 成就显示底图的图层
* @authors 何泓兵
* @date 20180408
* */
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