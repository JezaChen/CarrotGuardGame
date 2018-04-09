//
//  MoveControllerBase.cpp
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-9.
//  存在不懂问题
//

#include "MoveControllerBase.h"
#include "MapUtil.h"
#define STEP 10.0
bool MoveControllerBase::init(MonsterBase * pMonster)
{
	if (!Node::init()) {
		return false;
	}

	setMonster(pMonster);
	_iMonsterSpeed = _pMonster->getISpeed();
	_pMonster->addChild(this);

	auto Points = MapUtil::getInstance()->getMovePoses();

	_pMapPoints = new std::vector<Vec2>();

	for (int i = 0; i < Points.size(); i++) {
		Vec2 t_point;
		if (_pMonster->getILevel() == 1) t_point.x = Points.at(i).x + _pMonster->getContentSize().width / 2 - 15;
		if (_pMonster->getILevel() == 2) t_point.x = Points.at(i).x + 30;
		if (_pMonster->getILevel() == 3) t_point.x = Points.at(i).x + 40;
		t_point.y = Points.at(i).y - 5;
		_pMapPoints->push_back(t_point);
	}
	_pMonster->setPosition(*_pMapPoints->begin());

	listenerMonster(STEP / _pMonster->getISpeed());

	return true;
}

MoveControllerBase * MoveControllerBase::create(MonsterBase * pMonster) 
{
	auto aMonster = new MoveControllerBase();
	if (aMonster && aMonster->init(pMonster)) 
	{
		aMonster->autorelease();
		return aMonster;
	}
	CC_SAFE_DELETE(aMonster);
	return nullptr;
}

void MoveControllerBase::setMonster(MonsterBase * pMonster)
{
	_pMonster = pMonster;
}

void MoveControllerBase::listenerMonster(float t)
{
	if (_pMonster->getIHp() <= 0 || _pMonster->getIsDead())return;
	erasePoint();
	Vec2 pot = *_pMapPoints->begin();
	if (pot.x < _pMonster->getPositionX()) {
		_pMonster->setIsLeft(true);
	}
	else {
		_pMonster->setIsLeft(false);
	}
	MoveBy * pStep;
	if (_pMonster->getPositionX() == pot.x) {
		if (_pMonster->getPositionY() <= pot.y) {
			pStep = MoveBy::create(t, Vec2(0, STEP));
		}
		else {
			pStep = MoveBy::create(t, Vec2(0, -STEP));
		}
	}
	else {
		if (_pMonster->getPositionX() <= pot.x) {
			pStep = MoveBy::create(t, Vec2(STEP, 0));
		}
		else {
			pStep = MoveBy::create(t, Vec2(-STEP, 0));
		}
	}
	auto pMoveCall = CallFuncN::create([=](Node * pSender) {
		this->listenerMonster(STEP / _pMonster->getISpeed());
	});
	Sequence * seq = Sequence::create(pStep, pMoveCall, NULL);
	if (!_pMonster->getIsLeft()) {
		_pMonster->getSprite()->setRotationSkewY(0);
	}
	else {
		_pMonster->getSprite()->setRotationSkewY(180);
	}

	int MonsterState = _pMonster->getIState();
	int State_Slow = MonsterState & 2;
	int State_Stop = MonsterState & 4;
	int State_Poison = MonsterState & 8;
	if (State_Slow && _pMonster->getFSlowDuration() > 0)
	{
		_pMonster->setISpeed(_iMonsterSpeed / 3);
		float StateTime = _pMonster->getFSlowDuration() - t;
		if (StateTime < 0) StateTime = 0;
		_pMonster->setFSlowDuration(StateTime);
		Sprite * pTemp = Sprite::create();
		pTemp->setPosition(_pMonster->getContentSize().width / 2, 40);
		_pMonster->getSprite()->addChild(pTemp);
		Animation * pAnimation = AnimationMaker(_pMonster->getIBulletStateType(), t);
		auto pCallFunc = CallFunc::create([=]() {
			pTemp->removeFromParentAndCleanup(true);
			if (_pMonster->getFSlowDuration() <= 0)
			{
				_pMonster->setISpeed(_iMonsterSpeed);
				_pMonster->setIState(_pMonster->getIState() & 13);
			}
		});
		Sequence * pSequence = Sequence::create(Animate::create(pAnimation), pCallFunc, NULL);
		pTemp->runAction(pSequence);
	}
	if (State_Poison && _pMonster->getfPoisonDuration() > 0)
	{
		float StateTime = _pMonster->getfPoisonDuration() - t;
		if (StateTime < 0) StateTime = 0;
		_pMonster->setfPoisonDuration(StateTime);
		AtkProperty atk;
		atk._enAtkState = 1;
		atk._iAtk = 2;
		atk._iDuration = 0;

		Sprite * pTemp = Sprite::create();
		pTemp->setPosition(_pMonster->getContentSize().width / 2, 40);
		_pMonster->getSprite()->addChild(pTemp);
		Animation * pAnimation = AnimationMaker(6, t);
		auto pCallFunc = CallFunc::create([=]() {
			if (!_pMonster->getIsDead()) _pMonster->beHurt(atk);
			if (_pMonster->getfPoisonDuration() <= 0)
			{
				_pMonster->setIState(_pMonster->getIState() & 7);
			}
			pTemp->removeFromParentAndCleanup(true);
		});
		pTemp->runAction(Sequence::create(Animate::create(pAnimation), pCallFunc, NULL));
	}
	if (State_Stop && _pMonster->getfStopDuration() > 0)
	{
		float StateTime = _pMonster->getfStopDuration() - t;
		if (StateTime < 0) StateTime = 0;
		_pMonster->setfStopDuration(StateTime);
		Sprite * pTemp = Sprite::create();
		pTemp->setPosition(_pMonster->getContentSize().width / 2, 40);
		_pMonster->getSprite()->addChild(pTemp);
		Animation * pAnimation = AnimationMaker(_pMonster->getIBulletStateType(), t);
		auto pCallFunc = CallFunc::create([=]() {
			if (_pMonster->getfStopDuration() <= 0)
			{
				_pMonster->setIState(_pMonster->getIState() & 11);
			}
			this->listenerMonster(STEP / _pMonster->getISpeed());
			pTemp->removeFromParentAndCleanup(true);
		});
		pTemp->runAction(Sequence::create(Animate::create(pAnimation), pCallFunc, NULL));
		return;
	}
	_pMonster->runAction(seq);
}

