//
//Carrot.cpp
//CarrotFantasy
//
//Created by 何泓兵 on 18-4-11
//
//
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
		//创建萝卜的实体，为了方便继承了怪物实体基类；
		CC_BREAK_IF(!Entity::init(18, MONSTERCSVFILE));
		//萝卜生命值；
		iHp = 10;
		//设置萝卜的生命值；
		GameManager::getInstance()->setICarrotHp(iHp);
		//获取萝卜的移动位置；
		auto aPoints = MapUtil::getInstance()->getMovePoses();
		//设置锚点；
		getSprite()->setAnchorPoint(Vec2(0.5, 0));
		//萝卜的位置设定；
		this->setPosition((*(aPoints.end() - 2)).x + getContentSize().width / 2 - 20, (*(aPoints.end() - 2)).y - getContentSize().height / 2);
		//萝卜生命值精灵帧；
		_HpSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("BossHP10.png"));
		//设置萝卜生命值图层的位置；
		_HpSprite->setPosition(*(aPoints.end() - 1) - *(aPoints.end() - 2) + Vec2(-20, 10));
		//设置完毕添加进去；
		addChild(_HpSprite);
		//设置观察通知，发出字符串"CarrotHurt"，就用CarrotHurt函数处理
		NOTIFY->addObserver(this, callfuncO_selector(Carrot::CarrotBeHurt), "CarrotHurt", nullptr);
		//注册萝卜被玷污事件；
		registerCarrotTouchEvent();
		//TODO；
		srand(time(0));
		//每六秒胡萝卜卖一次萌；
		schedule(schedule_selector(Carrot::doAction), 6);

		bret = true;
	} while (0);

	return  bret;
}

void Carrot::registerCarrotTouchEvent()
{
	//设置创建单点触摸；
	auto pTouchEvent = EventListenerTouchOneByOne::create();

	pTouchEvent->onTouchBegan = [=](Touch * t, Event * e)
	{
		//如果触摸点在胡萝卜的框图内；
		if (getBoundingBox().containsPoint(t->getLocation())) 
		{
			//获取胡萝卜精灵；
			auto pCarrot = getSprite();
			//停止任何动作；
			pCarrot->stopAllActions();
			//设置不旋转；
			pCarrot->setRotation(0);
			//todo
			pCarrot->setTexture(SpriteFrameCache::getInstance()->getSpriteFrameByName(_sModelName + PHOTOPOSTFIX)->getTexture());
			pCarrot->runAction(doShakeOrBlink(10, 9));
		}
		return false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(pTouchEvent, getSprite());
}

ActionInterval * Carrot::doShakeOrBlink(int iImageFirstNumber, int iImageCount)
{
	//获取实例；
	auto cache = SpriteFrameCache::getInstance();
	//创建动画；
	Animation * pAnimation = Animation::create();
	std::string sSpriteFrameName;
	for (int i = iImageFirstNumber; i < iImageFirstNumber + iImageCount; i++)
	{
		std::string sSpriteFrameName = _sName + StringUtils::format("%2d.png", i);
		pAnimation->addSpriteFrame(cache->getSpriteFrameByName(sSpriteFrameName));
	}
	pAnimation->addSpriteFrame(cache->getSpriteFrameByName(_sModelName + PHOTOPOSTFIX));
	//设置延迟时间；
	pAnimation->setDelayPerUnit(0.1);
	//运行一次动画即可；
	pAnimation->setLoops(1);
	Animate * pAnimate = Animate::create(pAnimation);

    //胡萝卜随机发出卖萌声音；
    int tRandom = rand() % 3;
    SoundUtil::getInstance()->playEffectSound(StringUtils::format(CARROT, tRandom + 1));

	return pAnimate;
}

void Carrot::doAction(float t)
{
	//停止动作；
	getSprite()->stopAllActions();
    int tRandom = rand() % 3;
	switch (tRandom)
	{
		//按随机方式确立执行胡萝卜的卖萌动画；
	case 0: getSprite()->runAction(doShakeOrBlink(10, 9));
		break;
	case 1: getSprite()->runAction(doShakeOrBlink(21, 3));
		break;
		//胡萝卜摆式卖萌；
	case 2: getSprite()->runAction(Sequence::create(RotateBy::create(0.2, -20), RotateBy::create(0.2, 20), RotateBy::create(0.2, 30), RotateBy::create(0.2, -30), NULL));
		break;
	default:
		break;
	}

}

void Carrot::CarrotBeHurt(Ref * pRef)
{
	//被弄到了；
	SoundUtil::getInstance()->playEffectSound(CARROTCRASH);
	MonsterBase * pMonster = (MonsterBase *)pRef;
	//生命值减；
	iHp -= pMonster->getIAtk();
	if (iHp <= 0)
	{
		//设置胡萝卜生命为0；
		GameManager::getInstance()->setICarrotHp(0);
		auto tGameEndType = en_GameLose;
		//发出通知，游戏失败，兄贵继续努力；
		NOTIFY->postNotification("gameEnd", reinterpret_cast<Ref*>(&tGameEndType));
		NOTIFY->removeAllObservers(this);
		return;
	}
	//更新胡萝卜精灵生命值；
	GameManager::getInstance()->setICarrotHp(iHp);
	//TODO;
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
