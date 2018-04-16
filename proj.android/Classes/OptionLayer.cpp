//
// Created by jeza on 18-4-11.
//
#include "OptionLayer.h"
#include "SoundUtil.h"


bool OptionLayer::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!Layer::init());
        loadSource();
        bRet = true;
    } while (0);

    return bRet;
}

void OptionLayer::loadSource()
{
    //首先加在设置图层的背景
    //因为每一个图层的背景都不太相同
    //所以需要针对每一个图层进行对应的背景渲染
    auto aBg = Sprite::createWithSpriteFrameName("setting_bg.png");
    addChild(aBg);

    auto aText = Sprite::createWithSpriteFrameName("setting_bg_CN.png");
    addChild(aText);

    //获取当前的设置信息
    auto aCurSoundUtil = SoundUtil::getInstance();
    //获取当前背景音乐的状态
    bool bIsBgSoundOpen = aCurSoundUtil->getIsBackgroundSoundOpen();
    //获取当前音效的状态
    bool bIsEfSoundOpen = aCurSoundUtil->getIsEffectSoundOpen();

    //创建一个音效开关按钮
    auto aEfSoundBtnOn = MenuItemSprite::create(Sprite::createWithSpriteFrameName("soundfx_on_CN.png"), nullptr);
    auto aEfSoundBtnOff = MenuItemSprite::create(Sprite::createWithSpriteFrameName("soundfx_off_CN.png"), nullptr);
    auto aEfSoundBtnToggle = MenuItemToggle::createWithCallback([aCurSoundUtil](Ref *pSender)
                                                                {
                                                                    //来回切换
                                                                    aCurSoundUtil->setIsEffectSoundOpen(
                                                                            !aCurSoundUtil->getIsEffectSoundOpen());
                                                                },
            //TODO 很有意思
                                                                bIsEfSoundOpen ? aEfSoundBtnOn : aEfSoundBtnOff,
                                                                bIsEfSoundOpen ? aEfSoundBtnOff : aEfSoundBtnOn,
                                                                nullptr); //nullptr一定要加上

    aEfSoundBtnToggle->setPosition(-100, 83);

    //创建一个背景音乐开关按钮
    auto aBgSoundBtnOn = MenuItemSprite::create(Sprite::createWithSpriteFrameName("bgmusic_on_CN.png"), nullptr);
    auto aBgSoundBtnOff = MenuItemSprite::create(Sprite::createWithSpriteFrameName("bgmusic_off_CN.png"), nullptr);
    auto aBgSoundBtnToggle = MenuItemToggle::createWithCallback([aCurSoundUtil](Ref *pSender)
                                                                {
                                                                    //来回切换
                                                                    aCurSoundUtil->setIsBackgroundSoundOpen(
                                                                            !aCurSoundUtil->getIsBackgroundSoundOpen());
                                                                },
            //TODO 很有意思
                                                                bIsBgSoundOpen ? aBgSoundBtnOn : aBgSoundBtnOff,
                                                                bIsBgSoundOpen ? aBgSoundBtnOff : aBgSoundBtnOn,
                                                                nullptr);
                                                                
    aBgSoundBtnToggle->setPosition(100, 83);
    auto aMenu = Menu::create(aEfSoundBtnToggle, aBgSoundBtnToggle, nullptr);
    aMenu->setPosition(0, 0); //潜在bug fixed
    addChild(aMenu);
}
