//
// Created by jeza on 18-4-11.
//

#include "AboutUsLayer.h"

bool AboutUsLayer::init()
{
    bool bRet = false;

    do
    {
        CC_BREAK_IF(!Layer::init());

        createBg();

        bRet = true;
    } while (0);

    return bRet;
}

void AboutUsLayer::createBg()
{
    auto aBg = Sprite::create("Themes/credits_bg.png");
    addChild(aBg);
}


