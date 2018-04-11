/**
 * @brief 帮助界面图层
 * @details 也就是帮助场景的第一个图层
 * @author 陈建彰
 * @date 20180410
 * */


#pragma once
#ifndef HELP_LAYER_H
#define HELP_LAYER_H

#include "CommonDefine.h"
#include "ui/CocosGUI.h"

using namespace ui;

class HelpLayer : public Layer
{
public:
    CREATE_FUNC(HelpLayer);

    ~HelpLayer() override
    {}

protected:
    /**
     * @brief 初始化函数
     * */
    bool init() override;

    /**
     * @brief 创建滚动页面的函数
     * */
    virtual void createHelpPageView();

    /**
     * @brief 创建底部的函数
     * @details 就是下方那个页码的生成，但并不负责那个动态页码的生成，动态页码的生成由回调函数进行操纵
     * */
    void createBottom();

    /**
     * @brief 刚开始创造场景的时候调用该函数进行底部页面的快速初始化
     * @details 由于动态页码显示的有点慢，所以写出这个函数出来，用于快速显示进去那个图层的对应页码
     * */
    void createInitialBottomSprite();
private:
    Sprite *bottomSprite;
    int _iCurPageIndex = 0; //当前页码
    PageView *_pHelpPageView = nullptr; //滚动页面
};

#endif //HELP_LAYER_H