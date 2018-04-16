/**
* @brief 太阳爸爸炮塔类
* @extends TowerBase
* @details 太阳爸爸不具有旋转效果，具有范围攻击效果
* @authors 陈建彰 x 何泓兵
* @date 20180412
* */
#pragma once
#ifndef __CarrotFantasy__TowerSun__
#define __CarrotFantasy__TowerSun__

#include "TowerBase.h"

class TowerSun : public TowerBase
{
private:

    const int rId = 22;

    /**
     * @brief 重写基类的初始化函数
     * @details 要注销旋转检测调度器
     * @see 计时器监控回转
     */
    virtual bool init();

    /**
     * @brief 重写开火函数
     * @details 开火函数供调度器调用
     * @param dt 调度器要求引入的参数
     */
    virtual void fire(float dt);

    //动画执行精灵；
    Sprite *_doAnimationSprite;

    /**
     * @brief 太阳爸爸实质的攻击效果函数
     * @details 由fire调用的太阳实质攻击效果的函数
     * @todo 代码风格不统一
     * */
    void attack();

public:

    CREATE_FUNC(TowerSun);
};

#endif /* defined(__CarrotFantasy__TowerSun__) */