//
//  TowerArrow.cpp
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-12.
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
	AtkProperty atk;
	atk._enAtkState = 1;
	atk._iAtk = _iBulletId;
	atk._iDuration = 1;

	/**************************************************************/
	/**-----------------------攻击游戏主逻辑-----------------------**/
	/**************************************************************/

}