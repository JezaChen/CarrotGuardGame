//
//  BarriersLayer.cpp
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-8.
//
//

#include "BarriersLayer.h"

bool BarriersLayer::init()
{
	bool bRet = false;

	do
	{
		//自上而下的初始化函数
		CC_BREAK_IF(!EntityLayerBase::init());
		bRet = true;
	} while (0);

	return bRet;
}



