//
//Carrot.h
//CarrotFantasy
//
//Created by 何泓兵 on 18-4-11
//
//
#pragma once
#ifndef __CarrotFantasy__Carrot__
#define __CarrotFantasy__Carrot__

#include "Entity.h"

class Carrot :public Entity
{

public:
	//工厂模式；
	CREATE_FUNC(Carrot);
	/**
	* @brief 胡萝卜的矩形框图
	*/
	virtual Rect getBoundingBox()const;

	virtual ~Carrot();

protected:
	/**
	* @brief 胡萝卜及其生命值的图层设定
	* @details 胡萝卜被玷污以及自动卖萌；
	*/
	virtual bool init();
	/**
	* @brief 摇晃动作或眨眼动作
	* @param iImageFirstNumber 首张图片
	* @param iImageCount 图片数
	*/
	ActionInterval * doShakeOrBlink(int iImageFirstNumber, int iImageCount);
	/*
	* @brief 动画更新
	*/
	virtual void doAction(float t);
	/*
	* @brief 萝卜受伤了
	*/
	virtual void CarrotBeHurt(Ref * pRef);
	/*
	* @brief 注册胡萝卜触摸事件
	*/
	virtual void registerCarrotTouchEvent();
	/*
	* @brief 精灵生命值
	*/
	Sprite * _HpSprite;

	CC_SYNTHESIZE_PASS_BY_REF(int, iHp, IHP);

};

#endif /* defined(__CarrotFantasy__Carrot__) */