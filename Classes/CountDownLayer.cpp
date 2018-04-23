//
//  CountDownLayer.cpp
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-13.
//
#include "CountDownLayer.h"
#include "MapUtil.h"
#include "SoundUtil.h"

bool CountDownLayer::init() {
	if (!Layer::init())
	{
		return false;
	}

	Director::getInstance()->resume();

	countDownSprite = Sprite::createWithSpriteFrameName("countdown_11.png");//倒计时圆盘；
	countDownSprite->setName("countDownSprite");
	countDownSprite->setPosition(480, 320);
	addChild(countDownSprite, 2);

    //initEffectPosBlink();
    this->scheduleOnce(schedule_selector(CountDownLayer::effectPosBlink), 0.1f);

	this->schedule(schedule_selector(CountDownLayer::runArrow1), 0.40f);
	this->schedule(schedule_selector(CountDownLayer::runArrow2), 0.60f);
	this->schedule(schedule_selector(CountDownLayer::runArrow3), 0.80f);

	this->scheduleOnce(schedule_selector(CountDownLayer::Num1), 0.0f);
	this->scheduleOnce(schedule_selector(CountDownLayer::Num2), 1.0f);
	this->scheduleOnce(schedule_selector(CountDownLayer::Num3), 2.0f);
	this->scheduleOnce(schedule_selector(CountDownLayer::GameGo), 3.0f);
	this->scheduleOnce(schedule_selector(CountDownLayer::childDisappear), 3.6f);


	registerNoTouch();
	return true;
}
void CountDownLayer::Circle() 
{
	auto run = Sprite::createWithSpriteFrameName("countdown_12.png");
	auto r1 = RotateBy::create(3.0f, -1080);//三秒钟逆时针旋转1080度；
	run->setPosition(100, 100);
	run->runAction(r1);
	countDownSprite->addChild(run, 2);
}
void CountDownLayer::runArrow1(float t) 
{
	auto arrowSprite1 = Sprite::createWithSpriteFrameName("arrow.png");
	
	std::vector<Vec2> value = MapUtil::getInstance()->getMovePoses();
	//判断路径方向；
	Vec2 point1 = value.at(0);
	Vec2 point2 = value.at(1);

	if (point1.x == point2.x && point1.y >= point2.y) //向下标箭头
	{
		arrowSprite1->setRotation(90);
		arrowSprite1->setPosition(point1.x + 40, point1.y - 60);

	}
	else if (point1.x == point2.x && point1.y < point2.y) //向上标箭头
	{
		arrowSprite1->setRotation(-90);
		arrowSprite1->setPosition(point1.x + 40, point1.y + 60);

	}
	else if (point1.y == point2.y && point1.x >= point2.x) //向左标箭头
	{
		arrowSprite1->setScaleX(-1); //镜面翻转
		arrowSprite1->setPosition(point1.x - 5, point1.y - 30);
	}
	else if (point1.y == point2.y && point1.x < point2.x)
	{
		//右方向为起始方向；
		arrowSprite1->setPosition(point1.x + 80, point1.y - 30); //向右标箭头
	}
	//创建动作；
	auto fade = FadeOut::create(0.7f);
	arrowSprite1->runAction(fade);
	addChild(arrowSprite1);

}
void CountDownLayer::runArrow2(float t) 
{
	auto arrowSprite2 = Sprite::createWithSpriteFrameName("arrow.png");

	std::vector<Vec2> value = MapUtil::getInstance()->getMovePoses();

	Vec2 point1 = value.at(0);
	Vec2 point2 = value.at(1);

	if (point1.x == point2.x && point1.y >= point2.y)
	{
		arrowSprite2->setRotation(90);
		arrowSprite2->setPosition(point1.x + 40, point1.y - 90);

	}
	else if (point1.x == point2.x && point1.y < point2.y)
	{
		arrowSprite2->setRotation(-90);
		arrowSprite2->setPosition(point1.x + 40, point1.y + 90);

	}
	else if (point1.y == point2.y && point1.x >= point2.x)
	{
		arrowSprite2->setScaleX(-1);
		arrowSprite2->setPosition(point1.x - 35, point1.y - 30);
	}
	else if (point1.y == point2.y && point1.x < point2.x)
	{
		arrowSprite2->setPosition(point1.x + 110, point1.y - 30);
	}


	auto fade = FadeOut::create(0.7f);
	arrowSprite2->runAction(fade);
	addChild(arrowSprite2);
}
void CountDownLayer::runArrow3(float t) 
{
	auto arrowSprite3 = Sprite::createWithSpriteFrameName("arrow.png");

	std::vector<Vec2> value = MapUtil::getInstance()->getMovePoses();

	Vec2 point1 = value.at(0);
	Vec2 point2 = value.at(1);

	if (point1.x == point2.x && point1.y >= point2.y)
	{
		arrowSprite3->setRotation(90);
		arrowSprite3->setPosition(point1.x + 40, point1.y - 120);
	}
	else if (point1.x == point2.x && point1.y < point2.y)
	{
		arrowSprite3->setRotation(-90);
		arrowSprite3->setPosition(point1.x + 40, point1.y + 120);
	}
	else if (point1.y == point2.y && point1.x >= point2.x)
	{
		arrowSprite3->setScaleX(-1);
		arrowSprite3->setPosition(point1.x - 65, point1.y - 30);
	}
	else if (point1.y == point2.y && point1.x < point2.x)
	{
		arrowSprite3->setPosition(point1.x + 140, point1.y - 30);
	}
	auto fade = FadeOut::create(0.7f);
	arrowSprite3->runAction(fade);
	addChild(arrowSprite3);


}
void CountDownLayer::Num1(float t) 
{
	auto three = Sprite::createWithSpriteFrameName("countdown_01.png");//3
	Circle();
	SoundUtil::getInstance()->playEffectSound(COUNTDOWN);//倒计时的特效音乐；
	three->setPosition(100, 100);
	countDownSprite->addChild(three, 2);
}
void CountDownLayer::Num2(float t) 
{
	//清除所有孩子结点；
	countDownSprite->removeAllChildren();
	Circle();
	SoundUtil::getInstance()->playEffectSound(COUNTDOWN);
	auto two = Sprite::createWithSpriteFrameName("countdown_02.png");//2
	two->setPosition(100, 100);
	countDownSprite->addChild(two, 2);

}
void CountDownLayer::Num3(float t) 
{
	countDownSprite->removeAllChildren();
	Circle();
	SoundUtil::getInstance()->playEffectSound(COUNTDOWN);
	auto one = Sprite::createWithSpriteFrameName("countdown_03.png");//1
	one->setPosition(100, 100);
	countDownSprite->addChild(one, 2);
}
void CountDownLayer::GameGo(float t) 
{
	countDownSprite->removeAllChildren();
	Circle();
	SoundUtil::getInstance()->playEffectSound(GO);
	auto GO = Sprite::createWithSpriteFrameName("countdown_13.png");
	//比例设定，玄学调个1.05f；
	auto scale = ScaleBy::create(0.3f, 1.05f);
	//GO转了一圈出场；
	auto arotate = RotateBy::create(0.1f, 360);

	GO->setPosition(100, 100);
	countDownSprite->addChild(GO);
	GO->runAction(Spawn::create(scale, arotate, NULL));
}
void CountDownLayer::childDisappear(float t) 
{
	//this->removeChildByName("countDownSprite");
    this->removeAllChildren();
	//怪物出来吧
	NOTIFY->postNotification("startBuildMonster");
	//父节点中清出来
	removeFromParent();
}

