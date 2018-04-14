//
//  SharedMenu.h
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-13.
//
//
#pragma once
#ifndef __CarrotFantasy__SharedMenu__
#define __CarrotFantasy__SharedMenu__

#include "cocos2d.h"
using namespace cocos2d;

class SharedMenu : public Node
{
public:

	CREATE_FUNC(SharedMenu);

protected:
	/**
	* @brief 确认创建菜单栏
	*/
	virtual bool init();
	/**
	* @brief 创建分享菜单；
	* @details 分享至新浪、微博、微信
	*/
	virtual void createMenu();
};

#endif /* defined(__CarrotFantasy__SharedMenu__) */