/** @Copyright   保卫萝卜
*   @author      陈建彰
*   @date        2018/3/2
*   @brief       声音工具类
*/
#pragma once
#ifndef SOUND_UTIL_H
#define SOUND_UTIL_H
#include "CommonDefine.h"
class SoundUtil : public Ref
{
public:
    //单例模式两个宏
    CREATE_INSTANCE_FUNCTION(SoundUtil);

    DESTROY_INSTANCE_FUNCTION();

    /**
    @brief 播放背景音乐
    @param bgSound 背景音乐路径
    */
    void playBackgroundSound(const std::string &bgSound);

    /**
    @brief 播放特效音乐
    @param efSound 特效音乐路径
    */
    void playEffectSound(const std::string &efSound);

    /**
    @brief 设置、获取背景音乐是否打开
    */
    bool getIsBackgroundSoundOpen() { return _bIsBackgroundSoundOpen; }
    void setIsBackgroundSoundOpen(const bool &_bIsOpen) { _bIsBackgroundSoundOpen = _bIsOpen; }

    /**
    @brief 设置、获取特效音乐是否打开
    */
    bool getIsEffectSoundOpen() { return _bIsEffectSoundOpen; }
    void setIsEffectSoundOpen(const bool& _bIsOpen) { _bIsEffectSoundOpen = _bIsOpen; }

    /**
    @brief 停止播放背景音乐
    */
    void stopBackgroundSound();

protected:
    bool init()
    {
        return true;
    }

protected:
    bool _bIsBackgroundSoundOpen;  //背景音乐是否打开
    bool _bIsEffectSoundOpen;  //特效音效是否打开
};
#endif //SOUND_UTIL_H