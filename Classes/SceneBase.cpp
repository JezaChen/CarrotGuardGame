//
//  SceneBase.cpp
//  CarrotFantasy
//
//  Created by 何泓兵，陈建彰 on 18-3-30.
//
//

#include "SceneBase.h"

void SceneBase::sourceManager(const std::vector<std::string> &rSourceNameVec, const bool &rBLoad)
{
    auto pSpriteFrameCache = SpriteFrameCache::getInstance();
    for (auto &iterSourceName : rSourceNameVec)
    {
        if (rBLoad)
            pSpriteFrameCache->addSpriteFramesWithFile(iterSourceName + PLISTPOSTFIX, iterSourceName + PHOTOPOSTFIX);
        else pSpriteFrameCache->removeSpriteFramesFromFile(iterSourceName + PLISTPOSTFIX); //TODO 为毛要删掉
    }
}
