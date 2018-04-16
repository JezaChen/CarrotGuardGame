#pragma once
//
//  BulletFactory.cpp
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-10.
//
//

#include "BulletFactory.h"
#include "BulletBase.h"
#include "VictimEntityBase.h"
#include "TowerBase.h"


BulletBase *BulletFactory::createBullet(const int &rBulletId, TowerBase* rTower, VictimEntityBase *rVictimEntity)
{
	auto cache = SpriteFrameCache::getInstance();
	//通过plist切割png获取精灵帧；
	cache->addSpriteFramesWithFile("Themes/Towers/TBottle-hd.plist", "Themes/Towers/TBottle-hd.png");
	cache->addSpriteFramesWithFile("Themes/Towers/TFan-hd.plist", "Themes/Towers/TFan-hd.png");
	cache->addSpriteFramesWithFile("Themes/Towers/TShit-hd.plist", "Themes/Towers/TShit-hd.png");
	//从子弹基类创建子弹，传了攻击目标和id过来；
	auto pBullet = BulletBase::create(rBulletId, rVictimEntity);
	//设置子弹跟随怪物的方向旋转；
	pBullet->setRotation(90 - 180 * (rVictimEntity->getPosition() - rTower->getPosition()).getAngle() / M_PI);
	//射出类子弹需要调pos以便跑动；
	if (pBullet->getIBulletType() == en_GunBullet) 
	{
		pBullet->setPosition(rTower->getPosition() + Vec2(36 * sin(pBullet->getRotation() * M_PI / 180), 36 * cos(pBullet->getRotation() * M_PI / 180)));
	}
	//不是射出类的子弹就不用设置，直接获取塔的位置即可；
	else 
	{
		pBullet->setPosition(rTower->getPosition());
	}
	//子弹动起来；
	pBullet->doMove();

	return pBullet;
}