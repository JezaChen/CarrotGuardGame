#include "SceneManager.h"
#include "CommonSource.h"
#include "CommonDefine.h"
#include "SceneFactory.h"
#include "SoundUtil.h"


SceneManager* SceneManager::_gInstance;
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
    auto aSceneType = std::get<0>(changingScene);
    if(aSceneType == en_GameScene)
    {
        _iCurPageIndex = std::get<1>(changingScene);
    }
    if(aSceneType == en_LevelSelectScene)
    {
        _iCurLevelIndex = std::get<1>(changingScene);
    }
    if(aSceneType != en_GameScene) //若不是切换到游戏界面
    {
        //播放背景音乐
        SoundUtil::getInstance()->playBackgroundSound(BACKGROUNDSOUND.c_str());
    }
    checkCurrentPageAndLevel(); //为什么要检查

    auto pScene = SceneFactory::createScene(aSceneType);

    Director* pDirector = Director::getInstance();
    auto pRunScene = pDirector->getRunningScene();
    pRunScene ? pDirector->replaceScene(pScene) : pDirector->runWithScene(pScene);
}

void SceneManager::checkCurrentPageAndLevel()
{
    //获取当前主题的关卡数
    auto aCurPageLevelCount = THEME_LEVELCOUNT_ARRAY[_iCurPageIndex];

    //若当前关卡索引已经等于当前主题的关卡数
    if(aCurPageLevelCount == _iCurLevelIndex)
    {
        _iCurPageIndex++; //页面加一
        _iCurLevelIndex = 0; //关卡数清零
    } 
}

void SceneManager::notifyChangeScene(Ref* pData)
{
    auto enSceneType = *(reinterpret_cast<std::tuple<SceneType, int> *>(pData));
    changeScene(enSceneType);
}

void SceneManager::registerChangeSceneEvent()
{
    //注册监听事件
    NOTIFY->addObserver(this, callfuncO_selector(SceneManager::notifyChangeScene), "changeScene", nullptr);
}

int SceneManager::getCurrentPageIndex()
{
    return _iCurPageIndex;
}

int SceneManager::getCurrentLevelIndex()
{
    return _iCurLevelIndex;
}

