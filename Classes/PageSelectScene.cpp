//
// Created by jeza on 18-4-9.
//

#include "CommonDefine.h"
#include "PageSelectScene.h"
#include "PageViewLayer.h"

PageSelectScene::~PageSelectScene()
{
    CC_SAFE_RELEASE_NULL(_pPageViewLayer);
    CC_SAFE_RELEASE_NULL(_pMenuPanelLayer);
}

bool PageSelectScene::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!Scene::init());

        _pPageViewLayer = PageViewLayer::create();
        _pPageViewLayer->retain();

        //TODO 还有菜单Layer

        bRet = true;
    }while (0);
    return bRet;
}

void PageSelectScene::onEnter()
{
    Scene::onEnter();
    addChild(_pPageViewLayer);
    //TODO 还有菜单Layer
}




