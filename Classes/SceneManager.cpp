#include "SceneManager.h"
#include "CommonSource.h"
#include "CommonDefine.h"
#include "SceneFactory.h"
#include "SoundUtil.h"
#include "GameManager.h"


SceneManager* SceneManager::_gInstance;

bool SceneManager::init()
{
    bool bRet = false;
    do
    {
        registerChangeSceneEvent();
        bRet = true;
    }
    while (0);
    return bRet;
}

void SceneManager::initWelcomeScene()
{
    currentScene = en_WelcomeScene;
    auto currScene = std::make_tuple(currentScene, 0);
    changeScene(currScene);
    //播放背景音乐
    SoundUtil::getInstance()->playBackgroundSound(BACKGROUNDSOUND.c_str());
}

void SceneManager::unRegisterChangeSceneEvent()
{
    NOTIFICATION_CENTER->removeAllObservers(this);
}

void SceneManager::changeScene(const std::tuple<SceneType, int>& changingScene)
{
    Director::getInstance()->getScheduler()->setTimeScale(1);
    auto aSceneType = std::get<0>(changingScene);
    if (aSceneType == en_GameScene)
    {
        _iCurLevelIndex = std::get<1>(changingScene); //bug fixed
    }
    else if (aSceneType == en_LevelSelectScene)
    {
        _iCurPageIndex = std::get<1>(changingScene); //fixed
    }
    if (aSceneType != en_GameScene) //若不是切换到游戏界面
    {
        //播放背景音乐
        SoundUtil::getInstance()->playBackgroundSound(BACKGROUNDSOUND.c_str());
    }
    checkCurrentPageAndLevel(); //为什么要检查

    if (_iCurLevelIndex >= 12) //根据关卡数判断
        GameManager::getInstance()->setCurrGameType(en_BossMode); //设置GameManager的游戏模式为BOSS模式
    else
        GameManager::getInstance()->setCurrGameType(en_Adventure); //设置GameManager的游戏模式为冒险模式

        auto pScene = SceneFactory::createScene(aSceneType);

    Director* pDirector = Director::getInstance();
    auto pRunScene = pDirector->getRunningScene();
    pRunScene ? pDirector->replaceScene(pScene) : pDirector->runWithScene(pScene);
}

void SceneManager::checkCurrentPageAndLevel()
{
    //todo 暂时注释一下
    /*
     *
    //获取当前主题的关卡数
    auto aCurPageLevelCount = THEME_LEVELCOUNT_ARRAY[_iCurPageIndex];

    //若当前关卡索引已经等于当前主题的关卡数
    if (aCurPageLevelCount == _iCurLevelIndex)
    {
        _iCurPageIndex++; //页面加一
        _iCurLevelIndex = 0; //关卡数清零
    }
    */
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

void SceneManager::setCurrentPageIndex(const int& _iCurPageIndex)
{
    this->_iCurPageIndex = _iCurPageIndex;
}