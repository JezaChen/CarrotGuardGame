#include "LoadingSourceLayer.h"
#include "CommonSource.h"

bool LoadingSourceLayer::init()
{
    bool bRet = false;
    do{
        CC_BREAK_IF(!Layer::init());
        //创建一个进度条背景
        auto pProgressBarBg= Sprite::create("loading/fight_blood_top.png");
        pProgressBarBg->setPosition(465, 50);
        addChild(pProgressBarBg);
        pProgressBarBg->setScaleX(1.4f);

        //创建一个进度条
        auto pProgressBar = ProgressTimer::create(Sprite::create("loading/fight_blood_bg.png")); //Bug Fixed on 20180409
        pProgressBar->setType(ProgressTimer::Type::BAR);
        pProgressBar->setName("progressBar");
        pProgressBar->setMidpoint(Vec2::ANCHOR_MIDDLE_LEFT);
        pProgressBar->setBarChangeRate(Vec2::ANCHOR_BOTTOM_RIGHT);
        pProgressBar->setPercentage(100);
        pProgressBar->setPosition(465, 50);
        addChild(pProgressBar);
        pProgressBar->setScaleX(1.4f);

        //进度Label
        _pLoadingTitle = Label::createWithSystemFont("loading", "Arial", 20);
        addChild(_pLoadingTitle);
        _pLoadingTitle->setPosition(Vec2(410, 70));
        _pLoadingTitle->setAnchorPoint(Vec2(0, 0.5f));

        bRet = true;
    }while(0);

    return bRet;
}

void LoadingSourceLayer::loadSource()
{
    auto pDirector = Director::getInstance();
    static auto tIndex = 0;
    for(auto &iterOfSourcdeFile : ALLSOURCE)
    {
        pDirector->getInstance()->getTextureCache()->addImageAsync(iterOfSourcdeFile + PHOTOPOSTFIX, [&](Texture2D *pTexture) //用贴图缓冲类异步图片
                                                                  {
                                                                      SpriteFrameCache::getInstance()->addSpriteFramesWithFile(iterOfSourcdeFile + PLISTPOSTFIX, pTexture);
                                                                      ++tIndex;
                                                                      auto tPercentage = tIndex * 1.0f / ALLSOURCE.size() *100;
                                                                      (dynamic_cast<ProgressTimer*>(getChildByName("progressBar")))->setPercentage(tPercentage);
                                                                      _pLoadingTitle->setString(StringUtils::format("Loading %.f%%", tPercentage));
                                                                      if(tIndex == ALLSOURCE.size()) _funcShowMenuPanel();

                                                                  });
    }
}

void LoadingSourceLayer::setFuncShowMenuPanel(const std::function<void ()> &rFuncShowMenuPanel)
{
    _funcShowMenuPanel = rFuncShowMenuPanel;
}

void LoadingSourceLayer::onEnter()
{
    Layer::onEnter();
    loadSource();
}