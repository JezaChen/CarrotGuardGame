#include "SceneManager.h"
#include "CommonSource"
#include "CommonDefine"

bool SceneManager::init()
{
    bool bRet = false;
    do
    {
        registerChangeSceneEvent(); 
        bRet = true;
    } while (0);
    return bRet;
}

void SceneManager::initWelcomeScene()
{
    currentScene = en_WelcomeScene;
    auto currScene = std::make_tuple(currentScene, 0);
    changeScene(currScene); 
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
        _iCurPageIndex = std::get<1>(changingScene);
    }
    if(tSceneType == en_LevelSelectScene)
    {
        _iCUrLevelIndex = std::get<1>(changingScene);
    }
    if(tSceneType != en_GameScene) //若不是切换到游戏界面
    {
        //播放背景音乐
        SoundUtil::getInstance()->playBackgroundSound(BACKGROUNDSOUND.c_str());
    }
    checkCurrentPageAndLevel(); //为什么要检查

    auto pScene = SceneFactor

    Director pDirector = Director::getInstance();
    auto pRunScene = pDirector->getRunningScene(;
    pRunScene ? pDirector->replaceScene(pScene)
    checkCurrentPageAndLevel();


}
