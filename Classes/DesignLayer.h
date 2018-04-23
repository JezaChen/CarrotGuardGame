/**
* @brief 游戏中“关于我们”的设计者名字显示类
* @authors 何泓兵
* @date 20180408
* */
#pragma once
#ifndef __CarrotFantasy__DesignLayer__
#define __CarrotFantasy__DesignLayer__

#include "cocos2d.h"

using namespace cocos2d;

class DesignLayer : public Layer
{
public:

	CREATE_FUNC(DesignLayer);

protected:
	/*
	* @brie 添加显示作者的图层
	*/
	virtual bool init();
	/*
	* @brief 显示作者的图层
	*/
	virtual void loadSource();

};

#endif /* defined(__CarrotFantasy__DesignLayer__) */
