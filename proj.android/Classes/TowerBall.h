/**
 * @brief 精灵球炮塔类
 * @extends TowerBase
 * @details 精灵球筒不具有旋转，具有发射电击功能
 *
 * @authors 陈建彰 x 何泓兵
 * @date 20180412
 * */

#pragma once
#ifndef __CarrotFantasy__TowerBall__
#define __CarrotFantasy__TowerBall__

#include "TowerBase.h"

class TowerBall : public TowerBase
{
protected:
    /**
      * @brief 重写初始化函数
      * @extends TowerBase
      * @details 重写是因为要注销旋转调度器，精灵球没有旋转效果
      * */
    virtual bool init();

    /**
      * @brief 重写获取攻击目标函数
      * @details 因为精灵球一获取到目标就立即攻击，因而父类的方法不再适用，需要重写
      * @see 火烈炮筒跟它一样要重写
      */
    void chooseAtkTarget();

    /**
     * @brief 重写父类的攻击函数
     * @details 精灵球没有子弹，而父类的函数是调用子弹类，因而父类的方法不再适用，需要重写
     * @details 将开火的具体游戏逻辑写进里面
     * @see 开火后怪兽的受伤动画在这里实现，因为如果交给怪兽基类负责的话要一个个判断子弹类型，其实加大了工作强度，吃力不讨好
     */
    void fire(float dt);

    /**
     * @brief 失去攻击目标
     * @todo 这个写的好还是父类写得好，值得商榷
     */
    void missAtkTarget();

    const int rId = 10;
    //动画精灵；
    Sprite *_doActionSprite;

public:

    CREATE_FUNC(TowerBall);

};

#endif/* defined (__CarrotFantasy__TowerBall__)*/
