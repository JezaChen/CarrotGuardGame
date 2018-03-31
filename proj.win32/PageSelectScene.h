//
//  LevelSelectScene.h
//  newCardDefence
//
//  Created by ºÎãü±ø on 18-3-30.
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

	Layer *_pPageViewLayer = nullptr;

	Layer *_pMenuPanelLayer = nullptr;

	Layer *_pPageTurningLayer = nullptr;

};

#endif /* defined(__newCardDefence__LevelSelectScene__) */
