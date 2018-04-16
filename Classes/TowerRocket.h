/**
 * @brief 火箭炮塔类
 * @extends TowerBase
 * @details 火箭炮塔具有旋转，攻击是直线穿透型攻击
 *
 * @authors 陈建彰 x 何泓兵
 * @date 20180412
 * */
#pragma once
#ifndef __CarrotFantasy__TowerRocket__
#define __CarrotFantasy__TowerRocket__
#include "TowerBase.h"
class TowerRocket :public TowerBase {

	int const rId = 25;

	/**
     * @brief 重写初始化函数
     * @extends TowerBase
     * @todo 其实没有必要写的
     * */
	virtual bool init();

	/**
     * @brief 重写父类的攻击函数
     * @details 将开火的具体游戏逻辑写进里面
     * @todo 火箭是有子弹的，感觉没有必要写吧
     */
	virtual void fire(float dt);

public:

	CREATE_FUNC(TowerRocket);
};
#endif /* defined(__CarrotFantasy__TowerRocket__) */