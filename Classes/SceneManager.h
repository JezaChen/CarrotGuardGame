#pragma once
#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "CommonDefine.h"

class SceneManager : public Node
{
public:
    CREATE_INSTANCE_FUNCTION(SceneManager);
    DESTROY_INSTANCE_FUNCTION();
    virtual void initWelcomeScene();
    virtual int getCurrentPageIndex();
    virtual int getCurrentLevelIndex();
protected:
    virtual void changeScene(const std::tuple<SceneType, int> &ChangingScene);
    virtual void notifyChangeScene(Ref* pData);
    virtual void registerChangeSceneEvent();
    virtual void unRegisterChangeSceneEvent();
    virtual void checkCurrentPageAndLevel();
    virtual bool init();
    
    SceneType currentScene = en_WelcomeScene;

private:
    int _iCurPageIndex = 0;
    int _iCUrLevelIndex = 0;

    SceneManager() {}
    virtual ~SceneManager() {}
    SceneManager(const SceneManager&) = delete;
    SceneManager& operator=(const SceneManager&) = delete;
};

#endif //SCENE_MANAGER_H