/**
* @brief
* @details
* @extends
* @see
* @authors ³Â½¨ÕÃ
* @date 20180315
* */
#pragma once
#ifndef WELCOME_SCENE_H
#define WELCOME_SCENE_H

#include "CommonDefine.h"

class WelcomeScene :public Scene
{
public:
    CREATE_FUNC(WelcomeScene);
    virtual ~WelcomeScene();
protected:
    virtual bool init();
    virtual void onEnter()override;
    virtual void showMenu();

private:
    Layer * _pSpritesLayer = nullptr;
    Layer *_pMenuLayer = nullptr;
};

#endif // !WELCOME_SCENE_H
