#include "BossModeLevelSelectLayer.h"
#include "ui/CocosGUI.h"
#include "LocalLevelDataUtil.h"
#include "SceneManager.h"

using namespace ui;

BossModeLevelSelectLayer::~BossModeLevelSelectLayer()
{
    removeAllChildren();
    CC_SAFE_RELEASE_NULL(_pBossDetailsSprite);
    CC_SAFE_RELEASE_NULL(_pLockedBtn);
    CC_SAFE_RELEASE_NULL(_pStartBtn);
}

bool BossModeLevelSelectLayer::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!Layer::init());
        _pBossDetailsSprite = Sprite::create();
        loadData();
        loadSource();
        bRet = true;
    }
    while (0);
    return bRet;
}

void BossModeLevelSelectLayer::loadSource()
{
    //创建主背景
    auto aBackground = Sprite::createWithSpriteFrameName("boss_theme_bg.png");
    aBackground->setPosition(VisibleRectUtil::center());
    addChild(aBackground);

    //创建标题
    auto aTitle = Label::createWithSystemFont(TITLE_BOSS_MODE, "Microsoft YaHei UI", 30);
    aTitle->setPosition(475, 609);
    addChild(aTitle);

    //创建灯光
    if (_pCheckLockedMap->at(1))
    {
        auto aLight = Sprite::createWithSpriteFrameName("light.png");
        aLight->setPosition(480, 430);
        //addChild(aLight);
        _pBossDetailsSprite->addChild(aLight);
    }


    //一开始就显示第一个
    //默认展示第一个怪的信息
    Sprite* bossNameSp = Sprite::createWithSpriteFrameName("name_01_normal.png");
    bossNameSp->setPosition(Vec2(480, 490));
    _pBossDetailsSprite->addChild(bossNameSp);

    Sprite* bossHpSp = Sprite::createWithSpriteFrameName("blood_80000.png");
    bossHpSp->setPosition(Vec2(480, 130));
    _pBossDetailsSprite->addChild(bossHpSp, 10);

    Sprite* bossHpBg = Sprite::createWithSpriteFrameName("blood_bg.png");
    bossHpBg->setPosition(Vec2(480, 130));
    _pBossDetailsSprite->addChild(bossHpBg);

    Sprite* bossTime = Sprite::createWithSpriteFrameName("timelimit_90_CN.png");
    bossTime->setPosition(Vec2(350, 55));
    bossTime->setScale(0.93);
    _pBossDetailsSprite->addChild(bossTime);

    addChild(_pBossDetailsSprite);

    loadBossLevelButton();
    loadMenuItem();
}

void BossModeLevelSelectLayer::loadBossLevelButton()
{
    //记得有16个大BOSS啊
    auto aPageView = PageView::create();
    addChild(aPageView);
    aPageView->setContentSize(Size(960.0f, 640.0f));
    Size contentSize = this->getContentSize();

    for (int i = 0; i < 16; i++)
    {
        std::string bossImgPath = "boss_" + StringUtils::format("%02d", i + 1) + "_";
        Layout* pLayout = Layout::create();

        //TODO 怪物有两种状态：锁和没有被锁，这个依据玩家的数据而定
        //TODO 因而数据那块也要补

        int iTheme = i / 4 + 1; //获取这个BOSS对应的主题
        //检查是否被锁了
        if (!_pCheckLockedMap->at(iTheme))
            bossImgPath += "locked" + PHOTOPOSTFIX;
        else
            bossImgPath += "normal" + PHOTOPOSTFIX;

        auto gameButton = Button::create(bossImgPath, bossImgPath, bossImgPath, TextureResType::PLIST);
        gameButton->setPosition(Vec2(contentSize.width / 2, contentSize.height / 2));
        gameButton->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType event)
        {
            if (event == Widget::TouchEventType::ENDED)
            {
                this->changeToGameScene();
            }
        });

        pLayout->addChild(gameButton);

        aPageView->insertPage(pLayout, i);
    }

    aPageView->setPassFocusToChild(true);
    aPageView->scrollToPage(_iCurLevelIndex); //滚动到第一个页面
    aPageView->addEventListener([=](Ref* pSender, PageView::EventType event)
    {
        if (event == PageView::EventType::TURNING)
        {
            _iCurLevelIndex = aPageView->getCurrentPageIndex();
            _pBossDetailsSprite->removeAllChildrenWithCleanup(true);

            //根据Boss状态刷新灯光状态
            if (_pCheckLockedMap->at(_iCurLevelIndex / 4 + 1))
            {
                auto aLight = Sprite::createWithSpriteFrameName("light.png");
                aLight->setPosition(480, 430);
                //addChild(aLight);
                _pBossDetailsSprite->addChild(aLight);
            }

            //更新开始按钮状态
            _pStartBtn->setVisible(_pCheckLockedMap->at(_iCurLevelIndex / 4 + 1));
            _pLockedBtn->setVisible(!_pStartBtn->isVisible());

            //刷新Boss详细信息
            Sprite* bossNameSp = Sprite::createWithSpriteFrameName(
                StringUtils::format("name_%02d_normal.png", _iCurLevelIndex + 1));
            bossNameSp->setPosition(Vec2(480, 490));
            _pBossDetailsSprite->addChild(bossNameSp);

            int currBossHp = CsvUtil::getInstance()->getInt(_iCurLevelIndex + 1, en_BossHp, BOSSCSVFILE);
            Sprite* bossHpSp = Sprite::createWithSpriteFrameName(StringUtils::format("blood_%d.png", currBossHp));
            bossHpSp->setPosition(Vec2(480, 130));
            _pBossDetailsSprite->addChild(bossHpSp, 10);

            Sprite* bossHpBg = Sprite::createWithSpriteFrameName("blood_bg.png");
            bossHpBg->setPosition(Vec2(480, 130));
            _pBossDetailsSprite->addChild(bossHpBg);

            int currBossTime = CsvUtil::getInstance()->getInt(_iCurLevelIndex + 1, en_BossTime, BOSSCSVFILE);
            Sprite* bossTime = Sprite::createWithSpriteFrameName(
                StringUtils::format("timelimit_%d_CN.png", currBossTime));
            bossTime->setScale(0.93);
            bossTime->setPosition(Vec2(350, 55));
            _pBossDetailsSprite->addChild(bossTime);
        }
    });

    //addChild(aPageView, 3);
}

