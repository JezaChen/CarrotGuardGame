/**
 * @brief 炮塔帮助图层
 * @details 帮助场景中的炮塔帮助页面
 * @author 陈建彰
 * @date 20180410
 * */

#ifndef TOWERHELPLAYER_H
#define TOWERHELPLAYER_H

#include "CommonDefine.h"
#include "ui/CocosGUI.h"

using namespace ui;

class TowerHelpLayer : public Layer
{
public:
    CREATE_FUNC(TowerHelpLayer);

    ~TowerHelpLayer() override
    {}

protected:
    bool init() override;

    virtual void createTowerHelpPageView();

    virtual void createBottom();

    void createInitialBottomSprite();

private:
    PageView *_pTowerHelpPageView = nullptr;
    Sprite *bottomSprite;
    int _iCurPageIndex = 0;
};

#endif //TOWERHELPLAYER_H
