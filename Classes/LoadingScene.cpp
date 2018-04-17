#include "LoadingScene.h"
#include "SoundUtil.h"
#include "GameSceneII.h"


bool LoadingScene::init()
{
    bool bRet = false;
    do {
        CC_BREAK_IF(!Scene::init());

        //不能用createWithSpriteFrameName
        //因为没有加载到纹理当中
        auto aBg = Sprite::create(LOADINGSOURCE); //bug fixed

        aBg->setPosition(VisibleRectUtil::center());
        addChild(aBg);

        bRet = true;
    } while (0);
    return bRet;
}

void LoadingScene::onEnter()
{
    Scene::onEnter();
    SoundUtil::getInstance()->stopBackgroundSound(); //进入加载场景的时候，停止播放音乐
    NOTIFY->addObserver(this, callfuncO_selector(LoadingScene::loadSourceFinishedCallBack), "loadFinished", nullptr);

    _pGameScene = GameSceneII::create();
    _pGameScene->retain();
}

void LoadingScene::onExit()
{
    NOTIFY->removeAllObservers(this);
    CC_SAFE_RELEASE_NULL(_pGameScene);
    Scene::onExit();
}

void LoadingScene::loadSourceFinishedCallBack(Ref *pData)
{
    //渐变切换到游戏场景
    auto aTransScene = TransitionFade::create(0.2f, dynamic_cast<Scene*>(pData));
    Director::getInstance()->replaceScene(aTransScene);
}
