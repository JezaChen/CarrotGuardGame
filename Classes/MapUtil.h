
//
//  MapUtil.h
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-7.
//  太多看不懂，没有注释完
//
#pragma once
#ifndef __CarrotFantasy__MapUtil__
#define __CarrotFantasy_r_MapUtil__

#include "CommonDefine.h"

class MapUtil : public Ref
{
public:
	/*
	* @brief 单例设计模式
	* @details 属于cocos里的宏
	*/
	CREATE_INSTANCE_FUNCTION(MapUtil);

	DESTROY_INSTANCE_FUNCTION();
	/*
	* @brief 设置当前级别的平铺地图
	*/
	virtual void setCurrentLevelTiledMap(TMXTiledMap *pTiledMap);
	/*
	* @brief 获取移动位置
	*/
	virtual std::vector<Vec2> getMovePoses();
	/*
	* @brief 获取障碍物位置
	*/
	virtual std::vector<std::pair<std::string, Rect>> getBarrierPoses();
	/*
	* @brief 获取效果塔的位置
	*/
	virtual std::vector<Rect> getEffectTowerPoses();
	/*
	* @brief 删去障碍物
	* @param 障碍物的位置坐标
	*/
	virtual void removeBarrierRect(const Vec2 &rPos);

protected:
	/*
	* @brief 声明地图中必须的指针并分配内存
	* @return true 分配成功，否则返回false
	*/
	virtual bool init();
	/*
	* @brief 清理地图
	*/
	virtual void clearMap();
	/*
	* @Rect变量转Vec
	*/
	virtual void rectTransVec(const Rect &rRect);

private:
	/*
	* @brief 地图指针
	*/
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
