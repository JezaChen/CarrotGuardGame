//
//  TowerOptBtn.cpp
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-13.
//
//

#include "TowerOptBtn.h"
#include "CommonSource.h"
#include "MapUtil.h"
#include "TowerFactory.h"
#include "LevelConfigUtil.h"
#include "ScoreAndControlLayer.h"
#include "TowerBase.h"
#include "SoundUtil.h"

TowerOptBtn::TowerOptBtn()
{

}

TowerOptBtn::~TowerOptBtn()
{
	CC_SAFE_DELETE(_pCreateTowerItemSpVec);
	CC_SAFE_DELETE(_pGradeTowerItemSpVec);
}

bool TowerOptBtn::init()
{
	bool bRet = false;
	do
	{
		_pCreateTowerItemSpVec = new Vector<MenuItemSprite*>();
		_pGradeTowerItemSpVec = new Vector<MenuItemSprite*>();
		createMenuAndItems();
		this->schedule(schedule_selector(TowerOptBtn::ChangingItem));
		bRet = true;
	} while (0);
	return bRet;
}

void TowerOptBtn::hideTowerOpt()
{
	_bKeySpVisible = false;
	_pKeySp->setVisible(_bKeySpVisible);
	if (_pTowerRangeSp != nullptr) _pTowerRangeSp->setVisible(false);
	_pCreateMenu1->setVisible(false);
	_pCreateMenu2->setVisible(false);
}

void TowerOptBtn::showTowerOpt() {
	_bKeySpVisible = true;
	_pKeySp->setVisible(_bKeySpVisible);
}

void TowerOptBtn::createMenuAndItems() {
	_pKeySp = Sprite::create();
	_pKeySp->setVisible(false);
	_pCreateMenu1 = Menu::create();
	_pCreateMenu1->setVisible(false);
	_pCreateMenu2 = Menu::create();
	_pCreateMenu2->setVisible(false);
	_pGradeMenu = Menu::create();
	createTowerMenu();
	auto MenuAnimation = Animation::create();
	auto _pSpriteFrameCache = SpriteFrameCache::getInstance();
	for (int i = 1; i <= 4; ++i)
		MenuAnimation->addSpriteFrame(_pSpriteFrameCache->getSpriteFrameByName(StringUtils::format("select_0%d", i) + PHOTOPOSTFIX));
	MenuAnimation->setDelayPerUnit(0.1);
	MenuAnimation->setLoops(-1);

	_pKeySp->runAction(Animate::create(MenuAnimation));
	_pKeySp->addChild(_pCreateMenu1);
	_pKeySp->addChild(_pCreateMenu2);
	_pKeySp->addChild(_pGradeMenu);
	addChild(_pKeySp);

	_pTowerRangeSp = Sprite::create();
	_pTowerRangeSp->setPosition(40, 40);
	_pTowerRangeSp->setVisible(false);
	_pKeySp->addChild(_pTowerRangeSp);
}

