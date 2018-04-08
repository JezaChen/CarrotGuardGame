//
//  DataCollectLayer.cpp
//  CarrotFantasy
//
//  Created by ºÎãü±ø on 18-4-8.
//
//

#include "DataCollectLayer.h"


bool DataCollectLayer::init()
{
	bool bRet = false;


	do
	{
		CC_BREAK_IF(!Layer::init());

		loadSource();

		bRet = true;
	} while (0);

	return bRet;
}

void DataCollectLayer::loadSource()
{
	auto pBg = Sprite::createWithSpriteFrameName("statistics_bg.png");
	addChild(pBg);
}