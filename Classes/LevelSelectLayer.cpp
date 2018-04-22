//
// Created by jeza on 18-4-9.
//

#include "CommonDefine.h"
#include "LevelSelectLayer.h"
#include "LocalLevelDataUtil.h"
#include "ui/CocosGUI.h"
#include "SceneManager.h"

using namespace ui;

LevelSelectLayer::~LevelSelectLayer()
{
}

bool LevelSelectLayer::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!Layer::init());

        _iCurPageIndex = SceneManager::getInstance()->getCurrentPageIndex();

        loadData();
        loadSource();
        bRet = true;
    } while (0);
    return bRet;
}
void LevelSelectLayer::loadSource()
{
    //创建主背景
    auto aBackground = Sprite::createWithSpriteFrameName("ss_bg.png");
    aBackground->setPosition(VisibleRectUtil::center());
    addChild(aBackground);

    //创建标题
    auto aTitle = Label::createWithSystemFont(TITLE_SELECT_LEVEL, "Microsoft YaHei UI", 30); //TODO 其实有图的                                                                          //auto aTitle = Sprite::createWithSpriteFrameName("theme_bg_CN.png");
    aTitle->setPosition(475, 609);
    addChild(aTitle, 0);
    //aTitle->setScale(1.4);

    //创建下方两侧的云朵
    auto aCloud = Sprite::createWithSpriteFrameName("ss_cloud.png");
    aCloud->setPosition(VisibleRectUtil::center());
    addChild(aCloud);

    loadLevelButton();
    loadMenuItem();
}

void LevelSelectLayer::loadData()
{
    _DataValueMap = LocalLevelDataUtil::getInstance()->getLevelData();
}

void LevelSelectLayer::loadMenuItem()
{
    //创建退出按钮
    auto aBackBtn = MenuItemSprite::create(Sprite::createWithSpriteFrameName("ss_back_normal.png"),
                                           Sprite::createWithSpriteFrameName("ss_back_pressed.png"), [&](Ref *pSender)
                                           {
                                               auto enThemeSelectScene = std::make_tuple(en_ThemeSelectScene,
                                                                                         _iCurPageIndex);
                                               NOTIFICATION_CENTER->postNotification("changeScene",
                                                                                     reinterpret_cast<Ref *>(&enThemeSelectScene));
                                           });
    aBackBtn->setPosition(-445, 290);

    //创建帮助按钮
    auto aHelpBtn = MenuItemSprite::create(Sprite::createWithSpriteFrameName("ss_help_normal.png"),
                                           Sprite::createWithSpriteFrameName("ss_help_pressed.png"), [&](Ref *pSender)
                                           {
                                               auto enHelpScene = std::make_tuple(en_GameHelpScene, 0);
                                               NOTIFICATION_CENTER->postNotification("changeScene",
                                                                                     reinterpret_cast<Ref *>(&enHelpScene));
                                           });
    aHelpBtn->setPosition(450, 290);
    aHelpBtn->setScale(1.4);

    //创建开始按钮
    _pStartBtn = MenuItemSprite::create(Sprite::createWithSpriteFrameName("ss_play_normal_CN.png"),
                                        Sprite::createWithSpriteFrameName("ss_play_pressed_CN.png"), [&](Ref *pSender)
                                        {
                                            this->changeToGameScene();
                                        });

    _pStartBtn->setPosition(Vec2(0, -245));
    addChild(Menu::create(aBackBtn, aHelpBtn, _pStartBtn, nullptr), 14);
    _pStartBtn->setVisible(false);

    //创建锁住按钮
    _pLockBtn = Sprite::createWithSpriteFrameName("ss_locked_CN.png");
    _pLockBtn->setPosition(Vec2(480, 75));
    addChild(_pLockBtn, 1);
    _pLockBtn->setVisible(!_pLockBtn->isVisible());

}

std::tuple<int, bool> LevelSelectLayer::getLevelData(const int &riLevelIndex)
{
    //获取该关卡的value值
    auto aKey = StringUtils::format(LEVELKEY, _iCurPageIndex + 1, riLevelIndex);
    int iValue = _DataValueMap[aKey].asInt();

    //提取相应的数据
    int iCarrotType = iValue / 10;
    bool iBarriersAllCleaned = iValue % 10 != 0;

    //返回元祖
    return std::make_tuple(iCarrotType, iBarriersAllCleaned);
}

void LevelSelectLayer::changeToGameScene()
{
    if (std::get<0>(getLevelData(_iCurLevelIndex + 1)) == LEVEL_LOCK) return;
    auto enGameScene = std::make_tuple(en_GameScene, _iCurLevelIndex);
    NOTIFICATION_CENTER->postNotification("changeScene", reinterpret_cast<Ref *>(&enGameScene));
}

