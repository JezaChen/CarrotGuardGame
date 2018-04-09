//
//  PageViewLayer.cpp
//  CarrotFantasy
//
//  Created by Yan on 14-9-19.
//
//

#include "PageViewLayer.h"
#include "SceneManager.h"
#include "ui/UIButton.h"
#include "SoundUtil.h"
#include "CommonSource.h"

PageViewLayer::~PageViewLayer()
{
    CC_SAFE_RELEASE_NULL(_pPageView);
    CC_SAFE_DELETE(_pPagePointsVec);
}

bool PageViewLayer::init()
{
    bool bRet = false;

    do
    {
        CC_BREAK_IF(!Layer::init());

        _iPageIndex = SceneManager::getInstance()->getCurrentPageIndex();
        _pPagePointsVec = new Vector<MenuItemSprite*>;

        loadBackground();
        createThemePageView();
        createThemePoints();

        bRet = true;
    } while (0);
    return bRet;
}

void PageViewLayer::pageTurn(const bool &rBLeft)
{
    if (rBLeft)
    {
        if (_pPageView->getCurPageIndex() == 0) return;
        _pPageView->scrollToPage(_pPageView->getCurPageIndex() - 1);
    }
    else
    {
        //if(_pPageView->getCurPageIndex() + 1 == _pPageView->getPageCount()) return;
        _pPageView->scrollToPage(_pPageView->getCurPageIndex() + 1);
    }
}

void PageViewLayer::setActivePagePoint(const int &rIIndex)
{
    int tIndex = -1;
    for (auto & flagIter : *_pPagePointsVec)
    {
        if (rIIndex == ++tIndex)
        {
            flagIter->selected();
            continue;
        }
        flagIter->unselected();
    }
}


void PageViewLayer::loadBackground()
{
    auto pBg = Sprite::createWithSpriteFrameName(BG);
    pBg->setPosition(VisibleRectUtil::center());
    addChild(pBg);

    auto pTitle = Label::createWithSystemFont("选择关卡", "Arial", 30);
    pTitle->setPosition(Vec2(480, 615));
    addChild(pTitle);
}

void PageViewLayer::createThemePoints()
{
    auto pPageFlagMenu = Menu::create();
    auto tFlagCount = 5;//_pPageView->getPageCount();
    for (int i = 0; i < tFlagCount; ++i)
    {
        auto pPageFlagItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("theme_pos_normal.png"), Sprite::createWithSpriteFrameName("theme_pos_active.png"));
        pPageFlagItem->setPosition(Vec2(430 + 20 * i, 30));
        _pPagePointsVec->pushBack(pPageFlagItem);
        pPageFlagMenu->addChild(pPageFlagItem);
    }
    _pPagePointsVec->at(_iPageIndex)->selected();
    addChild(pPageFlagMenu);
}

void PageViewLayer::createThemePageView()
{
    _pPageView = PageView::create();
    _pPageView->retain();
    _pPageView->setContentSize(Size(960.0f, 640.0f));

    Size tBackgroundSize = this->getContentSize();
    Layout *pLayout = nullptr;
    int i = -1;
    for (auto & iterThemeName : PAGESOURCE)
    {
        pLayout = Layout::create();
        auto pButton = Button::create(iterThemeName, iterThemeName, iterThemeName, cocos2d::ui::Layout::TextureResType::PLIST);
        pButton->setPosition(Vec2(tBackgroundSize.width / 2, tBackgroundSize.height / 2 - 20));
        pButton->addTouchEventListener([&](Ref *pSender, Widget::TouchEventType event)
        {
            if (event == Widget::TouchEventType::ENDED)
            {
                int tCurPageIndex = _pPageView->getCurPageIndex();
                auto tEnSceneType = std::make_tuple(en_LevelSelectScene, tCurPageIndex);
                NOTIFY->postNotification("changeScene", reinterpret_cast<Ref*>(&tEnSceneType));
            }
        });
        pLayout->addChild(pButton);
        auto pThemeFlag = Sprite::createWithSpriteFrameName(StringUtils::format("theme_pack0%d_CN.png", i + 2));
        pThemeFlag->setScale(1.3f);
        pThemeFlag->setPosition(490, 320);
        pLayout->addChild(pThemeFlag);

        auto pThemeMark = Sprite::createWithSpriteFrameName(StringUtils::format("bookmark_10-12.png"));
        pThemeMark->setScale(1.5f);
        pThemeMark->setPosition(Vec2(710, 70));
        pLayout->addChild(pThemeMark);
        _pPageView->insertPage(pLayout, ++i);

    }
    _pPageView->setPassFocusToChild(true);
    _pPageView->scrollToPage(_iPageIndex);
    _pPageView->addEventListener([&](Ref *pSender, PageView::EventType event)
    {
        if (PageView::EventType::TURNING == event)
        {
            this->setActivePagePoint(_pPageView->getCurPageIndex());
        }
    });
    addChild(_pPageView, 14);
}


