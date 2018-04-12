//
//  TowerPlane.cpp
//  CarrotFantasy
//
//  Created by ºÎãü±ø on 18-4-12.
//
//

#include "TowerPlane.h"
#include "VictimEntityBase.h"
#include "MonsterBase.h"
#include "BarrierBase.h"
#include "MonsterManager.h"
#include "BarrierManager.h"
#include "SoundUtil.h"

bool TowerPlane::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!TowerBase::init(rId));
		_doAnimationSprite = Sprite::create();
		_doAnimationSprite->setAnchorPoint(Vec2(0.5, 0));
		_doAnimationSprite->setContentSize(Size(10, 1290));
		_doAnimationSprite->setVisible(false);
		addChild(_doAnimationSprite);
		bRet = true;
	} while (0);
	return bRet;
}
void TowerPlane::fire(float dt) 
{
	if (!_pAtkTarget || _pAtkTarget->getIsDead()) return;

	Animation *pAnimation = Animation::create();
	for (int i = 1; i <= 3; i++) 
	{

		std::string SpriteFrameName = _sModelName + StringUtils::format("%d.png", i);

		pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SpriteFrameName));
	}
	pAnimation->setDelayPerUnit(0.1f);
	pAnimation->setLoops(1);
	SoundUtil::getInstance()->playEffectSound("Music/Towers/Plane.mp3");

	CallFunc *pCallFunc = CallFunc::create([=]() 
	{

		attack();
	});
	getSprite()->runAction(Sequence::create(Animate::create(pAnimation), pCallFunc, NULL));
}
void TowerPlane::attack() 
{

	AtkProperty atk;
	atk._enAtkState = 1;
	atk._iAtk = _iBulletId;
	atk._iDuration = 0;

	_doAnimationSprite->setVisible(true);

	_doAnimationSprite->setRotation(getSprite()->getRotation());

	Animation *pAnimation = Animation::create();
	for (int i = 1; i <= 3; i++) 
	{
		std::string SpriteFrameName = _sName + StringUtils::format("%d.png", i);
		pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SpriteFrameName));
	}
	pAnimation->setLoops(1);
	pAnimation->setDelayPerUnit(0.1f);
	CallFunc *pCallFunc = CallFunc::create([=]() 
	{
		_doAnimationSprite->setVisible(false);
	});

	_doAnimationSprite->runAction(Sequence::create(Animate::create(pAnimation), pCallFunc, NULL));

	Animation *pHurtAnimation = Animation::create();
	for (int i = 1; i <= 5; i++) {
		std::string SpriteFrameName = StringUtils::format("PPlane0%d.png", i);
		pHurtAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SpriteFrameName));
	}
	pHurtAnimation->setLoops(1);
	pHurtAnimation->setDelayPerUnit(0.1f);

	int rt;
	int rd;
	if (_pAtkTarget && _pAtkTarget->getPositionX() > this->getPositionX())
	{
		rt = int(getSprite()->getRotation() + 365) % 360;
		rd = int(getSprite()->getRotation() + 355) % 360;
	}
	else
	{
		rt = int(getSprite()->getRotation() + 5) % 360;
		rd = int(getSprite()->getRotation() - 5) % 360;
	}
	Vector<MonsterBase *> MonsterVector = Vector<MonsterBase *>(MonsterManager::getInstance()->getMonsterVec());
	for (auto mIter = MonsterVector.begin(); mIter != MonsterVector.end();)
	{
		MonsterBase *pMonster = dynamic_cast<MonsterBase *>(*mIter);
		int rM = int(90 - 180 * (pMonster->getPosition() - this->getPosition()).getAngle() / M_PI) % 360;
		if (rM >= rd && rM <= rt) {
			pMonster->beHurt(atk);
			Sprite * pMonsterHurt = Sprite::create();
			pMonster->addChild(pMonsterHurt);
			CallFunc * pClear = CallFunc::create([=]() { pMonsterHurt->removeFromParentAndCleanup(true); });
			pMonsterHurt->runAction(Sequence::create(Animate::create(pHurtAnimation), pClear, NULL));
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

	Vector<BarrierBase *> BarrierVector = Vector<BarrierBase *>(BarrierManager::getInstance()->getBarrierVec());
	for (auto bIter = BarrierVector.begin(); bIter != BarrierVector.end();)
	{
		BarrierBase *pBarrier = dynamic_cast<BarrierBase *>(*bIter);
		int rB = int(90 - 180 * (pBarrier->getPosition() - this->getPosition()).getAngle() / M_PI) % 360;
		if (rB >= rd && rB <= rt) {
			pBarrier->beHurt(atk);
			Sprite * pBarrierHurt = Sprite::create();
			pBarrier->addChild(pBarrierHurt);
			CallFunc * pClear = CallFunc::create([=]() { pBarrierHurt->removeFromParentAndCleanup(true); });
			pBarrierHurt->runAction(Sequence::create(Animate::create(pHurtAnimation), pClear, NULL));
		}
		if (pBarrier->getIHp() <= 0 || pBarrier->getIsDead())
		{
			/*bIter = (auto)*/
			BarrierVector.eraseObject(pBarrier);
		}
		else
		{
			++bIter;
		}
	}
}