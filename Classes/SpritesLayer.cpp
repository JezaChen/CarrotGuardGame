#include "SpritesLayer.h"
#include "CommonSource.h"
#include "VisibleRect.h"

void SpritesLayer::createStaticSprites()
{
    auto pWelcomeMainBg = Sprite::createWithSpriteFrameName(MAIN_BACKGROUND);
    pWelcomeMainBg->setPosition(VisibleRectUtil::center());
    addChild(pWelcomeMainBg);

    auto pWelcomeMainBg_CN = Sprite::createWithSpriteFrameName(MAIN_BACKGROUND_CN);
    pWelcomeMainBg_CN->setPosition(_VisibleSize.width / 2 - 20, _VisibleSize.height / 2);
    addChild(pWelcomeMainBg_CN, 6);
}

void SpritesLayer::createDynamicSprites()
{
    //首先，画一个上方那个横穿屏幕的那朵大云
    auto pCloud1 = Sprite::createWithSpriteFrameName("cloud1.png");
    pCloud1->setAnchorPoint(Vec2(0, 0.5f));
    pCloud1->setPosition(-pCloud1->getContentSize().width, 450);
    //确立好初始位置
    auto pCloud1CallBack = CallFunc::create([pCloud1]() {pCloud1->setPositionX(-pCloud1->getContentSize().width); });
    //移动轨迹
    auto pCloud1MoveBy = MoveBy::create(20, Vec2(960 + pCloud1->getContentSize().width, 0));
    pCloud1->runAction(RepeatForever::create(Sequence::create(pCloud1CallBack, pCloud1MoveBy, nullptr)));
    addChild(pCloud1);

    //第二，画下方那个走的很快的云
    auto pCloud2 = Sprite::createWithSpriteFrameName("cloud2.png");
    pCloud2->setAnchorPoint(Vec2(0, 0.5f));
    pCloud2->setPosition(-pCloud2-> getContentSize().width, 550);
    auto pCloud2CallBack = CallFunc::create([pCloud2]() {pCloud2->setPositionX(-pCloud2->getContentSize().width); });
    auto pCloud2MoveBy = MoveBy::create(35, Vec2(960 + pCloud2->getContentSize().width, 0));
    pCloud2->runAction(RepeatForever::create(Sequence::create(pCloud2CallBack, pCloud2MoveBy, nullptr)));
    addChild(pCloud2);

    //最后，把那只鸟画出来
    auto pBird = Sprite::createWithSpriteFrameName("bird.png");
    pBird->setPosition(Vec2(200, 460));
    auto pBirdMoveBy = MoveBy::create(2, Vec2(0, 30));
    //循环地来回上下动
    pBird->runAction(RepeatForever::create(Sequence::create(pBirdMoveBy, pBirdMoveBy->reverse(), nullptr)));
    addChild(pBird);
}

void SpritesLayer::createCarrot()
{
    //创建萝卜Node
    _pCarrotAll = Node::create();
    _pCarrotAll->retain();
    _pCarrotAll->setName("carrot");

    //创建萝卜主体 
    auto pCarrot = Sprite::createWithSpriteFrameName("carrot.png");
    pCarrot->setAnchorPoint(Vec2(0.5f, 0)); //萝卜主体的锚点为底边中点
    _pCarrotAll->addChild(pCarrot, 2); //把萝卜主体放进去

    //左侧的叶子
    auto pLeaf1 = Sprite::createWithSpriteFrameName("leaf-1.png");
    pLeaf1->setPosition(Vec2(0, pCarrot->getContentSize().height)); //这是相对坐标系的设置，下同
    pLeaf1->setAnchorPoint(Vec2(1, 0.5f)); //设置anchor值为右侧边中点
    _pCarrotAll->addChild(pLeaf1, 1);
    pLeaf1->setName("leaf1");
    
    //右侧的叶子
    auto pLeaf3 = Sprite::createWithSpriteFrameName("leaf-3.png")
    pLeaf3->setAnchorPoint(Vec2(0.0f, 0.0f)); //锚点为左下角顶点
    pLeaf3->setPosition(Vec2(0, pCarrot->getContentSize().height - pLeaf3->getContentSize().height/2));
    pLeaf3->setName("leaf3");
    _pCarrotAll->addChild(pLeaf3, 1);

    //中间的叶子
    auto pLeaf2 = Sprite::createWithSpriteFrameName("leaf-2.png");
    pLeaf2->setAnchorPoint(Vec2(0.5f, 0.0f)); //锚点为底边中点
    pLeaf2->setPosition(Vec2(0, pCarrot->getContentSize().height - pLeaf2->getContentSize().height/3));
    pLeaf2->setName("leaf2");
    _pCarrotAll->addChild(pLeaf2, 1);

    _pCarrotAll->setContentSize(Size(pCarrot->getContentSize().width + 20, pCarrot->getContentSize().height + pLeaf2>getContentSize().height));
    _pCarrotAll->setPosition(_VisibleSize.width / 2 - 20, _VisibleSize.height / 2 - 50);
    _pCarrotAll->setScale(0);
    addChild(_pCarrotAll);

    //为了能使叶子动起来
    //使用调度器进行动画调度，调度时间为5秒
    schedule(schedule_selector(SpritesLayer::leafAction), 5);
}

void SpritesLayer::leafAction(float dt)
{
    //0.1秒内，旋转15度
    auto pRotate = RotateBy::create(0.1f, 15);
    auto pDelay = DelayTime::create(2.0f);
    //右边叶子的动作是：延迟2秒——旋转——逆旋转——旋转——逆旋转——延迟两秒
    _pCarrotAll->getChildByName("leaf3")->runAction(pDelay, pRotate, pRotate->reverse(), pRotate, pRotate->reverse(), pDelay, nullptr);
    //左边叶子的动作是：旋转——逆旋转——旋转——逆旋转——延迟两秒
    _pCarrotAll->getChildByName("leaf1")->runAction(pRotate, pRotate->reverse(), pRotate, pRotate->reverse(), pDelay, nullptr);

}