void TowerOptBtn::createTowerMenu() 
{
	int i = 1;
	for (auto &iterTower : LevelConfigUtil::getInstance()->getCurrentTowersInfo()) 
	{
		//log("%s", (iterTower + "01" + PHOTOPOSTFIX).c_str());
		int _TowerId = CsvUtil::getInstance()->findVal(iterTower, 1, TOWERCSVFILE);
		std::stringstream StoI;
		std::string _sUpgradeCost = CsvUtil::getInstance()->getStr(_TowerId, en_CreateCost, TOWERCSVFILE);
		StoI << _sUpgradeCost;
		int _upGradeMoney;
		StoI >> _upGradeMoney;
		if (iterTower == "Sun1") iterTower = "Sun";
		if (iterTower == "PPlane1") iterTower = "Plane";
		auto _TowerItemSp = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(iterTower + "01" + PHOTOPOSTFIX));
		auto _Toweritem = MenuItemSprite::create(_TowerItemSp, _TowerItemSp, [=](Ref* r) {
			TowerType _towerType;
			this->setTag(0);
			hideTowerOpt();
			//钱不够免谈；
			if (_upGradeMoney > _funcCheckMoney()) {
				return;
			}
			switch (_TowerId)
			{
			case 1:_towerType = en_GreenTower; break;
			case 4:_towerType = en_CloverTower; break;
			case 7:_towerType = en_ShitTower; break;
			case 10:_towerType = en_BallTower; break;
			case 13:_towerType = en_StarTower; break;
			case 16:_towerType = en_FireBottleTower; break;
			case 19:_towerType = en_BlueStarTower; break;
			case 22:_towerType = en_SunTower; break;
			case 25:_towerType = en_RocketTower; break;
			case 28:_towerType = en_PinTower; break;
			case 31:_towerType = en_SnowTower; break;
			case 34:_towerType = en_PlaneTower; break;
			case 37:_towerType = en_AnchorTower; break;
			default:
				break;
			}
			//创建塔；
			TowerFactory::createTower(_towerType, this->getPosition());
			SoundUtil::getInstance()->playEffectSound(BUILDTOWER);
			int createMoney = -CsvUtil::getInstance()->getInt(_TowerId, en_CreateCost, TOWERCSVFILE);
			//钱花了；
			NotificationCenter::getInstance()->postNotification("moneyChange", (Ref*)(&createMoney));
		});
		_Toweritem->setTag(_upGradeMoney);
		_Toweritem->setName(iterTower);
		_pCreateTowerItemSpVec->pushBack(_Toweritem);
		i < 5 ? _pCreateMenu1->addChild(_Toweritem) : _pCreateMenu2->addChild(_Toweritem);
		i++;
	}
	//对齐各个塔防的图案；
	_pCreateMenu1->alignItemsHorizontallyWithPadding(1);
	if (_pCreateTowerItemSpVec->size() > 4)	_pCreateMenu2->alignItemsHorizontallyWithPadding(1);
}

void TowerOptBtn::gradeTowerMenu(TowerBase* touchTower) {
	_pGradeMenu->removeAllChildrenWithCleanup(true);
	auto _pSpriteFrameCache = SpriteFrameCache::getInstance();
	_pTowerRangeSp->setSpriteFrame(_pSpriteFrameCache->getSpriteFrameByName("range_" + StringUtils::format("%d", touchTower->getIAtkRange()) + PHOTOPOSTFIX));
	_pTowerRangeSp->setVisible(true);
	//升级塔；
	auto _pAtkRange = Sprite::createWithSpriteFrame(_pSpriteFrameCache->getSpriteFrameByName(StringUtils::format("range_%d", touchTower->getIAtkRange()) + PHOTOPOSTFIX));
	auto UpgradeSp = Sprite::createWithSpriteFrame(_pSpriteFrameCache->getSpriteFrameByName("upgrade_" + touchTower->getSUpgradeCose() + PHOTOPOSTFIX));
	auto UpgradeItem = MenuItemSprite::create(UpgradeSp, UpgradeSp, [=](Ref* r) 
	{
		this->setTag(0);
		hideTowerOpt();
		if (touchTower->getIUpgradeCount() > 1) return;
		if (touchTower->getTowerGradeCost() > _funcCheckMoney()) return;
		touchTower->upGrade();
		SoundUtil::getInstance()->playEffectSound(UPGRADETOWER);
		touchTower->setIUpgradeCount(touchTower->getIUpgradeCount() + 1);
	});
	//卖掉塔；
	auto SellSp = Sprite::createWithSpriteFrame(_pSpriteFrameCache->getSpriteFrameByName(StringUtils::format("sell_%d", touchTower->getIValue()) + PHOTOPOSTFIX));
	auto SellItem = MenuItemSprite::create(SellSp, SellSp, [=](Ref* r) {
		this->setTag(0);
		hideTowerOpt();
		SoundUtil::getInstance()->playEffectSound(SELLTOWER);
		touchTower->doDead();
	});

	UpgradeItem->setName("upgrade_");
	UpgradeItem->setTag(touchTower->getTowerGradeCost());
	_pGradeTowerItemSpVec->pushBack(UpgradeItem);
	_pGradeMenu->addChild(UpgradeItem);
	_pGradeMenu->addChild(SellItem);
	if (this->getPositionY() >= 480) {
		if (this->getPositionX() < 80) UpgradeItem->setPosition(Vec2(80, 0));
		else UpgradeItem->setPosition(Vec2(-80, 0));
		SellItem->setPosition(Vec2(0, -80));
	}
	else if (this->getPositionY() < 80) {
		if (this->getPositionX() < 80) SellItem->setPosition(Vec2(80, 0));
		else SellItem->setPosition(Vec2(-80, 0));
		UpgradeItem->setPosition(Vec2(0, 80));
	}
	else _pGradeMenu->alignItemsVerticallyWithPadding(100);
	_pGradeMenu->setPosition(40, 40);
}

