/**
 * @brief 动态实体公共父类
 * @details 游戏场景中能移动的实体都要集成该类，该类来完成动态的一些属性
 * @authors 何泓兵 x 陈建彰
 * @version 0.90 Beta
 * */

#pragma once
#ifndef __CarrotFantasy__DynamicPropertyInterface__
#define __CarrotFantasy__DynamicPropertyInterface__

#include "CommonDefine.h"

class DynamicPropertyInterface
{
public:

	virtual ~DynamicPropertyInterface();

protected:
	/**
	 * @brief 创建动态实体的运动动画
	 * @param rAnimationFiles 运动动画各个帧的路径集合
	 */
	virtual void createDynamicEntityAnimation(const std::vector<std::string> &rAnimationFiles);

	/**
	 * @brief 初始化函数
	 * @details 用Id和CSV表格文件来初始化该实例，如初始化速度、攻击力
	 * @param rId 实体Id，实质上是对应表格的某一行
	 * @param rSCsvFileName 用于读取数据的CSV表格文件
	 * @return true 初始化成功，否则返回false
	 */
	virtual bool init(const int &rId, const std::string &rSCsvFileName);

	/**
	 * @brief 移动动画
	 * @details ?虚函数，子类必须定义属于自己的移动动画
	 * @param rDt 调度函数需要这一个参数
	 */
	virtual void doAction(const float &rDt) = 0;

	/**
	 * @brief 动态实体速度
	 */
	CC_SYNTHESIZE_PASS_BY_REF(unsigned int, _iSpeed, ISpeed);
	/**
	 * @brief 攻击能力
	 */
	CC_SYNTHESIZE_PASS_BY_REF(int, _iAtk, IAtk);

protected:

	Animation * _pAnimation = nullptr;

};

#endif /* defined(__CarrotFantasy__DynamicEntityBase__) */
