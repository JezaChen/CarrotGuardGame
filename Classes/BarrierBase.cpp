//
//  BarrierBase.cpp
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-8.
//
//  有一个空的函数

#include "BarrierBase.h"
#include "BarrierManager.h"
#include "MapUtil.h"

bool BarrierBase::init(const int &rId)
{
	bool bRet = false;

	do
	{
		CC_BREAK_IF(!VictimEntityBase::init(rId, BARRIERCSVFILE)); //调用父类的初始化，自上而下完成初始化操作
		BarrierManager::getInstance()->addBarrier(this); //往管理类注册自己
		bRet = true;
	} while (0);

	return bRet;
}

BarrierBase * BarrierBase::create(const int &rId) 
{

	BarrierBase * pBarriers = new BarrierBase(); //new一个出来

	if (pBarriers && pBarriers->init(rId)) //进行初始化操作
	{
		pBarriers->autorelease();
		return pBarriers; //要是初始化成功了，出厂
	}
	CC_SAFE_DELETE(pBarriers);
	return nullptr;
}

void BarrierBase::deadAction(const std::string &rSDeadImageFile)
{
	NOTIFY->postNotification("BarrierDead", this); //发出障碍物挂掉的通知
	MapUtil::getInstance()->removeBarrierRect(getPosition()); //地图去除障碍物，变成炮塔可用位置
	VictimEntityBase::deadAction();
}



