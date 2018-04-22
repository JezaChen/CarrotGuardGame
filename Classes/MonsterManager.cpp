//
//  MonsterManager.cpp
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-9.
//
//

#include "MonsterManager.h"
#include "MonsterBase.h"
#include "GameManager.h"

MonsterManager *MonsterManager::_gInstance;

MonsterManager::MonsterManager()
{

}

void MonsterManager::clearBeAtkLockState()
{
	for (auto &iterMonster : *_pMonsterVec)
	{
		iterMonster->setAtkTarget(false);
	}
}

MonsterManager::~MonsterManager()
{
	CC_SAFE_DELETE(_pMonsterVec);
}

bool MonsterManager::init()
{
	bool bRet = false;
	do
	{
		_pMonsterVec = new Vector<MonsterBase *>;
		registerDeadEvent();
		bRet = true;
	} while (0);

	return bRet;
}

Vector<MonsterBase*> &MonsterManager::getMonsterVec()
{
	return *_pMonsterVec;
}

void MonsterManager::addMonster(MonsterBase *pMonster)
{
	//添加怪物进向量统一管理；
	if (_pMonsterVec) _pMonsterVec->pushBack(pMonster);
	//添加怪物进图层，显示出来；
	_funcAddMonsterToLayer(pMonster);
}

void MonsterManager::setFuncAddMonsterToLayer(const std::function<void(Entity*)> &rFuncAddMonsterToLayer)
{
	_funcAddMonsterToLayer = rFuncAddMonsterToLayer;
}

void MonsterManager::registerDeadEvent()
{
	NOTIFY->addObserver(this, callfuncO_selector(MonsterManager::removeMonsterFromManager), "MonsterDead", nullptr);
	NOTIFY->addObserver(this, callfuncO_selector(MonsterManager::openCheckGameEnd), "openCheckGameWin", nullptr);
}

void MonsterManager::removeMonsterFromManager(Ref *pMonster)
{
	if (!(_pMonsterVec && _pMonsterVec->size())) return;
	_pMonsterVec->eraseObject(reinterpret_cast<MonsterBase*>(pMonster));

	if (_bIsOpenCheckGameEnd) //已经开启了游戏结束检查
	{
		if (!_pMonsterVec->size())
		{
			auto aEnGameWin = en_GameWin;
			if (GameManager::getInstance()->getICarrotHp() >= 1 || GameManager::getInstance()->getCurrGameType() == en_BossMode) 
                NOTIFY->postNotification("gameEnd", reinterpret_cast<Ref*>(&aEnGameWin));

			//发完通知后要重置该变量；
			_bIsOpenCheckGameEnd = false;
		}
	}
}

void MonsterManager::clearManager()
{
	_pMonsterVec->clear();
}

void MonsterManager::openCheckGameEnd(Ref *pSender)
{
	_bIsOpenCheckGameEnd = true;
}
