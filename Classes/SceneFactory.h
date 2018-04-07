#pragma once
#ifndef SCENE_FACTORY_H
#define SCENE_FACTORY_H

#include "CommonDefine.h"
/*
* @brief 场景工厂类
* @details 用于创造场景(Scene)
* @author 陈建彰
* @date 20180403
*/
class SceneFactory
{
public:
    /*
    * @brief 创建场景
    * @param rEnSceneTye 想要创建的场景类型
    * @return Scene* 返回创建的场景指针
    */
    static Scene* createScene(const SceneType &rEnSceneType);
};

#endif