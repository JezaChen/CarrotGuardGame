#include "BulletCuttle.h"

void BulletCuttle::doAction()
{
    for (int i = 1; i <= 2; ++i)
    {
        std::string SpriteFrameName = _sModelName + StringUtils::format("%d.png", i);
        _pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SpriteFrameName));
    }
    //设置延迟时间；
    _pAnimation->setDelayPerUnit(0.05);
    //无限执行，一直有弹射出；
    _pAnimation->setLoops(-1);
    //运行动画；
    getSprite()->runAction(Animate::create(_pAnimation));
}

void BulletCuttle::doMove()
{
    setRotation(_iRotation);
    doAction();

    float Hypotenuse = Vec2::ZERO.distance(Director::getInstance()->getVisibleSize());
    //Vec2 MovetoPosition = Vec2(Hypotenuse * sin(this->getRotation() * M_PI / 180), Hypotenuse * cos(this->getRotation() * M_PI / 180));
    Vec2 MovetoPosition = Vec2(Hypotenuse * sin(this->getRotation() * M_PI / 180), Hypotenuse * cos(this->getRotation() * M_PI / 180));
    float MoveDistance = MovetoPosition.distance(this->getPosition());

    //执行动画；
    this->runAction(Sequence::create(MoveBy::create(2000 / _iSpeed, MovetoPosition), nullptr));
    
}

bool BulletCuttle::init(const int& rId, VictimEntityBase* rVictimEntity, const int& rotation)
{
    bool bRet = false;
    do
    {
        //保证子弹基类的初始化成功；
        CC_BREAK_IF(!BulletBase::init(rId, rVictimEntity));
        _iRotation = rotation;

        bRet = true;
    }
    while (0);
    return bRet;
}

BulletCuttle* BulletCuttle::create(const int& rId, VictimEntityBase* rVictimEntity, const int& rotation)
{
    //分配内存给子弹指针；
    BulletCuttle* pBullet = new BulletCuttle();
    //初始化成功；
    if (pBullet->init(rId, rVictimEntity, rotation))
    {
        //设置自动释放；
        pBullet->autorelease();
        return pBullet;
    }
    //不成功就删除它；
    CC_SAFE_DELETE(pBullet);
    return nullptr;
}
