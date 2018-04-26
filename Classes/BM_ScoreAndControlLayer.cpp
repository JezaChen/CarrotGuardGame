#include "BM_ScoreAndControlLayer.h"
#include "PauseLayer.h"
#include "NumSprite.h"
#include "LevelConfigUtil.h"
#include "SoundUtil.h"
#include "CommonSource.h"
#include "MonsterLayer.h"
#include "GameSceneII.h"
#include "GameManager.h"
#include "SceneManager.h"

bool BM_ScoreAndControllerLayer::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!Layer::init());

        registerNotifyEvent();

        loadData();
        loadBg();

        createTopPanel();
        createBottomPanel();

        //这里的一秒太快了，改成1.8s = 1s
        schedule(schedule_selector(BM_ScoreAndControllerLayer::timeChange), 1.8f, 150, 4);
        schedule(schedule_selector(BM_ScoreAndControllerLayer::bossHpChanged), 0.6f);

        bRet = true;
    } while (0);

    return bRet;
}

void BM_ScoreAndControllerLayer::loadBg()
{
    auto tVisibleSize = Director::getInstance()->getVisibleSize();
    //菜单面板背景；
    auto pPanelBg = Sprite::createWithSpriteFrameName("MenuBG.png");
    pPanelBg->setPosition(Vec2(tVisibleSize.width / 2, tVisibleSize.height - pPanelBg->getContentSize().height / 2));
    addChild(pPanelBg);

    auto tSize = Sprite::create(MONSTERBATCHIMAGE)->getContentSize();
    auto pMonsterBatchCountSprite = NumSprite::createNum(
        StringUtils::format("%d", LevelConfigUtil::getInstance()->getCurrentMonsterBatchCount()), MONEYNUMIMAGE);
    addChild(pMonsterBatchCountSprite);

    _pMoneyLabel = NumSprite::createNum(StringUtils::format("%d", _iMoney), MONEYNUMIMAGE);
    addChild(_pMoneyLabel);
    _pMoneyLabel->release();
    _pMoneyLabel->setPosition(100, 603);

    //创建血量背景
    auto aBossHpBarBg = Sprite::createWithSpriteFrameName("menublood_02.png");
    aBossHpBarBg->setPosition(465, 595);
    addChild(aBossHpBarBg);
    //todo 要不要放大

    //创建血量进度条
    auto aBossHpBar = ProgressTimer::create(Sprite::createWithSpriteFrameName("menublood_01.png"));
    aBossHpBar->setType(ProgressTimer::Type::BAR);
    aBossHpBar->setName("BossHpBar");

    aBossHpBarBg->setScaleX(aBossHpBar->getContentSize().width / aBossHpBarBg->getContentSize().width - 0.14);
    aBossHpBarBg->setScaleY(aBossHpBar->getContentSize().height / aBossHpBarBg->getContentSize().height);


    //todo 看看官方api才行
    aBossHpBar->setMidpoint(Vec2::ANCHOR_MIDDLE_LEFT); //设置起点
                                                       //aBossHpBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
    aBossHpBar->setBarChangeRate(Vec2::ANCHOR_BOTTOM_RIGHT);
    aBossHpBar->setPercentage(100);
    aBossHpBar->setPosition(465, 595);
    addChild(aBossHpBar);
}

void BM_ScoreAndControllerLayer::createTopPanel()
{
    auto pPauseItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("pause01.png"),
        Sprite::createWithSpriteFrameName("pause02.png"));
    auto pContinueItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("pause11.png"),
        Sprite::createWithSpriteFrameName("pause12.png"));
    //暂停继续切换；
    auto pPauseItemToggleItem = MenuItemToggle::createWithCallback([&](Ref* pSender)
    {
        auto pDirector = Director::getInstance()->getInstance();
        pDirector->isPaused() ? pDirector->resume() : pDirector->pause();
        auto pGameManager = GameManager::getInstance();
        pGameManager->setIsPause(!pGameManager->getIsPause());
    }, pPauseItem, pContinueItem, nullptr);
    pPauseItemToggleItem->setPosition(300, 275);

    auto pChooseItems = MenuItemSprite::create(Sprite::createWithSpriteFrameName("menu01.png"),
        Sprite::createWithSpriteFrameName("menu02.png"), [&](Ref* pSender)
    {
        this->clickChooseItem();
    });
    pChooseItems->setPosition(400, 275);
    _pChooseItem = pChooseItems;
    //菜单面板；
    auto pMenuPanel = Menu::create(pPauseItemToggleItem, pChooseItems, nullptr);
    addChild(pMenuPanel);
}

void BM_ScoreAndControllerLayer::createBottomPanel()
{
    //创建计数器面板背景
    auto aTimerPanelSp = Sprite::createWithSpriteFrameName("honor_0.png");
    aTimerPanelSp->setPosition(100, 40); //todo
    addChild(aTimerPanelSp, 100);

    _pHonorSp = Sprite::createWithSpriteFrameName("honor_3.png");
    addChild(_pHonorSp, 100);
    _pHonorSp->setPosition(160, 35);

    createNumSprite();
}

