#pragma once

#ifndef BULLET_ARROW_H
#define BULLET_ARROW_H
#include "BulletBase.h"
#include "BulletFactory.h"

class BulletArrow : public BulletBase
{
    friend class BulletFactory;
protected:
    /**
    * @brief
    */
    void doAction();
    /**
    * @brief 射出子弹的移动
    */
    void doMove()override;
    /**
    * @brief 保证子弹基类的init函数实现
    */
    virtual bool init(const int &rId, VictimEntityBase *rVictimEntity, const int& rotation);
    /**
    * @breif 子弹创建
    */
    static BulletArrow * create(const int &rId, VictimEntityBase *rVictimEntity, const int& rotation);

    int _iRotation;
};

#endif
