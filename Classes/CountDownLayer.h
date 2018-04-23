/**
* @brief 游戏开始前的精灵图层类
* @details 设置倒计时动画，怪物方向标精灵动画，可建立塔防空地显示动画
* @authors 何泓兵
* @date 20180413
* */
#ifndef __CarrotFantasy__CountDownLayer__
#define __CarrotFantasy__CountDownLayer__
#pragma once
#include "cocos2d.h"
using namespace cocos2d;
class  CountDownLayer :public Layer
{
public:
	virtual bool init();

	CREATE_FUNC(CountDownLayer);

protected:
	/**
	* @brief 注册触摸无效
	* @details 设置成保护类型
	* @see 倒计时开始时触摸无效
	*/
	virtual void registerNoTouch();

private:
	int i = 0;
	Sprite * countDownSprite;
    Sprite* effPosSprites = nullptr;
    Sequence* _pFadeSequence = nullptr;

	/**
	* @brief 倒计时开始游戏
	*/
	void Num1(float t);//3
	void Num2(float t);//2
	void Num3(float t);//1
	void GameGo(float t);//开始
	/**
	* @brief 开始游戏的特效
	* @details 循环转动精灵
	*/
	void Circle();
	/**
	* @brief 怪物出现起始点的三个红色指示标方向的精灵
	*/
	void runArrow1(float t);
	void runArrow2(float t);
	void runArrow3(float t);


	//void clearArrow(float t);
	/**
	* @brief 清除孩子结点
	* @details 发出通知可以放怪物了
	*/
	void childDisappear(float t);
	/**
	* @brief 初始化可建立塔防空地的闪烁效果特效函数
	*/
    void initEffectPosBlink();
	/**
	* @brief 封装
	*/
    void effectPosBlink(float t);
};
#endif/* defined(__CarrotFantasy__CountDownLayer__)*/