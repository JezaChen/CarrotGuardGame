#pragma once
#ifndef __CarrotFantasy__Carrot__
#define __CarrotFantasy__Carrot__

#include "Entity.h"

class Carrot :public Entity
{

public:

	CREATE_FUNC(Carrot);

	virtual Rect getBoundingBox()const;

	virtual ~Carrot();

protected:

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