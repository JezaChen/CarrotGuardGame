//
//  CountDownLayer.cpp
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-13.
//  还没看过，晚上看
//
#include "CountDownLayer.h"
#include "MapUtil.h"
#include "SoundUtil.h"
Scene * CountDownLayer::createScene() {
	auto scene = Scene::create();
	auto layer = CountDownLayer::create();
	scene->addChild(layer);
	return scene;
}
bool CountDownLayer::init() {
	if (!Layer::init())
	{
		return false;
	}

	Director::getInstance()->resume();

	countDownSprite = Sprite::createWithSpriteFrameName("countdown_11.png");
	countDownSprite->setName("countDownSprite");
	countDownSprite->setPosition(480, 320);
	addChild(countDownSprite);
	this->schedule(schedule_selector(CountDownLayer::runArrow1), 0.40f);
	this->schedule(schedule_selector(CountDownLayer::runArrow2), 0.60f);
	this->schedule(schedule_selector(CountDownLayer::runArrow3), 0.80f);

	this->scheduleOnce(schedule_selector(CountDownLayer::Num1), 0.0f);
	this->scheduleOnce(schedule_selector(CountDownLayer::Num2), 1.0f);
	this->scheduleOnce(schedule_selector(CountDownLayer::Num3), 2.0f);
	this->scheduleOnce(schedule_selector(CountDownLayer::GameGo), 3.0f);
	this->scheduleOnce(schedule_selector(CountDownLayer::childDispear), 3.6f);
	registerNoTouch();
	return true;
}
void CountDownLayer::Circle() {
	auto run = Sprite::createWithSpriteFrameName("countdown_12.png");
	auto r1 = RotateBy::create(3.0f, -1080);
	run->setPosition(100, 100);
	run->runAction(r1);
	countDownSprite->addChild(run);
}
void CountDownLayer::runArrow1(float t) {
	auto arrowSprite1 = Sprite::createWithSpriteFrameName("arrow.png");

	std::vector<Vec2> value = MapUtil::getInstance()->getMovePoses();

	Vec2 point1 = value.at(0);
	Vec2 point2 = value.at(1);

	if (point1.x == point2.x && point1.y >= point2.y)
	{
		arrowSprite1->setRotation(90);
		arrowSprite1->setPosition(point1.x + 40, point1.y - 60);

	}
	if (point1.x == point2.x && point1.y < point2.y)
	{
		arrowSprite1->setRotation(-90);
		arrowSprite1->setPosition(point1.x + 40, point1.y + 60);

	}
	if (point1.y == point2.y && point1.x >= point2.x)
	{
		arrowSprite1->setScaleX(-1);
		arrowSprite1->setPosition(point1.x - 5, point1.y - 30);
	}
	if (point1.y == point2.y && point1.x < point2.x)
	{
		arrowSprite1->setPosition(point1.x + 80, point1.y - 30);
	}
	auto fade = FadeOut::create(0.7f);
	arrowSprite1->runAction(fade);
	addChild(arrowSprite1);

	i++;
}
void CountDownLayer::runArrow2(float t) {
	auto arrowSprite2 = Sprite::createWithSpriteFrameName("arrow.png");

	std::vector<Vec2> value = MapUtil::getInstance()->getMovePoses();

	Vec2 point1 = value.at(0);
	Vec2 point2 = value.at(1);

	if (point1.x == point2.x && point1.y >= point2.y)
	{
		arrowSprite2->setRotation(90);
		arrowSprite2->setPosition(point1.x + 40, point1.y - 90);

	}
	if (point1.x == point2.x && point1.y < point2.y)
	{
		arrowSprite2->setRotation(-90);
		arrowSprite2->setPosition(point1.x + 40, point1.y + 90);

	}
	if (point1.y == point2.y && point1.x >= point2.x)
	{
		arrowSprite2->setScaleX(-1);
		arrowSprite2->setPosition(point1.x - 35, point1.y - 30);
	}
	if (point1.y == point2.y && point1.x < point2.x)
	{
		arrowSprite2->setPosition(point1.x + 110, point1.y - 30);
	}


	auto fade = FadeOut::create(0.7f);
	arrowSprite2->runAction(fade);
	addChild(arrowSprite2);
	i++;
}
void CountDownLayer::runArrow3(float t) {
	auto arrowSprite3 = Sprite::createWithSpriteFrameName("arrow.png");

	std::vector<Vec2> value = MapUtil::getInstance()->getMovePoses();

	Vec2 point1 = value.at(0);
	Vec2 point2 = value.at(1);

	if (point1.x == point2.x && point1.y >= point2.y)
	{
		arrowSprite3->setRotation(90);
		arrowSprite3->setPosition(point1.x + 40, point1.y - 120);
	}
	if (point1.x == point2.x && point1.y < point2.y)
	{
		arrowSprite3->setRotation(-90);
		arrowSprite3->setPosition(point1.x + 40, point1.y + 120);
	}
	if (point1.y == point2.y && point1.x >= point2.x)
	{
		arrowSprite3->setScaleX(-1);
		arrowSprite3->setPosition(point1.x - 65, point1.y - 30);
	}
	if (point1.y == point2.y && point1.x < point2.x)
	{
		arrowSprite3->setPosition(point1.x + 140, point1.y - 30);
	}
	auto fade = FadeOut::create(0.7f);
	arrowSprite3->runAction(fade);
	addChild(arrowSprite3);


	i++;
}
void CountDownLayer::Num1(float t) {
	auto three = Sprite::createWithSpriteFrameName("countdown_01.png");
	Circle();
	SoundUtil::getInstance()->playEffectSound(COUNTDOWN);
	three->setPosition(100, 100);
	countDownSprite->addChild(three);
}
void CountDownLayer::Num2(float t) {
	countDownSprite->removeAllChildren();
	Circle();
	SoundUtil::getInstance()->playEffectSound(COUNTDOWN);
	auto two = Sprite::createWithSpriteFrameName("countdown_02.png");
	two->setPosition(100, 100);
	countDownSprite->addChild(two);

}
void CountDownLayer::Num3(float t) {
	countDownSprite->removeAllChildren();
	Circle();
	SoundUtil::getInstance()->playEffectSound(COUNTDOWN);
	auto one = Sprite::createWithSpriteFrameName("countdown_03.png");
	one->setPosition(100, 100);
	countDownSprite->addChild(one);
}
void CountDownLayer::GameGo(float t) {
	countDownSprite->removeAllChildren();
	Circle();
	SoundUtil::getInstance()->playEffectSound(GO);
	auto one = Sprite::createWithSpriteFrameName("countdown_13.png");
	auto scale = ScaleBy::create(0.3f, 1.05f);
	auto roate = RotateBy::create(0.1f, 360);

	one->setPosition(100, 100);
	countDownSprite->addChild(one);
	one->runAction(Spawn::create(scale, roate, NULL));
}
void CountDownLayer::childDispear(float t) {
	this->removeChildByName("countDownSprite");
	NOTIFY->postNotification("startBuildMonster");
	removeFromParent();
}

void CountDownLayer::registerNoTouch()
{
	auto pListener = EventListenerTouchOneByOne::create();

	pListener->setSwallowTouches(true);
	pListener->onTouchBegan = [](Touch *pTouch, Event *pEvent) {return true; };

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(pListener, this);

}


