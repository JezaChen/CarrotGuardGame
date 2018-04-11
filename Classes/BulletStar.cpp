//
//BulletStar.cpp
//CarrotFantasy
//
//Created by ºÎãü±ø on 18-4-11
//
//
#include "BulletStar.h"
#include "VictimEntityBase.h"
#include "MonsterManager.h"
#include "MonsterBase.h"
#include "BarrierManager.h"
#include "BarrierBase.h"

bool BulletStar::init(const int & rId, VictimEntityBase *rVictimEntity)
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!BulletBase::init(rId, rVictimEntity));

		bRet = true;
	} while (0);
	return bRet;
}

BulletStar * BulletStar::create(const int & rId, VictimEntityBase *rVictimEntity)
{
	BulletStar * pBullet = new BulletStar();
	if (pBullet && pBullet->init(rId, rVictimEntity))
	{
		pBullet->autorelease();
		return pBullet;
	}
	CC_SAFE_DELETE(pBullet);
	return nullptr;
}

void BulletStar::doAction()
{
	getSprite()->runAction(RepeatForever::create(RotateBy::create(0.7, 360)));
}

void BulletStar::doMove() 
{
	if (_pAtkTarget->getIsDead())
	{
		removeFromParent();
		setIsDead(true);
		return;
	}
	doAction();

	Animation * pAnimation = Animation::create();
	for (int i = 1; i < 7; i++)
	{
		std::string SpriteFrameName = StringUtils::format("PStar-1%d.png", i);
		pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SpriteFrameName));
	}
	pAnimation->setDelayPerUnit(0.05);
	pAnimation->setLoops(1);

	auto deadActionCF = CallFunc::create([=]()
	{

		Rect rect = Rect(_pAtkTarget->getPositionX() - 100, _pAtkTarget->getPositionY() - 100, 200, 200);
		if (_pAtkTarget->getAnimationFrameCount() != 0)
		{
			Vector<MonsterBase *>  MonsterVector = Vector<MonsterBase *>(MonsterManager::getInstance()->getMonsterVec());
			for (auto mIter = MonsterVector.begin(); mIter != MonsterVector.end();)
			{
				MonsterBase * pMonster = (MonsterBase *)(*mIter);
				//¼ì²âÅö×²£»
				if (rect.intersectsRect(pMonster->getBoundingBox()))
				{
					pMonster->beHurt(getAtkPro());
				}
				if (pMonster->getIHp() <= 0 || pMonster->getIsDead())
				{
					/*mIter = (auto)*/
					MonsterVector.eraseObject(pMonster);
				}
				else
				{
					++mIter;
				}
			}
		}
		else
		{
			Vector<BarrierBase *>  BarrierVector = Vector<BarrierBase *>(BarrierManager::getInstance()->getBarrierVec());
			for (auto bIter = BarrierVector.begin(); bIter != BarrierVector.end();)
			{
				BarrierBase * pBarrier = (BarrierBase *)(*bIter);
				if (rect.intersectsRect(pBarrier->getBoundingBox()))
				{
					pBarrier->beHurt(getAtkPro());
				}
				if (pBarrier->getIHp() <= 0 || pBarrier->getIsDead())
				{
					/*bIter =(auto)*/ 
					BarrierVector.eraseObject(pBarrier);
				}
				else
				{
					++bIter;
				}
			}
		}
		deadAction(_sName);
	});

	Vec2 MovetoPosition = _pAtkTarget->getPosition() - this->getPosition();
	float MoveDistance = this->getPosition().distance(_pAtkTarget->getPosition());
	getSprite()->runAction(Sequence::create(MoveBy::create(MoveDistance / _iSpeed, MovetoPosition), Animate::create(pAnimation), deadActionCF, NULL));
}

