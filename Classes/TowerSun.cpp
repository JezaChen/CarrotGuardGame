//
//  TowerSun.cpp
//  CarrotFantasy
//
//  Created by ������ x �½��� on 18-4-12.
//  
//
#include "TowerSun.h"
#include "MonsterBase.h"
#include "BarrierBase.h"
#include "MonsterManager.h"
#include "BarrierManager.h"
#include "SoundUtil.h"

bool TowerSun::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!TowerBase::init(rId));
		unschedule(schedule_selector(TowerSun::doRotation)); //̫��û����תЧ������Ҫע��������

		_doAnimationSprite = Sprite::create();
		_doAnimationSprite->setVisible(false);
		addChild(_doAnimationSprite);

		bRet = true;
	} while (0);
	return bRet;
}

void TowerSun::fire(float dt) {
	if (!_pAtkTarget || _pAtkTarget->getIsDead()) return;

	//todo ����ҲҪ��ת
	_pTowerPanel->runAction(Sequence::create(RotateBy::create(0.1, 30), RotateBy::create(0.1, -30), nullptr));

	//����Ч��������
	_doAnimationSprite->setVisible(true);

	//����������
	Animation * pAnimation = Animation::create();
	for (int i = 1; i <= 5; i++)
	{
		std::string SpriteFrameName = "P" + _sName + StringUtils::format("%d.png", i);
		pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SpriteFrameName));
	}
	pAnimation->setDelayPerUnit(0.1);
	pAnimation->setLoops(1);

	//���Ź�������
	SoundUtil::getInstance()->playEffectSound("Music/Towers/Sun.mp3");


	CallFunc * pCallFunc = CallFunc::create([=]() {
		attack();
		_doAnimationSprite->setVisible(false);
	});

	_doAnimationSprite->runAction(Sequence::create(Animate::create(pAnimation), pCallFunc, NULL));
}

void TowerSun::attack()
{
	AtkProperty atk;
	atk._enAtkState = 1;
	atk._iAtk = _iBulletId;
	atk._iDuration = 0;

	/*************************************************************/
	/**-----------------------������Ϸ���߼�-----------------------**/
	/*************************************************************/

	//���˶�����
	Animation * pHurtAction = Animation::create();
	for (int i = 1; i < 10; i++)
	{
		std::string hurtSpriteName = StringUtils::format("PSun0%d.png", i);
		pHurtAction->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(hurtSpriteName));
	}
	pHurtAction->setDelayPerUnit(0.03);
	pHurtAction->setLoops(1);

	Rect rect;
	//todo �����ΧӦ�����ļ���Ϊ׼
	if (getIId() == 22) { rect = Rect(this->getPositionX() - 100, this->getPositionY() - 100, 200, 200); }
	if (getIId() == 23) { rect = Rect(this->getPositionX() - 120, this->getPositionY() - 120, 240, 240); }
	if (getIId() == 24) { rect = Rect(this->getPositionX() - 140, this->getPositionY() - 140, 280, 280); }

	//�ȼ�����
	Vector<MonsterBase *>  MonsterVector = Vector<MonsterBase *>(MonsterManager::getInstance()->getMonsterVec());
	for (auto mIter = MonsterVector.begin(); mIter != MonsterVector.end();)
	{
		MonsterBase * pMonster = (MonsterBase *)(*mIter);
		if (rect.intersectsRect(pMonster->getBoundingBox())) //��ײ���
		{
			pMonster->beHurt(atk);
			//������ʾ���˶��������˾�����
			Sprite * pMonsterHurt = Sprite::create();
			pMonster->addChild(pMonsterHurt);
			CallFunc * pClear = CallFunc::create([=]() { pMonsterHurt->removeFromParentAndCleanup(true); });
			//���˾�����ʾ����
			pMonsterHurt->runAction(Sequence::create(Animate::create(pHurtAction), pClear, nullptr));
		}
		if (pMonster->getIHp() <= 0 || pMonster->getIsDead())
		{
			/*mIter =(auto)*/ 
			MonsterVector.eraseObject(pMonster);
		}
		else
		{
			++mIter;
		}
	}

	//�ټ���ϰ���
	Vector<BarrierBase *> BarrierVector = Vector<BarrierBase *>(BarrierManager::getInstance()->getBarrierVec());
	for (auto bIter = BarrierVector.begin(); bIter != BarrierVector.end();)
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
			/*bIter =(auto)*/ 
			BarrierVector.eraseObject(pBarrier);
		}
		else
		{
			++bIter;
		}
	}
}


