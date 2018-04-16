//
//  TowerBall.cpp
//  CarrotFantasy
//
//  Created by 何泓兵 x 陈建彰 on 18-4-12.
//  
//
#include "TowerBall.h"
#include "MonsterManager.h"
#include "MonsterBase.h"
#include "TowerManager.h"
#define CRIE(Atk)  (0.6 * ((Atk) - 9))

bool TowerBall::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!TowerBase::init(rId));
		if (_pTowerPanel)
			_pTowerPanel->removeFromParentAndCleanup(true);
		_doActionSprite = Sprite::create();
		addChild(_doActionSprite, 100);
		//精灵球没有旋转效果，所以要去除调度器
		unschedule(schedule_selector(TowerBall::doRocation));

		bRet = true;
	} while (0);
	return bRet;
}

void TowerBall::chooseAtkTarget() {

	auto tMonsterVec = MonsterManager::getInstance()->getMonsterVec();

	for (auto &iterMonster : tMonsterVec)
	{
		if (isInAtkRange(iterMonster->getPosition()))
		{
			fireAction(); //；立刻开火
			setAtkTarget(iterMonster);
			break;
		}
	}
}

void TowerBall::fire(float dt) {
	if (!_pAtkTarget || _pAtkTarget->getIsDead()) return;

	//创建攻击效果动画
	Animation * pAnimation = Animation::create();
	for (int i = 1; i <= 4; i++) {
		std::string SpriteFrameName = "P" + _sModelName + StringUtils::format("%d.png", i);
		pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SpriteFrameName));
	}
	pAnimation->setDelayPerUnit(0.03);
	pAnimation->setLoops(1); //循环一次播放就可以了，循环的工作是调度器那边的

    //动画精灵启动，用于启动上面创造的动画
	_doActionSprite->setVisible(true);
	//todo 这个缩放值得商榷
	_doActionSprite->setScale(this->getPosition().distance(_pAtkTarget->getPosition()) / _doActionSprite->getContentSize().height);
	_doActionSprite->setPosition((this->getPosition() + _pAtkTarget->getPosition()) / 2 - this->getPosition());
	//角度公式还是跟火烈炮筒一样的
	_doActionSprite->setRotation(90 - 180 * (_pAtkTarget->getPosition() - this->getPosition()).getAngle() / M_PI);
	_doActionSprite->runAction(Animate::create(pAnimation));

	//受伤精灵启动，用于显示怪兽的受伤动画
    //这个精灵作为怪兽精灵的子节点添加上去就可以了
	Sprite * pHurt = Sprite::create();
	_pAtkTarget->addChild(pHurt);
	Animation * pHurtAction = Animation::create();
	pHurtAction->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PBall01.png"));
	pHurtAction->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PBall02.png"));
	pHurtAction->setDelayPerUnit(0.05);
	pHurtAction->setLoops(1);
	CallFunc * clearCF = CallFunc::create([=]() { pHurt->removeFromParentAndCleanup(true); });

	//实质伤害效果启动
    //由于这个伤害效果没有对旁边怪物有附加伤害，所以就针对那个指定攻击怪物执行伤害函数
    //todo 随机数攻击法???
	AtkProperty atk;
	atk._enAtkState = 1;
	atk._iAtk = _iBulletId;
	atk._iDuration = 0;
	int CritPro = rand() % 10;
	if (CritPro > 0)
	{
		_pAtkTarget->beHurt(atk);
	}
	else
	{
		atk._iAtk = static_cast<int>(_iBulletId + CRIE(this->_iId) * _iBulletId);
		_pAtkTarget->beHurt(atk);
		pHurt->setScale(2);
	}

	pHurt->runAction(Sequence::create(Animate::create(pHurtAction), clearCF, NULL));
}

void TowerBall::missAtkTarget() {
	CC_SAFE_RELEASE_NULL(_pAtkTarget);
	_doActionSprite->setVisible(false); //终止攻击
}