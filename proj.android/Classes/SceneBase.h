/**
 * @brief 多变场景的直接基类
 * @authors 何泓兵、陈建彰
 * @date 20180409
 * */
#pragma once
#ifndef SCENE_BASE_H
#define SCENE_BASE_H

#include "CommonDefine.h"

/**
 * @class SceneBase
 * @brief 多变场景的直接基类
 * @details 由于某些场景呈现出精灵多变但整体架构一致的画面时，比如游戏画面、不同场景的关卡选择，
 * 由于资源名是一样的，需要同步地根据当前场景的类别动态加载资源，以便精灵的正确加载。
 * */
class SceneBase : public Scene
{
protected:
    /**
     * @brief 资源管理者函数，用于动态加载资源
     * @param rSourceNameVec 资源清单
     * @param rBLoad 是否在之前已经加载成功了
     * */
	virtual void sourceManager(const std::vector<std::string> &rSourceNameVec, const bool &rBLoad);
};

#endif //SCENE_BASE_H