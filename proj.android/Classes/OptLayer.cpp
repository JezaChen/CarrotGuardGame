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
        _pTowerOptBtn = TowerOptBtn::create();
        _pTowerOptBtn->setName("TowerOptBtn");
        _pTowerOptBtn->setTag(0);
        _pForbiddenSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("forbidden.png"));
        _pForbiddenSprite->setVisible(false);
        addChild(_pForbiddenSprite);
        addChild(_pTowerOptBtn);
        listenClick();
        bRet = true;
    } while (0);

    return bRet;
}

void OptLayer::listenClick()
{
    auto listen = EventListenerTouchOneByOne::create();
    listen->onTouchBegan = [=](Touch* t, Event* e) {
        auto tPos = t->getLocation();

        if (tPos.y > 590) return true;
        if (_pTowerOptBtn->getTag()) {
            _pTowerOptBtn->setTag(0);
            _pTowerOptBtn->hideTowerOpt();
        }
        else {
            Carrot* carrot = dynamic_cast<GameScene*>(Director::getInstance()->getRunningScene())->getCarrot();
            if (carrot->getBoundingBox().containsPoint(t->getLocation())) {
                return true;
            }
            for (auto & toweritem : TowerManager::getInstance()->getTowerVec()) {
                if (toweritem->getBoundingBox().containsPoint(t->getLocation())) {
                    _pTowerOptBtn->setTag(1);
                    _pTowerOptBtn->setPosition(toweritem->getPosition());
                    _pTowerOptBtn->showTowerOpt();
                    _pTowerOptBtn->gradeTowerMenu(toweritem);
                    return true;
                }
            }
            for (auto & blankitem : MapUtil::getInstance()->getEffectTowerPoses()) {
                if (blankitem.containsPoint(t->getLocation())) {
                    _pTowerOptBtn->setTag(1);
                    _pTowerOptBtn->setPosition(blankitem.origin + blankitem.size / 2);
                    _pTowerOptBtn->showTowerOpt();
                    _pTowerOptBtn->showCreateMenu();
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
            _pForbiddenSprite->setVisible(true);
            _pForbiddenSprite->runAction(Sequence::create(FadeIn::create(0.1), FadeOut::create(1), NULL));
            _pForbiddenSprite->setPosition(t->getLocation());
        }

        return true;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listen, this);
}