void CountDownLayer::initEffectPosBlink()
{
    effPosSprites = Sprite::create();
	//空地显示动画，一闪一闪
    auto aFadeIn = FadeIn::create(0.5f);
    auto aFadeOut = FadeOut::create(0.5f);
	//出现两次消失两次
    _pFadeSequence = Sequence::create(aFadeIn, DelayTime::create(0.5f), aFadeOut, DelayTime::create(0.2f), 
        aFadeIn, DelayTime::create(0.5f), aFadeOut, nullptr);

    auto effPos = MapUtil::getInstance()->getEffectTowerPoses();

    for (auto &iter : effPos)
    {
        float x = iter.origin.x;
        float y = iter.origin.y;
        float width = iter.size.width;
        float height = iter.size.height;

        auto posSprite = Sprite::createWithSpriteFrameName("select_00.png");
        posSprite->setPosition(x + width / 2, y + height / 2); 
        posSprite->setCascadeOpacityEnabled(true); //MUST BE ATTENTIONED 孩子必须要开启级联才能跟着老爸同步透明度
        effPosSprites->addChild(posSprite);
    }
    effPosSprites->setCascadeOpacityEnabled(true); //老爸也要开启级联才能与孩子一块更新透明度
    effPosSprites->setName("effPosSprites");
    addChild(effPosSprites, 0);
}

void CountDownLayer::effectPosBlink(float t)
{
	//封装
    initEffectPosBlink();
	//设置空地闪烁动画启动
    effPosSprites->runAction(_pFadeSequence);
}

void CountDownLayer::registerNoTouch()
{
    //倒计时的时候触控无效了
	auto pTouchEvent = EventListenerTouchOneByOne::create();
	//创建触摸
	pTouchEvent->setSwallowTouches(true);
	//设置触摸无效
	pTouchEvent->onTouchBegan = [](Touch *pTouch, Event *pEvent) {return true; };

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(pTouchEvent, this);

}


