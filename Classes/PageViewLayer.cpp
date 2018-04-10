//
// Created by jeza on 18-4-8.
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

//性能太差，估计要推掉
void PageViewLayer::setActivePagePoint(const int &riIndex)
{
    for (int i = 0; i < _pPagePointsVec->size(); i++)
    {
        if (riIndex == i) //若命中
            _pPagePointsVec->at(i)->selected(); //这个菜单项就被选择了，高亮显示
        else
            _pPagePointsVec->at(i)->unselected(); //否侧，就变成灰色
    }
}


void PageViewLayer::loadBackground()
{
    auto aBg = Sprite::createWithSpriteFrameName(BG);
    aBg->setPosition(VisibleRectUtil::center());
    addChild(aBg, 0);

    auto aTitle = Label::createWithSystemFont(TITLE_SELECT_LEVEL, "Microsoft YaHei UI", 30); //TODO 其实有图的
    //auto aTitle = Sprite::createWithSpriteFrameName("theme_bg_CN.png");
    aTitle->setPosition(475, 609);
    addChild(aTitle, 0);
    //aTitle->setScale(1.4);
}

void PageViewLayer::createThemePoints()
{
    auto aPageFlagMenu = Menu::create();
    int iPointCounts = 5; //TODO 暂定有五个点
    for (int i = 0; i < iPointCounts; i++)
    {
        //创建item，第一个是没有被选择的图像，第二个是被选择到的图像
        auto aPagePointItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("theme_pos_normal.png"),
            Sprite::createWithSpriteFrameName("theme_pos_active.png"));
        aPagePointItem->setPosition(Vec2(-40 + 20 * i, -280)); //放置到相应的位置
        _pPagePointsVec->pushBack(aPagePointItem);
        aPageFlagMenu->addChild(aPagePointItem);
    }
    _pPagePointsVec->at(_iPageIndex)->selected(); //这个相当于初始化选定
    addChild(aPageFlagMenu);
}

void PageViewLayer::createThemePageView()
{
    _pPageView = PageView::create();
    _pPageView->retain();
    _pPageView->setContentSize(Size(960.0f, 640.0f));

    //背景尺寸
    //TODO 似乎有点不对
    Size aBackgroundSize = this->getContentSize();
    Layout *pPageLayout = nullptr;
    int i = -1;
    for (auto &iterThemeName : PAGESOURCE)
    {
        pPageLayout = Layout::create();
        //每个主题的选择其实是有一个个按钮组成的，三个状态都是一样的
        auto aPageButton = Button::create(iterThemeName, iterThemeName, iterThemeName,
            cocos2d::ui::Layout::TextureResType::PLIST);
        aPageButton->setPosition(Vec2(aBackgroundSize.width / 2, aBackgroundSize.height / 2 - 20));
        aPageButton->addTouchEventListener([&](Ref *pSender, Widget::TouchEventType event)
        {
            //若鼠标点击落下
            if (event == Widget::TouchEventType::ENDED)
            {
                int iCurPageIndex = static_cast<int>(_pPageView->getCurrentPageIndex());
                auto aChangingSceneType = std::make_tuple(en_LevelSelectScene,
                    iCurPageIndex);
                //通知切换到关卡选择页面
                NOTIFICATION_CENTER->postNotification("changeScene",
                    reinterpret_cast<Ref *>(&aChangingSceneType));

            }
        });

        pPageLayout->addChild(aPageButton);

        //aThemeInfo 是按钮右上侧那个具体信息
        auto aThemeInfo = Sprite::createWithSpriteFrameName(StringUtils::format("theme_pack0%d_CN.png", i + 2));
        aThemeInfo->setScale(1.3f);
        aThemeInfo->setPosition(490, 320);
        pPageLayout->addChild(aThemeInfo);

        //aThemeMark 是下方那个关卡通关数
        auto aThemeMark = Sprite::createWithSpriteFrameName(StringUtils::format("bookmark_10-12.png")); //TODO
        aThemeMark->setScale(1.5f);
        aThemeMark->setPosition(710, 70);
        pPageLayout->addChild(aThemeMark);

        _pPageView->insertPage(pPageLayout, ++i);

    }

    _pPageView->setPassFocusToChild(true); //TODO ???
    _pPageView->scrollToPage(_iPageIndex);
    _pPageView->addEventListener([&](Ref *pSender, PageView::EventType event)
    {
        if (event == PageView::EventType::TURNING) {
            this->setActivePagePoint(
                static_cast<const int &>(_pPageView->getCurrentPageIndex()));
        }
    });
    addChild(_pPageView);
}


