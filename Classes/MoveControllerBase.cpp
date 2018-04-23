//
//  MoveControllerBase.cpp
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-9.
//  Updated by 陈建彰 since version 1.1
//

#include "MoveControllerBase.h"
#include "MapUtil.h"
#include "GameManager.h"

#define STEP 10.0

bool MoveControllerBase::init(MonsterBase *pMonster)
{
    if (!Node::init())
    {
        return false;
    }
	//绑定怪物
    setMonster(pMonster);

    _iMonsterSpeed = _pMonster->getISpeed();
    _pMonster->addChild(this);

    //初始化运动轨迹
    auto Points = MapUtil::getInstance()->getMovePoses();
    _pMapPoints = new std::vector<Vec2>();
    //对于每个点
    //要微调怪物的移动点，因为怪物大小不一运动的姿态需要改一些
    for (auto &Point : Points)
    {
        Vec2 t_point;
        if (_pMonster->getILevel() == 1) t_point.x = Point.x + _pMonster->getContentSize().width / 2 - 15;
        if (_pMonster->getILevel() == 2) t_point.x = Point.x + 30;
        if (_pMonster->getILevel() == 3) t_point.x = Point.x + 40;
        t_point.y = Point.y - 5;
        _pMapPoints->push_back(t_point);
    }
    _pMonster->setPosition(*_pMapPoints->begin());

    listenerMonster(STEP / _pMonster->getISpeed());

    return true;
}

MoveControllerBase *MoveControllerBase::create(MonsterBase *pMonster)
{
    auto aMonster = new MoveControllerBase();
    if (aMonster->init(pMonster))
    {
        aMonster->autorelease();
        return aMonster;
    }
    CC_SAFE_DELETE(aMonster);
    return nullptr;
}

void MoveControllerBase::setMonster(MonsterBase *pMonster)
{
    _pMonster = pMonster;
}