void TowerOptBtn::ChangingItem(float dt) 
{
	for (auto itemCreateSp = _pCreateTowerItemSpVec->begin(); itemCreateSp != _pCreateTowerItemSpVec->end(); itemCreateSp++) 
	{
		auto _pCreateItemSp = (*itemCreateSp);
		if (_pCreateItemSp->getTag() > _funcCheckMoney()) _pCreateItemSp->setNormalImage(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(_pCreateItemSp->getName() + "00" + PHOTOPOSTFIX)));
		else _pCreateItemSp->setNormalImage(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(_pCreateItemSp->getName() + "01" + PHOTOPOSTFIX)));
	}
	for (auto itemGradeSp = _pGradeTowerItemSpVec->begin(); itemGradeSp != _pGradeTowerItemSpVec->end(); itemGradeSp++) {
		auto _pGradeItemSp = (*itemGradeSp);
		if (_pGradeItemSp->getTag() != 0) {
			if (_pGradeItemSp->getTag() > _funcCheckMoney()) _pGradeItemSp->setNormalImage(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(_pGradeItemSp->getName() + StringUtils::format("%d", -_pGradeItemSp->getTag()) + PHOTOPOSTFIX)));
			else _pGradeItemSp->setNormalImage(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(_pGradeItemSp->getName() + StringUtils::format("%d", _pGradeItemSp->getTag()) + PHOTOPOSTFIX)));
		}
	}
}

void TowerOptBtn::setFuncCheckMoney(const std::function<int()> &rFuncCheckMoney) {
	_funcCheckMoney = rFuncCheckMoney;
}

void TowerOptBtn::showCreateMenu() 
{
	_pGradeMenu->removeAllChildrenWithCleanup(true);
	_pCreateMenu1->setVisible(true);
	_pCreateMenu2->setVisible(true);
	if (this->getPositionY() < 320) 
	{
		_pCreateMenu1->setPosition(40, 120);
		if (_pCreateTowerItemSpVec->size() > 4) 
		{
			_pCreateMenu2->setPosition(_pCreateMenu1->getPosition());
			_pCreateMenu1->setPosition(40, 200);
		}
	}
	else {
		_pCreateMenu1->setPosition(40, -50);
		if (_pCreateTowerItemSpVec->size() > 4)	
			_pCreateMenu2->setPosition(_pCreateMenu1->getPosition() - Vec2(0, 80));
	}
	int x1 = 120;
	int x2 = 120;
	switch (_pCreateTowerItemSpVec->size())
	{
	case 1:x1 = 0; break;
	case 2:x1 = 40; break;
	case 3:x1 = 80; break;
	case 4:x1 = 120; break;
	default:
		break;
	}
	switch (_pCreateTowerItemSpVec->size() - 4)
	{
	case 1:x2 = 0; break;
	case 2:x2 = 40; break;
	case 3:x2 = 80; break;
	case 4:x2 = 120; break;
	default:
		break;
	}
	if (this->getPositionX() <= 120) {
		_pCreateMenu1->setPosition(_pCreateMenu1->getPosition() + Vec2(x1, 0));
		_pCreateMenu2->setPosition(_pCreateMenu2->getPosition() + Vec2(x2, 0));
	}
	if (this->getPositionX() >= 840) {
		_pCreateMenu1->setPosition(_pCreateMenu1->getPosition() + Vec2(-x1, 0));
		_pCreateMenu2->setPosition(_pCreateMenu2->getPosition() + Vec2(-x2, 0));
	}
}

void TowerOptBtn::hideCreateMenu() {
	_pCreateMenu1->setVisible(false);
	_pCreateMenu2->setVisible(false);
}