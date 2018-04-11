//
// Created by jeza on 18-4-10.
//

#include "HelpLayer.h"
#include "NumSprite.h"

void HelpLayer::createHelpPageView()
{
    //创建一个页面
    _pHelpPageView = PageView::create();
    _pHelpPageView->setContentSize(Size(960.0f, 640.0f));

    //总共有四页
    for (int i = 1; i < 5; i++)
    {
        Layout *pLayout = Layout::create();
        //根据当前页数创建对应的精灵
        auto aHelpPicSprite = Sprite::createWithSpriteFrameName(StringUtils::format("tips_%d.png", i));
        auto aHelpTipsText = Sprite::createWithSpriteFrameName(StringUtils::format("tips_text_%d_CN.png", i));

        //还要创建一个数字精灵
        //用于页码的显示
        //std::string pageNum = StringUtils::format("%d", i);

        aHelpTipsText->setPosition(480, 160);
        aHelpPicSprite->setPosition(480, 370);

        pLayout->addChild(aHelpPicSprite);
        pLayout->addChild(aHelpTipsText);
        _pHelpPageView->insertPage(pLayout, i - 1);
    }
    _pHelpPageView->setPassFocusToChild(true);
    _pHelpPageView->scrollToPage(_iCurPageIndex);

    //注册滑动事件监听事件
    _pHelpPageView->addEventListener([=](Ref *pSender, PageView::EventType eventType)
                                     {
                                         if (eventType == PageView::EventType::TURNING)
                                         {
                                             _iCurPageIndex = static_cast<int>(_pHelpPageView->getCurrentPageIndex());
                                             bottomSprite->removeAllChildren();
                                             std::string num = StringUtils::format("%d", _iCurPageIndex +
                                                                                         1); //记得要加一,因为程序的页数是从0开始的
                                             auto newNumSprite = NumSprite::createNum(num,
                                                                                      "Themes/Items/numwhite-hd.png");
                                             newNumSprite->setPosition(465, 40);
                                             bottomSprite->addChild(newNumSprite); //TODO 孩子序号是否需要添加
                                         }
                                     });
    addChild(_pHelpPageView);
}

void HelpLayer::createBottom()
{
    //创建底部图像
    bottomSprite = Sprite::createWithSpriteFrameName("bottom.png");
    bottomSprite->setPosition(480, 50);
    addChild(bottomSprite);

    //创建一个斜杠
    auto aSprit = NumSprite::createSprit("Themes/Items/numwhite-hd.png");
    //创建数字四
    auto aNumFour = NumSprite::createNum("4", "Themes/Items/numwhite-hd.png");

    aSprit->setPosition(480, 55);
    aNumFour->setPosition(498, 55);

    addChild(aNumFour);
    addChild(aSprit);

    createInitialBottomSprite(); //为了加快页码显示，引入一个函数
}

void HelpLayer::createInitialBottomSprite()
{
    bottomSprite->removeAllChildren();
    std::string num = StringUtils::format("%d", _iCurPageIndex + 1); //初始化为先前的_iCurPageIndex
    auto newNumSprite = NumSprite::createNum(num, "Themes/Items/numwhite-hd.png");
    newNumSprite->setPosition(465, 40);
    bottomSprite->addChild(newNumSprite); 
}

bool HelpLayer::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!Layer::init());
        //PageView give_me_a_name;
        createBottom();
        createHelpPageView();
        bRet = true;
    } while (0);
    return bRet;
}
