//
//  MonsterBase.cpp
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-9.
//
//

#include "MonsterBase.h"
#include "MonsterManager.h"
#include "MoveControllerBase.h"
#include "SoundUtil.h"
#include "DynamicPropertyInterface.h"

bool MonsterBase::init(const int &rIId)
{
	bool bRet = false;

	do
	{
		//两个父类初始化
		CC_BREAK_IF(!VictimEntityBase::init(rIId, MONSTERCSVFILE));
		CC_BREAK_IF(!DynamicPropertyInterface::init(rIId, MONSTERCSVFILE));

		_bIsLeft = true;
		createAnimation();
		doAction(0.15f);

		//TODO
		_pMoveController = MoveControllerBase::create(this);
		MonsterManager::getInstance()->addMonster(this); //自我初始化的时候直接往管理类添加(注册)自己
		bRet = true;
	} while (0);
	return  bRet;
}

MonsterBase * MonsterBase::create(const int &rIId)
{
	auto pMonster = new MonsterBase();
	if (pMonster->init(rIId)) {
		pMonster->autorelease(); //设置自动释放
		return pMonster;
	}
	CC_SAFE_DELETE(pMonster); //初始化不成功就删掉它
	return nullptr;
}


void MonsterBase::createAnimation()
{
	//因为怪兽毕竟要动的嘛
	//肯定要几张图要它动起来呀
	//障碍物又不会动，只有动态实体才能动
	//所以这个方法就是动态实体(DynamicPropertyInterface)的方法
	std::vector<std::string> tAniamtionFiles;
	for (int i = 1; i <= _IAnimationFrameCount; i++)
		tAniamtionFiles.push_back(_sModelName + StringUtils::format("%d.png", i)); //将几张帧放在向量中

	createDynamicEntityAnimation(tAniamtionFiles); //调用动态实体接口的方法让它动起来
}

void MonsterBase::doAction(const float &rDt)
{
	_pAnimation->setDelayPerUnit(rDt); //设置延迟时间
	getSprite()->runAction(Animate::create(_pAnimation));
}

void MonsterBase::deadAction(const std::string &rSDeadImageFile)
{
	MonsterSound(); //TODO 播放声音??
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
