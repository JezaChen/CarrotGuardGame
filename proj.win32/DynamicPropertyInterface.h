#pragma once
//
//  DynamicPropertyInterFace.h
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-7.
//  @details 动态属性界面
//

#ifndef __CarrotFantasy__DynamicPropertyInterFace__
#define __CarrotFantasy__DynamicPropertyInterFace__

#include "PublicDefine.h"

class DynamicPropertyInterFace
{
public:

	virtual ~DynamicPropertyInterFace();

protected:
	/*
	* @brief 创建动态实体动画
	*/
	virtual void createDynamicEntityAnimation(const std::vector<std::string> &rAnimationFiles);
	/*
	* @brief 获取攻击力和速度
	* @return true 获取成功，否则返回false
	*/
	virtual bool init(const int &rId, const std::string &rSCsvFileName);
	/*
	* @brief 移动动画
	*/
	virtual void doAction(const float &rDt) = 0;
	/*
	* @brief 动态实体速度
	*/
	CC_SYNTHESIZE_PASS_BY_REF(unsigned int, _iSpeed, ISpeed);
	/*
	* @brief 子弹攻击力
	*/
	CC_SYNTHESIZE_PASS_BY_REF(int, _iAtk, IAtk);

protected:

	Animation * _pAnimation = nullptr;

};

#endif /* defined(__CarrotFantasy__DynamicEntityBase__) */
