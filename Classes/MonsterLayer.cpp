//
//  MonsterLayer.cpp
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-9.
//
//

#include "MonsterLayer.h"
#include "MapUtil.h"
#include "GameManager.h"

bool MonsterLayer::init()
{
	bool bRet = false;

	do
	{
		CC_BREAK_IF(!Layer::init());

        //冒险模式有站牌
        //BOSS模式没有站牌
        if (GameManager::getInstance()->getCurrGameType() == en_Adventure)
        {
            //创建出发处站牌精灵并加入到图层中
            auto pStart = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("start01.png"));
            pStart->setPosition(MapUtil::getInstance()->getMovePoses().at(0) + Vec2(40, -15));
            addChild(pStart);
        }
		registerMonsterDeadEvent();
		bRet = true;
	} while (0);

	return bRet;
}


void MonsterLayer::registerMonsterDeadEvent()
{
	NOTIFY->addObserver(this, callfuncO_selector(MonsterLayer::monsterDead), "monsterDeadMoney", nullptr);
}

void MonsterLayer::monsterDead(Ref *pData)
{
	auto aValue = *(reinterpret_cast<std::tuple<Vec2, int>*>(pData)); //传入的参数pData是一个元组，第一个参数是加钱图层要显示的坐标，第二个坐标是加钱的数目
	auto aMoney = std::get<1>(aValue);
	auto pMoney = Sprite::createWithSpriteFrameName(StringUtils::format("money%d.png", aMoney));
	auto pVec2 = std::get<0>(aValue);
	pMoney->setPosition(pVec2);
	addChild(pMoney);
	//创建一个动画序列
	pMoney->runAction(Sequence::create(MoveBy::create(0.6f, Vec2(0, 100)), DelayTime::create(0.4), FadeOut::create(0.4f), CallFunc::create([=]() {pMoney->removeFromParent(); }), NULL));

}

void MonsterLayer::onExit()
{
	Layer::onExit();
	NOTIFY->removeAllObservers(this);
}
