//
//  GameManager.cpp
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-8.
//
//

#include "GameManager.h"

GameManager* GameManager::_gInstance;


void GameManager::updateIncreasedMoney(Ref* pData)
{
    int increasedMoney = *(reinterpret_cast<int*>(pData));
    if (increasedMoney < 0) //少钱了就不用添加了!
        return; 
    _iIncreasedMoney += increasedMoney;
}

void GameManager::addOneEliminatedMonster(Ref* pData)
{
    _iEliminatedMonster++;
}

void GameManager::addOneEliminatedBoss(Ref* pData)
{
    _iEliminatedBoss++;
}

void GameManager::addOneClearedBarrier(Ref* pData)
{
    _iClearedBarriers++;
}


void GameManager::updateUserStatistics()
{
    auto* postVec = new std::vector<std::tuple<StatisticType, int>>();
    if (_gmCurrGameType == en_Adventure)
    {
        postVec->push_back(std::make_tuple(en_Stat_Adventure, 1));
    }
    else
    {
        postVec->push_back(std::make_tuple(en_Stat_BossMode, 1));
    }

    //增加的金钱
    postVec->push_back(std::make_tuple(en_Stat_Money, _iIncreasedMoney));
    //消灭的怪物
    postVec->push_back(std::make_tuple(en_Stat_MonsterAttack, _iEliminatedMonster));
    //消灭的BOSS
    postVec->push_back(std::make_tuple(en_Stat_BossAttack, _iEliminatedBoss));
    //清除的障碍物 
    postVec->push_back(std::make_tuple(en_Stat_BarrierClear, _iClearedBarriers));

    NOTIFICATION_CENTER->postNotification(STATDATACHANGE, reinterpret_cast<Ref*>(postVec));


    //赋空
    _gmCurrGameType = en_Adventure;
    _bIsWin = false;
    _iIncreasedMoney = _iClearedBarriers = _iEliminatedBoss = _iEliminatedMonster = 0;
}

bool GameManager::init()
{
    _bIsPause = _bIsWin = false;
    _iTime = _iIncreasedMoney = _iClearedBarriers = _iEliminatedBoss = _iEliminatedMonster = _iBossHp = 0;
    _gmCurrGameType = en_Adventure; //默认为冒险模式

    addObserver(); //记得要添加监听器
    return true;
}

void GameManager::addObserver()
{
    //注册金钱增加事件监听
    NOTIFICATION_CENTER->addObserver(this, callfuncO_selector(GameManager::updateIncreasedMoney), "moneyChange",
                                     nullptr);
    //注册障碍物消除事件监听
    NOTIFICATION_CENTER->addObserver(this, callfuncO_selector(GameManager::addOneClearedBarrier), "BarrierDead",
                                     nullptr);
    //注册BOSS消灭事件监听
    NOTIFICATION_CENTER->addObserver(this, callfuncO_selector(GameManager::addOneEliminatedBoss), "BossDead", nullptr);
    //注册怪物消灭事件监听
    NOTIFICATION_CENTER->addObserver(this, callfuncO_selector(GameManager::addOneEliminatedMonster), "MonsterDead",
                                     nullptr);
}

GameManager::~GameManager()
{
    NOTIFICATION_CENTER->removeAllObservers(this);
}
