/**
 * @brief 帮助场景菜单显示及控制
 * @details 显示帮助场景上方的各个切换用的按钮，并且负责完成图层切换的工作
 * @author 陈建彰
 * @date 20180410
 * */

#ifndef HELPMENUPANELLAYER_H
#define HELPMENUPANELLAYER_H

#include "CommonDefine.h"

class HelpMenuPanelLayer : public Layer
{
public:
    CREATE_FUNC(HelpMenuPanelLayer);
protected:
    bool init() override;

    virtual void createMenuPanel();

    virtual void loadBackground();

private:
    //三个开关菜单项
    MenuItemToggle *_pHelpBtn;
    MenuItemToggle *_pMonsterHelpBtn;
    MenuItemToggle *_pTowerHelpBtn;

    //多图层管理类
    //用于方便切换图层
    LayerMultiplex *_pLayers = nullptr;
};

#endif //HELPMENUPANELLAYER_H
