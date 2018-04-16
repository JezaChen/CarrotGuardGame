//
//  TowerOptBtn.h
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-13.
//  有点懵，注释可能存在问题
//
#pragma once
#ifndef __CarrotFantasy__TowerOptBtn__
#define __CarrotFantasy__TowerOptBtn__

#include "cocos2d.h"
class TowerBase;
using namespace cocos2d;

class TowerOptBtn : public Node
{
public:

	CREATE_FUNC(TowerOptBtn);

	TowerOptBtn();

	virtual ~TowerOptBtn();
	/**
	* @brief 隐藏塔的选项
	*/
	virtual void hideTowerOpt();
	/**
	* @brief 显示塔的选项
	*/
	virtual void showTowerOpt();
	/**
	* @brief 检查金币的设置函数
	*/
	virtual void setFuncCheckMoney(const std::function<int()> &rFuncCheckMoney);
	/**
	* @brief 创建塔的菜单栏
	* @details 点击空地时显示的菜单
	* @see 显示出各种塔防的图案
	*/
	virtual void createTowerMenu();
	/**
	* @brief 点击塔防展示的菜单
	* @details 升级塔防按钮、卖掉这个塔的按钮
	*/
	virtual void gradeTowerMenu(TowerBase* touchTower);
	/**
	* @brief 展示创建菜单
	* @details 创建菜单的位置选择
	* @see 各种坐标玄学调参
	*/
	virtual void showCreateMenu();
	/**
	* @brief 隐藏创建菜单
	*/
	virtual void hideCreateMenu();
protected:
	/**
	* @brief 
	* @details 计时器监控变化过程
	*/
	virtual bool init();
	/**
	* @brief 点击创建的塔以后的动画显示
	*/
	virtual void createMenuAndItems();
	/**
	* @brief 不太懂他在干嘛
	*/
	virtual void ChangingItem(float dt);

protected:
	bool _bKeySpVisible;
	Sprite* _pKeySp;
	Menu* _pCreateMenu1;
	Menu* _pCreateMenu2;
	Menu* _pGradeMenu;
	Sprite* _pTowerRangeSp;

	std::function<int()> _funcCheckMoney;

	Vector<MenuItemSprite *> *_pCreateTowerItemSpVec = nullptr;
	Vector<MenuItemSprite *> *_pGradeTowerItemSpVec = nullptr;
};


#endif /* defined(__CarrotFantasy__TowerOptBtn__) */