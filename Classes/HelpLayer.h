#pragma once
#ifndef HELP_LAYER_H
#define HELP_LAYER_H

#include "CommonDefine.h"

class HelpLayer : public Layer
{
public:
    CREATE_FUNC(HelpLayer);
    virtual ~HelpLayer();

protected:
    bool init()override;
    virtual void HelpPageView();

private:
    Sprite * bottomSprite;
    int _iCurLevelIndex = 0;
    
};
#endif //HELP_LAYER_H