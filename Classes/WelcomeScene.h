/**
* @brief
* @details
* @extends
* @see
* @authors 陈建彰
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

	/**
	* @brief 视频播放完成的回调函数
	*/
	void videoPlayOverCallback();
	/**
	* @brief 视频显示函数
	*/
	void showVideo();
	/**
	* @brief 视频播放状态，只有在android和ios平台有效
	*/
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)  
	void videoEventCallback(Ref* sender, cocos2d::experimental::ui::VideoPlayer::EventType eventType);
#endif 
private:
    Layer * _pSpritesLayer = nullptr;
    Layer *_pMenuLayer = nullptr;
};

#endif // !WELCOME_SCENE_H
