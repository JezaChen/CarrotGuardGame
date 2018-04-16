//
//  BulletBase.cpp
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-10.
//
//

#include "BulletBase.h"
#include "BulletManager.h"
#include "VictimEntityBase.h"

BulletBase *BulletBase::create(const int &rIId, VictimEntityBase *rVictimEntity)
{
    //子弹指针；
    auto pBullet = new BulletBase();
    if (pBullet && pBullet->init(rIId, rVictimEntity)) pBullet->autorelease();
    else
        CC_SAFE_DELETE(pBullet);
    return pBullet;
}

bool BulletBase::init(const int &rId, VictimEntityBase *rVictimEntity)
{
    bool bRet = false;

    do
    {
        CC_BREAK_IF(!Entity::init(rId, BULLETCSVFILE));
        CC_BREAK_IF(!DynamicPropertyInterface::init(rId, BULLETCSVFILE));
        //子弹攻击状态；
        _iAtkState = CsvUtil::getInstance()->getInt(_iId, en_AtkState, BULLETCSVFILE);
        //子弹种类；
        _iBulletType = CsvUtil::getInstance()->getInt(_iId, en_BulletType, BULLETCSVFILE);
        //死亡动画数目；
        _iDeadActCount = CsvUtil::getInstance()->getInt(_iId, en_DeadActCount, BULLETCSVFILE);
        CC_SAFE_RETAIN(rVictimEntity);
        _pAtkTarget = rVictimEntity;

        /**[即将废弃]**/
        _IdMap = new std::set<int>();

        BulletManager::getInstance()->addBullet(this);

        bRet = true;
    } while (0);

    return bRet;
}

void BulletBase::doAction(const float &rDt)
{
    switch (_iBulletType)
    {
        case en_NormalBullet:
        case en_GunBullet:
        {
            //这种类型的子弹没有旋转效果，其动画是有一帧一帧来组成的
            std::vector<std::string> tAnimationFiles;
            for (int i = 1; i <= _IAnimationFrameCount; ++i)
                tAnimationFiles.push_back(_sModelName + StringUtils::format("%d", i) + PHOTOPOSTFIX);

            //调用父类的动画构造方法，传入向量构造动画
            createDynamicEntityAnimation(tAnimationFiles);

            //todo ?
            _pAnimation->addSpriteFrame(
                    SpriteFrameCache::getInstance()->getSpriteFrameByName(_sModelName + "1" + PHOTOPOSTFIX));
            _pAnimation->setDelayPerUnit(rDt);
            getSprite()->runAction(Animate::create(_pAnimation));
            break;
        }
        case en_NoDisspper:
        {
            //这种类型的子弹只有一个帧，所以是无限旋转
            getSprite()->runAction(RepeatForever::create(RotateBy::create(0.7, 360)));
            break;
        }
        default:
            break;
    }
}

void BulletBase::doMove()
{
    if (_pAtkTarget->getIsDead())
    {
        removeFromParent();
        setIsDead(true);
        return;
    }
    doAction(0.2f);

    auto deadActionCF = CallFunc::create([=]()
                                         {
                                             if (_iBulletType == en_NormalBullet || _iBulletType == en_GunBullet ||
                                                 _iBulletType == en_StarBullet)
                                             {
                                                 if (_pAtkTarget != nullptr && !_pAtkTarget->getIsDead())
                                                     _pAtkTarget->beHurt(getAtkPro());
                                                 this->setPosition(_pAtkTarget->getPosition());
                                             }
                                             deadAction(_sName);
                                         });

    Vec2 MovetoPosition;
    float MoveDistance;
    switch (_iBulletType)
    {
        //todo 星星似乎没写好
        //todo 好像不用写了
        case en_NormalBullet:
        case en_GunBullet:
            MovetoPosition = _pAtkTarget->getPosition() - this->getPosition();
            MoveDistance = this->getPosition().distance(_pAtkTarget->getPosition());
            break;
        case en_NoDisspper:
        {
            float Hypotenuse = Vec2::ZERO.distance(Director::getInstance()->getVisibleSize());
            MovetoPosition = Vec2(Hypotenuse * sin(this->getRotation() * M_PI / 180),
                                  Hypotenuse * cos(this->getRotation() * M_PI / 180));
            MoveDistance = MovetoPosition.distance(this->getPosition());
            break;
        }
        default:
            break;
    }
    this->runAction(Sequence::create(MoveBy::create(MoveDistance / _iSpeed, MovetoPosition), deadActionCF, NULL));
}

AtkProperty BulletBase::getAtkPro()
{
    AtkProperty tAtkProperty;
    tAtkProperty._enAtkState = _iAtkState;
    tAtkProperty._iAtk = getIAtk();
    //持续时间设定；
    tAtkProperty._iDuration = CsvUtil::getInstance()->getInt(_iId, en_Duration, BULLETCSVFILE);
    tAtkProperty._iBulletsType = _iBulletType;
    return tAtkProperty;
}

void BulletBase::deadAction(const std::string &rSDeadImageFile)
{
    CC_SAFE_DELETE(_IdMap);
    Entity::deadAction(rSDeadImageFile);
}

std::set<int> &BulletBase::getIdMap()
{
    return *_IdMap;
}