//
//  NumSprite.h
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-3-30.
//
//
#pragma once
#ifndef __CarrotFantasy__NumSprite__
#define __CarrotFantasy__NumSprite__

#include "CommonDefine.h"

class NumSprite
{
public:
	/*
	*@brief 静态函数，用于创造数字精灵
	*@param rsNum 你想要哪个数字的精灵，你就传那个数字进去(数字串也行哦）
	*@param rsImage 在哪个图像进行切割
	*@author 何泓兵
	*/
	static Node *createNum(const std::string &rSNum, const std::string &rSImage);
};

#endif /* defined(__CarrotFantasy__NumSprite__) */