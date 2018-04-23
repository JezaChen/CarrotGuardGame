//
//  MapUtil.cpp
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-7.

#include "MapUtil.h"
#include "TowerFactory.h"
#include "GameManager.h"


MapUtil* MapUtil::_gInstance;


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
    }
    while (0);

    return bRet;
}

void MapUtil::setCurrentLevelTiledMap(cocos2d::TMXTiledMap* pTiledMap)
{
    //清理地图；
    clearMap();
    CC_SAFE_RELEASE_NULL(_pTildeMap);
    CC_SAFE_RETAIN(pTiledMap);
    _pTildeMap = pTiledMap;
    _gridSize = _pTildeMap->getTileSize();
    _mapSize = Size(_pTildeMap->getMapSize().width * _gridSize.width,
                    _pTildeMap->getMapSize().height * _gridSize.height);

    auto aMapGroup = _pTildeMap->getObjectGroup("PATH");
    auto aObjs = aMapGroup->getObjects();

    for (auto& iter : aObjs)
    {
        auto aObjMap = iter.asValueMap();
        auto aObjName = aObjMap.at("name").asString();
        auto aX = aObjMap.at("x").asFloat();
        auto aY = aObjMap.at("y").asFloat();
        auto aPos = Vec2(aX, aY);
        auto aWidth = aObjMap.at("width").asFloat();
        auto aHeight = aObjMap.at("height").asFloat();
        auto aRect = Rect(aX, aY, aWidth, aHeight);

        if (aObjName.find("PT") != std::string::npos)
        {
            _pMovePosMap->insert(std::make_pair(atoi(aObjName.substr(2).c_str()), aPos));
            continue;
        }
        if (aObjName.find("Obj") != std::string::npos)
        {
            rectTransVec(aRect);
            continue;
        }

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

void MapUtil::rectTransVec(const Rect& rRect)
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
}

void MapUtil::rectTransTower(const Rect& rRect, TowerType ttResultingTowerType)
{
    //todo 这逻辑写得弱鸡到我都看不下去......
    auto aWidth = rRect.size.width;
    auto aHeight = rRect.size.height;
    auto aX = rRect.origin.x;
    auto aY = rRect.origin.y;


    for (int i = 0; i < aWidth / TILESIZE; ++i)
    {
        for (int j = 0; j < aHeight / TILESIZE; ++j)
        {
            _pEffectTowerRectVec->push_back(Rect(aX + TILESIZE * i, aY + TILESIZE * j, TILESIZE, TILESIZE));
            TowerFactory::createTower(ttResultingTowerType, Vec2(aX + TILESIZE * i + TILESIZE / 2, aY + TILESIZE * j + TILESIZE / 2));
        }
    }
}

std::vector<Vec2> MapUtil::getMovePoses()
{
    std::vector<Vec2> tRetMovePosVec;
    for (auto& iter : *_pMovePosMap)
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

void MapUtil::removeBarrierRect(const Vec2& rPos)
{
    //                            _ooOoo_
    //                           o8888888o
    //                           88" . "88
    //                           (| -_- |)
    //                           O\  =  /O
    //                        ____/`---'\____
    //                      .'  \\|     |//  `.
    //                     /  \\|||  :  |||//  \
    //                    /  _||||| -:- |||||-  \
    //                    |   | \\\  -  /// |   |
    //                    | \_|  ''\---/''  |   |
    //                    \  .-\__  `-`  ___/-. /
    //                  ___`. .'  /--.--\  `. . __
    //               ."" '<  `.___\_<|>_/___.'  >'"".
    //              | | :  `- \`.;`\ _ /`;.`/ - ` : | |
    //              \  \ `-.   \_ __\ /__ _/   .-` /  /
    //         ======`-.____`-.___\_____/___.-`____.-'======
    //                            `=---='
    //        ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    //        /********************************************/
    //        /***************障碍物变炮塔逻辑***************/
    //        /********************************************/
    //        ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

    srand(time(nullptr));

    for (auto barrierIter = _pBarrierPosMap->begin(); barrierIter != _pBarrierPosMap->end(); ++barrierIter)
    {
        auto aBarrier = *barrierIter;
        if (aBarrier.second.containsPoint(rPos))
        {
            if (GameManager::getInstance()->getCurrGameType() == en_Adventure)
                rectTransVec(aBarrier.second);
            else
                rectTransTower(aBarrier.second, TowerType((rand() % 13))); //todo
            _pBarrierPosMap->erase(barrierIter);
            break;
        }
    }
}
