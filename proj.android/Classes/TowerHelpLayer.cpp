//
// Created by jeza on 18-4-10.
//

#include "TowerHelpLayer.h"
#include "NumSprite.h"

bool TowerHelpLayer::init()
{
    bool bRet = false;

    do
    {
        CC_BREAK_IF(!Layer::init());
        createBottom();
        createTowerHelpPageView();
        bRet = true;
    }
    while (0);
    return bRet;
}

void TowerHelpLayer::createTowerHelpPageView()
{
    //创建一个页面
    _pTowerHelpPageView = PageView::create();
    _pTowerHelpPageView->setContentSize(Size(960.0f, 640.0f));

    //总共有十八页
    for (int i = 1; i <= 18; i++)
    {
        Layout *pLayout = Layout::create();
        //根据当前页数创建对应的精灵
        auto aHelpPicSprite = Sprite::createWithSpriteFrameName(StringUtils::format("tower_%02d.png", i));
        auto aHelpTipsText = Sprite::createWithSpriteFrameName(StringUtils::format("tower_%02d_CN.png", i));

        //还要创建一个数字精灵
        //用于页码的显示
        //std::string pageNum = StringUtils::format("%d", i);

        aHelpTipsText->setPosition(480, 310);
        aHelpPicSprite->setPosition(480, 310);

        pLayout->addChild(aHelpPicSprite);
        pLayout->addChild(aHelpTipsText);
        _pTowerHelpPageView->insertPage(pLayout, i - 1);
    }
    _pTowerHelpPageView->setPassFocusToChild(true);
    _pTowerHelpPageView->scrollToPage(_iCurPageIndex);

    //注册滑动事件监听事件
    _pTowerHelpPageView->addEventListener([=](Ref *pSender, PageView::EventType eventType)
                                          {
                                              if (eventType == PageView::EventType::TURNING)
                                              {
                                                  _iCurPageIndex = static_cast<int>(_pTowerHelpPageView->getCurrentPageIndex());
                                                  bottomSprite->removeAllChildren();
                                                  std::string num = StringUtils::format("%d", _iCurPageIndex + 1);
                                                  auto newNumSprite = NumSprite::createNum(num,
                                                                                           "Themes/Items/numwhite-hd.png");
                                                  if (_iCurPageIndex + 1 < 10)
                                                      newNumSprite->setPosition(465, 40);
                                                  else
                                                      newNumSprite->setPosition(447, 40);
                                                  bottomSprite->addChild(newNumSprite);
                                              }
                                          });
    addChild(_pTowerHelpPageView);

}

void TowerHelpLayer::createBottom()
{
    //创建底部图像
    bottomSprite = Sprite::createWithSpriteFrameName("bottom.png");
    bottomSprite->setPosition(480, 50);
    addChild(bottomSprite);

    //创建一个斜杠
    auto aSprit = NumSprite::createSprit("Themes/Items/numwhite-hd.png");
    //创建数字十八
    auto aNumEighteen = NumSprite::createNum("18", "Themes/Items/numwhite-hd.png");

    aSprit->setPosition(480, 55);
    aNumEighteen->setPosition(498, 55);

    addChild(aNumEighteen);
    addChild(aSprit);

    createInitialBottomSprite(); //为了加快页码显示，引入一个函数
}

void TowerHelpLayer::createInitialBottomSprite()
{
    bottomSprite->removeAllChildren();
    std::string num = StringUtils::format("%d", _iCurPageIndex + 1); //初始化为先前的_iCurPageIndex
    auto newNumSprite = NumSprite::createNum(num, "Themes/Items/numwhite-hd.png");
    newNumSprite->setPosition(465, 40);
    bottomSprite->addChild(newNumSprite);
}
