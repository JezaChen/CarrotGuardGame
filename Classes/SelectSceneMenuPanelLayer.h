/**
 * @brief 主题选择场景中的菜单项
 * @details 有返回、主页、左、右
 * @author 陈建彰
 * @date 20180409
 * */

#ifndef MYGAME_SELECTSCENEMENUPANELLAYER_H
#define MYGAME_SELECTSCENEMENUPANELLAYER_H

#include "CommonDefine.h"
class PageViewLayer;

/**
 * @class MenuPanelLayer
 * @brief 主题选择场景菜单
 * @author 陈建彰
 * */
class MenuPanelLayer : public Layer
{
public:
    CREATE_FUNC(MenuPanelLayer);

    /**
     * @brief 用于设置页面切换逻辑函数
     * @param rfFuncPageTurn 将要设置页面切换的逻辑函数
     * */
    virtual void setPageTurnFunction(const std::function<void (const bool&)>&rfFuncPageTurn);

protected:
    /**
     * @brief 初始化函数
     * */
    virtual bool init();

    /**
     * @brief 创建函数
     * */
    virtual void createItemPanel();

private:
    std::function<void (const bool&)> _funcPageTurn;
};

#endif //MYGAME_SELECTSCENEMENUPANELLAYER_H
