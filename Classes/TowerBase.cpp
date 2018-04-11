//
//  TowerBase.cpp
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-9.
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

TowerBase::~TowerBase() {

	CC_SAFE_RELEASE_NULL(_pAtkTarget);
	CC_SAFE_RELEASE_NULL(_pTowerPanel);
}

bool TowerBase::init(const int &rId) {

	bool bRet = false;

	do {
		CC_BREAK_IF(!Entity::init(rId, TOWERCSVFILE));

		initTower();

		TowerManager::getInstance()->addTower(this);

		schedule(schedule_selector(TowerBase::checkAtkTarget), 0.1f);

		schedule(schedule_selector(TowerBase::fire), _iAtkSpace);

		schedule(schedule_selector(TowerBase::doRocation), 0.1f);

		bRet = true;
	} while (0);

	return  bRet;
}

void TowerBase::deadAction(const std::string &rSDeadImageFile)
{
	NOTIFY->postNotification("TowerDead", this);
	Entity::deadAction();
}

void TowerBase::checkAtkTarget(float dt) {
	if (!_pAtkTarget) chooseAtkTarget();
	else {
		if (_pAtkTarget->getIsDead() || (!_pAtkTarget->getAtkTarget() && _bIsHaveAtkTarget))
		{
			missAtkTarget();
			setIsHaveAtkTarget(false);
			return;
		}
		checkTargetIsOutOfRange();
	}
}

void  TowerBase::chooseAtkTarget() {

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

bool TowerBase::isInAtkRange(const cocos2d::Vec2 &rPos) {

	bool bRet = false;

	do
	{
		auto tDistance = getPosition().distance(rPos);
		auto RangeSp = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("range_%d", _iAtkRange) + PHOTOPOSTFIX));
		CC_BREAK_IF(!(tDistance < RangeSp->getContentSize().width / 2 + 30));
		bRet = true;
	} while (0);

	return bRet;
}

void TowerBase::fire(float dt) {
	if (!_pAtkTarget || _pAtkTarget->getIsDead()) return;
	fireAction();

	auto createBulletCF = CallFunc::create([=]() {
		if (!_pAtkTarget) return;
		BulletFactory::createBullet(_iBulletId, this, _pAtkTarget);
	});

	this->runAction(Sequence::create(DelayTime::create(0.15), createBulletCF, NULL));
}

void TowerBase::checkTargetIsOutOfRange() {
	if (_pAtkTarget) {
		if (!isInAtkRange(_pAtkTarget->getPosition())) missAtkTarget();
	}
}

void TowerBase::missAtkTarget() {
	CC_SAFE_RELEASE_NULL(_pAtkTarget);
}

void TowerBase::setAtkTarget(VictimEntityBase *pVictimEntity) {

	CC_SAFE_RELEASE_NULL(_pAtkTarget);
	_pAtkTarget = pVictimEntity;
	CC_SAFE_RETAIN(_pAtkTarget);
}

TowerBase* TowerBase::create(const int &rId) {
	auto t = new TowerBase();

	if (t && t->init(rId)) {
		t->autorelease();
		return t;
	}

	CC_SAFE_DELETE(t);
	return nullptr;
}

void TowerBase::doRocation(float dt) {

	if (!_pAtkTarget) return;

	if (_bIsRotation) getSprite()->runAction(RotateTo::create(0.1, 90 - 180 * (_pAtkTarget->getPosition() - this->getPosition()).getAngle() / M_PI));
}

void TowerBase::fireAction() {
	std::string soundName = _sName;
	if (soundName == "BStar") soundName = "PStar";
	SoundUtil::getInstance()->playEffectSound(StringUtils::format("Music/Towers/%s.mp3", soundName.c_str()));
	auto pAnimation = Animation::create();
	auto pSpriteFrameCache = SpriteFrameCache::getInstance();
	for (int i = 1; i <= this->getAnimationFrameCount(); i++)
		pAnimation->addSpriteFrame(pSpriteFrameCache->getSpriteFrameByName(_sModelName + StringUtils::format("%d", i) + PHOTOPOSTFIX));
	pAnimation->addSpriteFrame(pSpriteFrameCache->getSpriteFrameByName(_sModelName + "1" + PHOTOPOSTFIX));
	pAnimation->setDelayPerUnit(0.05);
	pAnimation->setLoops(1);

	auto pAnimate = Animate::create(pAnimation);

	this->getSprite()->runAction(pAnimate);
}

void TowerBase::upGrade() {
	std::stringstream StoI;
	StoI << _sUpgradeCost;
	int upGradeMoney;
	StoI >> upGradeMoney;
	upGradeMoney = -upGradeMoney;
	NotificationCenter::getInstance()->postNotification("moneyChange", (Ref*)(&upGradeMoney));

	auto upGradeCounts = this->getIUpgradeCount();
	_pGradeMark->removeFromParentAndCleanup(true);
	getSprite()->removeFromParentAndCleanup(true);
	Entity::initProperty(this->getIId() + 1, TOWERCSVFILE);

	initTower();
	this->_iUpgradeCount = upGradeCounts;
}

void TowerBase::initTower()
{
	if (_pTowerPanel) removeChild(_pTowerPanel);
	CC_SAFE_RELEASE_NULL(_pTowerPanel);

	auto pCsvUtil = CsvUtil::getInstance();
	_iBulletId = pCsvUtil->getInt(_iId, en_BulletId, TOWERCSVFILE);
	_iAtkRange = pCsvUtil->getInt(_iId, en_Range, TOWERCSVFILE);
	_iAtkSpace = pCsvUtil->getDouble(_iId, en_Space, TOWERCSVFILE);
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
	for (int i = 1; i <= 2; i++) {
		aniGradeMark->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("showupgrade0%d.png", i)));
	}
	aniGradeMark->setDelayPerUnit(0.5);
	aniGradeMark->setLoops(-1);
	_pGradeMark->setZOrder(3);
	_pGradeMark->runAction(Animate::create(aniGradeMark));
	_pGradeMark->setPosition(0, 50);
	addChild(_pGradeMark);
	//塔面板指针操作；
	_pTowerPanel = Sprite::createWithSpriteFrameName(pCsvUtil->getStr(_iId, en_TowerBase, TOWERCSVFILE));
	_pTowerPanel->retain();
	_pTowerPanel->setZOrder(1);
	addChild(_pTowerPanel);
	getSprite()->setZOrder(2);
}

int TowerBase::getTowerGradeCost() {
	std::stringstream StoI;
	StoI << _sUpgradeCost;
	int upGradeMoney;
	StoI >> upGradeMoney;
	return upGradeMoney;
}

void TowerBase::showGradeMark() {
	_pGradeMark->setVisible(true);
}

void TowerBase::hideGradeMark() {
	_pGradeMark->setVisible(false);
}