//
//  BarrierBase.cpp
//  CarrotFantasy
//
//  Created by 陈建彰 on 18-4-22.
//
//  
#include "AdvertisementLayer.h"
#include "SoundUtil.h"

AdvertisementLayer::~AdvertisementLayer()
{
    SoundUtil::getInstance()->playBackgroundSound(BACKGROUNDSOUND);
}

bool AdvertisementLayer::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!Layer::init());

        createBg();
        createAdMusic();
        changeAdImg();

        bRet = true;
    }
    while (0);
    return bRet;
}

void AdvertisementLayer::createBg()
{
    auto contentSize = Director::getInstance()->getVisibleSize();
    auto aBg = Sprite::createWithSpriteFrameName("themepackad_bg.png"); //todo 到时候要动态加载
    aBg->setPosition(contentSize.width / 2, contentSize.height / 2);
    aBg->setScaleY(0.70);
    addChild(aBg);
}

void AdvertisementLayer::changeAdImg()
{
    auto action = RepeatForever::create(Sequence::create(CallFunc::create(CC_CALLBACK_0(AdvertisementLayer::createAd1, this)), 
        DelayTime::create(12), CallFunc::create(CC_CALLBACK_0(AdvertisementLayer::createAd2, this)), 
        DelayTime::create(3), CallFunc::create(CC_CALLBACK_0(AdvertisementLayer::createAd3, this)), 
        DelayTime::create(15), CallFunc::create(CC_CALLBACK_0(AdvertisementLayer::createAd4, this)), 
        DelayTime::create(14), CallFunc::create(CC_CALLBACK_0(AdvertisementLayer::createAd5, this)), 
        DelayTime::create(13), CallFunc::create(CC_CALLBACK_0(AdvertisementLayer::createAd6, this)), 
        DelayTime::create(13), CallFunc::create(CC_CALLBACK_0(AdvertisementLayer::createAd7, this)), 
        DelayTime::create(48), CallFunc::create(CC_CALLBACK_0(AdvertisementLayer::createAd8, this)),
        DelayTime::create(23),
        nullptr));

    runAction(action);
}

void AdvertisementLayer::createAdMusic()
{
    SoundUtil::getInstance()->stopBackgroundSound();
    SoundUtil::getInstance()->playEffectSound("Music/TanWanLanYue/0.mp3");
}

void AdvertisementLayer::createAd1()
{
    removeChildByName("Ad8");
    createAdMusic();

    auto adImg = Sprite::create("Themes/TanWanLanYue/1.png");
    adImg->setPosition(480, 330);
    adImg->setScale(604.0 / adImg->getContentSize().width);
    adImg->setName("Ad1");
    addChild(adImg);
}

void AdvertisementLayer::createAd2()
{
    removeChildByName("Ad1");

    auto adImg = Sprite::create("Themes/TanWanLanYue/2.png");
    adImg->setPosition(480, 330);
    adImg->setScale(604.0 / adImg->getContentSize().width);
    adImg->setName("Ad2");
    addChild(adImg);
}

void AdvertisementLayer::createAd3()
{
    removeChildByName("Ad2");

    auto adImg = Sprite::create("Themes/TanWanLanYue/3.png");
    adImg->setPosition(480, 330);
    adImg->setScale(604.0 / adImg->getContentSize().width);
    adImg->setName("Ad3");
    addChild(adImg);
}

void AdvertisementLayer::createAd4()
{
    removeChildByName("Ad3");

    auto adImg = Sprite::create("Themes/TanWanLanYue/4.png");
    adImg->setPosition(480, 330);
    adImg->setScale(604.0 / adImg->getContentSize().width);
    adImg->setName("Ad4");
    addChild(adImg);
}

void AdvertisementLayer::createAd5()
{
    removeChildByName("Ad4");

    auto adImg = Sprite::create("Themes/TanWanLanYue/5.png");
    adImg->setPosition(480, 330);
    adImg->setScale(604.0 / adImg->getContentSize().width);
    adImg->setName("Ad5");
    addChild(adImg);
}

void AdvertisementLayer::createAd6()
{
    removeChildByName("Ad5");

    auto adImg = Sprite::create("Themes/TanWanLanYue/6.png");
    adImg->setPosition(480, 330);
    adImg->setScale(604.0 / adImg->getContentSize().width);
    adImg->setName("Ad6");
    addChild(adImg);
}

void AdvertisementLayer::createAd7()
{
    removeChildByName("Ad6");

    auto adImg = Sprite::create("Themes/TanWanLanYue/7.png");
    adImg->setPosition(480, 330);
    adImg->setScale(604.0 / adImg->getContentSize().width);
    adImg->setName("Ad7");
    addChild(adImg);
}

void AdvertisementLayer::createAd8()
{
    removeChildByName("Ad7");

    auto adImg = Sprite::create("Themes/TanWanLanYue/8.png");
    adImg->setPosition(480, 330);
    adImg->setScale(604.0 / adImg->getContentSize().width);
    adImg->setName("Ad8");
    addChild(adImg);
}
