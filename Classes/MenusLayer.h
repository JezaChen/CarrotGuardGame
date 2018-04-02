#pragma once
#ifndef MENUS_LAYER_H

#define MENUS_LAYER_H

#include "CommonDefine.h"

class MenusLayer : public Layer
{
public:
    CREATE_FUNC(MenusLayer);
protected:
    /*
    @brief 初始化函数
    */
    virtual bool init();

    /*
    @brief 创建目录按钮
    */
    virtual void createMenuItems();
};

#endif // MENUS_LAYER_H
