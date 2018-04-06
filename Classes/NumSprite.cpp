//
//  NumSprite.cpp
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-3-30.
//  
//
#include "NumSprite.h"

Node *NumSprite::createNum(const std::string &rSNum, const std::string &rSImage)
{
	//原图大小获取；
	auto aSize = Sprite::create(rSImage)->getContentSize(); 
	auto aINumSize = rSNum.size();

	auto pNumNode = Node::create();
	pNumNode->retain();

	for (int i = 0; i < aINumSize; ++i)
	{
		//按照rSNum的size创造精灵，并把精灵加入pNumNode中
		auto aINum = atoi(StringUtils::format("%c", rSNum.at(i)).c_str());
		auto pNum = Sprite::create(rSImage, Rect(aSize.width / 12 * (aINum + 2), 0, aSize.width / 12, aSize.height));
		auto aPos = Vec2(pNum->getContentSize().width * i, 0);
		pNum->setPosition(aPos);
		pNumNode->addChild(pNum);
	}
	return pNumNode;
}