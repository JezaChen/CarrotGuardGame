//
// Created by jeza on 18-4-11.
//

#include "SettingMenuPanelLayer.h"
#include "OptionLayer.h"
#include "DataStatisticsLayer.h"
#include "AboutUsLayer.h"


bool SettingMenuPanelLayer::init()
{
    bool bRet = false;

    do
    {
        CC_BREAK_IF(!Layer::init());

        createMultiplexLayer();

        createMenuPanel();

        bRet = true;
    } while (0);

    return bRet;
}

void SettingMenuPanelLayer::createMenuPanel()
{
    //创建一个返回主页的按钮
    auto aHomeBtn = MenuItemSprite::create(Sprite::createWithSpriteFrameName("setting_home_normal.png"),
                                           Sprite::createWithSpriteFrameName("setting_home_pressed.png"),
                                           [](Ref *pSender)
                                           {
                                               auto enWelcomeScene = std::make_tuple(en_WelcomeScene, 0);
                                               NOTIFICATION_CENTER->postNotification("changeScene",
                                                                                     reinterpret_cast<Ref *>(&enWelcomeScene));
                                           });
    aHomeBtn->setPosition(-480 + aHomeBtn->getContentSize().width / 2, 320 - aHomeBtn->getContentSize().height / 2);

    //创建设置图层的按钮
    auto aOptionBtn = MenuItemSprite::create(Sprite::createWithSpriteFrameName("options_normal_CN.png"),
                                             Sprite::createWithSpriteFrameName("options_selected_CN.png"),
                                             [=](Ref *pSender)
                                             {
                                                 _pLayerMultiplex->switchTo(0);
                                             });

    aOptionBtn->setPosition(-200,273);

    //创建数据图层的按钮
    auto aStatisticsBtn = MenuItemSprite::create(Sprite::createWithSpriteFrameName("statistics_normal_CN.png"),
                                                 Sprite::createWithSpriteFrameName("statistics_selected_CN.png"),
                                                 [=](Ref *pSender)
                                                 {
                                                     _pLayerMultiplex->switchTo(1);
                                                 });

    aStatisticsBtn->setPosition(0, 273);

    //创建关于图层的按钮
    auto aAboutUsBtn = MenuItemSprite::create(Sprite::createWithSpriteFrameName("credits_normal_CN.png"),
                                              Sprite::createWithSpriteFrameName("credits_selected_CN.png"),
                                              [=](Ref *pSender)
                                              {
                                                  _pLayerMultiplex->switchTo(2);
                                              });

    aAboutUsBtn->setPosition(200, 273);

    auto aMenu = Menu::create(aHomeBtn, aOptionBtn, aStatisticsBtn, aAboutUsBtn, nullptr);
    addChild(aMenu);
}

void SettingMenuPanelLayer::createMultiplexLayer()
{
    //创建一个多图层管理类对象
    _pLayerMultiplex = LayerMultiplex::create(OptionLayer::create(), DataStatLayer::create(), AboutUsLayer::create(),
                                              nullptr);
    _pLayerMultiplex->retain();
    _pLayerMultiplex->setPosition(VisibleRectUtil::center());
    addChild(_pLayerMultiplex);
}

SettingMenuPanelLayer::~SettingMenuPanelLayer()
{
    CC_SAFE_RELEASE_NULL(_pLayerMultiplex);
}