void BM_ScoreAndControllerLayer::registerNotifyEvent()
{
    NOTIFY->addObserver(this, callfuncO_selector(BM_ScoreAndControllerLayer::moneyChange), "moneyChange", nullptr);
}

void BM_ScoreAndControllerLayer::unRegisterNotifyEvent()
{
    NOTIFY->removeAllObservers(this);
}

void BM_ScoreAndControllerLayer::moneyChange(cocos2d::Ref* pData)
{
    setMoneyNum(*(reinterpret_cast<int*>(pData)));
}

void BM_ScoreAndControllerLayer::bossHpChanged(float dt)
{
    _iBossCurrHp = GameManager::getInstance()->getIBossHp();
    //_iBossCurrHp = (_iBossCurrHp > 0 ? _iBossCurrHp : 0);
    auto aPercentage = _iBossCurrHp * 1.0f / _iBossTotalHp * 100;
    (dynamic_cast<ProgressTimer*>(getChildByName("BossHpBar")))->setPercentage(aPercentage);
}

void BM_ScoreAndControllerLayer::timeChange(float dt)
{
    if (_iTimeLimit == 0)
        return;

    _iTimeLimit -= 1;
    GameManager::getInstance()->setICurrTime(_iTimeLimit);

    removeChildByName("TimerSp");
    createNumSprite(); //重构计时精灵

    if (_iTimeLimit == 0)
    {
        //游戏失败
        auto aGameType = en_GameLose;
        NOTIFICATION_CENTER->postNotification("gameEnd", reinterpret_cast<Ref*>(&aGameType));
    }
}

void BM_ScoreAndControllerLayer::setMoneyNum(const int& rIMoneyNum)
{
    auto tPos = _pMoneyLabel->getPosition();
    _pMoneyLabel->removeFromParent();
    _iMoney += rIMoneyNum;
    _pMoneyLabel = NumSprite::createNum(StringUtils::format("%d", _iMoney), MONEYNUMIMAGE);
    addChild(_pMoneyLabel);
    _pMoneyLabel->setPosition(tPos);
}

void BM_ScoreAndControllerLayer::loadData()
{
    //关卡初始金钱；
    _iMoney = LevelConfigUtil::getInstance()->getCurrentLevelInitialMoney();

    //todo 是否从0开始的
    int iThemeIndex = SceneManager::getInstance()->getCurrentPageIndex();
    int iLevelIndex = SceneManager::getInstance()->getCurrentLevelIndex();
    int iBossId = (iThemeIndex + 1) * (iLevelIndex - 12) + 1;

    _iTimeLimit = CsvUtil::getInstance()->getInt(iBossId, en_BossTime, BOSSCSVFILE);
    _iBossCurrHp = _iBossTotalHp = CsvUtil::getInstance()->getInt(iBossId, en_BossHp, BOSSCSVFILE);
    GameManager::getInstance()->setIBossHp(_iBossTotalHp);

    GameManager::getInstance()->setICurrTime(_iTimeLimit); //在游戏管理类更改时间
}

void BM_ScoreAndControllerLayer::setPauseFlagIsClose()
{
    _bIsOpenChooseMenu = false;
}

void BM_ScoreAndControllerLayer::onExit()
{
    Layer::onExit();
    unRegisterNotifyEvent();
}

void BM_ScoreAndControllerLayer::createNumSprite()
{
    //bug fixed 两位数和三位数的间隔处理方式不太一致
    if (_iTimeLimit % 99 == 0)
        _pTimeSp = NumSprite::createNum(StringUtils::format("%d", _iTimeLimit), "Themes/Items/numyellow-hd.png", 35);
    else
        _pTimeSp = NumSprite::createNum(StringUtils::format("%d", _iTimeLimit), "Themes/Items/numyellow-hd.png", 20);
    _pTimeSp->setName("TimerSp");
    _pTimeSp->setPosition(50, 35);
    addChild(_pTimeSp, 100);

    //add 再加上一个成就精灵
    if (_iTimeLimit == 9)
    {
        _pHonorSp->setSpriteFrame("honor_2.png");
        _pHonorSp->runAction(Sequence::create(JumpBy::create(0.5f, Vec2(0, 0), 60, 2), DelayTime::create(0.5f), JumpBy::create(0.5f, Vec2(0, 0), 60, 2), nullptr));
    }
    else if (_iTimeLimit == 5)
    {
        _pHonorSp->setSpriteFrame("honor_1.png");
        _pHonorSp->runAction(Sequence::create(JumpBy::create(0.5f, Vec2(0, 0), 60, 2), DelayTime::create(0.5f), JumpBy::create(0.5f, Vec2(0, 0), 60, 2), nullptr));
    }
}

void BM_ScoreAndControllerLayer::clickChooseItem()
{
    if (!_bIsOpenChooseMenu)
    {
        auto pPauseLayer = PauseLayer::create();
        pPauseLayer->setFuncFlagPauseLayerIsClose(CC_CALLBACK_0(BM_ScoreAndControllerLayer::setPauseFlagIsClose, this));
        this->addChild(pPauseLayer, 1);
        _bIsOpenChooseMenu = true;
    }
}
