//
//  TowerManager.cpp
//  CarrotFantasy
//
//  Created by ºÎãü±ø on 18-4-11.
//
//
#include "TowerManager.h"
#include "TowerBase.h"

TowerManager *TowerManager::_gInstance;

TowerManager::TowerManager()
{
}

TowerManager::~TowerManager()
{
	CC_SAFE_DELETE(_pTowerVec);
}

bool TowerManager::init()
{
	bool bRet = false;
	do
	{
		_pTowerVec = new Vector<TowerBase *>();
		registerTowerDeadEvent();
		bRet = true;
	} while (0);

	return bRet;
}

Vector<TowerBase*> &TowerManager::getTowerVec()
{
	return *_pTowerVec;
}

void TowerManager::addTower(TowerBase *pTower)
{
	if (_pTowerVec) _pTowerVec->pushBack(pTower);
	_funcAddTowerToLayer(pTower);
}

void TowerManager::setFuncAddTowerLayer(const std::function<void(Entity *)> &rFuncAddEntityLayer)
{
	_funcAddTowerToLayer = rFuncAddEntityLayer;
}

void TowerManager::registerTowerDeadEvent()
{
	NOTIFY->addObserver(this, callfuncO_selector(TowerManager::removeTowerFromManager), "TowerDead", nullptr);
}

void TowerManager::removeTowerFromManager(Ref *pTower)
{
	if (!(_pTowerVec && _pTowerVec->size())) return;
	_pTowerVec->eraseObject(reinterpret_cast<TowerBase*>(pTower));
}

void TowerManager::clearManager()
{
	_pTowerVec->clear();
}


int TowerManager::getMoney() {
	return _funcCheckMoney();
}

void TowerManager::setFuncCheckMoney(const std::function<int()> &rFuncCheckMoney) {
	_funcCheckMoney = rFuncCheckMoney;
}