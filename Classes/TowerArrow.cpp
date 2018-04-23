//
//  TowerArrow.cpp
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-23.
//
//
#include "TowerArrow.h"
#include "VictimEntityBase.h"
#include "MonsterBase.h"
#include "BarrierBase.h"
#include "MonsterManager.h"
#include "BarrierManager.h"
#include "SoundUtil.h"

bool TowerArrow::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!TowerBase::init(rId));

		_doAnimationSprite = Sprite::create();
		_doAnimationSprite->setAnchorPoint(Vec2(0.5, 0));
		_doAnimationSprite->setContentSize(Size(10, 1290));
		_doAnimationSprite->setVisible(false);

		addChild(_doAnimationSprite);
		bRet = true;
	} while (0);
	return bRet;
}
void TowerArrow::fire(float dt)
{
	if (!_pAtkTarget || _pAtkTarget->getIsDead()) return;


	//创建攻击时弓箭的动画
	Animation *pAnimation = Animation::create();
	for (int i = 1; i <= 2; i++)
	{

		std::string SpriteFrameName = "P" + _sName + StringUtils::format("0%d.png", i);

		pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SpriteFrameName));
	}
	pAnimation->setDelayPerUnit(0.1f);
	pAnimation->setLoops(1);
	SoundUtil::getInstance()->playEffectSound("Music/Towers/Arrow.mp3");

	//创建一个子精灵用于显示开火动画
	_doAnimationSprite->setVisible(true);

	CallFunc *pCallFunc = CallFunc::create([=]()
	{
		attack();
	});
	getSprite()->runAction(Sequence::create(Animate::create(pAnimation), pCallFunc, nullptr));
}

void TowerArrow::attack()
{
	//创建攻击属性
	AtkProperty atk;
	atk._enAtkState = 1;
	atk._iAtk = _iBulletId;
	atk._iDuration = 0;

	//攻击精灵启动
	_doAnimationSprite->setVisible(true);

	//攻击精灵角度与炮塔精灵的角度要一致
	_doAnimationSprite->setRotation(getSprite()->getRotation());

	//攻击精灵动画创建
	Animation *pAnimation = Animation::create();
	for (int i = 1; i <= 3; i++)
	{
		std::string SpriteFrameName = _sName + StringUtils::format("%d.png", i);
		pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SpriteFrameName));
	}
	pAnimation->setLoops(1);
	pAnimation->setDelayPerUnit(0.1f);
	CallFunc *pCallFunc = CallFunc::create([=]()
	{
		_doAnimationSprite->setVisible(false);
	});

	_doAnimationSprite->runAction(Sequence::create(Animate::create(pAnimation), pCallFunc, nullptr));

	//伤害动画启动
}
