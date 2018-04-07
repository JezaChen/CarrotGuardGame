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

void MapUtil::setCurrentLevelTiledMap(cocos2d::TMXTiledMap *pTiledMap)
{
	clearMap();
	CC_SAFE_RELEASE_NULL(_pTildeMap);
	CC_SAFE_RETAIN(pTiledMap);
	_pTildeMap = pTiledMap;
	_gridSize = _pTildeMap->getTileSize();
	_mapSize = Size(_pTildeMap->getMapSize().width * _gridSize.width, _pTildeMap->getMapSize().height * _gridSize.height);

	auto tMapGroup = _pTildeMap->getObjectGroup("PATH");
	auto tObjs = tMapGroup->getObjects();

	for (auto &iter : tObjs)
	{
		auto tObjMap = iter.asValueMap();
		auto tObjName = tObjMap.at("name").asString();
		auto tX = tObjMap.at("x").asFloat();
		auto tY = tObjMap.at("y").asFloat();
		auto tPos = Vec2(tX, tY);
		auto tWidth = tObjMap.at("width").asFloat();
		auto tHeight = tObjMap.at("height").asFloat();
		auto tRect = Rect(tX, tY, tWidth, tHeight);

		if (tObjName.find("PT") != std::string::npos)
		{
			_pMovePosMap->insert(std::make_pair(atoi(tObjName.substr(2).c_str()), tPos));
			continue;
		}
		if (tObjName.find("Obj") != std::string::npos)
		{
			rectTransVec(tRect);
			continue;
		}

		auto tIndex = tObjName.find("Ob");
		if (std::string::npos != tIndex)
		{
			_pBarrierPosMap->push_back(std::make_pair(tObjName.substr(0, tIndex + 2), tRect));
			continue;
		}

		_pEffectTowerRectVec->push_back(tRect);
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
	auto tWidth = rRect.size.width;
	auto tHeight = rRect.size.height;
	auto tX = rRect.origin.x;
	auto tY = rRect.origin.y;
	if (TILESIZE == tWidth && TILESIZE == tHeight)
	{
		_pEffectTowerRectVec->push_back(Rect(tX, tY, _gridSize.width, _gridSize.height));
		return;
	}
	if (tWidth > TILESIZE && tHeight > TILESIZE)
	{
		for (int i = 0; i < tWidth / TILESIZE; ++i)
		{
			for (int j = 0; j < tHeight / TILESIZE; ++j)
			{
				_pEffectTowerRectVec->push_back(Rect(tX + TILESIZE * i, tY + TILESIZE * j, TILESIZE, TILESIZE));
			}
		}
		return;
	}

	if (tWidth > TILESIZE)
	{
		for (int i = 0; i < tWidth / TILESIZE; ++i)
		{
			_pEffectTowerRectVec->push_back(Rect(tX + i * TILESIZE, tY, _gridSize.width, _gridSize.height));
		}
	}

	if (tHeight > TILESIZE)
	{
		for (int i = 0; i < tHeight / TILESIZE; ++i)
		{
			_pEffectTowerRectVec->push_back(Rect(tX, tY + i * TILESIZE, _gridSize.width, _gridSize.height));
		}
	}
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
		auto tBarrier = *barrierIter;
		if (tBarrier.second.containsPoint(rPos))
		{
			rectTransVec(tBarrier.second);
			_pBarrierPosMap->erase(barrierIter);
			break;
		}
	}
}




