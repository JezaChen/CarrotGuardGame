//
//  GameEndLayer.cpp
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-16.
//
//

#include "GameEndLayer.h"
#include "SharedMenu.h"
#include "LevelConfigUtil.h"
#include "NumSprite.h"
#include "SceneManager.h"
#include "GameManager.h"
#include "SoundUtil.h"
#include "LocalLevelDataUtil.h"
#include "MapUtil.h"

GameEndLayer *GameEndLayer::create(const GameEndType &rEnGameEndType)
{
	auto pGameEndLayer = new GameEndLayer();

	if (!(pGameEndLayer && pGameEndLayer->init(rEnGameEndType))) CC_SAFE_DELETE(pGameEndLayer);

	return pGameEndLayer;
}

bool GameEndLayer::init(const GameEndType &rEnGameEndType)
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

void GameEndLayer::saveLevelData()
{
	if (en_GameWin != _enGameEndType) return;

	auto tCurLevelIndex = SceneManager::getInstance()->getCurrentLevelIndex() + 1;

	auto tCurPageIndex = SceneManager::getInstance()->getCurrentPageIndex() + 1;

	auto tLevelData = std::make_tuple(_iCarrotType, 0, tCurPageIndex, tCurLevelIndex);//bug fixed  顺序反了
	NOTIFY->postNotification(LEVELDATACHANGE, reinterpret_cast<Ref*>(&tLevelData));

	if (tCurLevelIndex == 12)
	{
		++tCurPageIndex;
		tCurLevelIndex = 0;
	}

	auto tNextLevelData = std::make_tuple(1, 0, tCurPageIndex, tCurLevelIndex + 1);
	NOTIFY->postNotification(LEVELDATACHANGE, reinterpret_cast<Ref*>(&tNextLevelData));

    //bug fixed 游戏通关历史数据更新应该放在关卡通关数据后面 
    GameManager::getInstance()->setIsWin((_enGameEndType == en_GameWin));
    GameManager::getInstance()->updateUserStatistics(); //及时保存文件
}


void GameEndLayer::createMenu()
{
	auto pBg = Sprite::createWithSpriteFrameName(std::get<0>(GAMEENDSOURCE[_enGameEndType]));
	pBg->setPosition(Vec2(VisibleRectUtil::center()));
	addChild(pBg);

	auto pTitle = Sprite::createWithSpriteFrameName(GAMEENDTITLE);
	addChild(pTitle);
	pTitle->setPosition(Vec2(VisibleRectUtil::center()));

	auto pChooseLevelItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName(CHOOSESOURCE[0]), Sprite::createWithSpriteFrameName(CHOOSESOURCE[1]), [](Ref *pSender)
	{
		auto enLevelSelectScene = std::make_tuple(en_LevelSelectScene, SceneManager::getInstance()->getCurrentPageIndex());
		NOTIFY->postNotification("changeScene", reinterpret_cast<Ref *>(&enLevelSelectScene));
	});
	pChooseLevelItem->setPosition(Vec2(-120, -100));

	auto pAgainItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName(std::get<1>(GAMEENDSOURCE[_enGameEndType])), Sprite::createWithSpriteFrameName(std::get<2>(BM_GAMEENDSOURCE[_enGameEndType])), [&](Ref *pSender)
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

void GameEndLayer::loadInfo()
{
    //当前关卡有多少波怪
	auto pMonsterBatchNode = NumSprite::createNum(StringUtils::format("%02d", LevelConfigUtil::getInstance()->getCurrentMonsterBatchCount()), MONEYNUMIMAGE);
	pMonsterBatchNode->setPosition(Vec2(563, 350));
	addChild(pMonsterBatchNode);

	auto tMonsterBatchCount = GameManager::getInstance()->getIMonsterBatch();
	if (en_GameLose == _enGameEndType) --tMonsterBatchCount;

    //杀了多少波怪
	auto pCurMonsterBatchNode = NumSprite::createNum(StringUtils::format("%02d", tMonsterBatchCount), MONSTERBATCHIMAGE);
	pCurMonsterBatchNode->setPosition(Vec2(465, 350));
	addChild(pCurMonsterBatchNode);

    //当前关卡序号
	auto pCurLevelNode = NumSprite::createNum(StringUtils::format("%02d", SceneManager::getInstance()->getCurrentLevelIndex() + 1), LITTLENUMIMAGE);
	pCurLevelNode->setPosition(Vec2(415, 290));
	addChild(pCurLevelNode);

	checkCarrotType();
}

void GameEndLayer::checkCarrotType()
{
	auto tCarrotHp = GameManager::getInstance()->getICarrotHp();

	if (GOLDCARROTHP == tCarrotHp)
	{
		_sCarrotType = GOLDCARROT;
		_iCarrotType = 4;
	}

	if (tCarrotHp > SILVERCARROTHP1 && tCarrotHp <= SILVERCARROTHP2)
	{
		_sCarrotType = SILVERCARROT;
		_iCarrotType = 3;
	}
	if (tCarrotHp > 0 && tCarrotHp <= SILVERCARROTHP1)
	{
		_sCarrotType = NORMALCARROT;
		_iCarrotType = 2;
	}

	if (_sCarrotType.size())
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

void GameEndLayer::onExit()
{
	Director::getInstance()->resume();
	Layer::onExit();
}

void GameEndLayer::onEnter()
{
	Layer::onEnter();
	registerNoTouch();
	loadInfo();
	saveLevelData();
	Director::getInstance()->pause();
	playGameEndSound();
}

void GameEndLayer::playGameEndSound()
{
	if (en_GameLose == _enGameEndType) SoundUtil::getInstance()->playEffectSound(GAMELOSE);
	else SoundUtil::getInstance()->playEffectSound(GAMEWIN);
}

void GameEndLayer::registerNoTouch()
{
	auto pListener = EventListenerTouchOneByOne::create();

	pListener->setSwallowTouches(true); //设置吞没事件
	pListener->onTouchBegan = [](Touch *pTouch, Event *pEvent) {return true;};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(pListener, this);
}



