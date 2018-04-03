#include "SceneFactory.h"

Scene* SceneFactory::createScene(const SceneType &rEnSceneType)
{
    Scene *pScene = nullptr;
    switch(rEnSceneType)
    {
        case en_WelcomeScene:
            pScene = WelcomeScene::create();
            break;
        case en_GameHelpScene:
            pScene = HelpScene::create(); //TODO:这个还没有写
            break;
        case en_PageSelectScene:
            pScene = PageSelectScene::create();
            break;
        case en_LevelSelectScene:
            pScene = LevelSelectScene::create();
            break;
        case en_GameSettingScene:
            pScene = GameSettingScene::create();
            break;
    }
}