/**
* @brief 加载游戏场景
* @details 游戏进入前需要加载资源，此时需要呈现游戏场景
* @author 陈建彰
* @date 20180412
* */

#include"CommonDefine.h"

class GameSceneII;
//class GameScene;

class LoadingScene : public Scene
{
public:
    /**
    * @brief 创建宏
    * @details cocos2d-x自带宏
    */
    CREATE_FUNC(LoadingScene);
    
protected:
    /**
    * @brief 初始化函数
    */
    bool init()override;

    /**
    * @brief 场景进入的时候调用的函数
    */
    void onEnter()override;

    /**
    * @brief 场景退出的时候调用的函数
    */
    void onExit()override;

    /**
    * @brief GameScene的加载资源函数完成后，会回调该函数，以切换到游戏场景
    */
    virtual void loadSourceFinishedCallBack(Ref *pData);

protected:
    GameSceneII * _pGameScene = nullptr;
};
#pragma once
