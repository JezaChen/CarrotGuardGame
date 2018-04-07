
//
//  MapUtil.h
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-7.
//  太多看不懂，没有注释完
//
#pragma once
#ifndef __CarrotFantasy__MapUtil__
#define __CarrotFantasy__MapUtil__

#include "PublicDefine.h"

class MapUtil : public Ref
{
public:
	/*
	* @brief 单例设计模式
	* @details 属于cocos里的宏
	*/
	CREATE_INSTANCE_FUNC(MapUtil);

	DESTROY_INSTANCE_FUNC();
	/*
	* @brief 设置当前级别的平铺地图
	*/
	virtual void setCurrentLevelTiledMap(TMXTiledMap *pTiledMap);
	/*
	* @brief 获取移动pos
	*/
	virtual std::vector<Vec2> getMovePoses();

	virtual std::vector<std::pair<std::string, Rect>> getBarrierPoses();

	virtual std::vector<Rect> getEffectTowerPoses();

	virtual void removeBarrierRect(const Vec2 &rPos);

protected:

	virtual bool init();

	virtual void clearMap();

	virtual void rectTransVec(const Rect &rRect);

private:

	TMXTiledMap *_pTildeMap = nullptr;

	std::map<int, Vec2> *_pMovePosMap = nullptr;

	std::vector<std::pair<std::string, Rect>> *_pBarrierPosMap = nullptr;

	std::vector<Rect> *_pEffectTowerRectVec = nullptr;

private:

	Size _gridSize;
	Size _mapSize;

private:

	virtual ~MapUtil();

};


#endif /* defined(__CarrotFantasy__MapUtil__) */
