//
//  TowerSnow.cpp
//  CarrotFantasy
//
//  Created by ������ on 18-4-12.
//  
//
#include "TowerSnow.h"
#include "MonsterBase.h"
#include "BarrierBase.h"
#include "MonsterManager.h"
#include "BarrierManager.h"
#include "SoundUtil.h"

bool TowerSnow::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!TowerBase::init(rId));
		unschedule(schedule_selector(TowerSnow::doRotation)); //ѩ��û����תЧ������Ҫע��������

		//������������
		_doAnimationSprite = Sprite::create();
		_doAnimationSprite->setVisible(false);
		addChild(_doAnimationSprite); //���뵽����������

		bRet = true;
	} while (0);
	return bRet;
}

void TowerSnow::fire(float dt) {
	if (!_pAtkTarget || _pAtkTarget->getIsDead()) return;

	//����Ч��������
	_doAnimationSprite->setVisible(true);
	//����������
	Animation * pAnimation = Animation::create();
	for (int i = 1; i <= 5; i++)
	{
		std::string SpriteFrameName = "P" + _sModelName + StringUtils::format("%d.png", i);
		pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SpriteFrameName));
	}
	pAnimation->setDelayPerUnit(0.1);
	pAnimation->setLoops(1);
	SoundUtil::getInstance()->playEffectSound("Music/Towers/Snow.mp3"); //���Ź�������

	CallFunc * pCallFunc = CallFunc::create([=]() {
		attack();
		_doAnimationSprite->setVisible(false);
	});

	_doAnimationSprite->runAction(Sequence::create(Animate::create(pAnimation), pCallFunc, NULL));
}

void TowerSnow::attack()
{
	AtkProperty atk;
	atk._enAtkState = 4;
	atk._iAtk = _iBulletId;
	atk._iDuration = 2;
	atk._iBulletsType = _iBulletId;

	Rect rect;
	//���������ȼ�ȷ��������Χ
	//Ϊ�˺���Ŀ���ײ�����»���
	if (getIId() == 31) { rect = Rect(this->getPositionX() - 80, this->getPositionY() - 80, 160, 160); }
	if (getIId() == 32) { rect = Rect(this->getPositionX() - 100, this->getPositionY() - 100, 200, 200); }
	if (getIId() == 33) { rect = Rect(this->getPositionX() - 120, this->getPositionY() - 120, 240, 240); }

	/*************************************************************/
	/**-----------------------������Ϸ���߼�-----------------------**/
	/*************************************************************/

	//todo �߼����Ǻͷɻ���ô��
	Vector<MonsterBase *>  MonsterVector = Vector<MonsterBase *>(MonsterManager::getInstance()->getMonsterVec());
	for (auto mIter = MonsterVector.begin(); mIter != MonsterVector.end();)
	{
		MonsterBase * pMonster = (MonsterBase *)(*mIter);
		if (rect.intersectsRect(pMonster->getBoundingBox()))
		{
			pMonster->beHurt(atk);
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
	Vector<BarrierBase *> BarrierVector = Vector<BarrierBase *>(BarrierManager::getInstance()->getBarrierVec());
	for (auto bIter = BarrierVector.begin(); bIter != BarrierVector.end();)
	{
		BarrierBase * pBarrier = (BarrierBase *)(*bIter);
		if (rect.intersectsRect(pBarrier->getBoundingBox()))
		{
			pBarrier->beHurt(atk);
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
