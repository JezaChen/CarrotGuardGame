//
// BulletRocket.cpp
// CarrotFantasy
//
// Created by ºÎãü±ø on 18-4-11.
//
//

#include "BulletRocket.h"
#include "VictimEntityBase.h"

bool BulletRocket::init(const int & rId, VictimEntityBase *rVictimEntity)
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!BulletBase::init(rId, rVictimEntity));

		bRet = true;
	} while (0);
	return bRet;
}

BulletRocket * BulletRocket::create(const int & rId, VictimEntityBase *rVictimEntity)
{
	//·ÖÅäÄÚ´æ£»
	BulletRocket * pBullet = new BulletRocket();
	if (pBullet && pBullet->init(rId, rVictimEntity))
	{
		pBullet->autorelease();
		return pBullet;
	}
	CC_SAFE_DELETE(pBullet);
	return nullptr;
}

void BulletRocket::doAction()
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

void BulletRocket::doMove() {
	if (_pAtkTarget->getIsDead())
	{
		removeFromParent();
		setIsDead(true);
		return;
	}
	doAction();

	float Hypotenuse = Vec2::ZERO.distance(Director::getInstance()->getVisibleSize());
	Vec2 MovetoPosition = Vec2(Hypotenuse * sin(this->getRotation() * M_PI / 180), Hypotenuse * cos(this->getRotation() * M_PI / 180));
	float MoveDistance = MovetoPosition.distance(this->getPosition());

	this->runAction(MoveBy::create(MoveDistance / _iSpeed, MovetoPosition));
}