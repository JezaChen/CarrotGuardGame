//
//  NumSprite.cpp
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-3-30.
//  这个cpp还是横竖看不懂；
//
#include "NumSprite.h"
#include<cstdio>
#include<cstdlib>

Node *NumSprite::createNum(const std::string &rSNum, const std::string &rSImage)
{
	auto tSize = Sprite::create(rSImage)->getContentSize(); //原图大小获取；
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