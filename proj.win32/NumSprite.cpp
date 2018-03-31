//
//  NumSprite.cpp
//  CarrotFantasy
//
//  Created by ºÎãü±ø on 18-3-30.
//
//

#include "NumSprite.h"

Node *NumSprite::createNum(const std::string &rSNum, const std::string &rSImage)
{
	auto tSize = Sprite::create(rSImage)->getContentSize();
	auto tINumSize = rSNum.size();

	auto pNumNode = Node::create();
	pNumNode->retain();

	for (int i = 0; i < tINumSize; ++i)
	{
		auto tINum = atoi(StringUtils::format("%c", rSNum.at(i)).c_str());
		auto pNum = Sprite::create(rSImage, Rect(tSize.width / 12 * (tINum + 2), 0, tSize.width / 12, tSize.height));
		auto tPos = Vec2(pNum->getContentSize().width * i, 0);
		pNum->setPosition(tPos);
		pNumNode->addChild(pNum);
	}
	return pNumNode;
}