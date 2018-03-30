#pragma once
#ifndef COMMON_DEFINE_H
#define COMMON_DEFINE_H

#include "cocos2d.h"
#include "CsvUtil.h"

using namespace cocos2d;

#define CREATE_INSTANCE_FUNCTION(__CLASS__)                  \
private:                                                     \
    static __CLASS__ *_gInstance;                            \
public:                                                      \
    static __CLASS__ *getInstance()                          \
    {                                                        \
        if(!_gInstance)                                      \
        {                                                    \
            _gInstance = new __CLASS__();                    \
            if(_gInstance && _gInstance->init())             \
            {                                                \
                _gInstance->autoRelease();                   \
                _gInstance->retain();                        \
            }                                                \
            else                                             \
            {                                                \
                CC_SAFE_DELETE(_gInstance);                  \
            }                                                \
        }                                                    \
        return _gInstance;                                   \
    }

#define DESTROY_INSTANCE_FUNCTION(__CLASS__)                 \
static void destroyInstance()                                \
{                                                            \
    CC_SAFE_RELEASE_NULL(_gInstance);                        \
}                                                            


#define NOTIFICATION_CENTER cocos2d::NotificationCenter::getInstance()

enum SceneType
{
    en_WelcomeScene,  // 欢迎场景
    en_GameSettingScene,  // 设置场景
    en_GameHelpScene,  // 帮助场景
    en_PageSelectScene,  // 页面选择场景
    en_LevelSelectScene,  // 关卡选择场景
    en_GameScene  // 游戏场景
};


#endif // !COMMON_DEFINE_H

