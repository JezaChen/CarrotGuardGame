//
// Created by jeza on 18-4-11.
//

#include "SettingScene.h"
#include "SettingMenuPanelLayer.h"

GameSettingScene::~GameSettingScene()
{
    CC_SAFE_RELEASE_NULL(_pPanelLayer);
}

bool GameSettingScene::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!Scene::init());

        _pPanelLayer = SettingMenuPanelLayer::create();
        _pPanelLayer->retain();

        bRet = true;
    } while (0);
    return bRet;
}

void GameSettingScene::onEnter()
{
    Scene::onEnter();
    addChild(_pPanelLayer);
}
