/**
 * @brief 帮助界面图层
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
    bool init() override;

    virtual void createHelpPageView();

    void createBottom();

    void createInitialBottomSprite();
private:
    Sprite *bottomSprite;
    int _iCurPageIndex = 0;
    PageView *_pHelpPageView = nullptr;
};

#endif //HELP_LAYER_H