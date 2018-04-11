//
// BullePin.cpp
// CarrotFantasy
//
// Created by ºÎãü±ø on 18-4-11.
//
//
#include "BulletPin.h"
#include "BulletPin.h"
#include "VictimEntityBase.h"

bool BulletPin::init(const int & rId, VictimEntityBase *rVictimEntity)
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!BulletBase::init(rId, rVictimEntity));

		bRet = true;
	} while (0);
	return bRet;
}

BulletPin * BulletPin::create(const int & rId, VictimEntityBase *rVictimEntity)
{
	BulletPin * pBullet = new BulletPin();
	if (pBullet && pBullet->init(rId, rVictimEntity))
	{
		pBullet->autorelease();
		return pBullet;
	}
	CC_SAFE_DELETE(pBullet);
	return nullptr;
}

void BulletPin::doAction()
{

	for (int i = 1; i <= _IAnimationFrameCount; ++i)
	{
		std::string SpriteFrameName = _sModelName + StringUtils::format("%d.png", i);
		_pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SpriteFrameName));
	}
	_pAnimation->setDelayPerUnit(0.05);
	_pAnimation->setLoops(-1);
	getSprite()->runAction(Animate::create(_pAnimation));
}

void BulletPin::doMove() {

	if (_pAtkTarget->getIsDead())
	{
		removeFromParent();
		setIsDead(true);
		return;
	}
	doAction();

	auto deadActionCF = CallFunc::create([=]()
	{

		if (_pAtkTarget != nullptr && !_pAtkTarget->getIsDead())
			_pAtkTarget->beHurt(getAtkPro());
		deadAction(_sName);

	});

	float Hypotenuse = Vec2::ZERO.distance(Director::getInstance()->getVisibleSize());
	Vec2 MovetoPosition = _pAtkTarget->getPosition() - this->getPosition();
	float MoveDistance = this->getPosition().distance(_pAtkTarget->getPosition());
	this->runAction(Sequence::create(MoveBy::create(MoveDistance / _iSpeed, MovetoPosition), deadActionCF, NULL));
}