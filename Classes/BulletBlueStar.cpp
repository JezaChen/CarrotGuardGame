//
// BulletBlueStar.cpp
// CarrotFantasy
//
// Created by 何泓兵 on 18-4-11.
//
//
#include "BulletBlueStar.h"
#include "VictimEntityBase.h"
#include "MonsterManager.h"
#include "MonsterBase.h"
#include "BarrierManager.h"
#include "BarrierBase.h"

bool BulletBlueStar::init(const int & rId, VictimEntityBase *rVictimEntity)
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

BulletBlueStar * BulletBlueStar::create(const int & rId, VictimEntityBase *rVictimEntity)
{
	//分配内存给子弹指针；
	BulletBlueStar * pBullet = new BulletBlueStar();
	//初始化成功；
	if (pBullet && pBullet->init(rId, rVictimEntity))
	{
		//设置自动释放；
		pBullet->autorelease();
		return pBullet;
	}
	//不成功就删除它；
	CC_SAFE_DELETE(pBullet);
	return nullptr;
}

void BulletBlueStar::doAction()
{
	//子弹不停地瞄准(旋转瞄准);
	getSprite()->runAction(RepeatForever::create(RotateBy::create(0.7, 360)));
}

void BulletBlueStar::doMove() {
	if (_pAtkTarget->getIsDead())
	{
		//如果攻击目标已经死掉，从父节点中删去，设置死亡并返回；
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
		std::string SpriteFrameName = StringUtils::format("PBStar-1%d.png", i);
		pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SpriteFrameName));
	}
	//设置动画延迟时间；
	pAnimation->setDelayPerUnit(0.05);
	//运行一次即可；
	pAnimation->setLoops(1);

	auto deadActionCF = CallFunc::create([=]()
	{

		Rect rect = Rect(_pAtkTarget->getPositionX() - 70, _pAtkTarget->getPositionY() - 70, 140, 140);
		//怪物的动画帧数不等于0；
		if (_pAtkTarget->getAnimationFrameCount() != 0)
		{
			//获取怪物vector；
			Vector<MonsterBase *> MonsterVector = Vector<MonsterBase *>(MonsterManager::getInstance()->getMonsterVec());
            for (int i = MonsterVector.size() - 1; i >= 0; i--)
			{
				MonsterBase * pMonster = (MonsterBase *)(MonsterVector.at(i));
				//检测矩形相交，即检测是否击中；
				if (rect.intersectsRect(pMonster->getBoundingBox()))
				{
					//击中，设置伤害；
					pMonster->beHurt(getAtkPro());
				}
				//打死了；
				if (pMonster->getIHp() <= 0 || pMonster->getIsDead())
				{
					/*mIter = (auto)*/
					//清除；
					MonsterVector.eraseObject(pMonster);
				}
			}
		}
		else//为0的是障碍物的动画帧数；
		{
			Vector<BarrierBase *> BarrierVector = Vector<BarrierBase *>(BarrierManager::getInstance()->getBarrierVec());
            for (int i = BarrierVector.size() - 1; i >= 0; i--)
			{
				BarrierBase * pBarrier = (BarrierBase *)(BarrierVector.at(i));
				if (rect.intersectsRect(pBarrier->getBoundingBox()))
				{
					//击中，设置伤害；
					pBarrier->beHurt(getAtkPro());
				}
				//打死了
				if (pBarrier->getIHp() <= 0 || pBarrier->getIsDead())
				{
					/*bIter = (auto)*/ 
					//清除；
					BarrierVector.eraseObject(pBarrier);
				}
			}
		}
		deadAction(_sName);
	});
	//移动的坐标；
	Vec2 MovetoPosition = _pAtkTarget->getPosition() - this->getPosition();
	//移动的距离；
	float MoveDistance = this->getPosition().distance(_pAtkTarget->getPosition());
	//执行动画；
	getSprite()->runAction(Sequence::create(MoveBy::create(MoveDistance / _iSpeed, MovetoPosition), Animate::create(pAnimation), deadActionCF, NULL));
}