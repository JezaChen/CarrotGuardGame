//
// Created by jeza1 on 2018/4/9.
//

#include "SelectSceneMenuPanelLayer.h"
#include "SoundUtil.h"
#include "CommonSource.h"

bool MenuPanelLayer::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!Layer::init());

        createItemPanel();

        bRet = true;
    } while (0);

    return bRet;
}

void MenuPanelLayer::setPageTurnFunction(const std::function<void(const bool &)> &rfFuncPageTurn) {
    _funcPageTurn = rfFuncPageTurn;
}

void MenuPanelLayer::createItemPanel() {
    //创建返回主页按钮
    //第一个参数是正常形态，第二个参数被按下去的形态
    auto aBtnHome = MenuItemSprite::create(Sprite::createWithSpriteFrameName("theme_home_normal.png"), Sprite::createWithSpriteFrameName("theme_home_pressed.png"), [](Ref *pSender)
    {
        //点击事件发生后，通知切换到主页场景
        auto enWelcomeScene = std::make_tuple(en_WelcomeScene, -1);
        NOTIFICATION_CENTER->postNotification("changeScene", reinterpret_cast<Ref*>(&enWelcomeScene));
    });
    aBtnHome->setPosition(Vec2(-445, 290));
    aBtnHome->setScale(1.4);

    //创建帮助按钮
    auto aBtnHelp = MenuItemSprite::create(Sprite::createWithSpriteFrameName("ss_help_normal.png"), Sprite::createWithSpriteFrameName("ss_help_pressed.png"), [](Ref *pSender)
    {
        //点击事件发生后，通知切换到帮助场景
        auto tEnHelpScene = std::make_tuple(en_GameHelpScene, 0);
        NOTIFICATION_CENTER->postNotification("changeScene", reinterpret_cast<Ref*>(&tEnHelpScene));
    });
    aBtnHelp->setPosition(Vec2(445, 290));
    aBtnHelp->setScale(1.4);
    //左切按钮
    auto aBtnLeft = MenuItemSprite::create(Sprite::createWithSpriteFrameName("theme_pointleft_normal.png"), Sprite::createWithSpriteFrameName("theme_pointleft_pressed.png"), [this](Ref *pSender)
    {
        _funcPageTurn(true);
    });
    aBtnLeft->setPosition(Vec2(-400, 0)); //bug fixed: 锚点在中点位置

    //右切按钮
    auto aBtnRight = MenuItemSprite::create(Sprite::createWithSpriteFrameName("theme_pointright_normal.png"), Sprite::createWithSpriteFrameName("theme_pointright_pressed.png"), [this](Ref *pSender)
    {
        _funcPageTurn(false);
    });
    aBtnRight->setPosition(Vec2(400, 0));

    auto aMenu = Menu::create(aBtnHome, aBtnHelp, aBtnLeft, aBtnRight, nullptr);
    addChild(aMenu);
}