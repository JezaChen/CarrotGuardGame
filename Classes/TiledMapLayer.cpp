//
// Created by jeza on 18-4-11.
//

#include "TiledMapLayer.h"
#include "SceneManager.h"
#include "MapUtil.h"

bool TiledMapLayer::init()
{
    //md
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!Layer::init());
        loadMap();
        bRet = true;
    } while (0);
    return bRet;
}

//加载地图资源
void TiledMapLayer::loadMap()
{
    //加载瓦片地图
    auto aCurLevelTiledMapFullPath =
            StringUtils::format(GAMESCENEMAP, SceneManager::getInstance()->getCurrentPageIndex() + 1,
                                SceneManager::getInstance()->getCurrentLevelIndex() + 1) + "BGPath.tmx";
    _pTiledMap = TMXTiledMap::create(aCurLevelTiledMapFullPath);

    //加载游戏背景
    auto aBg = Sprite::createWithSpriteFrameName("BG1.png");
    aBg->setPosition(VisibleRectUtil::center());
    addChild(aBg);

    //加载游戏地图的图片画面
    //之前的瓦片地图是肉眼看不到的
    auto aMapImage = Sprite::createWithSpriteFrameName("Path.png");
    aMapImage->setPosition(VisibleRectUtil::center());
    addChild(aMapImage);

    MapUtil::getInstance()->setAndAnalyzeCurrentLevelTiledMap(_pTiledMap); //记得要设置并分析该瓦片地图啊
}
