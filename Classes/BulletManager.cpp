
//
//  BulletManager.cpp
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-10.
//
//

#include "BulletManager.h"
#include "BulletBase.h"

BulletManager *BulletManager::_gInstance;

BulletManager::BulletManager()
{
}

BulletManager::~BulletManager()
{
	CC_SAFE_DELETE(_pBulletVec);
}

bool BulletManager::init()
{
	bool bRet = false;
	do
	{
		_pBulletVec = new Vector<BulletBase *>();

		bRet = true;
	} while (0);

	return bRet;
}

Vector<BulletBase*> &BulletManager::getBulletVec()
{
	return *_pBulletVec;
}
//把子弹加入子弹vector；
void BulletManager::addBullet(BulletBase *pBullet)
{
	if (_pBulletVec) _pBulletVec->pushBack(pBullet);
	_funcAddBulletLayer(pBullet);
}

void BulletManager::setFuncAddBulletLayer(const std::function<void(Entity *)> &rFuncAddBulletLayer)
{
	_funcAddBulletLayer = rFuncAddBulletLayer;
}
//子弹要是射出去了，就从vector中清出；
void BulletManager::checkBulletIsDead()
{
	for (auto iterBullet = _pBulletVec->begin(); iterBullet != _pBulletVec->end();)
	{
		if ((*iterBullet)->getIsDead()) iterBullet = _pBulletVec->erase(iterBullet);
		else ++iterBullet;
	}
}

//清空子弹的vector；
void BulletManager::clearManager()
{
	_pBulletVec->clear();
}



