#pragma once
#ifndef SCENE_FACTORY_H
#define SCENE_FACTORY_H

#include "CommonDefine.h"
class SceneFactory
{
public:
    static Scene* createScene(const SceneType &rEnSceneType);
}

#endif