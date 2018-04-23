//
//  TowerMushroom.cpp
//  CarrotFantasy
//
//  Created by ������ on 18-4-22.
//  
//
#include "TowerMushroom.h"
#include "MonsterBase.h"
#include "BarrierBase.h"
#include "MonsterManager.h"
#include "BarrierManager.h"
#include "SoundUtil.h"

bool TowerMushroom::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!TowerBase::init(rId));
		unschedule(schedule_selector(TowerMushroom::doRotation)); //Ģ��û����תЧ������Ҫע��������

		_doAnimationSprite = Sprite::create();
		_doAnimationSprite->setVisible(false);
		addChild(_doAnimationSprite);

		bRet = true;
	} while (0);
	return bRet;
}

void TowerMushroom::fire(float dt) {
	if (!_pAtkTarget || _pAtkTarget->getIsDead()) return;


	//����Ч����������
	_doAnimationSprite->setVisible(true);

	//������������
	Animation * pAnimation = Animation::create();
	for (int i = 1; i <= 5; i++)
	{
		std::string SpriteFrameName = "P" + _sName + StringUtils::format("%d.png", i);
		pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SpriteFrameName));
	}
	pAnimation->setDelayPerUnit(0.1);
	pAnimation->setLoops(1);

	//���Ź�������
	SoundUtil::getInstance()->playEffectSound("Music/Towers/Mushroom.mp3");


	CallFunc * pCallFunc = CallFunc::create([=]() {
		attack();
		_doAnimationSprite->setVisible(false);
	});

	_doAnimationSprite->runAction(Sequence::create(Animate::create(pAnimation), pCallFunc, NULL));
}

void TowerMushroom::attack()
{
	AtkProperty atk;
	atk._enAtkState = 1;
	atk._iAtk = _iBulletId;
	atk._iDuration = 0;

	/*************************************************************/
	/**-----------------------������Ϸ���߼�-----------------------**/
	/*************************************************************/

	//���˶�������
	Animation * pHurtAction1 = Animation::create();
	Animation * pHurtAction2 = Animation::create();
	for (int i = 1; i <= 2; i++)
	{
		std::string hurtSpriteName = StringUtils::format("PMushroom-%d1.png", i);
		pHurtAction1->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(hurtSpriteName));
	}
	pHurtAction1->setDelayPerUnit(0.03);
	pHurtAction1->setLoops(1);

	for (int i = 1; i <= 3; i++)
	{
		std::string hurtSpriteName = StringUtils::format("PMushroom0%d.png", i);
		pHurtAction2->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(hurtSpriteName));
	}
	pHurtAction2->setDelayPerUnit(0.03);
	pHurtAction2->setLoops(1);

	Rect rect;
	//todo �����ΧӦ�����ļ���Ϊ׼
	if (getIId() == 22) { rect = Rect(this->getPositionX() - 100, this->getPositionY() - 100, 200, 200); }
	if (getIId() == 23) { rect = Rect(this->getPositionX() - 120, this->getPositionY() - 120, 240, 240); }
	if (getIId() == 24) { rect = Rect(this->getPositionX() - 140, this->getPositionY() - 140, 280, 280); }

	//�ȼ�����
	Vector<MonsterBase *>  MonsterVector = Vector<MonsterBase *>(MonsterManager::getInstance()->getMonsterVec());
	for (int i = 0; i < MonsterVector.size(); i++)
	{
		MonsterBase * pMonster = (MonsterBase *)(MonsterVector.at(i));
		if (rect.intersectsRect(pMonster->getBoundingBox())) //��ײ���
		{
			pMonster->beHurt(atk);
			//������ʾ���˶��������˾�������
			Sprite * pMonsterHurt = Sprite::create();
			pMonster->addChild(pMonsterHurt);
			CallFunc * pClear = CallFunc::create([=]() { pMonsterHurt->removeFromParentAndCleanup(true); });
			//���˾�����ʾ����
			pMonsterHurt->runAction(Sequence::create(Animate::create(pHurtAction1), pClear, nullptr));
		}
		if (pMonster->getIHp() <= 0 || pMonster->getIsDead())
		{
			MonsterVector.eraseObject(pMonster);
		}
	}

	//�ټ���ϰ���
	Vector<BarrierBase *> BarrierVector = Vector<BarrierBase *>(BarrierManager::getInstance()->getBarrierVec());
	for (int i=0;i<BarrierVector.size();i++)
	{
		BarrierBase * pBarrier = (BarrierBase *)(BarrierVector.at(i));
		if (rect.intersectsRect(pBarrier->getBoundingBox()))
		{
			pBarrier->beHurt(atk);
			Sprite * pBarrierHurt = Sprite::create();
			pBarrier->addChild(pBarrierHurt);
			CallFunc * pClear = CallFunc::create([=]() { pBarrierHurt->removeFromParentAndCleanup(true); });
			pBarrierHurt->runAction(Sequence::create(Animate::create(pHurtAction2), pClear, NULL));
		}
		if (pBarrier->getIHp() <= 0 || pBarrier->getIsDead())
		{
			BarrierVector.eraseObject(pBarrier);
		}
	}
}



