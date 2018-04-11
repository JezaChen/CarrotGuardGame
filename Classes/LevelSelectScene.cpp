//
// Created by jeza on 18-4-9.
//

#include "LevelSelectScene.h"
#include "LevelSelectLayer.h"
#include "SceneManager.h"

LevelSelectScene::~LevelSelectScene()
{
    CC_SAFE_RELEASE_NULL(_pLevelSelectLayer);
    //动态删除当前主题的资源
    sourceManager(std::vector<std::string>{THEMESSOURCE[_iThemeIndex]}, false);
}

bool LevelSelectScene::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!Scene::init());
        //动态获取当前主题的资源
        _iThemeIndex = SceneManager::getInstance()->getCurrentPageIndex();
        sourceManager(std::vector<std::string>{THEMESSOURCE[_iThemeIndex]}, true);

        _pLevelSelectLayer = LevelSelectLayer::create();
        _pLevelSelectLayer->retain();
        bRet = true;
    } while (0);

    return bRet;
}

void LevelSelectScene::onEnter()
{
    Scene::onEnter();
    addChild(_pLevelSelectLayer); //加入该layer
}

