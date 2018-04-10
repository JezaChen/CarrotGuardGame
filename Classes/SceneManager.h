#pragma once
#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "CommonDefine.h"

/*
* @class SceneManage 
* @brief 场景控制器，用于切换场景等
* @author 陈建彰
* @date 20180403
*/
class SceneManager : public Node
{
public:
    /**
    * @brief cocos2d宏定义函数，用于创建和销毁实例
    */
    CREATE_INSTANCE_FUNCTION(SceneManager);
    DESTROY_INSTANCE_FUNCTION();

    /**
    * @brief 用于初始化欢迎界面
    */
    virtual void initWelcomeScene();

    /**
    * @brief 获取当前页面和关卡Index
    * @ps 还是有点不太懂有什么用
    */
    virtual int getCurrentPageIndex();
    virtual int getCurrentLevelIndex();
protected:

    /**
    * @brief 切换场景
    * @details 提供切换场景功能的实质函数
    * @param changingScene 一个元组，第一个元素是待切换场景的类型，第二个元素是附带参数
    */
    virtual void changeScene(const std::tuple<SceneType, int> &ChangingScene);

    /**
    * @brief 通知切换场景
    * @param Ref* 一个Ref指针，其实传进去的是想要切换的情景
    * @details 为什么要写这个函数，因为cocos2d的通知机制需要一个执行函数，以便执行某个通知对应的操作；
    *          而该执行函数需要传一个Ref参数，所以想要发出一个有关切换场景的通知的时候，我将该参数类型
    *          和附带参数的元组转换成一个Ref指针即可
    */
    virtual void notifyChangeScene(Ref* pData);

    /**
    * @brief 注册切换场景的监听事件
    */
    virtual void registerChangeSceneEvent();

    /**
    * @brief 注销切换场景的监听事件
    */
    virtual void unRegisterChangeSceneEvent();

    /**
    * @brief 检查页面和关卡之间的关系是否合法???
    */
    virtual void checkCurrentPageAndLevel();

    /**
    * @brief 初始化函数
    */
    virtual bool init();
    
    SceneType currentScene = en_WelcomeScene;

private:
    int _iCurPageIndex = 0;
    int _iCurLevelIndex = 0;

    SceneManager() {}
    virtual ~SceneManager() {}
    SceneManager(const SceneManager&) = delete; //不允许复制构造
    SceneManager& operator=(const SceneManager&) = delete; //不允许赋值
};

#endif //SCENE_MANAGER_H