void LevelSelectLayer::loadLevelButton()
{
    auto aPageView = PageView::create();
    aPageView->setContentSize(Size(960.0f, 640.0f));
    Size contentSize = this->getContentSize();

    for (int i = 0; i < THEME_LEVELCOUNT_ARRAY[_iCurPageIndex]; i++)
    {
        std::string mapThumbNail = MAPNAME + StringUtils::format("%02d", i + 1) + PHOTOPOSTFIX;
        Layout *pLayout = Layout::create();

        //获取该关卡的怪兽数目
        auto aTotalMonsterBatchCount = CsvUtil::getInstance()->getInt(
                1 + SceneManager::getInstance()->getCurrentPageIndex() * 12 + i, 3, LEVELCSVFILE);

        //获取对应数目的精灵
        auto aTotalMonsterBatchPicSprite = Sprite::createWithSpriteFrameName(
                StringUtils::format("ss_waves_%d.png", aTotalMonsterBatchCount));
        aTotalMonsterBatchPicSprite->setPosition(500, 535);
        pLayout->addChild(aTotalMonsterBatchPicSprite);

        auto gameButton = Button::create(mapThumbNail, mapThumbNail, mapThumbNail, TextureResType::PLIST);
        gameButton->setPosition(Vec2(contentSize.width / 2, contentSize.height / 2 + 35));
        gameButton->addTouchEventListener([&](Ref *pSender, Widget::TouchEventType event)
                                          {
                                              if (event == Widget::TouchEventType::ENDED)
                                                  //唤起切换游戏界面的函数
                                                  //判断关卡是否被锁的逻辑在changeToGameScene函数里面的
                                                  this->changeToGameScene(); 
                                          });

        auto aTowerBar = Sprite::createWithSpriteFrameName(
                TOWERNAME + StringUtils::format("%02d", i + 1) + PHOTOPOSTFIX);
        aTowerBar->setPosition(Vec2(contentSize.width / 2,
                                    contentSize.height / 2 - gameButton->getContentSize().height / 2 -
                                    aTowerBar->getContentSize().height / 2 + 35));
        pLayout->addChild(gameButton);
        pLayout->addChild(aTowerBar);

        //开始绘画星数、清除障碍物之类的荣誉标识
        auto aLevelData = getLevelData(i + 1);

        auto aCarrotType = std::get<0>(aLevelData);
        auto aBarriersAllCleaned = std::get<1>(aLevelData);

        if (aCarrotType == LEVEL_LOCK)
        {
            auto aLock = Sprite::createWithSpriteFrameName("ss_locked_icon.png");
            aLock->setPosition(620, 255);
            pLayout->addChild(aLock);
        }
        else
        {
            std::string sCarrotType = "";
            if (aCarrotType == LEVEL_STAR3)
                sCarrotType = GOLDCARROT; //金萝卜
            else if (aCarrotType == LEVEL_STAR2)
                sCarrotType = SILVERCARROT; //银萝卜
            else if (aCarrotType == LEVEL_STAR1)
                sCarrotType = NORMALCARROT; //普通萝卜

            if (aCarrotType > 1)
            {
                auto aCarrot = Sprite::createWithSpriteFrameName(sCarrotType);
                aCarrot->setPosition(620, 255);
                pLayout->addChild(aCarrot);
            }

            if (aBarriersAllCleaned > 0)
            {
                auto aBarriersCleaned = Sprite::createWithSpriteFrameName(BARRIERCLEAN);
                aBarriersCleaned->setPosition(500, 255);
                pLayout->addChild(aBarriersCleaned);
            }
        }
        aPageView->insertPage(pLayout, i);
    }

    aPageView->setPassFocusToChild(true); //TODO
    aPageView->scrollToPage(_iCurLevelIndex); //TODO 这个，游戏返回的时候该怎么修改index
    aPageView->addEventListener([=](Ref *pSender, PageView::EventType event)
                                {
                                    if (event == PageView::EventType::TURNING) //滑动事件
                                    {
                                        _iCurLevelIndex = static_cast<int>(aPageView->getCurrentPageIndex());
                                        bool bIsLocked = std::get<0>(this->getLevelData(_iCurLevelIndex + 1)) ==
                                                         LEVEL_LOCK; //是否仍处于锁住状态

                                        //根据状态对按钮状态进行调整
                                        _pStartBtn->setEnabled(!bIsLocked);
                                        _pStartBtn->setVisible(!bIsLocked);
                                        _pLockBtn->setVisible(bIsLocked);
                                    }
                                });
    addChild(aPageView, 3); //最后不要忘记添加上去
}




