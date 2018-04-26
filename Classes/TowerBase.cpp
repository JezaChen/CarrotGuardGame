//
//  TowerBase.cpp
//  CarrotFantasy
//
//  Created by 何泓兵 x 陈建彰 on 18-4-9.
//
//
#include "TowerBase.h"
#include "TowerManager.h"
#include "VictimEntityBase.h"
#include "CsvUtil.h"
#include "BulletBase.h"
#include "BulletFactory.h"
#include "MonsterManager.h"
#include "MonsterBase.h"
#include "SoundUtil.h"
#include "MapUtil.h"

TowerBase::~TowerBase()
{

    CC_SAFE_RELEASE_NULL(_pAtkTarget);
    CC_SAFE_RELEASE_NULL(_pTowerPanel);
}

bool TowerBase::init(const int &rId)
{

    bool bRet = false;

    do
    {
        CC_BREAK_IF(!Entity::init(rId, TOWERCSVFILE));

        initTower();

        TowerManager::getInstance()->addTower(this);

        //注册三个调度器
        schedule(schedule_selector(TowerBase::checkAtkTarget), 0.1f); //检查攻击目标每0.1次执行一次
        schedule(schedule_selector(TowerBase::fire), _iAtkInterval); //攻击视炮塔而定
        schedule(schedule_selector(TowerBase::doRotation), 0.1f); //检查旋转是否对其攻击目标，每0.1秒执行一次

        bRet = true;
    } while (0);

    return bRet;
}

void TowerBase::deadAction(const std::string &rSDeadImageFile)
{
    NOTIFY->postNotification("TowerDead", this); //发出通知
    MapUtil::getInstance()->removeBarrierRect(getPosition()); //地图去除炮塔，变成炮塔可用位置，类比于障碍物
    Entity::deadAction();
}

void TowerBase::checkAtkTarget(float dt)
{
    //若没有攻击目标，就选择一个来开炮吧
    if (!_pAtkTarget) chooseAtkTarget();
    else //有攻击目标，也要判断是否符合要求
    {
        //第一步是判断要不要重新选择攻击目标

        //第二个参数是指玩家没有选中但炮塔攻击了它，那就取消再选择一个
        //第二个参数是为了随机化攻击
        if (_pAtkTarget->getIsDead() || (!_pAtkTarget->getAtkTarget() && _bIsHaveAtkTarget))
        {
            missAtkTarget();
            setIsHaveAtkTarget(false);
            return;
        }
        checkTargetIsOutOfRange(); //第二步，检查是否超出了范围
    }
}

void TowerBase::chooseAtkTarget()
{
    //游戏逻辑有点简单
    //就是获取怪物向量，遍历这个向量，满足范围条件的第一个就攻击它
    //可以利用一些算法优化它

    auto tMonsterVec = MonsterManager::getInstance()->getMonsterVec();

    for (auto &iterMonster : tMonsterVec)
    {
        if (isInAtkRange(iterMonster->getPosition()))
        {
            setAtkTarget(iterMonster);
            break;
        }
    }
}

bool TowerBase::isInAtkRange(const cocos2d::Vec2 &rPos)
{
    //TODO 这种判断方式有点暴力
    bool bRet = false;

    do
    {
        auto tDistance = getPosition().distance(rPos); //获取该坐标相对于该炮塔的距离

        auto RangeSp = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(
                StringUtils::format("range_%d", _iAtkRange) + PHOTOPOSTFIX)); //获取范围精灵
        CC_BREAK_IF(!(tDistance < RangeSp->getContentSize().width / 2 + 30)); //两个距离相对比
        bRet = true;
    } while (0);

    return bRet;
}

void TowerBase::fire(float dt)
{
    if (!_pAtkTarget || _pAtkTarget->getIsDead()) return; //攻击目标没了的话就不要瞎攻击了

    fireAction(); //炮塔开火动画启动

    //创建子弹，显示出来并发射
    auto createBulletCF = CallFunc::create([=]()
                                           {
                                               if (!_pAtkTarget) return;
                                               BulletFactory::createBullet(_iBulletId, this, _pAtkTarget);
                                           });

    //运行子弹流程动画
    this->runAction(Sequence::create(DelayTime::create(0.15), createBulletCF, NULL));
}

void TowerBase::checkTargetIsOutOfRange()
{
    if (_pAtkTarget)
    {
        if (!isInAtkRange(_pAtkTarget->getPosition()))
            missAtkTarget(); //范围超过的时候就放弃攻击了
    }
}

void TowerBase::missAtkTarget()
{
    CC_SAFE_RELEASE_NULL(_pAtkTarget);
}

void TowerBase::setAtkTarget(VictimEntityBase *pVictimEntity)
{

    CC_SAFE_RELEASE_NULL(_pAtkTarget);
    _pAtkTarget = pVictimEntity;
    CC_SAFE_RETAIN(_pAtkTarget); //由于missAtkTarget引用了它一次，这里就要去引用一次
}