void MoveControllerBase::erasePoint() {
	if (_pMapPoints->size() == 1) {
		return;
	}
	if (_pMonster->getPosition() == *_pMapPoints->begin()) {
		_pMapPoints->erase(_pMapPoints->begin());
		if (_pMapPoints->size() == 1)
		{
			NOTIFY->postNotification("CarrotHurt", _pMonster);
			NOTIFY->postNotification("MonsterDead", _pMonster);
			_pMonster->setIsDead(true);
			_pMonster->removeFromParentAndCleanup(true);
		}
	}
}

MoveControllerBase::~MoveControllerBase()
{
	CC_SAFE_DELETE(_pMapPoints);
}

Animation * MoveControllerBase::AnimationMaker(int iBulletType, float t)
{
	Animation * pAnimation = Animation::create();
	if (iBulletType == 1)
	{
		//大便减速；
		pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PShit-11.png"));
		pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PShit-12.png"));
		pAnimation->setDelayPerUnit(t / 2);
	}
	else if (iBulletType == 5)
	{
		//蓝星星减速；
		pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PBStar-21.png"));
		pAnimation->setDelayPerUnit(t);
	}
	else if (iBulletType == 15 || iBulletType == 30 || iBulletType == 45)
	{
		//冰冻减速；
		pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PSnow01.png"));
		pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PSnow02.png"));
		pAnimation->setDelayPerUnit(t / 2);
	}
	else if (iBulletType == 6)
	{
		//放毒针减速；
		pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PPin01.png"));
		pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PPin02.png"));
		pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PPin03.png"));
		pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PPin04.png"));
		pAnimation->setDelayPerUnit(t / 4);
	}
	pAnimation->setLoops(1);
	return pAnimation;
}
