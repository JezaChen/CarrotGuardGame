/**
 * @brief 雪花炮塔类
 * @extends TowerBase
 * @details 带毒针筒不具有旋转效果，具有冻结作用
 * @authors 陈建彰 x 何泓兵
 * @date 20180412
 * */
#pragma once
#ifndef __CarrotFantasy__TowerSnow__
#define __CarrotFantasy__TowerSnow__

#include "TowerBase.h"

class TowerSnow : public TowerBase
{

    const int rId = 31;

    /**
     * @brief 重写父类的初始化函数
     * @details 因为雪花没有旋转作用，所以要注销掉调度器
     * @see 计时器监控回转
     * @see 创建动画精灵并加入树中
     */
    virtual bool init();

    /**
     * @brief 重写开火函数
     * @see 实际上开火的实际函数是下面的attack()函数
     */
    virtual void fire(float dt);

    //开火时攻击动作精灵
    Sprite *_doAnimationSprite;

    /**
     * @brief 实际开火效果函数
     * */
    void attack();

public:

    CREATE_FUNC(TowerSnow);
};

#endif /* defined(__CarrotFantasy__TowerSnow__) */