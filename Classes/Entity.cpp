//
//  Entity.cpp
//  newCardDefence
//
//  Created by 何泓兵 on 18-4-6.
//  存在不懂问题；
//

#include "Entity.h"
#include "CommonSource.h"

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

	//获取第一列，也就是实体的名字(Name)
	_sName = pData.at(en_Name);
	//获取第二列，也就是实体的模型名字(ModelName)
	_sModelName = pData.at(en_ModelName);
	//获取第三列，也就是实体的值(Value)
	_iValue = atoi(pData.at(en_Value).c_str());
	//获取第四列，也就是实体动画的帧数(AnimationFrameCount)
	_IAnimationFrameCount = pCsvUtil->getInt(rId, en_AnimationCount, rSCsvFileName);
	//获取第五列，也就是实体的等级(Level)
	_iLevel = pCsvUtil->getInt(_iId, en_Level, rSCsvFileName);
	_bIsDead = false;
	std::string sSpriteName;

	if (_IAnimationFrameCount) sSpriteName = _sModelName + "1" + PHOTOPOSTFIX;
	else sSpriteName = _sModelName + PHOTOPOSTFIX;

	//用精灵帧创建精灵；
	bindSprite(Sprite::createWithSpriteFrameName(sSpriteName));
}

void Entity::bindSprite(cocos2d::Sprite *pSprite)
{
	if (_pSprite) //如果已经绑定了精灵，需要进行解绑
	{
		_pSprite->stopAllActions(); //停止一切活动
		removeChild(_pSprite);
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


void Entity::doDead() //外界能调用的死亡函数
{
	//这里也看不懂；
    //死了当然是送钱啦 by Jeza
	NOTIFY->postNotification("moneyChange", reinterpret_cast<Ref*>(&_iValue));
	setIsDead(true);
	_pSprite->stopAllActions();
	deadAction(); //播放死亡动画
}

void Entity::deadAction(const std::string &rSDeadImageFile)
{

	auto sDeadImageFile = rSDeadImageFile;
	//动画创建指针；
	auto pAnimation = Animation::create();
	//获取精灵帧缓存
	auto pSpriteFrameCache = SpriteFrameCache::getInstance();
	if (sDeadImageFile.empty()) //若参数为空字符串
	{
	    //加载默认死亡动画
        //每个大主题的死亡动画有所差异
		if (1 == _iLevel) sDeadImageFile = "air0";
		else if (2 == _iLevel) sDeadImageFile = "air1";
		else if (3 == _iLevel) sDeadImageFile = "air2";
		for (int index = 1; index <= _IAnimationFrameCount; ++index)
			pAnimation->addSpriteFrame(pSpriteFrameCache->getSpriteFrameByName(sDeadImageFile + StringUtils::format("%d", index) + PHOTOPOSTFIX));

	}
	else
	{
	    //TODO 要看看不是默认的参数到底是什么
		for (int i = 1; i <= 2; i++)
			//添加精灵缓存(按名添加精灵缓存）
			pAnimation->addSpriteFrame(pSpriteFrameCache->getSpriteFrameByName(sDeadImageFile + StringUtils::format("%02d", i) + PHOTOPOSTFIX));
	}

	pAnimation->setLoops(1); //只播放一次就行了
	pAnimation->setDelayPerUnit(0.1f);
	//这个为什么这样？
    //创建一个动画序列，死亡动画播放后执行去除精灵函数
	_pSprite->runAction(Sequence::create(Animate::create(pAnimation), CallFunc::create([this]() {this->removeFromParent(); }), NULL));
}

Rect Entity::getBoundingBox()const
{
	//获取坐标；
	auto tPos = getPosition();
	//获取精灵原图大小；
	auto tSize = _pSprite->getContentSize();
	//精灵的锚点处于中点
	return Rect(tPos.x - tSize.width / 2, tPos.y - tSize.height / 2, tSize.width, tSize.height);
}

unsigned int Entity::getmID()
{
	return _myID;
}
