//
//  BulletBase.cpp
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-10.
//  有问号就是不懂的
//   idmap是什么
//

#include "BulletBase.h"
#include "BulletManager.h"
#include "VictimEntityBase.h"

BulletBase *BulletBase::create(const int &rIId, VictimEntityBase *rVictimEntity)
{
	//子弹指针；
	auto pBullet = new BulletBase();
	//初始化成功的话，就设置自动释放；
	if (pBullet && pBullet->init(rIId, rVictimEntity)) pBullet->autorelease();
	//初始化不成功就删掉它；
	else CC_SAFE_DELETE(pBullet);
	return pBullet;
}

bool BulletBase::init(const int &rId, VictimEntityBase *rVictimEntity)
{
	bool bRet = false;

	do
	{
		//初始化实体基类和动态实体公共父类；
		CC_BREAK_IF(!Entity::init(rId, BULLETCSVFILE));
		CC_BREAK_IF(!DynamicPropertyInterface::init(rId, BULLETCSVFILE));
		//子弹攻击状态；
		_iAtkState = CsvUtil::getInstance()->getInt(_iId, en_AtkState, BULLETCSVFILE);
		//子弹种类；
		_iBulletType = CsvUtil::getInstance()->getInt(_iId, en_BulletType, BULLETCSVFILE);
		//死亡动画数目；
		_iDeadActCount = CsvUtil::getInstance()->getInt(_iId, en_DeadActCount, BULLETCSVFILE);
		//设置自动叠加；
		CC_SAFE_RETAIN(rVictimEntity);
		//设置攻击目标为参数的实体；
		_pAtkTarget = rVictimEntity;
		//？？
		_IdMap = new std::set<int>();
		//自我初始化的时候直接往管理类添加(注册)自己
		BulletManager::getInstance()->addBullet(this);

		bRet = true;
	} while (0);

	return  bRet;
}

void BulletBase::doAction(const float &rDt)
{
	switch (_iBulletType)
	{
	case en_NormalBullet:
	case en_GunBullet:
	{
		std::vector<std::string> tAnimationFiles;
		for (int i = 1; i <= _IAnimationFrameCount; ++i)
			//添加动画到路径向量里统一管理；
			tAnimationFiles.push_back(_sModelName + StringUtils::format("%d", i) + PHOTOPOSTFIX);
		//根据路径向量创建子弹的运动动画；
		createDynamicEntityAnimation(tAnimationFiles);
		//添加精灵帧；
		_pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(_sModelName + "1" + PHOTOPOSTFIX));
		//设置延迟时间；
		_pAnimation->setDelayPerUnit(rDt);
		//动画启动；
		getSprite()->runAction(Animate::create(_pAnimation));
		break;
	}
	case en_NoDisspper:
	{
		//重复动作设置和角度调整；
		getSprite()->runAction(RepeatForever::create(RotateBy::create(0.7, 360)));
		break;
	}
	default:
		break;
	}
}

void BulletBase::doMove() 
{
	//如果攻击目标已经死了，那就从父节点中删去，并记录死亡后返回；
	if (_pAtkTarget->getIsDead())
	{
		removeFromParent();
		setIsDead(true);
		return;
	}
	//如果没死的话，设置延迟时间并发动攻击；
	doAction(0.2f);
	//？？
	//拉姆达表达式已经忘光，你来注释吧
	auto deadActionCF = CallFunc::create([=]()
	{
		if (_iBulletType == en_NormalBullet || _iBulletType == en_GunBullet || _iBulletType == en_StarBullet) {
			if (_pAtkTarget != nullptr && !_pAtkTarget->getIsDead())
				_pAtkTarget->beHurt(getAtkPro());
			this->setPosition(_pAtkTarget->getPosition());
		}
		deadAction(_sName);
	});
	//移动位置；
	Vec2 MovetoPosition;
	//移动距离；
	float MoveDistance;
	switch (_iBulletType)
	{
	case en_NormalBullet:
	case en_GunBullet:
		//移动坐标等于攻击目标坐标减去该子弹的坐标；
		MovetoPosition = _pAtkTarget->getPosition() - this->getPosition();
		//计算距离，勾股定理；
		MoveDistance = this->getPosition().distance(_pAtkTarget->getPosition());
		break;
	case en_NoDisspper:
	{
		//斜边 Hypotenuse；

		float Hypotenuse = Vec2::ZERO.distance(Director::getInstance()->getVisibleSize());
		//三角函数求坐标；
		MovetoPosition = Vec2(Hypotenuse * sin(this->getRotation() * M_PI / 180), Hypotenuse * cos(this->getRotation() * M_PI / 180));
		//内置勾股定理求距离
		MoveDistance = MovetoPosition.distance(this->getPosition());
		break;
	}
	default:
		break;
	}
	//子弹发射；
	//？？
	//这两种情况有什么区别吗？
	this->runAction(Sequence::create(MoveBy::create(MoveDistance / _iSpeed, MovetoPosition), deadActionCF, NULL));
}

AtkProperty BulletBase::getAtkPro()
{
	AtkProperty tAtkProperty;
	//攻击类型
	tAtkProperty._enAtkState = _iAtkState;
	//攻击力；
	tAtkProperty._iAtk = getIAtk();
	//持续时间设定；
	tAtkProperty._iDuration = CsvUtil::getInstance()->getInt(_iId, en_Duration, BULLETCSVFILE);
	tAtkProperty._iBulletsType = _iBulletType;
	return tAtkProperty;
}

void BulletBase::deadAction(const std::string &rSDeadImageFile)
{
	CC_SAFE_DELETE(_IdMap);
	//按照死亡动画路径参数执行死亡动画；
	Entity::deadAction(rSDeadImageFile);
}

std::set<int>& BulletBase::getIdMap()
{
	return *_IdMap;
}