//
//  DynamicPropertyInterface.cpp
//  CarrotFantasy
//
//  Created by ������ on 18-4-7.
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
		_pAnimation = Animation::create();
		_pAnimation->retain();

		auto pCsvUtil = CsvUtil::getInstance();

		//��ȡ�����ļ�����ʼ����������
		_iAtk = pCsvUtil->getInt(rId, en_Atk, rSCsvFileName);
		_iSpeed = static_cast<unsigned int>(pCsvUtil->getInt(rId, en_Speed, rSCsvFileName));
		bRet = true;
	} while (0);

	return bRet;
}

void DynamicPropertyInterface::createDynamicEntityAnimation(const std::vector<std::string> &rAnimationFiles)
{
	auto pSpriteFrameCache = SpriteFrameCache::getInstance();
	for (auto &animationFile : rAnimationFiles)
		_pAnimation->addSpriteFrame(pSpriteFrameCache->getSpriteFrameByName(animationFile));
	_pAnimation->setLoops(-1); //����ѭ��
}

