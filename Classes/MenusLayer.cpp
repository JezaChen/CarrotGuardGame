#include "MenusLayer.h"
#include "AdvertisementLayer.h"

MenusLayer::~MenusLayer()
{
    CC_SAFE_RELEASE_NULL(_pAdCloseButton); //因为retain了一次，所以要释放一次
}

bool MenusLayer::init()
{
    bool res = false;
    do
    {
        CC_BREAK_IF(!Layer::init());
        createMenuItems();
        res = true;
    }
    while (0);
    return res;
}

void MenusLayer::createMenuItems()
{
    auto pBtnAdventureMode = MenuItemSprite::create(
        Sprite::createWithSpriteFrameName("btn_adventure_normal_CN.png"),
        Sprite::createWithSpriteFrameName("btn_adventure_pressed_CN.png"),
        [](Ref* pSender)
        {
            // 点击该按钮后进入页面选择场景（大关卡选择）
            auto levelScene = std::make_tuple(en_ThemeSelectScene, 0); //传进选择大关卡场景
            NOTIFICATION_CENTER->postNotification("changeScene", reinterpret_cast<Ref *>(&levelScene)); // 通知切换场景
        }
    );
    pBtnAdventureMode->setPosition(Vec2(180, 100));

    auto pBtnBossMode = MenuItemSprite::create(
        Sprite::createWithSpriteFrameName("btn_boss_normal_CN.png"),
        Sprite::createWithSpriteFrameName("btn_boss_pressed_CN.png"),
        [](Ref* pSender)
        {
            // 点击该按钮后进入BOSS模式场景
            auto levelScene = std::make_tuple(en_BossModeScene, 0); //传进选择Boss场景
            NOTIFICATION_CENTER->postNotification("changeScene", reinterpret_cast<Ref *>(&levelScene)); // 通知切换场景
        }
    );
    pBtnBossMode->setPosition(Vec2(pBtnAdventureMode->getPositionX() + 300, pBtnAdventureMode->getPositionY()));

    /*if (true) // boss模式没有完成，先加上锁
    {
        auto pLock = Sprite::createWithSpriteFrameName("locked.png");
        pLock->setPosition(pBtnBossMode->getPositionX() + pBtnBossMode->getContentSize().width / 2 - 20,
                           pBtnBossMode->getPositionY() - 20);
        addChild(pLock, 1);
    }*/

    auto pBtnNestMode = MenuItemSprite::create(
        Sprite::createWithSpriteFrameName("btn_nest_normal_CN.png"),
        Sprite::createWithSpriteFrameName("btn_nest_pressed_CN.png"),
        [](Ref* pSender)
        {
            //TODO
        }
    );
    pBtnNestMode->setPosition(Vec2(pBtnBossMode->getPositionX() + 300, 100));

    if (true) // nest模式没有完成，先加上锁
    {
        auto pLock = Sprite::createWithSpriteFrameName("locked.png");
        pLock->setPosition(pBtnNestMode->getPositionX() + pBtnNestMode->getContentSize().width / 2 - 20,
                           pBtnNestMode->getPositionY() - 20);
        addChild(pLock, 1);
    }

    auto pBtnSetting = MenuItemSprite::create(
        Sprite::createWithSpriteFrameName("btn_setting_normal.png"),
        Sprite::createWithSpriteFrameName("btn_setting_pressed.png"),
        [](Ref* pSender)
        {
            auto gameSettingScene = std::make_tuple(en_GameSettingScene, 0);
            NOTIFICATION_CENTER->postNotification("changeScene", reinterpret_cast<Ref *>(&gameSettingScene));
        }
    );
    pBtnSetting->setPosition(Vec2(200, 220));

    auto pBtnHelp = MenuItemSprite::create(
        Sprite::createWithSpriteFrameName("btn_help_normal.png"),
        Sprite::createWithSpriteFrameName("btn_help_pressed.png"),
        [](Ref* pSender)
        {
            auto GameHelpScene = std::make_tuple(en_GameHelpScene, 0);
            NOTIFICATION_CENTER->postNotification("changeScene", reinterpret_cast<Ref *>(&GameHelpScene));
        }
    );
    pBtnHelp->setPosition(Vec2(750, 220));

    auto _pChatButton = MenuItemSprite::create(Sprite::create("Themes/TanWanLanYue/chat.png"), nullptr,
                                               [&](Ref* pSender)
                                               {
                                                   auto adLayer = AdvertisementLayer::create();
                                                   adLayer->setName("AdLayer");
                                                   addChild(adLayer);
                                                   _pAdCloseButton->setVisible(true);
                                                   _pAdCloseButton->setGlobalZOrder(20);
                                               });
    _pChatButton->setPosition(660, 420);
    _pChatButton->setScale(0.1);

    auto blinkAction = Blink::create(20, 50);
    _pChatButton->runAction(blinkAction);
    //_pChatButton->setContentSize(Size(10, 10));

    _pChatButton->setVisible(true);

    _pAdCloseButton = MenuItemSprite::create(Sprite::createWithSpriteFrameName("ad_close_normal.png"),
                                                  Sprite::createWithSpriteFrameName("ad_close_pressed.png"),
                                                  [&](Ref* pSender)
                                                  {
                                                      removeChildByName("AdLayer");
                                                      _pAdCloseButton->setVisible(false);
                                                  });
    _pAdCloseButton->setScale(0.55);
    _pAdCloseButton->setPosition(806, 327);
    _pAdCloseButton->setName("AdCloseBtn");
    _pAdCloseButton->retain(); //要retain一下吧
    _pAdCloseButton->setVisible(false);
    //_pAdCloseButton->setScale(0.1);

    _pMenu = Menu::create(pBtnAdventureMode, pBtnBossMode, pBtnNestMode, pBtnSetting, pBtnHelp, _pChatButton, _pAdCloseButton,
                              nullptr); //bug fixed
    _pMenu->setPosition(Vec2::ZERO);
    addChild(_pMenu);
}