void MoveControllerBase::listenerMonster(float t)
{
    if (_pMonster->getIHp() <= 0 || _pMonster->getIsDead())
        return; //死掉赶紧返回

    erasePoint(); //擦除旧轨迹，其实是将走过的路排除出轨迹路线

    //获取运动对象剩余轨迹的第一个坐标
    Vec2 pot = *_pMapPoints->begin();

    //根据剩余轨迹的第一个坐标x轴坐标
    //确定怪物目前向左还是向右
    _pMonster->setIsLeft(pot.x < _pMonster->getPositionX());

    //开始运动
    MoveBy *pStep;
    if (_pMonster->getPositionX() == pot.x) //当前x坐标和下一x坐标相同
    {
        if (_pMonster->getPositionY() <= pot.y) //但当前y坐标小于下一y坐标
        {
            pStep = MoveBy::create(t, Vec2(0, STEP)); //就向上爬
        }
        else //否则
        {
            pStep = MoveBy::create(t, Vec2(0, -STEP)); //就向下爬
        }
    }
    else //否则，当前x坐标不同于下一x坐标
    {
        if (_pMonster->getPositionX() <= pot.x)
        {
            pStep = MoveBy::create(t, Vec2(STEP, 0)); //向左
        }
        else
        {
            pStep = MoveBy::create(t, Vec2(-STEP, 0)); //向右
        }
    }

    auto pMoveCall = CallFuncN::create([=](Node *pSender)
                                       {
                                           this->listenerMonster(STEP / _pMonster->getISpeed());
                                       });
    Sequence *seq = Sequence::create(pStep, pMoveCall, NULL);

    if (!_pMonster->getIsLeft()) //如果运动体向左走
    {
        _pMonster->getSprite()->setRotationSkewY(0); //镜面翻转向左
    }
    else //否则，如果运动体向右走
    {
        _pMonster->getSprite()->setRotationSkewY(180); //镜面翻转向右
    }

    //获取怪物受攻击状态
    int MonsterState = _pMonster->getIState();
    int State_Slow = MonsterState & 2;
    int State_Stop = MonsterState & 4;
    int State_Poison = MonsterState & 8;
    int State_Slow_And_Shrink = MonsterState & 16; //这个是香菇攻击专用

    //当怪兽遭受到减速的时候处理
    if (State_Slow && _pMonster->getFSlowDuration() > 0)
    {
        _pMonster->setISpeed(_iMonsterSpeed / 3);
        float StateTime = _pMonster->getFSlowDuration() - t; //更新一下怪物受减速攻击持续时间，直接减去调度时间即可
        if (StateTime < 0) StateTime = 0; //若为负数了，那就清零
        _pMonster->setFSlowDuration(StateTime);

        //创建一个子精灵，用于显示怪物移动受阻动画
        Sprite *pTemp = Sprite::create();
        pTemp->setPosition(_pMonster->getContentSize().width / 2, 40);
        _pMonster->getSprite()->addChild(pTemp);

        //创建一个动画
        Animation *pAnimation = AnimationMaker((int) _pMonster->getIBulletStateType(), t);
        auto pCallFunc = CallFunc::create([=]()
                                          {
                                              pTemp->removeFromParentAndCleanup(true);
                                              if (_pMonster->getFSlowDuration() <= 0)
                                              {
                                                  _pMonster->setISpeed(_iMonsterSpeed); //恢复原来的速度
                                                  _pMonster->setIState(_pMonster->getIState() & 13); //恢复原来的状态
                                              }
                                          });
        Sequence *pSequence = Sequence::create(Animate::create(pAnimation), pCallFunc, nullptr);
        pTemp->runAction(pSequence);
    }

	//当怪兽遭受到减速变小的时候处理(蘑菇)
	if (State_Slow_And_Shrink  && _pMonster->getfSlowAndShrinkDuration() > 0)
	{
		_pMonster->setISpeed(_iMonsterSpeed / 3);
		float StateTime = _pMonster->getfSlowAndShrinkDuration() - t; //更新一下怪物受减速攻击持续时间，直接减去调度时间即可
		if (StateTime < 0) StateTime = 0; //若为负数了，那就清零
		_pMonster->setFSlowDuration(StateTime);

		
	    //_pMonster->setContentSize(Size(_pMonster->getContentSize().width / 3, _pMonster->getContentSize().height / 3));
        _pMonster->getSprite()->setScale(0.66);

		//创建一个子精灵，用于显示怪物移动受阻动画
		Sprite *pTemp = Sprite::create();
		pTemp->setPosition(_pMonster->getContentSize().width / 2, 40);
		_pMonster->getSprite()->addChild(pTemp);

		//创建一个动画
		Animation *pAnimation = AnimationMaker((int)_pMonster->getIBulletStateType(), t);
		auto pCallFunc = CallFunc::create([=]()
		{
			pTemp->removeFromParentAndCleanup(true);
			if (_pMonster->getfSlowAndShrinkDuration() <= 0)
			{
				_pMonster->setISpeed(_iMonsterSpeed); //恢复原来的速度
                _pMonster->getSprite()->setScale(1); //恢复原来的大小
				_pMonster->setIState(_pMonster->getIState() & 15); //恢复原来的状态
			}
		});
		Sequence *pSequence = Sequence::create(Animate::create(pAnimation), pCallFunc, nullptr);
		pTemp->runAction(pSequence);
	}

    //当怪兽遭受到毒性攻击的时候处理
    if (State_Poison && _pMonster->getfPoisonDuration() > 0)
    {
        float StateTime = _pMonster->getfPoisonDuration() - t; //更新一下怪物受减速攻击持续时间，直接减去调度时间即可
        if (StateTime < 0) StateTime = 0; //若为负数了，那就清零
        _pMonster->setfPoisonDuration(StateTime);

        AtkProperty atk;
        atk._enAtkState = 1;
        atk._iAtk = 2;
        atk._iDuration = 0;

        //创建一个子精灵，用于显示怪物中毒动画
        Sprite *pTemp = Sprite::create();
        pTemp->setPosition(_pMonster->getContentSize().width / 2, 40);
        _pMonster->getSprite()->addChild(pTemp);
        Animation *pAnimation = AnimationMaker(6, t);
        auto pCallFunc = CallFunc::create([=]()
                                          {
                                              if (!_pMonster->getIsDead()) _pMonster->beHurt(atk); //恢复正常的攻击属性
                                              if (_pMonster->getfPoisonDuration() <= 0)
                                              {
                                                  _pMonster->setIState(_pMonster->getIState() & 7);
                                              }
                                              pTemp->removeFromParentAndCleanup(true);
                                          });
        pTemp->runAction(Sequence::create(Animate::create(pAnimation), pCallFunc, NULL));
    }

    //当怪兽遭受到停止攻击的时候处理
    if (State_Stop && _pMonster->getfStopDuration() > 0)
    {
        float StateTime = _pMonster->getfStopDuration() - t;
        if (StateTime < 0) StateTime = 0;
        _pMonster->setfStopDuration(StateTime);
        Sprite *pTemp = Sprite::create();
        pTemp->setPosition(_pMonster->getContentSize().width / 2, 40);
        _pMonster->getSprite()->addChild(pTemp);
        Animation *pAnimation = AnimationMaker(_pMonster->getIBulletStateType(), t);
        auto pCallFunc = CallFunc::create([=]()
                                          {
                                              if (_pMonster->getfStopDuration() <= 0)
                                              {
                                                  _pMonster->setIState(_pMonster->getIState() & 11);
                                              }
                                              this->listenerMonster(STEP / _pMonster->getISpeed());
                                              pTemp->removeFromParentAndCleanup(true);
                                          });
        pTemp->runAction(Sequence::create(Animate::create(pAnimation), pCallFunc, NULL));
        return;
    }
    _pMonster->runAction(seq);
}

