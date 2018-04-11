//
// Created by jeza on 18-4-11.
//

#include "HelpScene.h"
#include "HelpMenuPanelLayer.h"

HelpScene::~HelpScene()
{
    CC_SAFE_RELEASE_NULL(_pMenuPanelLayer);
}

bool HelpScene::init()
{
    bool bRet = false;

    do
    {
        CC_BREAK_IF(!Scene::init());

        _pMenuPanelLayer = HelpMenuPanelLayer::create();
        _pMenuPanelLayer->retain();

        bRet = true;
    } while (0);

    return bRet;
}

void HelpScene::onEnter()
{
    Scene::onEnter();
    addChild(_pMenuPanelLayer);
}