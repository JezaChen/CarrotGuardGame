//
// Created by jeza on 18-4-14.
//

#include "BM_MonsterBuilder.h"
#include "SoundUtil.h"
#include "MonsterManager.h"
#include "MonsterFactory.h"
#include "GameManager.h"
#include "MonsterBase.h"
#include "LevelConfigUtil.h"
#include "MapUtil.h"
#include "SceneManager.h"

bool BM_MonsterBuilder::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!Node::init());

        _fDelayTime = DELAY_TIME; //TODO �Ż���
        _iTotalNumber = 21; //暂定出21个怪物
        _iCurrNumber = 1;

        loadData();

        createCMonsterAnimation(); //bug fixed

        //GameManager::getInstance()->setIMonsterBatch(_iMonsterBatch);

        //_iMonsterBatch = LevelConfigUtil::getInstance()->getCurrentMonsterBatchCount(); //��ȡ��ǰ�ؿ�����Ĳ���

        this->setPosition(MapUtil::getInstance()->getMovePoses().at(0) + Vec2(40, -15));

        bRet = true; //bug fixed
    }
    while (0);
    return bRet;
}

void BM_MonsterBuilder::onEnter()
{
    Node::onEnter();
    schedule(schedule_selector(BM_MonsterBuilder::createMonsters), 1.5, 20001, 3);
}

void BM_MonsterBuilder::createMonsters(float t)
{
    if (_iCurrNumber == _iTotalNumber) //所有怪物都出完了
    {
        this->unschedule(schedule_selector(BM_MonsterBuilder::createMonsters)); //注销调度器
        NOTIFICATION_CENTER->postNotification("openCheckGameWin"); //开启游戏胜利检测
    }


    if (_fDelayTime < DELAY_TIME && MonsterManager::getInstance()->getMonsterVec().size() == 0)
        _fDelayTime += t;

    else if (_fDelayTime >= DELAY_TIME)
    {
        monsterFactoryControl(); //生成一个怪物
        _iCurrNumber++;
    }
}

//TODO 游戏逻辑还是太简单了
void BM_MonsterBuilder::monsterFactoryControl()
{

    SoundUtil::getInstance()->playEffectSound(BUILDMONSTER);
    MonsterBase* pMonster = nullptr;
    if (_iCurrNumber != 21)
    {
        if (_iCurrNumber <= 10)
            pMonster = MonsterFactory::createMonster(MonsterType(_iFirstMonsterType));
        else
            pMonster = MonsterFactory::createMonster(MonsterType(_iSecondMonsterType));

        pMonster->setIHp(800); //BOSS模式的小怪血也比较厚
        pMonster->setIValue(268); //BOSS模式的小怪钱也给多点吧，要注意钱的数目不能随便乱写，要面向资源
    }
    else
    {
        pMonster = MonsterFactory::createMonster(MonsterType(_iBossType));
    }
    pMonster->getSprite()->runAction(Animate::create(_createMonsterAnimation)); //运行生成怪物动画
}


void BM_MonsterBuilder::loadData()
{
    srand(time(nullptr));
    _iFirstMonsterType = rand() % 3 + 1;
    _iSecondMonsterType = (_iFirstMonsterType + 1) % 3 + 1;

    _iCurrTheme = SceneManager::getInstance()->getCurrentPageIndex();
    _iCurrLevel = SceneManager::getInstance()->getCurrentLevelIndex();

    _iBossType = 19 + _iCurrTheme * (_iCurrLevel - 12);
}

BM_MonsterBuilder::~BM_MonsterBuilder()
{
    CC_SAFE_RELEASE_NULL(_createMonsterAnimation);
}

void BM_MonsterBuilder::createCMonsterAnimation()
{
    _createMonsterAnimation = Animation::create();
    _createMonsterAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("mcm01.png"));
    _createMonsterAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("mcm02.png"));
    _createMonsterAnimation->setDelayPerUnit(0.15f); //时间间隔为0.15s
    _createMonsterAnimation->setLoops(1); //循环一次就可以了
    _createMonsterAnimation->retain();
}
