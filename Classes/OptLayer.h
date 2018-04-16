#pragma once

#include "CommonDefine.h"
#include "TowerOptBtn.h"


class OptLayer : public Layer
{
public:
    CREATE_FUNC(OptLayer);
    ~OptLayer() override {}

protected:
    bool init()override;

    void listenClick();

    
    TowerOptBtn* _pTowerOptBtn;
    bool _bKeyOptBtn;
    Sprite *_pForbiddenSprite;
};