void MoveControllerBase::erasePoint()
{
    if (_pMapPoints->size() == 1)
    {
        return;
    }

    if (_pMonster->getPosition() == *_pMapPoints->begin()) //已经到达转弯点
    {
        if (GameManager::getInstance()->getCurrGameType() == en_Adventure)
        {
            //如果是冒险模式，直接擦除即可
            _pMapPoints->erase(_pMapPoints->begin());

        }
        else
        {
            //如果是boss模式，无穷循环
            auto tmp = *(_pMapPoints->begin());
            _pMapPoints->erase(_pMapPoints->begin());
            _pMapPoints->push_back(tmp);
            return; //后面的语句不用执行了
        }

        //若擦除后剩余的轨迹只剩下了一个坐标
        //以为着怪物已经到达了萝卜坐标，发生了碰撞
        if (_pMapPoints->size() == 1)
        {
            NOTIFY->postNotification("CarrotHurt", _pMonster); //萝卜被咬一口
            NOTIFY->postNotification("MonsterDead", _pMonster); //怪物随后挂掉
            _pMonster->setIsDead(true);
            _pMonster->removeFromParentAndCleanup(true);
        }
    }
}

MoveControllerBase::~MoveControllerBase()
{
    CC_SAFE_DELETE(_pMapPoints);
}

Animation *MoveControllerBase::AnimationMaker(int iBulletType, float t)
{
    Animation *pAnimation = Animation::create();
    if (iBulletType == 1)
    {
        //大便减速；
        pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PShit-11.png"));
        pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PShit-12.png"));
        pAnimation->setDelayPerUnit(t / 2);
    }
    else if (iBulletType == 5)
    {
        //蓝星星减速；
        pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PBStar-21.png"));
        pAnimation->setDelayPerUnit(t);
    }
    else if (iBulletType == 15 || iBulletType == 30 || iBulletType == 45)
    {
        //冰冻减速；
        pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PSnow01.png"));
        pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PSnow02.png"));
        pAnimation->setDelayPerUnit(t / 2);
    }
    else if (iBulletType == 6)
    {
        //放毒针减速；
        pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PPin01.png"));
        pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PPin02.png"));
        pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PPin03.png"));
        pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PPin04.png"));
        pAnimation->setDelayPerUnit(t / 4);
    }
    else if (iBulletType == 301 || iBulletType == 302 || iBulletType == 303)
    {
        //毒蘑菇缩小减速泡泡
        if (_pMonster->getIId() == 1 || _pMonster->getIId() == 2 || _pMonster->getIId() == 3
            || _pMonster->getIId() == 7 || _pMonster->getIId() == 8)
        {
            pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PMushroom-11.png"));
        }
        else
        {
            pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PMushroom-21.png"));
        }
        pAnimation->setDelayPerUnit(t); //bug fixed
    }
    else if (iBulletType == 7)
    {
        for (int i = 1; i <= 3; i++)
        {
            pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("PFish-1%d.png", i)));
        }
        pAnimation->setDelayPerUnit(t / 3);
    }
    pAnimation->setLoops(1);
    return pAnimation;
}
