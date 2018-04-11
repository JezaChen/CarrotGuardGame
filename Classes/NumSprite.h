/**
 * @brief 数字精灵
 * @authors 何泓兵，陈建彰
 * */
#pragma once
#ifndef __CarrotFantasy__NumSprite__
#define __CarrotFantasy__NumSprite__

#include "CommonDefine.h"

class NumSprite
{
public:
	/**
	 * @brief 静态函数，用于创造数字精灵
	 * @param rsNum 你想要哪个数字的精灵，你就传那个数字进去(数字串也行哦）
	 * @param rsImage 在哪个图像进行切割
	 * @author 何泓兵
	 */
	static Node *createNum(const std::string &rSNum, const std::string &rSImage);

	/**
	 * @brief 静态函数，用于创造斜杠精灵
	 * @details 有一些场合需要用到斜杠，所以在这个工具类加上这个函数，用于创造斜杠精灵
	 * @param rsImage 在哪个图像进行切割
	 * @author 陈建彰
	 */
	static Sprite *createSprit(const std::string &rsImage);
};

#endif /* defined(__CarrotFantasy__NumSprite__) */