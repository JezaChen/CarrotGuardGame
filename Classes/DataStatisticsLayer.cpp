//
// Created by jeza on 18-4-11.
//

#include "DataStatisticsLayer.h"
#include "LocalLevelDataUtil.h"
#include "NumSprite.h"

bool DataStatLayer::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!Layer::init());

        loadData(); //º”‘ÿ ˝æ›
        createBg(); //º”‘ÿ±≥æ∞
        createNumSprite(); //º”‘ÿ ˝◊÷æ´¡È

        bRet = true;
    }
    while (0);

    return bRet;
}

void DataStatLayer::createBg()
{
    auto aBg = Sprite::createWithSpriteFrameName("statistics_bg.png");
    addChild(aBg);

    auto aText = Sprite::createWithSpriteFrameName("statistics_bg_CN.png");
    addChild(aText);
}

void DataStatLayer::loadData()
{
    auto dataMap = LocalLevelDataUtil::getInstance()->getLevelData();
    _iAdventureModeClearance = dataMap.at(USER_STATISTICS[en_Stat_Adventure]).asInt();
    _iCrypticModeClearance = dataMap.at(USER_STATISTICS[en_Stat_Cryptic]).asInt();
    _iBossModeClearance = dataMap.at(USER_STATISTICS[en_Stat_BossMode]).asInt();
    _iTotalMoney = dataMap.at(USER_STATISTICS[en_Stat_Money]).asInt();
    _iTotalBarriers = dataMap.at(USER_STATISTICS[en_Stat_BarrierClear]).asInt();
    _iTotalMonster = dataMap.at(USER_STATISTICS[en_Stat_MonsterAttack]).asInt();
    _iTotalBoss = dataMap.at(USER_STATISTICS[en_Stat_BossAttack]).asInt();
}

void DataStatLayer::createNumSprite()
{
    std::string sAdventureModeClearance = StringUtils::format("%d", _iAdventureModeClearance);
    auto AdventureModeClearanceSp = NumSprite::createNum(sAdventureModeClearance, MONEYNUMIMAGE, 35);
    AdventureModeClearanceSp->setPosition(245 - 25 * sAdventureModeClearance.size(), 115);
    AdventureModeClearanceSp->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT); //”“∂‘∆Î∞…
    addChild(AdventureModeClearanceSp);

    std::string sCrypticModeClearance = StringUtils::format("%d", _iCrypticModeClearance);
    auto CrypticModeClearanceSp = NumSprite::createNum(sCrypticModeClearance, 
                                                       MONEYNUMIMAGE, 35);
    CrypticModeClearanceSp->setPosition(245 - 25 * sCrypticModeClearance.size(), 55);
    CrypticModeClearanceSp->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT); //”“∂‘∆Î∞…
    addChild(CrypticModeClearanceSp);

    std::string sBossModeClearance = StringUtils::format("%d", _iBossModeClearance);
    auto BossModeClearanceSp = NumSprite::createNum(sBossModeClearance,
                                                    MONEYNUMIMAGE, 35);
    BossModeClearanceSp->setPosition(245 - 25 * sBossModeClearance.size(), 0);
    BossModeClearanceSp->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT); //”“∂‘∆Î∞…
    addChild(BossModeClearanceSp);

    std::string sTotalMoney = StringUtils::format("%d", _iTotalMoney);
    auto TotalMoneySp = NumSprite::createNum(sTotalMoney,
                                             MONEYNUMIMAGE, 35);
    TotalMoneySp->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT); //”“∂‘∆Î∞…
    TotalMoneySp->setPosition(320 - 25 * sTotalMoney.size(), -60);
    addChild(TotalMoneySp);

    std::string sTotalMonster = StringUtils::format("%d", _iTotalMonster);
    auto TotalMonsterSp = NumSprite::createNum(sTotalMonster,
                                               MONEYNUMIMAGE, 35);
    TotalMonsterSp->setPosition(320 - 25 * sTotalMonster.size(), -115);
    TotalMonsterSp->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT); //”“∂‘∆Î∞…
    addChild(TotalMonsterSp);

    std::string sTotalBoss = StringUtils::format("%d", _iTotalBoss);
    auto TotalBossSp = NumSprite::createNum(sTotalBoss,
                                            MONEYNUMIMAGE, 35);
    TotalBossSp->setPosition(320 - 25 * sTotalBoss.size(), -170);
    TotalBossSp->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT); //”“∂‘∆Î∞…
    addChild(TotalBossSp);

    std::string sTotalBarriers = StringUtils::format("%d", _iTotalBarriers);
    auto TotalBarrierSp = NumSprite::createNum(sTotalBarriers,
                                               MONEYNUMIMAGE, 35);
    TotalBarrierSp->setPosition(320 - 25 * sTotalBarriers.size(), -230);
    TotalBarrierSp->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT); //”“∂‘∆Î∞…
    addChild(TotalBarrierSp);
}
