//
//  CollisionManager.cpp
//  CarrotFantasy
//
//  Created by ºÎãü±ø on 18-4-12.
//  TODO£ºÐ´¶àÁË£¿£¿£¿
//
#include "CollisionManager.h"
#include "BarrierBase.h"
#include "MonsterBase.h"
#include "BulletBase.h"


void CollisionManager::collision(Vector<BarrierBase *> &rBarrierVec, Vector<MonsterBase *> &rMonsterVec, Vector<BulletBase*> &rBulletVec)
{
	for (int i = 0; i < rBulletVec.size(); ++i)
	{
		BulletBase * pBullet = rBulletVec.at(i);
		if (pBullet == nullptr || pBullet->getIsDead() || pBullet->getIBulletType() != 2)
			continue;
		MonsterAndBullet(pBullet, rMonsterVec);
		BarrierAndBullet(pBullet, rBarrierVec);
	}
}

void CollisionManager::MonsterAndBullet(BulletBase * pBullet, Vector<MonsterBase *> &rMonsterVec)
{
	for (int i = 0; i < rMonsterVec.size(); ++i)
	{
		MonsterBase * pMonster = rMonsterVec.at(i);
		if (pBullet == nullptr || pBullet->getIsDead() || pMonster == nullptr || pMonster->getIsDead())
			continue;
		if (pBullet->getBoundingBox().intersectsRect(pMonster->getBoundingBox()))
		{
			if (pBullet->getIdMap().find(pMonster->getmID()) == pBullet->getIdMap().end())
			{
				pBullet->getIdMap().insert(pMonster->getmID());
				pMonster->beHurt(pBullet->getAtkPro());
				Sprite * HurtSprite = Sprite::create();
				pMonster->addChild(HurtSprite);
				CallFunc * ClearF = CallFunc::create([=]() {HurtSprite->removeFromParentAndCleanup(true); });
				HurtSprite->runAction(Sequence::create(Animate::create(AnimationMaker(pBullet->getSName(), pBullet->getAnimationFrameCount() + 1)), ClearF, NULL));
			
                if (pBullet->getIId() >= 25 && pBullet->getIId() <= 27)
                {
                    pBullet->getIdMap().erase(pMonster->getmID());
                    pBullet->setPosition(pMonster->getPosition());
                    pBullet->stopAllActions();
                    pBullet->doDead();
                    return;
                }
			}
		}
	}
}
void CollisionManager::BarrierAndBullet(BulletBase * pBullet, Vector<BarrierBase *> &rBarrierVec)
{
	for (int i = 0; i < rBarrierVec.size(); ++i)
	{
		BarrierBase * pBarrier = rBarrierVec.at(i);
		if (pBullet == nullptr || pBullet->getIsDead() || pBarrier == nullptr || pBarrier->getIsDead())
			continue;
		if (pBullet->getBoundingBox().intersectsRect(pBarrier->getBoundingBox()))
		{
			if (pBullet->getIdMap().find(pBarrier->getmID()) == pBullet->getIdMap().end())
			{
				pBullet->getIdMap().insert(pBarrier->getmID());
				pBarrier->beHurt(pBullet->getAtkPro());
				Sprite * HurtSprite = Sprite::create();
				pBarrier->addChild(HurtSprite);
				CallFunc * ClearF = CallFunc::create([=]() {HurtSprite->removeFromParentAndCleanup(true); });
				HurtSprite->runAction(Sequence::create(Animate::create(AnimationMaker(pBullet->getSName(), pBullet->getAnimationFrameCount() + 1)), ClearF, NULL));
				if (pBarrier->getAtkTarget() || pBullet->getIId() >= 25 && pBullet->getIId() <= 27)
				{
					pBullet->getIdMap().erase(pBarrier->getmID());
					pBullet->setPosition(pBarrier->getPosition());
					pBullet->stopAllActions();
					pBullet->doDead();
					return;
				}
			}
		}
	}
}

Animation * CollisionManager::AnimationMaker(std::string BulletName, int SpriteFrameCount)
{
	Animation * pAnimation = Animation::create();
	if (SpriteFrameCount == 2 || SpriteFrameCount == 4)
	{
		for (int i = 1; i <= SpriteFrameCount; i++)
		{
			std::string SpriteFrameName = BulletName + StringUtils::format("%02d.png", i);
			pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SpriteFrameName));
		}
	}
	else
	{
		for (int i = 1; i <= SpriteFrameCount; i++)
		{
			std::string SpriteFrameName = BulletName + StringUtils::format("-1%d.png", i);
			pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SpriteFrameName));
		}
	}
	pAnimation->setDelayPerUnit(0.1);
	pAnimation->setLoops(1);
	return pAnimation;
}