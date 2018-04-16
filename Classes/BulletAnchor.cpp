#pragma once

#include "BulletAnchor.h"
#include "VictimEntityBase.h"
#include "MonsterManager.h"
#include "MonsterBase.h"
#include "BarrierManager.h"
#include "BarrierBase.h"



bool BulletAnchor::init(const int & rId, VictimEntityBase *rVictimEntity)
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

BulletAnchor * BulletAnchor::create(const int & rId, VictimEntityBase *rVictimEntity)
{
	//分配内存；
	BulletAnchor * pBullet = new BulletAnchor();
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

void BulletAnchor::doAction()
{
	//子弹不停地瞄准(旋转瞄准);
	getSprite()->runAction(RepeatForever::create(RotateBy::create(0.7, 360)));
}

void BulletAnchor::doMove() 
{
	//如果攻击目标已经死掉，从父节点中删去，设置死亡并返回；
	if (_pAtkTarget->getIsDead())
	{
		removeFromParent();
		setIsDead(true);
		return;
	}
	//瞄准；
	doAction();

	Animation * pAnimation = Animation::create();
	//七个开花动画，依次创建；
	for (int i = 1; i < 7; i++)
	{
		std::string SpriteFrameName = StringUtils::format("PAnchor-1%d.png", i);
		pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SpriteFrameName));
	}
	//设置动画延迟时间；
	pAnimation->setDelayPerUnit(0.05);
	//运行一次即可；
	pAnimation->setLoops(1);

	auto deadActionCF = CallFunc::create([=]() 
	{
		//获取障碍物向量；
		auto BarrierVector = BarrierManager::getInstance()->getBarrierVec();
		//获取障碍物向量大小；
		auto  size = BarrierVector.size();
		if (size > 0)
		{
			//锚的对障碍物攻击是具有随机属性的；
			int num1 = rand() % size;
			int num2 = rand() % size;
			int num3 = rand() % size;
			//设置锚对随机障碍物的攻击目标；
			//auto barrierPoint = (BarrierVector.at(num1))->getPosition();
			auto barrierPoint1 = (BarrierVector.at(num1))->getPosition();
			auto barrierPoint2 = (BarrierVector.at(num2))->getPosition();
			auto barrierPoint3 = (BarrierVector.at(num3))->getPosition();
			//对三个障碍物设置三个动作；
			MoveTo * move1 = MoveTo::create(2.5f, barrierPoint1);
			MoveTo * move2 = MoveTo::create(2.0f, barrierPoint2);
			MoveTo * move3 = MoveTo::create(1.5f, barrierPoint3);
			//创建三种旋转动作，角度不同；
			RotateBy * rotate1 = RotateBy::create(0.05f, 30);
			RotateBy * rotate2 = RotateBy::create(0.05f, 35);
			RotateBy * rotate3 = RotateBy::create(0.05f, 25);
			//设置动作的延续；
			RepeatForever * rep1 = RepeatForever::create(rotate1);
			RepeatForever * rep2 = RepeatForever::create(rotate2);
			RepeatForever * rep3 = RepeatForever::create(rotate3);

			//创建精灵帧
			std::string SpriteFrameName = StringUtils::format("PAnchor%d2.png", getILevel());
			SpriteFrame * fileName = SpriteFrameCache::getInstance()->getSpriteFrameByName(SpriteFrameName);
			//创建等级最高时存在的三个反弹锚；
			auto Anchor1 = Sprite::createWithSpriteFrame(fileName);
			auto Anchor2 = Sprite::createWithSpriteFrame(fileName);
			auto Anchor3 = Sprite::createWithSpriteFrame(fileName);

			auto layer = Director::getInstance()->getRunningScene()->getChildByTag(1);
			//等级为1时只有一个反弹锚；
			if (getILevel() == 1)
			{
				Anchor1->setPosition(_pAtkTarget->getPosition());
				layer->addChild(Anchor1);

				auto dieCf = CallFunc::create([=]() 
				{
					//反弹锚给予随机障碍物伤害；
					BarrierVector.at(num1)->beHurt(getAtkPro());
					//击中后回收；
					Anchor1->removeFromParentAndCleanup(true);
				});
				//旋转起来；
				Anchor1->runAction(rep1);
				//反弹锚启动，攻击！
				Anchor1->runAction(Sequence::create(move1, Animate::create(pAnimation), dieCf, NULL));
			}
			//两个反弹锚；
			if (getILevel() == 2)
			{
				Anchor1->setPosition(_pAtkTarget->getPosition());
				layer->addChild(Anchor1);
				Anchor2->setPosition(_pAtkTarget->getPosition());
				layer->addChild(Anchor2);

				auto dieCf1 = CallFunc::create([=]() {
					BarrierVector.at(num1)->beHurt(getAtkPro());
					Anchor1->removeFromParentAndCleanup(true);
				});
				auto dieCf2 = CallFunc::create([=]() {
					BarrierVector.at(num2)->beHurt(getAtkPro());
					Anchor2->removeFromParentAndCleanup(true);
				});
				Anchor1->runAction(rep1);
				Anchor2->runAction(rep2);
				Anchor1->runAction(Sequence::create(move1, Animate::create(pAnimation), dieCf1, NULL));
				Anchor2->runAction(Sequence::create(move2, Animate::create(pAnimation), dieCf2, NULL));
			}
			//三个反弹锚；
			if (getILevel() == 3)
			{
				Anchor1->setPosition(_pAtkTarget->getPosition());
				layer->addChild(Anchor1);
				Anchor2->setPosition(_pAtkTarget->getPosition());
				layer->addChild(Anchor2);
				Anchor3->setPosition(_pAtkTarget->getPosition());
				layer->addChild(Anchor3);

				auto dieCf1 = CallFunc::create([=]() {
					BarrierVector.at(num1)->beHurt(getAtkPro());
					Anchor1->removeFromParentAndCleanup(true);
				});
				auto dieCf2 = CallFunc::create([=]() {
					BarrierVector.at(num2)->beHurt(getAtkPro());
					Anchor2->removeFromParentAndCleanup(true);
				});
				auto dieCf3 = CallFunc::create([=]() {
					BarrierVector.at(num3)->beHurt(getAtkPro());
					Anchor3->removeFromParentAndCleanup(true);
				});
				Anchor1->runAction(rep1);
				Anchor2->runAction(rep2);
				Anchor3->runAction(rep3);
				Anchor1->runAction(Sequence::create(move1, Animate::create(pAnimation), dieCf1, NULL));
				Anchor2->runAction(Sequence::create(move2, Animate::create(pAnimation), dieCf2, NULL));
				Anchor3->runAction(Sequence::create(move3, Animate::create(pAnimation), dieCf3, NULL));
			}
		}

		Rect rect = Rect(_pAtkTarget->getPositionX() - 100, _pAtkTarget->getPositionY() - 100, 200, 200);
		for (auto mIter = MonsterManager::getInstance()->getMonsterVec().begin(); mIter != MonsterManager::getInstance()->getMonsterVec().end(); mIter++)
		{
			MonsterBase * pMonster = (MonsterBase *)(*mIter);
			if (rect.intersectsRect(pMonster->getBoundingBox()))
			{//击中，设置伤害；
				pMonster->beHurt(getAtkPro());
			}
			//打死了；
			if (pMonster->getIHp() <= 0 || pMonster->getIsDead())
			{
				//为什么直接break？
				break;
			}
		}
		for (auto bIter = BarrierManager::getInstance()->getBarrierVec().begin(); bIter != BarrierManager::getInstance()->getBarrierVec().end(); bIter++)
		{
			BarrierBase * pBarrier = (BarrierBase *)(*bIter);
			if (rect.intersectsRect(pBarrier->getBoundingBox()))
			{
				//击中，设置伤害；
				pBarrier->beHurt(getAtkPro());
			}
			if (pBarrier->getIHp() <= 0 || pBarrier->getIsDead())
			{
				//打死了
				//TODO：为什么不清除？
				//BarrierVector.eraseObject(pBarrier);是不是应该加这句；
				break;
			}
		}
		deadAction(_sName);

	});
	//非穿透攻击，移动坐标；
	Vec2 MovetoPosition = _pAtkTarget->getPosition() - this->getPosition();
	//移动距离；
	float MoveDistance = this->getPosition().distance(_pAtkTarget->getPosition());
	//执行动画；
	getSprite()->runAction(Sequence::create(MoveBy::create(MoveDistance / _iSpeed, MovetoPosition), Animate::create(pAnimation), deadActionCF, NULL));

}
