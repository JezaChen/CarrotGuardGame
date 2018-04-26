/**
 * @brief 游戏关卡页面(主题)选择画面，包括背景，但这个并没有包含菜单（包含左右选择）
 * @author 陈建彰
 * @date 20180408
 * @version 1.1
 * */
#pragma once
#ifndef PAGEVIEWLAYER_H
#define PAGEVIEWLAYER_H

#include "CommonDefine.h"
#include "ui/UIPageView.h"

using namespace ui;

/**
 * @class PageViewLayer
 * @brief 游戏主题选择界面
 * @details 也就是中间那块
 * */
class PageViewLayer : public Layer
{
public:
    CREATE_FUNC(PageViewLayer);
    /**
     * @brief 析构函数
     * */
    virtual ~PageViewLayer();

    /**
     * @brief 页面切换
     * @param rbLeft 是否向左切换
     * */
    virtual void pageTurn(const bool &rbLeft);

protected:
    /**
     * @brief 初始化函数
     * */
    virtual bool init();

    /**
     * @brief 用于更新当前主题页面的活动圆点
     * @details 当某个主题页面被显示出来，其对应的圆点会由灰色变为白色，呈高亮状态
     * @param riIndex 当前主题页面的索引号
     * */
    virtual void setActivePagePoint(const int &riIndex);

    /**
     * @brief 创建并显示ThemePageView
     * */
    virtual void createThemePageView();

    /**
     * @brief 创建并显示下方的小圆点
     * */
    virtual void createThemePoints();

    /**
     * @brief 显示背景
     * */
    virtual void loadBackground();

    /**
     * @breif 加载资源
     * @since 1.1
     * @details 为了能够正常显示每个主题的通关数，要改进
     */
    virtual void loadData();

private:
    PageView *_pPageView = nullptr;
    int _iPageIndex = 0; //当前页面索引
    Vector<MenuItemSprite*> *_pPagePointsVec = nullptr; //存储小圆点的向量
    std::vector<int>* _pLevelsPastEachTheme = nullptr; //每个主题的通关数
};

#endif //PAGEVIEWLAYER_H
