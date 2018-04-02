#include "SceneManager.h"

bool SceneManager::init()
{
    bool bRet = false;
    do
    {
        registerChangeSceneEvent(); //注册监听事件
        bRet = true;
    } while (0);
    return bRet;
}

void SceneManager::initWelcomeScene()
{
    currentScene = en_WelcomeScene;
    auto currScene = std::make_tuple(currentScene, 0);
    changeScene(currScene); //调用自己的函数创建欢迎界面
}

void SceneManager::unRegisterChangeSceneEvent()
{
    NOTIFICATION_CENTER->removeAllObservers(this);
}

void SceneManager::changeScene(const std::tuple<SceneType, int>& changingScene)
{
    Director::getInstance()->getScheduler()->setTimeScale(1);
    auto tSceneType = std::get<0>(changingScene);
    if(tSceneType == en_GameScene)
    {

    }
}