TowerBase *TowerBase::create(const int &rId)
{
    auto t = new TowerBase();

    if (t->init(rId))
    {
        t->autorelease();
        return t;
    }

    CC_SAFE_DELETE(t);
    return nullptr;
}

void TowerBase::doRotation(float dt)
{

    if (!_pAtkTarget) return;

    //旋转对其攻击者
    //这个公式有点意思
    if (_bIsRotation) getSprite()->runAction(RotateTo::create(0.1, static_cast<float>(90 - 180 *
                                                                                           (_pAtkTarget->getPosition() -
                                                                                            this->getPosition()).getAngle() /
                                                                                            M_PI)));
}

void TowerBase::fireAction()
{
    //首先播放声音
    std::string soundName = _sName;
    if (soundName == "BStar") soundName = "PStar"; //TODO 太蠢了，得改
    SoundUtil::getInstance()->playEffectSound(StringUtils::format("Music/Towers/%s.mp3", soundName.c_str()));

    //然后创建动画
    auto pAnimation = Animation::create();
    auto pSpriteFrameCache = SpriteFrameCache::getInstance();
    for (int i = 1; i <= this->getAnimationFrameCount(); i++) //按动画帧数(炮塔表格文件给出)来
        //TODO 这个代码改一改，太长了
        pAnimation->addSpriteFrame(
                pSpriteFrameCache->getSpriteFrameByName(_sModelName + StringUtils::format("%d", i) + PHOTOPOSTFIX));
    pAnimation->addSpriteFrame(pSpriteFrameCache->getSpriteFrameByName(_sModelName + "1" + PHOTOPOSTFIX));
    pAnimation->setDelayPerUnit(0.05);
    pAnimation->setLoops(1); //一次就可以了

    auto pAnimate = Animate::create(pAnimation);

    this->getSprite()->runAction(pAnimate);
}

void TowerBase::upGrade()
{
    //std::stringstream StoI;
    //StoI << _sUpgradeCost;
    //int upGradeMoney;
    //StoI >> upGradeMoney;
    //upGradeMoney = -upGradeMoney;
    //兄台何必呢
    int upGradeMoney = -(atoi(_sUpgradeCost.c_str()));

    NOTIFICATION_CENTER->postNotification("moneyChange", (Ref *) (&upGradeMoney)); //发出通知

    auto upGradeCounts = this->getIUpgradeCount();

    _pGradeMark->removeFromParentAndCleanup(true);
    getSprite()->removeFromParentAndCleanup(true);

    Entity::initProperty(this->getIId() + 1, TOWERCSVFILE); //重新构建精灵
    initTower(); //再初始化一次

    this->_iUpgradeCount = upGradeCounts;
}

void TowerBase::initTower()
{
    if (_pTowerPanel) removeChild(_pTowerPanel);
    CC_SAFE_RELEASE_NULL(_pTowerPanel);

    auto pCsvUtil = CsvUtil::getInstance();
    _iBulletId = pCsvUtil->getInt(_iId, en_BulletId, TOWERCSVFILE);
    _iAtkRange = pCsvUtil->getInt(_iId, en_Range, TOWERCSVFILE);
    _iAtkInterval = pCsvUtil->getDouble(_iId, en_Space, TOWERCSVFILE);
    _sUpgradeCost = pCsvUtil->getStr(_iId, en_UpGradeCost, TOWERCSVFILE);
    _bIsRotation = pCsvUtil->getInt(_iId, en_IsRotation, TOWERCSVFILE);
    _iUpgradeCount = 0;
    _iCreateCost = pCsvUtil->getInt(_iId, en_CreateCost, TOWERCSVFILE);
    _bIsHaveAtkTarget = false;

    _pGradeMark = Sprite::create();
    //隐藏等级标志；
    _pGradeMark->setVisible(false);

    //动画等级标志；
    auto aniGradeMark = Animation::create();
    for (int i = 1; i <= 2; i++)
    {
        aniGradeMark->addSpriteFrame(
                SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("showupgrade0%d.png", i)));
    }
    aniGradeMark->setDelayPerUnit(0.5);
    aniGradeMark->setLoops(-1);
    _pGradeMark->setZOrder(3);
    _pGradeMark->runAction(Animate::create(aniGradeMark));
    _pGradeMark->setPosition(0, 50);
    addChild(_pGradeMark, 10);

    //todo 这变量名...
    //塔基创建
    _pTowerPanel = Sprite::createWithSpriteFrameName(pCsvUtil->getStr(_iId, en_TowerBase, TOWERCSVFILE));
    _pTowerPanel->retain();
    _pTowerPanel->setLocalZOrder(1); //todo
    addChild(_pTowerPanel);
    getSprite()->setZOrder(2);
}

int TowerBase::getTowerGradeCost()
{
    return atoi(_sUpgradeCost.c_str());
}

void TowerBase::showGradeMark()
{
    _pGradeMark->setVisible(true);
}

void TowerBase::hideGradeMark()
{
    _pGradeMark->setVisible(false);
}