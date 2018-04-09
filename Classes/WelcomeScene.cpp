#include "WelcomeScene.h"
#include "SpritesLayer.h"
#include "MenusLayer.h"
#include "LoadingSourceLayer.h"
#include "Config.h"

WelcomeScene::~WelcomeScene()
{
    CC_SAFE_RELEASE_NULL(_pMenuLayer); //安全释放MenuLayer
    CC_SAFE_RELEASE_NULL(_pSpritesLayer); //安全释放SpriteLayer
}

bool WelcomeScene::init()
{
    bool bRet = false;
    do {
        CC_BREAK_IF(!Scene::init());
        //创建欢迎界面精灵们的图层
        _pSpritesLayer = SpritesLayer::create();
        _pSpritesLayer->retain();

        //创建欢迎界面菜单的图层
        _pMenuLayer = MenusLayer::create();
        _pMenuLayer->retain();

        bRet = true;
    } while (0);

    return bRet;
}

void WelcomeScene::onEnter()
{
    Scene::onEnter();
    addChild(_pSpritesLayer); //无论加载是否完成，那几个怪物萝卜都显示出来
    if (!Config::getInstance()->getIsLoadSource()) //如果加载资源完成后
    {
        auto pLoadingLayer = LoadingSourceLayer::create();
        pLoadingLayer->setFuncShowMenuPanel(CC_CALLBACK_0(WelcomeScene::showMenu, this)); //传递一个回调函数，用于加载资源完毕后回调showMenu
        pLoadingLayer->setName("loadingLayer");
        addChild(pLoadingLayer);
    }
    else
    {
        addChild(_pMenuLayer);
    }
}

void WelcomeScene::showMenu()
{
    getChildByName("loadingLayer")->removeFromParent(); //去除加载进度条
    addChild(_pMenuLayer);
    Config::getInstance()->setIsLoadSource(true);
}
