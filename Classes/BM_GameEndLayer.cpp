//
//  BM_GameEndLayer.cpp
//  CarrotFantasy
//
//  Created by 陈建彰 on 18-4-16.
//
//

#include "BM_GameEndLayer.h"
#include "SharedMenu.h"
#include "LevelConfigUtil.h"
#include "NumSprite.h"
#include "SceneManager.h"
#include "GameManager.h"
#include "SoundUtil.h"

BM_GameEndLayer *BM_GameEndLayer::create(const GameEndType &rEnGameEndType)
{
    auto pBM_GameEndLayer = new BM_GameEndLayer();

    if (!pBM_GameEndLayer->init(rEnGameEndType))
        CC_SAFE_DELETE(pBM_GameEndLayer);

    return pBM_GameEndLayer;
}

bool BM_GameEndLayer::init(const GameEndType &rEnGameEndType)
{
    bool bRet = false;

    do
    {
        CC_BREAK_IF(!Layer::init());

        auto pBlackLayer = LayerColor::create(Color4B(0, 0, 0, 130));

        addChild(pBlackLayer);

        _enGameEndType = rEnGameEndType;

        createMenu();

        bRet = true;
    } while (0);

    return bRet;
}

void BM_GameEndLayer::saveLevelData()
{
    if (en_GameWin != _enGameEndType) return;

    auto tCurLevelIndex = SceneManager::getInstance()->getCurrentLevelIndex() + 1;
    auto tCurPageIndex = SceneManager::getInstance()->getCurrentPageIndex() + 1;

    //保存这个关卡的数据
    auto tLevelData = std::make_tuple(_iCarrotType, 0, tCurPageIndex, tCurLevelIndex); //bug fixed 第一个和第二个反了 
    NOTIFY->postNotification(LEVELDATACHANGE, reinterpret_cast<Ref*>(&tLevelData));

    /*if (tCurLevelIndex == 12)
    {
    ++tCurPageIndex;
    tCurLevelIndex = 0;
    }*/

    //下一个关卡解锁
    if (tCurLevelIndex == 16) return; //不要解锁下一个主题，因为解锁逻辑不是冒险模式的解锁逻辑

    auto tNextLevelData = std::make_tuple(LEVEL_UNLOCK_BUT_NO_PASS, 0, tCurPageIndex, tCurLevelIndex + 1); //bug fixed 第一个和第二个反了 
    NOTIFY->postNotification(LEVELDATACHANGE, reinterpret_cast<Ref*>(&tNextLevelData));
}


void BM_GameEndLayer::createMenu()
{
    auto pBg = Sprite::createWithSpriteFrameName(std::get<0>(BM_GAMEENDSOURCE[_enGameEndType]));
    pBg->setPosition(Vec2(VisibleRectUtil::center()));
    addChild(pBg);

    auto pTitle = Sprite::createWithSpriteFrameName(BM_GAMEENDTITLE[_enGameEndType]);
    addChild(pTitle);
    pTitle->setPosition(Vec2(VisibleRectUtil::center()));

    auto pChooseLevelItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName(CHOOSESOURCE[0]), Sprite::createWithSpriteFrameName(CHOOSESOURCE[1]), [](Ref *pSender)
    {
        auto enBossModeSelectScene = std::make_tuple(en_BossModeScene, SceneManager::getInstance()->getCurrentPageIndex());
        NOTIFY->postNotification("changeScene", reinterpret_cast<Ref *>(&enBossModeSelectScene));
    });
    pChooseLevelItem->setPosition(Vec2(-120, -100));

    auto pAgainItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName(std::get<1>(GAMEENDSOURCE[_enGameEndType])), Sprite::createWithSpriteFrameName(std::get<2>(GAMEENDSOURCE[_enGameEndType])), [&](Ref *pSender)
    {
        auto tCurLevelIndex = SceneManager::getInstance()->getCurrentLevelIndex();
        std::tuple<SceneType, int> tEnGameScene;
        if (en_GameLose == _enGameEndType) tEnGameScene = std::make_tuple(en_GameScene, tCurLevelIndex);
        else tEnGameScene = std::make_tuple(en_GameScene, tCurLevelIndex + 1);
        NOTIFY->postNotification("changeScene", reinterpret_cast<Ref *>(&tEnGameScene));
    });
    pAgainItem->setPosition(Vec2(120, -100));

    auto pMenu = Menu::create(pChooseLevelItem, pAgainItem, nullptr);
    //pMenu->setAnchorPoint(Vec2::ZERO);
    addChild(pMenu);

    addChild(SharedMenu::create());
}

