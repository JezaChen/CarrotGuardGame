/**
 * @brief 火烈炮筒炮塔类
 * @extends TowerBase
 * @details 火烈炮筒具有旋转，发射火线功能，一旦攻击某个怪物，周围的怪物也会收到攻击
 *
 * @authors 陈建彰 x 何泓兵
 * @date 20180412
 * */

#pragma once
#ifndef __CarrotFantasy__TowerFireBottle__
#define __CarrotFantasy__TowerFireBottle__
#include "TowerBase.h"

class TowerFireBottle :public TowerBase {
protected:
	/**
	* @brief 重写初始化函数
	* @see 创建动画精灵并加入树中
	*/
	virtual bool init();

	/**
	 * @brief 重写获取攻击目标函数
	 * @details 因为火烈炮筒一获取到目标就立即攻击，因而父类的方法不再适用，需要重写
	 */
	void  chooseAtkTarget();

	/**
	 * @brief 失去攻击目标
	 * @todo 与父类没什么区别，可以去掉？
	 */
	void missAtkTarget();

	/**
	 * @brief 重写父类的攻击函数
	 * @details 火烈炮筒没有子弹，而父类的函数是调用子弹类，因而父类的方法不再适用，需要重写
	 * @details 将开火的具体游戏逻辑写进里面
	 * @see 开火后怪兽的受伤动画在这里实现，因为如果交给怪兽基类负责的话要一个个判断子弹类型，其实加大了工作强度，吃力不讨好
	 */
	void fire(float dt);

	const int rId = 16;
	//动画精灵；
	Sprite * _doActionSprite;

public:

	CREATE_FUNC(TowerFireBottle);

};
#endif/* defined(__CarrotFantasy__TowerFireBottle__)*/