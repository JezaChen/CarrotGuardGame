#pragma once
#ifndef MENUS_LAYER_H

#define MENUS_LAYER_H

#include "CommonDefine.h"

/**
 * @class MenusLayer
 * @brief 欢迎界面上的菜单图层
 * @author 陈建彰
 * */
class MenusLayer : public Layer
{
public:
    CREATE_FUNC(MenusLayer);
    ~MenusLayer()override;

protected:
    /**
     * @brief 初始化函数
     * @return true 如果初始化成功
     * @return false 如果初始化失败
    */
    virtual bool init();

    /**
    @brief 创建目录按钮
    */
    virtual void createMenuItems();

    Menu *_pMenu = nullptr;

    MenuItemSprite *_pAdCloseButton = nullptr;
};

#endif // MENUS_LAYER_H
