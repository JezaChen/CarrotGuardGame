#pragma once
//
// BullePin.cpp
// CarrotFantasy
//
// Created by 何泓兵 on 18-4-11.
//
//
#include "BulletPin.h"
#include "BulletPin.h"
#include "VictimEntityBase.h"

bool BulletPin::init(const int & rId, VictimEntityBase *rVictimEntity)
{
	bool bRet = false;
	do
	{
		//保证子弹基类的初始化成功；
		CC_BREAK_IF(!BulletBase::init(rId, rVictimEntity));

		bRet = true;
	} while (0);
	return bRet;
}

BulletPin * BulletPin::create(const int & rId, VictimEntityBase *rVictimEntity)
{
	//分配内存给子弹指针；
	BulletPin * pBullet = new BulletPin();
	if (pBullet && pBullet->init(rId, rVictimEntity))
	{
		//初始化成功，设置自动释放；
		pBullet->autorelease();
		return pBullet;
	}
	//不成功就删除它；
	CC_SAFE_DELETE(pBullet);
	return nullptr;
}

void BulletPin::doAction()
{

	for (int i = 1; i <= _IAnimationFrameCount; ++i)
	{
		std::string SpriteFrameName = _sModelName + StringUtils::format("%d.png", i);
		_pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SpriteFrameName));
	}
	//设置延迟时间；
	_pAnimation->setDelayPerUnit(0.05);
	//无限执行，一直有弹射出；
	_pAnimation->setLoops(-1);
	//运行动画；
	getSprite()->runAction(Animate::create(_pAnimation));
}
//重写了BulletBase里的doMove()；
void BulletPin::doMove() {

	if (_pAtkTarget->getIsDead())
	{
		//如果攻击目标已经死掉，从父节点中删去，设置死亡并返回；
		removeFromParent();
		setIsDead(true);
		return;
	}
	doAction();

	auto deadActionCF = CallFunc::create([=]()
	{
		//如果攻击目标存在并没有死，打他；
		if (_pAtkTarget != nullptr && !_pAtkTarget->getIsDead())
			_pAtkTarget->beHurt(getAtkPro());
		//执行死亡动画；
		deadAction(_sName);
	});
	//这个斜边参数没有用到，莫名其妙；
	float Hypotenuse = Vec2::ZERO.distance(Director::getInstance()->getVisibleSize());
	//普通的攻击，不是穿透攻击；
	Vec2 MovetoPosition = _pAtkTarget->getPosition() - this->getPosition();
	float MoveDistance = this->getPosition().distance(_pAtkTarget->getPosition());
	this->runAction(Sequence::create(MoveBy::create(MoveDistance / _iSpeed, MovetoPosition), deadActionCF, NULL));
}