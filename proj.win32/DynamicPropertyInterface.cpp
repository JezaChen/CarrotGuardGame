//
//  DynamicPropertyInterFace.cpp
//  CarrotFantasy
//
//  Created by ºÎãü±ø on 18-4-7.
//
//

#include "DynamicPropertyInterFace.h"

DynamicPropertyInterFace::~DynamicPropertyInterFace()
{
	CC_SAFE_RELEASE_NULL(_pAnimation);
}

bool DynamicPropertyInterFace::init(const int &rId, const std::string &rSCsvFileName)
{
	bool bRet = false;
	do
	{
		auto pCsvUtil = CsvUtil::getInstance();
		_pAnimation = Animation::create();
		_pAnimation->retain();
		_iAtk = pCsvUtil->getInt(rId, en_Atk, rSCsvFileName);
		_iSpeed = pCsvUtil->getInt(rId, en_Speed, rSCsvFileName);
		bRet = true;
	} while (0);

	return bRet;
}

void DynamicPropertyInterFace::createDynamicEntityAnimation(const std::vector<std::string> &rAnimationFiles)
{
	auto pSpriteFrameCache = SpriteFrameCache::getInstance();
	for (auto &animationFile : rAnimationFiles)
		_pAnimation->addSpriteFrame(pSpriteFrameCache->getSpriteFrameByName(animationFile));
	_pAnimation->setLoops(-1);
}


