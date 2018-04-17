//
//  DesignLayer.cpp
//  CarrotFantasy
//
//  Created by ºÎãü±ø on 18-4-8.
//
//

#include "DesignLayer.h"



bool DesignLayer::init()
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

void DesignLayer::loadSource()
{
	auto apBg = Sprite::create("Themes/credits_bg.png");
	addChild(apBg);
}