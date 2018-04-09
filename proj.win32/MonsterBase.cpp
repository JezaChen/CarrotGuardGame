//
//  MonsterBase.cpp
//  CarrotFantasy
//
//  Created by ºÎãü±ø on 18-4-9.
//
//

#include "MonsterBase.h"
#include "MonsterManager.h"
#include "MoveControllerBase.h"
#include "SoundUtil.h"

bool MonsterBase::init(const int &rIId)
{
	bool bRet = false;

	do
	{
		CC_BREAK_IF(!VictimEntityBase::init(rIId, MONSTERCSVFILE));
		CC_BREAK_IF(!DynamicPropertyInterFace::init(rIId, MONSTERCSVFILE));
		_bIsLeft = true;
		createAnimation();
		doAction(0.15f);
		_pMoveController = MoveControllerBase::create(this);
		MonsterManager::getInstance()->addMonster(this);
		bRet = true;
	} while (0);
	return  bRet;
}

MonsterBase * MonsterBase::create(const int &rIId)
{
	auto pMonster = new MonsterBase();
	if (pMonster && pMonster->init(rIId)) {
		pMonster->autorelease();
		return pMonster;
	}
	CC_SAFE_DELETE(pMonster);
	return nullptr;
}

void MonsterBase::behurtAction()
{

}

void MonsterBase::createAnimation()
{
	std::vector<std::string> tAniamtionFiles;
	for (int i = 1; i <= _IAnimationFrameCount; i++)
		tAniamtionFiles.push_back(_sModelName + StringUtils::format("%d.png", i));
	createDynamicEntityAnimation(tAniamtionFiles);
}

void MonsterBase::doAction(const float &rDt)
{
	_pAnimation->setDelayPerUnit(rDt);
	getSprite()->runAction(Animate::create(_pAnimation));
}

void MonsterBase::deadAction(const std::string &rSDeadImageFile)
{
	MonsterSound();
	NOTIFY->postNotification("MonsterDead", this);
	getSprite()->removeAllChildrenWithCleanup(true);
	_pMoveController->stopAllActions();
	VictimEntityBase::deadAction();
}

void MonsterBase::MonsterSound()
{
	int fFigure = rand() % 3 + 1;
	if (_sName.find("land") != std::string::npos)
	{
		SoundUtil::getInstance()->playEffectSound(MONSTERMUSIC + StringUtils::format("Land11%d.mp3", fFigure));
	}
	else if (_sName.find("fly") != std::string::npos)
	{
		SoundUtil::getInstance()->playEffectSound(MONSTERMUSIC + StringUtils::format("Fat14%d.mp3", fFigure));
	}
	else if (_sName.find("fat") != std::string::npos)
	{
		SoundUtil::getInstance()->playEffectSound(MONSTERMUSIC + StringUtils::format("Fat14%d.mp3", fFigure));
	}
	else
	{
		SoundUtil::getInstance()->playEffectSound(MONSTERMUSIC + "BigBoss.mp3");
	}
}

void MonsterBase::setMaxSpeed(const int &iSpeed)
{
	setISpeed(iSpeed);
	_pMoveController->setIMonsterSpeed(iSpeed);
}
