//
//  OptLayer.cpp
//  CarrotFantasy
//
//  Created by ºÎãü±ø on 18-4-16.
//
//

#include "OptLayer.h"
#include "MapUtil.h"
#include "TowerManager.h"
#include "TowerBase.h"
#include "BarrierBase.h"
#include "BarrierManager.h"
#include "TowerOptBtn.h"
#include "TowerBase.h"
#include "MonsterManager.h"
#include "MonsterBase.h"
#include "SoundUtil.h"
#include "Carrot.h"
#include "GameScene.h"

bool OptLayer::init()
{
	bool bRet = false;

	do
	{
		CC_BREAK_IF(!Layer::init());
		towerOptBtn = TowerOptBtn::create();
		towerOptBtn->setName("towerOptBtn");
		towerOptBtn->setTag(0);
		_pforbiddenSp = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("forbidden.png"));
		_pforbiddenSp->setVisible(false);
		addChild(_pforbiddenSp);
		addChild(towerOptBtn);
		listener();
		bRet = true;
	} while (0);

	return bRet;
}

void OptLayer::listener()
{
	auto listen = EventListenerTouchOneByOne::create();
	listen->onTouchBegan = [=](Touch* t, Event* e) {
		auto tPos = t->getLocation();

		if (tPos.y > 590) return true;
		if (towerOptBtn->getTag()) {
			towerOptBtn->setTag(0);
			towerOptBtn->hideTowerOpt();
		}
		else {
			Carrot* carrot = dynamic_cast<GameScene*>(Director::getInstance()->getRunningScene())->getCarrot();
			if (carrot->getBoundingBox().containsPoint(t->getLocation())) {
				return true;
			}
			for (auto & toweritem : TowerManager::getInstance()->getTowerVec()) {
				if (toweritem->getBoundingBox().containsPoint(t->getLocation())) {
					towerOptBtn->setTag(1);
					towerOptBtn->setPosition(toweritem->getPosition());
					towerOptBtn->showTowerOpt();
					towerOptBtn->gradeTowerMenu(toweritem);
					return true;
				}
			}
			for (auto & blankitem : MapUtil::getInstance()->getEffectTowerPoses()) {
				if (blankitem.containsPoint(t->getLocation())) {
					towerOptBtn->setTag(1);
					towerOptBtn->setPosition(blankitem.origin + blankitem.size / 2);
					towerOptBtn->showTowerOpt();
					towerOptBtn->showCreateMenu();
					return true;
				}

			}
			auto tMonsterVec = MonsterManager::getInstance()->getMonsterVec();
			for (auto & monsterIter : tMonsterVec)
			{
				if (monsterIter->getBoundingBox().containsPoint(t->getLocation()))
				{
					auto tMonsterLockFlag = monsterIter->getAtkTarget();
					BarrierManager::getInstance()->clearBeAtkLockState();
					MonsterManager::getInstance()->clearBeAtkLockState();
					monsterIter->setAtkTarget(!tMonsterLockFlag);
					return true;
				}
			}
			auto tBarrierVec = BarrierManager::getInstance()->getBarrierVec();
			for (auto & barrierItem : tBarrierVec)
			{
				if (barrierItem->getBoundingBox().containsPoint(t->getLocation()))
				{
					auto tBarrierLockFlag = barrierItem->getAtkTarget();
					MonsterManager::getInstance()->clearBeAtkLockState();
					BarrierManager::getInstance()->clearBeAtkLockState();
					barrierItem->setAtkTarget(!tBarrierLockFlag);
					return true;
				}
			}
			SoundUtil::getInstance()->playEffectSound(SELECTFAULT);
			_pforbiddenSp->setVisible(true);
			_pforbiddenSp->runAction(Sequence::create(FadeIn::create(0.1), FadeOut::create(1), NULL));
			_pforbiddenSp->setPosition(t->getLocation());
		}

		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listen, this);
}
