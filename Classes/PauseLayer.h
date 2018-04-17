//
//  PauseLayer.h
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-13.
//
//
#pragma once
#ifndef __CarrotFantasy__PauseLayer__
#define __CarrotFantasy__PauseLayer__

#include "CommonDefine.h"

class PauseLayer :public Layer
{
public:

	CREATE_FUNC(PauseLayer);
	/**
	* @brief 暂停图层(关闭)
	*/
	virtual void setFuncFlagPauseLayerIsClose(const std::function<void()> & rFuncFlagPauseLayerIsClose);

protected:
	/**
	* @brief 确认图层加载init
	* @details 创建颜色图层，创建菜单和分享菜单，关闭触摸事件
	*/
	virtual bool init();
	/**
	* @brief 叫暂停
	*/
	virtual void onEnter()override;
	/**
	* @brief 叫继续
	*/
	virtual void onExit()override;
	/**
	* @brief 创建菜单栏
	* @details 继续游戏、重新开始、退出游戏
	*/
	virtual void createMenu();
	/**
	* @brief 创建分享菜单
	*/
	virtual void createSharedMenu();
	/**
	* @brief 关闭触摸事件
	*/
	virtual void closeTouchEvent();

	std::function<void()> _funcFlagPauseLayerIsClose;
};

#endif /* defined(__CarrotFantasy__PauseLayer__) */