//
// Created by jeza on 18-4-14.
//

#include "MonsterBuilder.h"
#include "SoundUtil.h"
#include "MonsterManager.h"
#include "MonsterFactory.h"
#include "GameManager.h"
#include "MonsterBase.h"
#include "LevelConfigUtil.h"
#include "MapUtil.h"

bool MonsterBuilder::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!Node::init());

        _fDelayTime = DELAY_TIME; //TODO 优化？
        _iNumber = 0;
        _iCurrBatch = 0;
        _iMonsterCountsInCurrBatch = 0;
        _iMonsterBatch = 0;

        createCMonsterAnimation(); //bug fixed

        GameManager::getInstance()->setIMonsterBatch(_iMonsterBatch);

        _iMonsterBatch = LevelConfigUtil::getInstance()->getCurrentMonsterBatchCount(); //获取当前关卡怪物的波数

        this->setPosition(MapUtil::getInstance()->getMovePoses().at(0) + Vec2(40, -15));

        bRet = true; //bug fixed
    }while (0);
    return bRet;
}

void MonsterBuilder::onEnter()
{
    Node::onEnter();
    schedule(schedule_selector(MonsterBuilder::createMonsters), 1.5, 20001, 3);
}

void MonsterBuilder::createMonsters(float t)
{
    if (_iMonsterCountsInCurrBatch == 0 && _fDelayTime >= DELAY_TIME)
    {
        //需要刷新波数
        _iCurrBatch++;
        NOTIFICATION_CENTER->postNotification("monsterBatchChange", (Ref *)&(_iCurrBatch)); //发送一个通知
        GameManager::getInstance()->setIMonsterBatch(_iCurrBatch);
    }

    if(_iCurrBatch == _iMonsterBatch) //最后一波
    {
        SoundUtil::getInstance()->playEffectSound(FINALWAVE);
        this->unschedule(schedule_selector(MonsterBuilder::createMonsters)); //去除调度器
        NOTIFICATION_CENTER->postNotification("openCheckGameWin");
    }
    //当延迟时间小于生成下一波怪物的延迟时间且当前波的怪物全部被清空了，延迟时间继续增加
    //第二个条件是因为只有该波怪物全部消掉了才能准备生成下一波怪物
    if(_fDelayTime < DELAY_TIME && MonsterManager::getInstance()->getMonsterVec().size() == 0)
        _fDelayTime += t;
    else if (_fDelayTime >= DELAY_TIME)
    {
        monsterFactoryControl(); //生成一个怪物
        _iMonsterCountsInCurrBatch++;
        if(_iMonsterCountsInCurrBatch == 10) //当前波生成怪物的数目等于十个了
        {
            _iMonsterCountsInCurrBatch = 0;
            _fDelayTime = 0; //延迟时间也要更新
        }
    }
}

//TODO 游戏逻辑还是太简单了
void MonsterBuilder::monsterFactoryControl()
{
    /*SoundUtil::getInstance()->playEffectSound(BUILDMONSTER);
    int number = 10 - (_iCurrBatch - 1) * 2;
    if(_iNumber == 10) _iNumber = 0; //当_iNumber等于10了，意味着波数已经刷新了
    MonsterBase* pMonster = nullptr;
    if ((_iCurrBatch == _iMonsterBatch || _iCurrBatch % 10 == 0) && _iNumber == 5)
        pMonster = MonsterFactory::createMonster(en_Boss_Big);
    else
    {
        if (_iNumber < number)
            pMonster = MonsterFactory::createMonster(MonsterType(1 + int(_iCurrBatch / 5)));
        else
            pMonster = MonsterFactory::createMonster(MonsterType(4 + int(_iCurrBatch / 5)));
    }
    pMonster->setIHp(pMonster->getIHp() + (_iCurrBatch - 1) / 5 * pMonster->getIHp()); //随着波数的增加，怪物的血越来越厚
    pMonster->setMaxSpeed(pMonster->getISpeed() + int(_iCurrBatch / 5) * 10);
    pMonster->getSprite()->runAction(Animate::create(_createMonsterAnimation)); //怪物精灵显示生成动画*/

    SoundUtil::getInstance()->playEffectSound(BUILDMONSTER);
    if (_iNumber == 10)_iNumber = 0;
    int number = 10 - (_iCurrBatch - 1) * 2;
    MonsterBase * pMonster;
    if (_iCurrBatch == _iMonsterBatch && _iNumber == 5)
    {
        pMonster = MonsterFactory::createMonster(en_Boss_Big);
    }
    else
    {
        if (_iNumber < number)
        {
            pMonster = MonsterFactory::createMonster(MonsterType(1 + int(_iCurrBatch / 5)));
        }
        else
        {
            pMonster = MonsterFactory::createMonster(MonsterType(4 + int(_iCurrBatch / 5)));
        }
    }
    pMonster->setIHp(pMonster->getIHp() + (_iCurrBatch - 1) / 5 * pMonster->getIHp());
    pMonster->setMaxSpeed(pMonster->getISpeed() + int(_iCurrBatch / 5) * 10);
    pMonster->getSprite()->runAction(Animate::create(_createMonsterAnimation));
    _iNumber++;
}

int MonsterBuilder::getCurrBatch()
{
    return _iCurrBatch;
}

MonsterBuilder::~MonsterBuilder()
{
    CC_SAFE_RELEASE_NULL(_createMonsterAnimation);
}

void MonsterBuilder::createCMonsterAnimation()
{
    _createMonsterAnimation = Animation::create();
    _createMonsterAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("mcm01.png"));
    _createMonsterAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("mcm02.png"));
    _createMonsterAnimation->setDelayPerUnit(0.15f); //两个帧的间隔
    _createMonsterAnimation->setLoops(1); //只播放一次就可以了
    _createMonsterAnimation->retain();
}
