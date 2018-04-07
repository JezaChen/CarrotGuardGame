//
//  BarrierManager.cpp
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-7.
//  存在不懂问题
//

#include "BarrierManager.h"
#include "BarrierBase.h"
#include "SceneManager.h"

BarrierManager *BarrierManager::_gInstance;

BarrierManager::BarrierManager()
{

}

BarrierManager::~BarrierManager()
{
	CC_SAFE_DELETE(_pBarrierVec);
}


bool BarrierManager::init()
{
	bool bRet = false;

	do
	{
		_pBarrierVec = new Vector<BarrierBase*>();
		registerBarrierDeadEvent();
		bRet = true;
	} while (0);

	return bRet;
}

Vector<BarrierBase*> &BarrierManager::getBarrierVec()
{
	return *_pBarrierVec;
}

void BarrierManager::addBarrier(BarrierBase *pBarrier)
{
	if (_pBarrierVec) _pBarrierVec->pushBack(pBarrier);
	_funcAddBarrierToLayer(pBarrier);
}

void BarrierManager::setFuncAddBarrierToLayer(const std::function<void(Entity *)> &rFuncAddBarrierToLayer)
{
	_funcAddBarrierToLayer = rFuncAddBarrierToLayer;
}

void BarrierManager::registerBarrierDeadEvent()
{
	//这个是干嘛的？
	NOTIFY->addObserver(this, callfuncO_selector(BarrierManager::removeBarrierFromManager), "BarrierDead", nullptr);
}
//妈耶，这个完全不知道在干嘛
void BarrierManager::removeBarrierFromManager(Ref *pBarrier)
{
	if (!(_pBarrierVec && _pBarrierVec->size())) return;
	_pBarrierVec->eraseObject(reinterpret_cast<BarrierBase*>(pBarrier));

	if (!_pBarrierVec->size())
	{
		auto aThemeIndex = SceneManager::getInstance()->getCurrentPageIndex() + 1;
		auto aLevelIndex = SceneManager::getInstance()->getCurrentLevelIndex() + 1;
		auto aLevelData = std::make_tuple(1, 1, aThemeIndex, aLevelIndex);
		NOTIFY->postNotification(LEVELDATACHANGE, reinterpret_cast<Ref*>(&aLevelData));
	}
}

void BarrierManager::clearManager()
{
	_pBarrierVec->clear();
}

void BarrierManager::clearBeAtkLockState()
{
	for (auto &iterBarrier : *_pBarrierVec)
		iterBarrier->setAtkTarget(false);
}



