#include "SceneFactory.h"
#include "WelcomeScene.h"
#include "ThemeSelectScene.h"
#include "LevelSelectScene.h"

Scene* SceneFactory::createScene(const SceneType &rEnSceneType)
{
    Scene *pScene = nullptr;
    switch(rEnSceneType)
    {
        case en_WelcomeScene:
            pScene = WelcomeScene::create();
            break;
        case en_GameHelpScene:
            //pScene = HelpScene::create(); //TODO:这个还没有写
            break;
        case en_ThemeSelectScene:
            pScene = PageSelectScene::create();
            break;
        case en_LevelSelectScene:
            pScene = LevelSelectScene::create();
            break;
        case en_GameSettingScene:
           // pScene = GameSettingScene::create();
            break;
        case en_GameScene:
            //值得注意的是，切换的是加载场景
            //pScene = LoadingScene::create(); //TODO
            break;
        default:
            break;
    }
    return pScene;
}