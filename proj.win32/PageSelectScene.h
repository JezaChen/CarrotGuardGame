//
//  LevelSelectScene.h
//  newCardDefence
//
//  Created by 何泓兵 on 18-3-30.
//
//
#pragma once
#ifndef __newCardDefence__PageSelectScene__
#define __newCardDefence__PageSelectScene__

#include "PublicDefine.h"


class PageSelectScene : public Scene
{
public:

	CREATE_FUNC(PageSelectScene);

	virtual ~PageSelectScene();

protected:

	virtual bool init();

	virtual void onEnter()override;

private:

	Layer *_pPageViewLayer = nullptr;//页面查看图层；

	Layer *_pMenuPanelLayer = nullptr;//菜单面板图层；

	Layer *_pPageTurningLayer = nullptr;//页面转换图层；

};

#endif /* defined(__newCardDefence__LevelSelectScene__) */
