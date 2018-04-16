/**
* @brief 船锚炮塔类
* @extends TowerBase
* @details 船锚炮塔具有旋转效果，具有瞎几把扔锚效果
* @authors 陈建彰 x 何泓兵
* @date 20180412
* */
#pragma once

#include "TowerBase.h"

class TowerAnchor : public TowerBase
{
private:
    Sprite *_doActionSprite;
    int const rId = 37;

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
    void fire(float dt);


public:
    CREATE_FUNC(TowerAnchor);
};
