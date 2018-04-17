#pragma once
#ifndef  SPRITES_LAYER_H
#define SPRITES_LAYER_H

#include "CommonDefine.h"
class SpritesLayer : public Layer
{
public:
    CREATE_FUNC(SpritesLayer);
    virtual ~SpritesLayer();
protected:
    /*
    @brief  初始化函数
    */
    virtual bool init();
    /*
    @brief 创建静态、不会动的精灵
    */
    virtual void createStaticSprites();
    /*
    @brief 创建动态的精灵
    */
    virtual void createDynamicSprites();
    /*
    @brief 创建中间的那个大萝卜
    */
    virtual void createCarrot();
    /*
    @brief 萝卜上方那个会动的叶子运动
    @param dt  //TODO
    */
    virtual void leafAction(float dt);

private:
    Node * _pCarrotAll = nullptr;
    const Size _VisibleSize = Director::getInstance()->getVisibleSize();
};

#endif // ! SPRITES_LAYER_H
