//
// Created by jeza on 18-4-10.
//

#include "MonsterHelpLayer.h"

bool MonsterHelpLayer::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!Layer::init());
        createMonsterHelpLayer();
        bRet = true;
    } while (0);
    return bRet;
}

void MonsterHelpLayer::createMonsterHelpLayer()
{
    //创建图片(没有文字的)精灵
    auto monsterHelpPic = Sprite::createWithSpriteFrameName("help_monster.png");
    monsterHelpPic->setPosition(480, 280);
    monsterHelpPic->setScale(0.95f);
    addChild(monsterHelpPic);

    //创建带有提示文字的精灵
    auto monsterDetailsText = Sprite::createWithSpriteFrameName("help_monster_CN.png");
    monsterDetailsText->setScale(0.95f);
    monsterDetailsText->setPosition(480, 280); //真~玄学调参大法...跪了
    addChild(monsterDetailsText);
}