void BM_GameEndLayer::loadInfo()
{

    //还有多少时间
    //只有赢了才显示
    if (_enGameEndType == en_GameWin)
    {
        auto aCurTimeNode = NumSprite::createNum(StringUtils::format("%02d", GameManager::getInstance()->getICurrTime()), MONSTERBATCHIMAGE);
        aCurTimeNode->setPosition(Vec2(465, 350));
        addChild(aCurTimeNode);
    }
    //当前关卡BOSS名字
    //todo 是否从0开始的
    int iThemeIndex = SceneManager::getInstance()->getCurrentPageIndex();
    int iLevelIndex = SceneManager::getInstance()->getCurrentLevelIndex();
    int iBossId = (iThemeIndex + 1) * (iLevelIndex - 12) + 1;

    auto aCurBossNameNode = Sprite::createWithSpriteFrameName(StringUtils::format("names_%02d", iBossId) + PHOTOPOSTFIX);
    aCurBossNameNode->setPosition(Vec2(480, 290));
    addChild(aCurBossNameNode);

    checkCarrotType();
}

void BM_GameEndLayer::checkCarrotType()
{
    auto aRemainingTime = GameManager::getInstance()->getICurrTime();

    if (aRemainingTime >= GOLDCARROTTIME)
    {
        _sCarrotType = "ss_gainhonor_3.png"; //bug fixed BOSS模式下的成就不是显示萝卜了，是显示KO，下同
        _iCarrotType = 4;
    }

    else if (aRemainingTime <= SILVERCARROTTIME1 && aRemainingTime >= SILVERCARROTTIME2)
    {
        _sCarrotType = "ss_gainhonor_2.png";
        _iCarrotType = 3;
    }
    else if (aRemainingTime > 0)
    {
        _sCarrotType = "ss_gainhonor_1.png";
        _iCarrotType = 2;
    }

    if (!_sCarrotType.empty())
    {
        //        auto pGameWinParticle = ParticleSystemQuad::create("loading/test.plist");
        //        auto pBatch = ParticleBatchNode::createWithTexture(pGameWinParticle->getTexture());
        //        pBatch->addChild(pGameWinParticle);
        //        addChild(pBatch, 19);

        auto pCarrotMedal = Sprite::createWithSpriteFrameName(_sCarrotType);
        pCarrotMedal->setPosition(485, 455);
        addChild(pCarrotMedal, 20);
    }

}

void BM_GameEndLayer::onExit()
{
    Director::getInstance()->resume();
    Layer::onExit();
}

void BM_GameEndLayer::onEnter()
{
    Layer::onEnter();
    registerNoTouch();
    loadInfo();

    saveLevelData();

    /******************************************************************/
    /****************************游戏管理类的操作************************/
    /******************************************************************/
    GameManager::getInstance()->setIsWin((_enGameEndType == en_GameWin));
    GameManager::getInstance()->updateUserStatistics(); //及时保存文件

    Director::getInstance()->pause();
    playGameEndSound();
}

void BM_GameEndLayer::playGameEndSound()
{
    if (en_GameLose == _enGameEndType) SoundUtil::getInstance()->playEffectSound(GAMELOSE);
    else SoundUtil::getInstance()->playEffectSound(GAMEWIN);
}

void BM_GameEndLayer::registerNoTouch()
{
    auto pListener = EventListenerTouchOneByOne::create();

    pListener->setSwallowTouches(true); //设置吞没事件
    pListener->onTouchBegan = [](Touch *pTouch, Event *pEvent) {return true; };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(pListener, this);
}



