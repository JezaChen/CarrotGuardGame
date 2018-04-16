//
//  TowerBall.cpp
//  CarrotFantasy
//
//  Created by ������ x �½��� on 18-4-12.
//  
//
#include "TowerBall.h"
#include "MonsterManager.h"
#include "MonsterBase.h"
#include "TowerManager.h"
#define CRIE(Atk)  (0.6 * ((Atk) - 9))

bool TowerBall::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!TowerBase::init(rId));
		if (_pTowerPanel)
			_pTowerPanel->removeFromParentAndCleanup(true);
		_doActionSprite = Sprite::create();
		addChild(_doActionSprite, 100);
		//������û����תЧ��������Ҫȥ��������
		unschedule(schedule_selector(TowerBall::doRotation));

		bRet = true;
	} while (0);
	return bRet;
}

void TowerBall::chooseAtkTarget() {

	auto tMonsterVec = MonsterManager::getInstance()->getMonsterVec();

	for (auto &iterMonster : tMonsterVec)
	{
		if (isInAtkRange(iterMonster->getPosition()))
		{
			fireAction(); //�����̿���
			setAtkTarget(iterMonster);
			break;
		}
	}
}

void TowerBall::fire(float dt) {
	if (!_pAtkTarget || _pAtkTarget->getIsDead()) return;

	//��������Ч������
	Animation * pAnimation = Animation::create();
	for (int i = 1; i <= 4; i++) {
		std::string SpriteFrameName = "P" + _sModelName + StringUtils::format("%d.png", i);
		pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SpriteFrameName));
	}
	pAnimation->setDelayPerUnit(0.03);
	pAnimation->setLoops(1); //ѭ��һ�β��žͿ����ˣ�ѭ���Ĺ����ǵ������Ǳߵ�

    //��������������������洴��Ķ���
	_doActionSprite->setVisible(true);
	//todo �������ֵ����ȶ
	_doActionSprite->setScale(this->getPosition().distance(_pAtkTarget->getPosition()) / _doActionSprite->getContentSize().height);
	_doActionSprite->setPosition((this->getPosition() + _pAtkTarget->getPosition()) / 2 - this->getPosition());
	//�Ƕȹ�ʽ���Ǹ�������Ͳһ����
	_doActionSprite->setRotation(90 - 180 * (_pAtkTarget->getPosition() - this->getPosition()).getAngle() / M_PI);
	_doActionSprite->runAction(Animate::create(pAnimation));

	//���˾������������ʾ���޵����˶���
    //���������Ϊ���޾�����ӽڵ������ȥ�Ϳ�����
	Sprite * pHurt = Sprite::create();
	_pAtkTarget->addChild(pHurt);
	Animation * pHurtAction = Animation::create();
	pHurtAction->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PBall01.png"));
	pHurtAction->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PBall02.png"));
	pHurtAction->setDelayPerUnit(0.05);
	pHurtAction->setLoops(1);
	CallFunc * clearCF = CallFunc::create([=]() { pHurt->removeFromParentAndCleanup(true); });

	//ʵ���˺�Ч����
    //��������˺�Ч��û�ж��Ա߹����и����˺������Ծ�����Ǹ�ָ����������ִ���˺�����
    //todo �����������???
	AtkProperty atk;
	atk._enAtkState = 1;
	atk._iAtk = _iBulletId;
	atk._iDuration = 0;
	int CritPro = rand() % 10;
	if (CritPro > 0)
	{
		_pAtkTarget->beHurt(atk);
	}
	else
	{
		atk._iAtk = static_cast<int>(_iBulletId + CRIE(this->_iId) * _iBulletId);
		_pAtkTarget->beHurt(atk);
		pHurt->setScale(2);
	}

	pHurt->runAction(Sequence::create(Animate::create(pHurtAction), clearCF, NULL));
}

void TowerBall::missAtkTarget() {
	CC_SAFE_RELEASE_NULL(_pAtkTarget);
	_doActionSprite->setVisible(false); //��ֹ����
}