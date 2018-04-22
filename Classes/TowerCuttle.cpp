//
//  TowerCuttle.cpp
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-19.
//  
//
#include "TowerCuttle.h"
#include "MonsterBase.h"
#include "BarrierBase.h"
#include "MonsterManager.h"
#include "BarrierManager.h"
#include "SoundUtil.h"
#include "BulletBase.h"
#include "CsvUtil.h"


bool TowerCuttle::init()
{
	bool bRet = false;
	do
	{
		//确保塔的基类初始化
		CC_BREAK_IF(!TowerBase::init(rId));
		//大章鱼没有旋转效果，需要注销调度器
		unschedule(schedule_selector(TowerCuttle::doRotation));

		_doAnimationSprite = Sprite::create();
		//设置图层不可见；
		_doAnimationSprite->setVisible(false);
		addChild(_doAnimationSprite);

		bRet = true;
	} while (0);
	return bRet;
}
void TowerCuttle::fire(float dt) {
	if (!_pAtkTarget || _pAtkTarget->getIsDead()) return;

	//创建攻击效果动画
	Animation * pAnimation = Animation::create();
	for (int i = 1; i <= 3; i++) {
		std::string SpriteFrameName = "P" + _sModelName + StringUtils::format("1%d.png", i);
		pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SpriteFrameName));
	}
	pAnimation->setDelayPerUnit(0.03);
	pAnimation->setLoops(1); //循环一次播放就可以了，循环的工作是调度器那边的


	//攻击效果精灵启动
	_doAnimationSprite->setVisible(true);

	//子弹动画启动
	BulletDoAction();

	//播放攻击声音
	SoundUtil::getInstance()->playEffectSound("Music/Towers/Cuttle.mp3");


	CallFunc * pCallFunc = CallFunc::create([=]() {
		attack();
		_doAnimationSprite->setVisible(false);
	});

	_doAnimationSprite->runAction(Sequence::create(Animate::create(pAnimation),pCallFunc, NULL));
}
void TowerCuttle::attack()
{
	atk._enAtkState = 1;
	atk._iAtk = _iBulletId;
	atk._iDuration = 0;

	/*************************************************************/
	/**-----------------------攻击游戏主逻辑-----------------------**/
	/*************************************************************/

	//受伤动画启动
	Animation * pHurtAction = Animation::create();
	for (int i = 1; i < 4; i++)
	{
		std::string hurtSpriteName = StringUtils::format("PCuttle0%d.png", i);
		pHurtAction->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(hurtSpriteName));
	}
	pHurtAction->setDelayPerUnit(0.03);
	pHurtAction->setLoops(1);

	Rect rect;
	//todo 这个范围应该以文件的为准
	if (getIId() == 40) { rect = Rect(this->getPositionX() - 100, this->getPositionY() - 100, 200, 200); }
	if (getIId() == 41) { rect = Rect(this->getPositionX() - 120, this->getPositionY() - 120, 240, 240); }
	if (getIId() == 42) { rect = Rect(this->getPositionX() - 140, this->getPositionY() - 140, 280, 280); }

	//先检测怪物
	Vector<MonsterBase *>  MonsterVector = Vector<MonsterBase *>(MonsterManager::getInstance()->getMonsterVec());
	for (int i = 0; i < MonsterVector.size(); i++)
	{
		MonsterBase * pMonster = (MonsterBase *)(MonsterVector.at(i));
		if (rect.intersectsRect(pMonster->getBoundingBox())) //碰撞检测
		{
			pMonster->beHurt(atk);
			//用于显示受伤动画的受伤精灵启动
			Sprite * pMonsterHurt = Sprite::create();
			pMonster->addChild(pMonsterHurt);
			//受伤精灵显示动画
			CallFunc * pClear = CallFunc::create([=]() 
			{ pMonsterHurt->removeFromParentAndCleanup(true); });
			pMonsterHurt->runAction(Sequence::create(Animate::create(pHurtAction), pClear, nullptr));
		}
		if (pMonster->getIHp() <= 0 || pMonster->getIsDead())
		{
			MonsterVector.eraseObject(pMonster);
		}
	}

	//再检测障碍物
	Vector<BarrierBase *> BarrierVector = Vector<BarrierBase *>(BarrierManager::getInstance()->getBarrierVec());
	for (int i = 0; i < BarrierVector.size(); i++)
	{
		BarrierBase * pBarrier = (BarrierBase *)(MonsterVector.at(i));
		if (rect.intersectsRect(pBarrier->getBoundingBox()))
		{
			pBarrier->beHurt(atk);
			Sprite * pBarrierHurt = Sprite::create();
			pBarrier->addChild(pBarrierHurt);
			CallFunc * pClear = CallFunc::create([=]() 
			{ pBarrierHurt->removeFromParentAndCleanup(true); });
			pBarrierHurt->runAction(Sequence::create(Animate::create(pHurtAction), pClear, NULL));
		}
		if (pBarrier->getIHp() <= 0 || pBarrier->getIsDead())
		{
			BarrierVector.eraseObject(pBarrier);
		}

	}

}

void TowerCuttle::BulletDoAction()
{
	//攻击子弹动画启动
	Animation * pAnimation2 = Animation::create();
	for (int i = 1; i <= 2; i++)
	{
		std::string SpriteFrameName = "P" + _sModelName + StringUtils::format("%d.png", i);
		pAnimation2->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SpriteFrameName));
	}
	pAnimation2->setDelayPerUnit(0.1);
	pAnimation2->setLoops(1);

	_doAnimationSprite->runAction(Sequence::create(Animate::create(pAnimation2),  NULL));
}

void TowerCuttle::bulletMoveToFar()
{

	atk._enAtkState = 1;
	atk._iAtk = _iBulletId;
	atk._iDuration = 0;

	if (_pAtkTarget->getIsDead())
	{
		//如果攻击目标已经死掉，从父节点中删去，设置死亡并返回；
		removeFromParent();
		setIsDead(true);
		return;
	}
	BulletDoAction();

	auto deadActionCF = CallFunc::create([=]()
	{
		//如果攻击目标存在并没有死，打他；
		if (_pAtkTarget != nullptr && !_pAtkTarget->getIsDead())
			_pAtkTarget->beHurt(atk);
		//执行死亡动画；
		deadAction(_sName);
	});
	//普通的攻击，不是穿透攻击；
	Vec2 MovetoPosition = _pAtkTarget->getPosition() - this->getPosition();
	float MoveDistance = this->getPosition().distance(_pAtkTarget->getPosition());
	this->runAction(Sequence::create(MoveBy::create(MoveDistance / _iSpeed, MovetoPosition), deadActionCF, NULL));
	//TODO:_iSpeed不知道怎么读；
}
