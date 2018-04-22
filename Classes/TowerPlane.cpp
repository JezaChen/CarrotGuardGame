//
//  TowerPlane.cpp
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-12.
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

	//创建攻击时飞机的动画
	//todo 不妨调用父类的fireAction?
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
	getSprite()->runAction(Sequence::create(Animate::create(pAnimation), pCallFunc, nullptr));
}
void TowerPlane::attack() 
{
	//创建攻击属性
	AtkProperty atk;
	atk._enAtkState = 1;
	atk._iAtk = _iBulletId;
	atk._iDuration = 0;

	//攻击精灵启动
	_doAnimationSprite->setVisible(true);

	//攻击精灵角度与炮塔精灵的角度要一致
	_doAnimationSprite->setRotation(getSprite()->getRotation());

	//攻击精灵动画启动
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

	_doAnimationSprite->runAction(Sequence::create(Animate::create(pAnimation), pCallFunc, nullptr));

	//伤害动画启动
	Animation *pHurtAnimation = Animation::create();
	for (int i = 1; i <= 5; i++) {
		std::string SpriteFrameName = StringUtils::format("PPlane0%d.png", i);
		pHurtAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SpriteFrameName));
	}
	pHurtAnimation->setLoops(1);
	pHurtAnimation->setDelayPerUnit(0.1f);

	/*************************************************************/
	/**-----------------------攻击游戏主逻辑-----------------------**/
    /*************************************************************/
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

	//先写攻击怪物逻辑
	Vector<MonsterBase *> MonsterVector = Vector<MonsterBase *>(MonsterManager::getInstance()->getMonsterVec());
    for (int i = MonsterVector.size() - 1; i >= 0; i--)
	{
		MonsterBase *pMonster = dynamic_cast<MonsterBase *>(MonsterVector.at(i));
		int rM = int(90 - 180 * (pMonster->getPosition() - this->getPosition()).getAngle() / M_PI) % 360;
		if (rM >= rd && rM <= rt) {
			pMonster->beHurt(atk);
			Sprite * pMonsterHurt = Sprite::create();
			pMonster->addChild(pMonsterHurt);
			CallFunc * pClear = CallFunc::create([=]() { pMonsterHurt->removeFromParentAndCleanup(true); });
			pMonsterHurt->runAction(Sequence::create(Animate::create(pHurtAnimation), pClear, nullptr));
		}
		//todo 这个逻辑不应该在这里有，去除试试
        /**[可能要废弃]**/
		if (pMonster->getIHp() <= 0 || pMonster->getIsDead())
		{
			/*mIter = (auto)*/
			MonsterVector.eraseObject(pMonster);
		}
	}

	//后写攻击障碍物逻辑
	Vector<BarrierBase *> BarrierVector = Vector<BarrierBase *>(BarrierManager::getInstance()->getBarrierVec());
    for (int i = BarrierVector.size() - 1; i >= 0; i--)
	{
		BarrierBase *pBarrier = dynamic_cast<BarrierBase *>(BarrierVector.at(i));
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
	}
}