#include "SoundUtil.h"
#include "SimpleAudioEngine.h"

SoundUtil* SoundUtil::_gInstance;
void SoundUtil::playBackgroundSound(const std::string & bgSound)
{
    //TODO 先注释掉
    //if (!_bIsBackgroundSoundOpen)
        //return; //如果背景音乐开关没有打开，不播放

    //调用SimpleAudioEngine播放音乐，设置为循环播放
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(bgSound.c_str(), true);
}

void SoundUtil::playEffectSound(const std::string &efSound)
{
    if (!_bIsEffectSoundOpen)
        return; //如果音效开关没有打开，不播放

    //调用SimpleAudioEngine播放音乐，不循环播放
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(efSound.c_str());
}

void SoundUtil::stopBackgroundSound()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

