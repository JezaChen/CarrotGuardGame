//
//  MapUtil.cpp
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-7.
//  map这个到底是std里的还是游戏地图；
//  暂时不注释了，我们一起讨论一下这个cpp吧

#include "MapUtil.h"


MapUtil *MapUtil::_gInstance;


MapUtil::~MapUtil()
{
    CC_SAFE_DELETE(_pMovePosMap);
    CC_SAFE_DELETE(_pBarrierPosMap);
    CC_SAFE_DELETE(_pEffectTowerRectVec);
    CC_SAFE_RELEASE_NULL(_pTildeMap);
}

bool MapUtil::init()
{
    bool bRet = false;

    do
    {
        _pBarrierPosMap = new std::vector<std::pair<std::string, Rect>>;
        _pEffectTowerRectVec = new std::vector<Rect>;
        _pMovePosMap = new std::map<int, Vec2>;

        bRet = true;
    } while (0);

    return bRet;
}

void MapUtil::setAndAnalyzeCurrentLevelTiledMap(cocos2d::TMXTiledMap *pTiledMap)
{
    //清理地图；
    clearMap();
    CC_SAFE_RELEASE_NULL(_pTildeMap);
    CC_SAFE_RETAIN(pTiledMap);
    _pTildeMap = pTiledMap;
    _gridSize = _pTildeMap->getTileSize();

    auto aMapGroup = _pTildeMap->getObjectGroup("PATH");
    auto aObjs = aMapGroup->getObjects();

    for (auto &iter : aObjs)
    {
        auto aObjMap = iter.asValueMap();
        auto aObjName = aObjMap.at("name").asString();
        auto aX = aObjMap.at("x").asFloat();
        auto aY = aObjMap.at("y").asFloat();
        auto aPos = Vec2(aX, aY);
        auto aWidth = aObjMap.at("width").asFloat();
        auto aHeight = aObjMap.at("height").asFloat();
        auto aRect = Rect(aX, aY, aWidth, aHeight);

        //PT就是PATH
        //怪物移动的路线
        if (aObjName.find("PT") != std::string::npos)
        {
            _pMovePosMap->insert(std::make_pair(atoi(aObjName.substr(2).c_str()), aPos));
            continue;
        }

        //Obj是炮塔有效放置位置
        if (aObjName.find("Obj") != std::string::npos)
        {
            //由于Obj块是矩形块，有大有小
            //而炮塔只能放置在一个小方块中
            //因而我们需要将Obj块拆成一个个小方块，放置在向量中
            rectTransVec(aRect);
            continue;
        }

        //ob是障碍物位置
        //障碍物方块无须拆，直接放在向量即可
        auto tIndex = aObjName.find("Ob");
        if (std::string::npos != tIndex)
        {
            _pBarrierPosMap->push_back(std::make_pair(aObjName.substr(0, tIndex + 2), aRect));
            continue;
        }

        _pEffectTowerRectVec->push_back(aRect);
    }
}

void MapUtil::clearMap()
{
    _pEffectTowerRectVec->clear();
    _pBarrierPosMap->clear();
    _pMovePosMap->clear();
}

void MapUtil::rectTransVec(const Rect &rRect)
{
    auto aWidth = rRect.size.width;
    auto aHeight = rRect.size.height;
    auto aX = rRect.origin.x;
    auto aY = rRect.origin.y;

    for (int i = 0; i < aWidth / TILESIZE; ++i)
    {
        for (int j = 0; j < aHeight / TILESIZE; ++j)
        {
            _pEffectTowerRectVec->push_back(Rect(aX + TILESIZE * i, aY + TILESIZE * j, TILESIZE, TILESIZE));
        }
    }
    return;
}

std::vector<Vec2> MapUtil::getMovePoses()
{
    std::vector<Vec2> tRetMovePosVec;
    for (auto &iter : *_pMovePosMap)
        tRetMovePosVec.push_back(iter.second);

    return tRetMovePosVec;
}

std::vector<Rect> MapUtil::getEffectTowerPoses()
{
    return *_pEffectTowerRectVec;
}

std::vector<std::pair<std::string, Rect>> MapUtil::getBarrierPoses()
{
    return *_pBarrierPosMap;
}

void MapUtil::removeBarrierRect(const Vec2 &rPos)
{
    for (auto barrierIter = _pBarrierPosMap->begin(); barrierIter != _pBarrierPosMap->end(); ++barrierIter)
    {
        auto aBarrier = *barrierIter;
        if (aBarrier.second.containsPoint(rPos))
        {
            rectTransVec(aBarrier.second); //拆成小方块，此时可以放置炮塔了
            _pBarrierPosMap->erase(barrierIter); //记得要及时擦除
            //TODO 两句话要不要换一下顺序？
            break;
        }
    }
}