void BossModeLevelSelectLayer::loadMenuItem()
{
    //创建返回主页按钮
    auto aHomeBtn = MenuItemSprite::create(Sprite::createWithSpriteFrameName("theme_home_normal.png"),
                                           Sprite::createWithSpriteFrameName("theme_home_pressed.png"),
                                           [&](Ref* pSender)
                                           {
                                               auto enWelcomeScene = std::make_tuple(en_WelcomeScene, 0);
                                               NOTIFICATION_CENTER->postNotification("changeScene",
                                                                                     reinterpret_cast<Ref *>(&
                                                                                         enWelcomeScene));
                                           });
    aHomeBtn->setPosition(-445, 290);

    //创建帮助按钮
    auto aHelpBtn = MenuItemSprite::create(Sprite::createWithSpriteFrameName("ss_help_normal.png"),
                                           Sprite::createWithSpriteFrameName("ss_help_pressed.png"), [&](Ref* pSender)
                                           {
                                               auto enHelpScene = std::make_tuple(en_GameHelpScene, 0);
                                               NOTIFICATION_CENTER->postNotification("changeScene",
                                                                                     reinterpret_cast<Ref *>(&
                                                                                         enHelpScene));
                                           });
    aHelpBtn->setPosition(450, 290);
    aHelpBtn->setScale(1.4);

    //创建开始按钮
    _pStartBtn = MenuItemSprite::create(Sprite::createWithSpriteFrameName("theme_play_normal_CN.png"),
                                        Sprite::createWithSpriteFrameName("theme_play_pressed_CN.png"),
                                        [&](Ref* pSender)
                                        {
                                            this->changeToGameScene();
                                        });
    _pStartBtn->setPosition(Vec2(130, -265));
    _pStartBtn->setScale(0.9);
    addChild(Menu::create(aHomeBtn, aHelpBtn, _pStartBtn, nullptr));
    _pCheckLockedMap->at(1) ? _pStartBtn->setVisible(true) : _pStartBtn->setVisible(false); //一开始看下开始按钮是否有效

    //创建锁住按钮
    _pLockedBtn = Sprite::createWithSpriteFrameName("theme_locked_CN.png");
    _pLockedBtn->setPosition(Vec2(610, 55));
    addChild(_pLockedBtn, 1);
    _pLockedBtn->setVisible(!_pStartBtn->isVisible());
}

std::tuple<int, bool> BossModeLevelSelectLayer::getLevelData(const int& riIndex)
{
    int iCurThemeIndex = riIndex / 4; //主题号
    int iActualLevelIndex = riIndex % 4 + 12; //实际的关卡号

    //获取该关卡的value值
    auto aKey = StringUtils::format(LEVELKEY, iCurThemeIndex + 1, iActualLevelIndex + 1);
    int iValue = _DataValueMap[aKey].asInt();

    //提取相应的数据
    int iCarrotType = iValue / 10;
    bool iBarriersAllCleaned = iValue % 10 != 0;

    //返回元祖
    return std::make_tuple(iCarrotType, iBarriersAllCleaned);
}

void BossModeLevelSelectLayer::changeToGameScene()
{
    int iCurThemeIndex = _iCurLevelIndex / 4; //主题号
    int iActualLevelIndex = _iCurLevelIndex % 4 + 12; //实际的关卡号

    SceneManager::getInstance()->setCurrentPageIndex(iCurThemeIndex);

    if (std::get<0>(getLevelData(_iCurLevelIndex)) == LEVEL_LOCK)
        return;

    auto enGameScene = std::make_tuple(en_GameScene, iActualLevelIndex);
    NOTIFICATION_CENTER->postNotification("changeScene", reinterpret_cast<Ref *>(&enGameScene));
}

void BossModeLevelSelectLayer::loadData()
{
    //TODO 这个用于读取该怪物锁不锁住的
    //TODO 需要文件那块弄好了才行
    _DataValueMap = LocalLevelDataUtil::getInstance()->getLevelData();
    checkThemeUnlocked();
}

//TODO 即将废弃
void BossModeLevelSelectLayer::checkThemeUnlocked()
{
    auto aValueMap = LocalLevelDataUtil::getInstance()->getLevelData();

    _pCheckLockedMap = new std::map<int, bool>();
    //初始化主题通关哈希表
    for (int i = 1; i <= 4; i++)
        _pCheckLockedMap->insert(std::make_pair(i, false));


    //TODO 目前只支持三个主题
    //逐个主题来检测
    for (int iTheme = 1; iTheme <= 3; iTheme++)
    {
        //每个主题用第八个关卡通关情况就可以了
        std::string sKey = StringUtils::format(LEVELKEY, iTheme, 8);
        int iValue = aValueMap[sKey].asInt();
        bool bIsLevelPast = iValue / 10 > 1;
        if (!bIsLevelPast)
            break;
        _pCheckLockedMap->at(iTheme) = true; //如果第八关通过了，意味这个主题的大Boss都被解锁了
    }
}
