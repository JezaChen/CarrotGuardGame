//
//  TowerFireBottle.cpp
//  CarrotFantasy
//
//  Created by ºÎãü±ø on 18-4-12.
//  
//
#include "TowerFireBottle.h"
#include "MonsterManager.h"
#include "MonsterBase.h"
#include "BarrierManager.h"
#include "BarrierBase.h"
#include "TowerManager.h"
#include "SoundUtil.h"

bool TowerFireBottle::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!TowerBase::init(rId));

		_doActionSprite = Sprite::create();
		addChild(_doActionSprite, -100);

		bRet = true;
	} while (0);
	return bRet;
}

void  TowerFireBottle::chooseAtkTarget() {

	auto tMonsterVec = MonsterManager::getInstance()->getMonsterVec();

	for (auto &iterMonster : tMonsterVec)
	{
		if (isInAtkRange(iterMonster->getPosition()))
		{
			fireAction();
			setAtkTarget(iterMonster);
			break;
		}
	}
}

void TowerFireBottle::fire(float dt) {
	if (!_pAtkTarget || _pAtkTarget->getIsDead()) return;

	Animation * pAnimation = Animation::create();
	for (int i = 1; i <= 2; i++) {
		std::string SpriteFrameName = "P" + _sModelName + StringUtils::format("%d.png", i);
		pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SpriteFrameName));
	}
	pAnimation->setDelayPerUnit(0.05);
	pAnimation->setLoops(1);
	SoundUtil::getInstance()->playEffectSound("Music/Towers/FireBottle.mp3");

	_doActionSprite->setVisible(true);
	_doActionSprite->setScaleY(this->getPosition().distance(_pAtkTarget->getPosition()) / _doActionSprite->getContentSize().height);
	_doActionSprite->setPosition((this->getPosition() + _pAtkTarget->getPosition()) / 2 - this->getPosition());
	_doActionSprite->setRotation(90 - 180 * (_pAtkTarget->getPosition() - this->getPosition()).getAngle() / M_PI);
	_doActionSprite->runAction(Animate::create(pAnimation));

	AtkProperty atk;
	atk._enAtkState = 1;
	atk._iAtk = int(_iBulletId * 0.8);
	atk._iDuration = 0;

	Animation * pHurtAction = Animation::create();
	pHurtAction->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PFBottle01.png"));
	pHurtAction->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PFBottle02.png"));
	pHurtAction->setDelayPerUnit(0.06);
	pHurtAction->setLoops(1);

	Rect rect = Rect(_pAtkTarget->getPositionX() - 60, _pAtkTarget->getPositionY() - 60, 120, 120);
	if (_pAtkTarget->getAnimationFrameCount() != 0)
	{
		for (auto mIter = MonsterManager::getInstance()->getMonsterVec().begin(); mIter != MonsterManager::getInstance()->getMonsterVec().end(); mIter++)
		{
			MonsterBase * pMonster = (MonsterBase *)(*mIter);
			if (rect.intersectsRect(pMonster->getBoundingBox()))
			{
				pMonster->beHurt(atk);
				Sprite * pMonsterHurt = Sprite::create();
				pMonster->addChild(pMonsterHurt);
				CallFunc * pClear = CallFunc::create([=]() { pMonsterHurt->removeFromParentAndCleanup(true); });
				pMonsterHurt->runAction(Sequence::create(Animate::create(pHurtAction), pClear, NULL));
			}
			if (pMonster->getIHp() <= 0 || pMonster->getIsDead())
			{
				break;
			}
		}
	}
	else
	{
		for (auto bIter = BarrierManager::getInstance()->getBarrierVec().begin(); bIter != BarrierManager::getInstance()->getBarrierVec().end(); bIter++)
		{
			BarrierBase * pBarrier = (BarrierBase *)(*bIter);
			if (rect.intersectsRect(pBarrier->getBoundingBox()))
			{
				pBarrier->beHurt(atk);
				Sprite * pBarrierHurt = Sprite::create();
				pBarrier->addChild(pBarrierHurt);
				CallFunc * pClear = CallFunc::create([=]() { pBarrierHurt->removeFromParentAndCleanup(true); });
				pBarrierHurt->runAction(Sequence::create(Animate::create(pHurtAction), pClear, NULL));
			}
			if (pBarrier->getIHp() <= 0 || pBarrier->getIsDead())
			{
				break;
			}
		}
	}
}

void TowerFireBottle::missAtkTarget() {
	CC_SAFE_RELEASE_NULL(_pAtkTarget);
	_doActionSprite->setVisible(false);
}
