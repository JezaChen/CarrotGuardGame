/**
 * @brief 设置场景额菜单图层
 * @details 负责菜单按钮的显示以及完成一些图层切换的操作
 * @author 陈建彰
 * @date 20180411
 * */

#ifndef SETTINGMENUPANELLAYER_H
#define SETTINGMENUPANELLAYER_H

#include "CommonDefine.h"

class SettingMenuPanelLayer : public Layer
{
public:
    CREATE_FUNC(SettingMenuPanelLayer);

    ~SettingMenuPanelLayer() override;

protected:
    bool init() override;

    /**
     * @brief 创建菜单项
     * */
    virtual void createMenuPanel();

    /**
     * @brief 创建多图层管理
     * */
    virtual void createMultiplexLayer();

private:
    LayerMultiplex *_pLayerMultiplex = nullptr;
};

#endif //SETTINGMENUPANELLAYER_H
