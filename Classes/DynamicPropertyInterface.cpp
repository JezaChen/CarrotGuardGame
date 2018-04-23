//
//  DynamicPropertyInterface.cpp
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-7.
//

#include "DynamicPropertyInterface.h"

DynamicPropertyInterface::~DynamicPropertyInterface()
{
	CC_SAFE_RELEASE_NULL(_pAnimation);
}

bool DynamicPropertyInterface::init(const int &rId, const std::string &rSCsvFileName)
{
	bool bRet = false;
	do
	{
		auto pCsvUtil = CsvUtil::getInstance();
		//创建动画，引用计数加一，避免自动释放；
		_pAnimation = Animation::create();
		_pAnimation->retain();
		_iAtk = pCsvUtil->getInt(rId, en_Atk, rSCsvFileName);
		_iSpeed = pCsvUtil->getInt(rId, en_Speed, rSCsvFileName);
		bRet = true;
	} while (0);

	return bRet;
}

void DynamicPropertyInterface::createDynamicEntityAnimation(const std::vector<std::string> &rAnimationFiles)
{
	auto pSpriteFrameCache = SpriteFrameCache::getInstance();
	for (auto &animationFile : rAnimationFiles)
		_pAnimation->addSpriteFrame(pSpriteFrameCache->getSpriteFrameByName(animationFile));
	//设置无限执行；
	_pAnimation->setLoops(-1);
}


