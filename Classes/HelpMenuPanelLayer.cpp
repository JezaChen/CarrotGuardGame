//
// Created by jeza on 18-4-11.
//

#include "HelpMenuPanelLayer.h"
#include "HelpLayer.h"
#include "MonsterHelpLayer.h"
#include "TowerHelpLayer.h"


bool HelpMenuPanelLayer::init()
{
    bool bRet = false;

    do
    {
        CC_BREAK_IF(!Layer::init());

        //TODO ???
        _pLayers = LayerMultiplex::create(HelpLayer::create(), MonsterHelpLayer::create(), TowerHelpLayer::create(),
                                          nullptr);
        addChild(_pLayers);

        loadBackground();
        createMenuPanel();

        bRet = true;
    } while (0);

    return bRet;
}

//TODO 这鬼玩意效率太低
void HelpMenuPanelLayer::createMenuPanel()
{
    //创建一个返回主页的按钮
    auto aHomeBtn = MenuItemSprite::create(Sprite::createWithSpriteFrameName("help_home_normal.png"),
                                           Sprite::createWithSpriteFrameName("help_home_pressed.png"), [](Ref *pSender)
                                           {
                                               auto enWelcomeScene = std::make_tuple(en_WelcomeScene, 0);
                                               NOTIFICATION_CENTER->postNotification("changeScene",
                                                                                     reinterpret_cast<Ref *>(&enWelcomeScene));
                                           });
    //aHomeBtn->setPosition(aHomeBtn->getContentSize().width / 2, 640 - aHomeBtn->getContentSize().height / 2);
    aHomeBtn->setPosition(-480 + aHomeBtn->getContentSize().width / 2, 320 - aHomeBtn->getContentSize().height / 2);

    //现在开始创造"帮助"开关按钮
    //创建两种状态下的精灵：正常状态和被选中的状态
    auto aNormalType = MenuItemSprite::create(Sprite::createWithSpriteFrameName("tips_normal_CN.png"), nullptr);
    auto aSelectedType = MenuItemSprite::create(Sprite::createWithSpriteFrameName("tips_selected_CN.png"), nullptr);
    auto aHelpLayer = HelpLayer::create();
    aHelpLayer->setName("HelpLayer");

    addChild(aHelpLayer); //默认进去就显示第一个帮助Layer

    _pHelpBtn = MenuItemToggle::createWithCallback([=](Ref *pSender)
                                                   {
                                                       _pMonsterHelpBtn->setSelectedIndex(0);
                                                       _pTowerHelpBtn->setSelectedIndex(0);


                                                       this->removeChildByName("MonsterHelpLayer");
                                                       this->removeChildByName("TowerHelpLayer");
                                                       this->removeChildByName("HelpLayer");

                                                       if (_pHelpBtn->getSelectedIndex() == 1)
                                                       {
                                                           auto aNewHelpLayer = HelpLayer::create();
                                                           aNewHelpLayer->setName("HelpLayer");
                                                           addChild(aNewHelpLayer);
                                                       }
                                                   }, aNormalType, aSelectedType, nullptr);

    _pHelpBtn->setSelectedIndex(1); //由于默认进去就显示第一个帮助Layer,所以第一个按钮要处于被选中的状态

    //接下来开始创造"怪物"开关按钮
    aNormalType = MenuItemSprite::create(Sprite::createWithSpriteFrameName("monster_normal_CN.png"), nullptr);
    aSelectedType = MenuItemSprite::create(Sprite::createWithSpriteFrameName("monster_selected_CN.png"), nullptr);
    auto aMonsterHelpLayer = MonsterHelpLayer::create();
    aMonsterHelpLayer->setName("MonsterLayer");
    //addChild(aMonsterHelpLayer);
    _pMonsterHelpBtn = MenuItemToggle::createWithCallback([=](Ref *pSender)
                                                          {
                                                              _pHelpBtn->setSelectedIndex(0);
                                                              _pTowerHelpBtn->setSelectedIndex(0);


                                                              this->removeChildByName("MonsterHelpLayer");
                                                              this->removeChildByName("TowerHelpLayer");
                                                              this->removeChildByName("HelpLayer");

                                                              if (_pMonsterHelpBtn->getSelectedIndex() == 1)
                                                              {
                                                                  auto aNewMonsterHelpLayer = MonsterHelpLayer::create();
                                                                  aNewMonsterHelpLayer->setName("MonsterHelpLayer");
                                                                  addChild(aNewMonsterHelpLayer);
                                                              }
                                                          }, aNormalType, aSelectedType, nullptr);

    //最后开始创造"炮塔"开关按钮
    aNormalType = MenuItemSprite::create(Sprite::createWithSpriteFrameName("tower_normal_CN.png"), nullptr);
    aSelectedType = MenuItemSprite::create(Sprite::createWithSpriteFrameName("tower_selected_CN.png"), nullptr);
    auto aTowerHelpLayer = TowerHelpLayer::create();
    aTowerHelpLayer->setName("TowerHelpLayer");
    //addChild(aTowerHelpLayer);
    _pTowerHelpBtn = MenuItemToggle::createWithCallback([=](Ref *pSender)
                                                        {
                                                            _pHelpBtn->setSelectedIndex(0);
                                                            _pMonsterHelpBtn->setSelectedIndex(0);


                                                            this->removeChildByName("MonsterHelpLayer");
                                                            this->removeChildByName("TowerHelpLayer");
                                                            this->removeChildByName("HelpLayer");

                                                            if (_pTowerHelpBtn->getSelectedIndex() == 1)
                                                            {
                                                                auto aNewTowerHelpLayer = TowerHelpLayer::create();
                                                                aNewTowerHelpLayer->setName("TowerHelpLayer");
                                                                addChild(aNewTowerHelpLayer);
                                                            }
                                                        }, aNormalType, aSelectedType, nullptr);

    auto aMenuPanel = Menu::create(aHomeBtn, _pHelpBtn, _pMonsterHelpBtn, _pTowerHelpBtn, nullptr);
    //那三个按钮记得要调好位置
    _pHelpBtn->setPosition(-160, 270);
    _pMonsterHelpBtn->setPosition(0, 270);
    _pTowerHelpBtn->setPosition(160, 270);

    addChild(aMenuPanel, 2);
}

void HelpMenuPanelLayer::loadBackground()
{
    auto pBg = Sprite::createWithSpriteFrameName("help_bg.png");
    pBg->setPosition(VisibleRectUtil::center());
    addChild(pBg);
}
