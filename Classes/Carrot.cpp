#include "Carrot.h"
#include "MapUtil.h"
#include "MonsterBase.h"
#include "MonsterManager.h"
#include "GameManager.h"
#include "SoundUtil.h"

Carrot::~Carrot()
{
	NOTIFY->removeAllObservers(this);
}

bool Carrot::init()
{
	bool bret = false;

	do
	{
		CC_BREAK_IF(!Entity::init(18, MONSTERCSVFILE));

		iHp = 10;

		GameManager::getInstance()->setICarrotHp(iHp);
		auto tPoints = MapUtil::getInstance()->getMovePoses();
		getSprite()->setAnchorPoint(Vec2(0.5, 0));
		this->setPosition((*(tPoints.end() - 2)).x + getContentSize().width / 2 - 20, (*(tPoints.end() - 2)).y - getContentSize().height / 2);
		_HpSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("BossHP10.png"));
		_HpSprite->setPosition(*(tPoints.end() - 1) - *(tPoints.end() - 2) + Vec2(-20, 10));
		addChild(_HpSprite);

		NOTIFY->addObserver(this, callfuncO_selector(Carrot::CarrotBeHurt), "CarrotHurt", nullptr);
		registerCarrotTouchEvent();

		srand(time(0));
		schedule(schedule_selector(Carrot::doAction), 6);

		bret = true;
	} while (0);

	return  bret;
}

void Carrot::registerCarrotTouchEvent()
{
	auto pTouchEvent = EventListenerTouchOneByOne::create();

	pTouchEvent->onTouchBegan = [=](Touch * t, Event * e)
	{
		if (getBoundingBox().containsPoint(t->getLocation())) {
			auto pCarrot = getSprite();
			pCarrot->stopAllActions();
			pCarrot->setRotation(0);
			pCarrot->setTexture(SpriteFrameCache::getInstance()->getSpriteFrameByName(_sModelName + PHOTOPOSTFIX)->getTexture());
			pCarrot->runAction(doShakeOrBlink(10, 9));
		}
		return false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(pTouchEvent, getSprite());
}

ActionInterval * Carrot::doShakeOrBlink(int iImageFirstNumber, int iImageCount)
{
	auto cache = SpriteFrameCache::getInstance();
	Animation * pAnimation = Animation::create();
	std::string sSpriteFrameName;
	for (int i = iImageFirstNumber; i < iImageFirstNumber + iImageCount; i++)
	{
		std::string sSpriteFrameName = _sName + StringUtils::format("%2d.png", i);
		pAnimation->addSpriteFrame(cache->getSpriteFrameByName(sSpriteFrameName));
	}
	pAnimation->addSpriteFrame(cache->getSpriteFrameByName(_sModelName + PHOTOPOSTFIX));
	pAnimation->setDelayPerUnit(0.1);
	pAnimation->setLoops(1);
	Animate * pAnimate = Animate::create(pAnimation);
	return pAnimate;
}

void Carrot::doAction(float t)
{
	getSprite()->stopAllActions();
	int tRandom = rand() % 3;
	switch (tRandom)
	{
	case 0: getSprite()->runAction(doShakeOrBlink(10, 9));
		break;
	case 1: getSprite()->runAction(doShakeOrBlink(21, 3));
		break;
	case 2: getSprite()->runAction(Sequence::create(RotateBy::create(0.2, -20), RotateBy::create(0.2, 20), RotateBy::create(0.2, 30), RotateBy::create(0.2, -30), NULL));
		break;
	default:
		break;
	}
	SoundUtil::getInstance()->playEffectSound(StringUtils::format(CARROT, tRandom + 1));
}

void Carrot::CarrotBeHurt(Ref * pRef)
{
	SoundUtil::getInstance()->playEffectSound(CARROTCRASH);
	MonsterBase * pMonster = (MonsterBase *)pRef;
	iHp -= pMonster->getIAtk();
	if (iHp <= 0)
	{
		GameManager::getInstance()->setICarrotHp(0);
		auto tGameEndType = en_GameLose;
		NOTIFY->postNotification("gameEnd", reinterpret_cast<Ref*>(&tGameEndType));
		NOTIFY->removeAllObservers(this);
		return;
	}
	GameManager::getInstance()->setICarrotHp(iHp);
	Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(getSprite());
	unscheduleAllSelectors();
	_HpSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("BossHP%02d.png", iHp)));
	std::string HurtSpriteName;
	if (iHp == 5 || iHp == 7)
	{
		HurtSpriteName = StringUtils::format("hlb%d.png", iHp + 1);
	}
	else
	{
		HurtSpriteName = StringUtils::format("hlb%d.png", iHp);
	}
	getSprite()->stopAllActions();
	getSprite()->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(HurtSpriteName));
}

Rect Carrot::getBoundingBox()const
{
	return Rect(getPositionX() - getContentSize().width / 2, getPositionY(), getContentSize().width, getContentSize().height);
}
