/**
 * @brief 飞机炮塔类
 * @extends TowerBase
 * @details 飞机炮塔具有旋转，具有直线穿透功能
 * @authors 陈建彰 x 何泓兵
 * @date 20180412
 * */

#pragma once
#ifndef __CarrotFantasy__TowerPlane__
#define __CarrotFantasy__TowerPlane__

#include "TowerBase.h"

class TowerPlane : public TowerBase
{

    int const rId = 34;

    /**
      * @brief 重写初始化函数
      * @extends TowerBase
      * */
    virtual bool init();

    /**
     * @brief 重写父类的攻击函数
     * @param dt 调度器要求引入用到的调度时间
     * @details 飞机没有子弹，而父类的函数是调用子弹类，因而父类的方法不再适用，需要重写
     * @details 将开火的具体游戏逻辑写进里面
     * @see 然而实际的攻击效果由attack()方法来实现
     */
    virtual void fire(float dt);


    Sprite *_doAnimationSprite;

public:
    /**
     * @brief 飞机实质的攻击效果函数
     * @details 由fire调用的飞机实质攻击效果的函数
     * @todo 代码风格不统一
     * */
    void attack();

    CREATE_FUNC(TowerPlane);
};

#endif /* defined(__CarrotFantasy__TowerPlane__) */