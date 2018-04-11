//
//  BulletFactory.cpp
//  CarrotFantasy
//
//  Created by ºÎãü±ø on 18-4-10.
//
//

#include "BulletFactory.h"
#include "BulletBase.h"
#include "VictimEntityBase.h"
#include "TowerBase.h"


BulletBase *BulletFactory::createBullet(const int &rBulletId, TowerBase* rTower, VictimEntityBase *rVictimEntity)
{
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("Themes/Towers/TBottle-hd.plist", "Themes/Towers/TBottle-hd.png");
	cache->addSpriteFramesWithFile("Themes/Towers/TFan-hd.plist", "Themes/Towers/TFan-hd.png");
	cache->addSpriteFramesWithFile("Themes/Towers/TShit-hd.plist", "Themes/Towers/TShit-hd.png");

	auto pBullet = BulletBase::create(rBulletId, rVictimEntity);
	pBullet->setRotation(90 - 180 * (rVictimEntity->getPosition() - rTower->getPosition()).getAngle() / M_PI);
	if (pBullet->getIBulletType() == en_GunBullet) {
		pBullet->setPosition(rTower->getPosition() + Vec2(36 * sin(pBullet->getRotation() * M_PI / 180), 36 * cos(pBullet->getRotation() * M_PI / 180)));
	}
	else {
		pBullet->setPosition(rTower->getPosition());
	}

	pBullet->doMove();

	return pBullet;
}