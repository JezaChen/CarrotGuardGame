//
// BulletRocket.cpp
// CarrotFantasy
//
// Created by 何泓兵 on 18-4-11.
//
//

#include "BulletRocket.h"
#include "VictimEntityBase.h"

bool BulletRocket::init(const int & rId, VictimEntityBase *rVictimEntity)
{
	bool bRet = false;
	do
	{
		//确保子弹基类的成功初始化；
		CC_BREAK_IF(!BulletBase::init(rId, rVictimEntity));

		bRet = true;
	} while (0);
	return bRet;
}

BulletRocket * BulletRocket::create(const int & rId, VictimEntityBase *rVictimEntity)
{
	//分配内存；
	BulletRocket * pBullet = new BulletRocket();
	if (pBullet && pBullet->init(rId, rVictimEntity))
	{
		//初始化成功就设置自动释放；
		pBullet->autorelease();
		return pBullet;
	}
	//否则删掉他；
	CC_SAFE_DELETE(pBullet);
	return nullptr;
}

void BulletRocket::doAction()
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
//重写了BulletBase里的doMove(),因为火箭弹是能射穿的特殊防御塔；
void BulletRocket::doMove() 
{
	if (_pAtkTarget->getIsDead())
	{
		//如果攻击目标已经死掉，从父节点中删去，设置死亡并返回；
		removeFromParent();
		setIsDead(true);
		return;
	}
	doAction();
	//火箭弹能射穿怪物和障碍物；
	float Hypotenuse = Vec2::ZERO.distance(Director::getInstance()->getVisibleSize());
	Vec2 MovetoPosition = Vec2(Hypotenuse * sin(this->getRotation() * M_PI / 180), Hypotenuse * cos(this->getRotation() * M_PI / 180));
	float MoveDistance = MovetoPosition.distance(this->getPosition());
	//运行动画；
	this->runAction(MoveBy::create(MoveDistance / _iSpeed, MovetoPosition));
}