//
//  Entity.cpp
//  newCardDefence
//
//  Created by 何泓兵 on 18-4-6.
//  
//

#include "Entity.h"
#include "CommonSource.h"
//赋初值；
unsigned long Entity::ID = 0;
Entity::~Entity()
{
	CC_SAFE_RELEASE_NULL(_pSprite);
	//安全删除精灵；
}

bool Entity::init(const int &rId, const std::string &rSCsvFileName)
{
	bool bRet = false;
	do
	{
		initProperty(rId, rSCsvFileName);
		++ID;
		_myID = ID;
		bRet = true;
	} while (0);

	return bRet;
}

const Size &Entity::getContentSize()const
{
	return _pSprite->getContentSize();
}


void Entity::initProperty(const int &rId, const std::string &rSCsvFileName)
{
	auto pCsvUtil = CsvUtil::getInstance();

	_iId = rId;
	auto pData = pCsvUtil->getRowData(rId, rSCsvFileName);
	_sName = pData.at(en_Name);
	_sModelName = pData.at(en_ModelName);
	_iValue = atoi(pData.at(en_Value).c_str());
	_IAnimationFrameCount = pCsvUtil->getInt(rId, en_AnimationCount, rSCsvFileName);
	_iLevel = pCsvUtil->getInt(_iId, en_Level, rSCsvFileName);
	_bIsDead = false;
	std::string sSpriteName = "";
	if (_IAnimationFrameCount) sSpriteName = _sModelName + "1" + PHOTOPOSTFIX;
	else sSpriteName = _sModelName + PHOTOPOSTFIX;

	//创建绑定；
	bindSprite(Sprite::createWithSpriteFrameName(sSpriteName));
}

void Entity::bindSprite(cocos2d::Sprite *pSprite)
{
	//精灵不存在
	if (_pSprite)
	{
		_pSprite->stopAllActions();
		removeChild(_pSprite);
		//去除
	}
	CC_SAFE_RELEASE_NULL(_pSprite);
	_pSprite = pSprite;
	CC_SAFE_RETAIN(_pSprite);
	addChild(_pSprite);
}

Sprite* Entity::getSprite()
{
	return _pSprite;
}


void Entity::doDead()
{
	//发出金钱改变的通知
	NOTIFY->postNotification("moneyChange", reinterpret_cast<Ref*>(&_iValue));
	setIsDead(true);
	//停止所有动画，执行死亡动画
	_pSprite->stopAllActions();
	deadAction();
}

void Entity::deadAction(const std::string &rSDeadImageFile)
{

	auto sDeadImageFile = rSDeadImageFile;
	//动画创建；
	auto pAnimation = Animation::create();

	auto pSpriteFrameCache = SpriteFrameCache::getInstance();
	//如果死亡动画不空
	if (sDeadImageFile.empty())
	{
		//死亡动画前缀；
		if (1 == _iLevel) sDeadImageFile = "air0";
		else if (2 == _iLevel) sDeadImageFile = "air1";
		else if (3 == _iLevel) sDeadImageFile = "air2";
		for (int index = 1; index <= _IAnimationFrameCount; ++index)
			pAnimation->addSpriteFrame(pSpriteFrameCache->getSpriteFrameByName(sDeadImageFile + StringUtils::format("%d", index) + PHOTOPOSTFIX));

	}
	else
	{
		for (int i = 1; i <= 2; i++)
			//添加死亡动画
			pAnimation->addSpriteFrame(pSpriteFrameCache->getSpriteFrameByName(sDeadImageFile + StringUtils::format("%02d", i) + PHOTOPOSTFIX));
	}

	pAnimation->setLoops(1);
	pAnimation->setDelayPerUnit(0.1f);
	//执行死亡动画后，从父结点中清除掉死掉的怪物精灵
    if (_sName != "PCuttle")
	    _pSprite->runAction(Sequence::create(Animate::create(pAnimation), CallFunc::create([this]() {this->removeFromParent(); }), NULL));
    else //patch 章鱼子弹不要死亡了
        this->removeFromParent();
}

Rect Entity::getBoundingBox()const
{
	//获取坐标；
	auto tPos = getPosition();
	//获取精灵原图大小；
	auto tSize = _pSprite->getContentSize();
    if (_sName == "PCuttle")
    {
        return Rect(tPos.x - tSize.width / 4, tPos.y - tSize.height / 4, tSize.width / 2, tSize.height / 2);
    }
    return Rect(tPos.x - tSize.width / 2, tPos.y - tSize.height / 2, tSize.width, tSize.height);
}

unsigned int Entity::getmID()
{
	return _myID;
}
