//
//  BarriersLayer.cpp
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-8.
//
//

#include "BarriersLayer.h"
#include "BarrierBase.h"
#include "BarrierManager.h"
#include "MapUtil.h"
bool BarriersLayer::init()
{
	bool bRet = false;

	do
	{
		//自上而下的初始化函数
		CC_BREAK_IF(!EntityLayerBase::init());
		NOTIFY->addObserver(this, callfuncO_selector(BarriersLayer::DeleteBarrierLayer), "BarrierClean", nullptr);
		bRet = true;
	} while (0);

	return bRet;
}

void BarriersLayer::DeleteBarrierLayer(Ref* rBarrierVec)
{
	//出现一次消失一次；
	auto aFadeIn = FadeIn::create(0.5f);
	auto aFadeOut = FadeOut::create(0.5f);

	Sequence *_pFadeSequence = Sequence::create(aFadeIn, DelayTime::create(0.5f), aFadeOut, nullptr);

		auto aSprite = Sprite::createWithSpriteFrameName("targetscleard_CN.png");
		aSprite->setPosition(480,100);

	    addChild(aSprite, 1);
		aSprite->runAction(_pFadeSequence);
}




