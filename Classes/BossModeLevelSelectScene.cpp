#include "BossModeLevelSelectScene.h"
#include "BossModeLevelSelectLayer.h"

BossModeLevelSelectScene::~BossModeLevelSelectScene()
{
    CC_SAFE_RELEASE_NULL(_pBMLevelSelectLayer);
}


bool BossModeLevelSelectScene::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!Scene::init());

        //建立个界面图层
        _pBMLevelSelectLayer = BossModeLevelSelectLayer::create();
        _pBMLevelSelectLayer->retain();
        bRet = true;
    }
    while (0);

    return bRet;
}

void BossModeLevelSelectScene::onEnter()
{
    Scene::onEnter();
    addChild(_pBMLevelSelectLayer);
}
