/**
 * @brief 选择主题页面
 * @authors 何泓兵
 * @co_author 陈建彰
 * */
#pragma once
#ifndef PAGESELECT_SCENE_H
#define PAGESELECT_SCENE_H

#include "CommonDefine.h"


class PageSelectScene : public Scene
{
public:

	CREATE_FUNC(PageSelectScene);

	~PageSelectScene()override;

protected:

	/**
	 * @brief 初始化函数
	 * */
	bool init() override;

	/**
	 * @brief
	 * */
	void onEnter() override;

private:

	Layer *_pPageViewLayer = nullptr; //主题查看图层，也就是中间那块

	Layer *_pMenuPanelLayer = nullptr; //菜单面板图层，也就是顶部那块

	Layer *_pPageTurningLayer = nullptr; //页面转换图层；

};

#endif //PAGESELECT_SCENE_H
