//
// Created by jeza on 18-4-11.
//

#include "DataStatisticsLayer.h"

//TODO 还没有加上实质功能
bool DataStatLayer::init()
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

void DataStatLayer::createBg()
{
    auto aBg = Sprite::createWithSpriteFrameName("statistics_bg.png");
    addChild(aBg);

    auto aText = Sprite::createWithSpriteFrameName("statistics_bg_CN.png");
    addChild(aText);

}
