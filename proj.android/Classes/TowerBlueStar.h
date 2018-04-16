/**
 * @brief 蓝色星星炮塔类
 * @extends TowerBase
 * @details 蓝色星星没有旋转(因而需要在初始化那里注销调度器)、具有冻结作用
 * @authors 陈建彰 x 何泓兵
 * @date 20180409
 * */

#pragma once

#ifndef __CarrotFantasy__TowerBlueStar__
#define __CarrotFantasy__TowerBlueStar__

#include "TowerBase.h"

class TowerBlueStar : public TowerBase
{

    int const rId = 19;

    /**
     * @brief 重写初始化函数
     * @extends TowerBase
     * @details 重写是因为要注销旋转调度器，蓝色星星没有旋转效果
     */
    virtual bool init();

    /**
     * @brief 重写蓝色星星开炮函数
     * @details 处理一下开火间歇时间
     * @todo
     */
    virtual void fire(float dt);

public:

    CREATE_FUNC(TowerBlueStar);
};

#endif /* defined(__CarrotFantasy__TowerBlueStar__) */