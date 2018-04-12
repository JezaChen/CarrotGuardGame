//
// Created by jeza on 18-4-11.
//

#include "GameSceneII.h"
#include "EntityLayerBase.h"
#include "SceneManager.h"
#include "TiledMapLayer.h"
#include "LevelConfigUtil.h"

GameSceneII::~GameSceneII()
{
    CC_SAFE_RELEASE_NULL(_pBarriersLayer);
    CC_SAFE_RELEASE_NULL(_pBulletsLayer);
    //CC_SAFE_RELEASE_NULL(_pCarrot);
    CC_SAFE_RELEASE_NULL(_pMonsterLayer);
    CC_SAFE_RELEASE_NULL(_pOptLayer);
    CC_SAFE_RELEASE_NULL(_pScoreAndControllerLayer);
    CC_SAFE_RELEASE_NULL(_pTiledMapLayer);
    CC_SAFE_RELEASE_NULL(_pTowersLayer);
    CC_SAFE_DELETE(_pSourceVec);
}

bool GameSceneII::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!Scene::init());

        _pSourceVec = new std::vector<std::string>;
        this->setName("GameScene");
        preLoadSource();

        bRet = true;

    } while (0);
    return bRet;
}

void GameSceneII::onEnter()
{
    Scene::onEnter();
    addLayers();
}

void GameSceneII::onExit()
{

}

//TODO 好像不太行的样子
void GameSceneII::preLoadSource()
{
    int iCurThemeIndex = SceneManager::getInstance()->getCurrentPageIndex() + 1;
    int iCurLevelIndex = SceneManager::getInstance()->getCurrentLevelIndex() + 1;

    LevelConfigUtil::getInstance()->loadLevelConfig();
    //现在开始加载资源
    //把对应关卡资源的完全路径放在一个向量中
    //然后对应向量每个元素进行异步加载
    _pSourceVec->push_back(StringUtils::format(GAMESCENEBG1, iCurThemeIndex));
    //加载对应关卡游戏界面的背景
    _pSourceVec->push_back(StringUtils::format(GAMESCENEMAP, iCurThemeIndex, iCurLevelIndex) + "BG-hd");
    //加载障碍物资源
    _pSourceVec->push_back(StringUtils::format(GAMESCENEBARRIER, iCurThemeIndex));
    //加载小怪兽资源
    _pSourceVec->push_back(StringUtils::format(GAMESCENEMONSTER1, iCurThemeIndex));
    //加载大怪兽资源
    _pSourceVec->push_back(StringUtils::format(GAMESCENEMONSTER2, iCurThemeIndex));

    //对向量的每一个资源路径，进行异步加载
    for (auto &iterSourcePath : *_pSourceVec)
    {
        Director::getInstance()->getTextureCache()->addImageAsync(iterSourcePath + PHOTOPOSTFIX,
                                                                  [&](Texture2D *pTexture)
                                                                  {
                                                                      _iSourceCount++;
                                                                      SpriteFrameCache::getInstance()->addSpriteFramesWithFile(
                                                                              iterSourcePath + PLISTPOSTFIX, pTexture);
                                                                      if (_iSourceCount == _pSourceVec->size())
                                                                      {
                                                                          createLayers();
                                                                          NOTIFICATION_CENTER->postNotification(
                                                                                  "loadFinished",
                                                                                  static_cast<Ref *>(this));
                                                                      }
                                                                  });
    }
}

void GameSceneII::unLoadSource()
{
    sourceManager(*_pSourceVec, false);
}

void GameSceneII::createLayers()
{
    //TODO 目前只支持加载地图
    _pTiledMapLayer = TiledMapLayer::create();
    _pTiledMapLayer->retain();
}

void GameSceneII::addLayers()
{
    //TODO 目前只支持加入地图图层
    addChild(_pTiledMapLayer);
}
