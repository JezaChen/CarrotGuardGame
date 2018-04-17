/**
 * @brief 游戏场景地图管理类
 * @details 游戏场景有些地方是怪物移动的路线，有些是障碍物，有些是可以放置炮塔的地方，需要这个地图管理类进行统筹、管理
 * @author 陈建彰
 * @date 20180413
 * */

#pragma once
#ifndef __CarrotFantasy__MapUtil__
#define __CarrotFantasy_r_MapUtil__

#include "CommonDefine.h"

class MapUtil : public Ref
{
public:
    /**
     * @brief 单例设计模式
     * @details 属于cocos里的宏
     */
CREATE_INSTANCE_FUNCTION(MapUtil);

    DESTROY_INSTANCE_FUNCTION();

    /**
     * @brief 读取、设置并分析当前关卡的瓦片地图
     * @details 用传进的瓦片地图的数据初始化实例，这个才是真正的初始化函数
     * @param pTiledMap 当前关卡瓦片地图
     * */
    virtual void setAndAnalyzeCurrentLevelTiledMap(TMXTiledMap *pTiledMap);

    /**
     * @brief 获取怪物移动路线
     * @return 怪物可移动路线每个点的坐标向量
     */
    virtual std::vector<Vec2> getMovePoses();

    /**
     * @brief 获取障碍物位置
     * @return 一个元组向量，每个元组第一个参数是指示障碍物的字符串，第二个参数是障碍物的具体坐标
     */
    virtual std::vector<std::pair<std::string, Rect>> getBarrierPoses();

    /**
     * @brief 获取能够放置炮塔的坐标
     * @return 一个存储矩形向量
     * @details 之所以返回个矩形向量，是因为有些障碍物是特别大个的，单个坐标是没有办法描述大型障碍物
     */
    virtual std::vector<Rect> getEffectTowerPoses();

    /**
     * @brief 移去障碍物坐标
     * @details 就是说，障碍物被消灭掉了，这位置就空着了，并没有障碍物在里面，这时候地图需要动态刷新
     * @param 障碍物的位置坐标
     * @todo 炮塔就不用移去吗???
     */
    virtual void removeBarrierRect(const Vec2 &rPos);

protected:
    /**
     * @brief 声明地图中必须的指针并分配内存
     * @brief 你直接叫初始化函数就行了... by Chen
     * @return true 分配成功，否则返回false
     */
    virtual bool init();

    /**
     * @brief 清理地图
     */
    virtual void clearMap();

    /**
     * @brief 矩形拆分
     * @details 1-地图文件的炮塔有效放置位置是一个大小不一的举行块来的，而炮塔本身只能放在一个小方块中，这时候要拆分矩形变成一个个小方块，并放在对应的向量中
     * @details 2-障碍物拆除后，此时可以放置炮塔了，而障碍物有时候占据的范围比较大，这时候需要拆分一个个小方块
     */
    virtual void rectTransVec(const Rect &rRect);

private:
    /**
     * @brief 地图指针
     */
    TMXTiledMap *_pTildeMap = nullptr;

    /**
     * @brief 怪物可移动轨迹的坐标向量
     * @details 坐标相对于路径块左上方
     * */
    std::map<int, Vec2> *_pMovePosMap = nullptr;

    std::vector<std::pair<std::string, Rect>> *_pBarrierPosMap = nullptr; //障碍物位置向量

    std::vector<Rect> *_pEffectTowerRectVec = nullptr; //炮塔可以放置的坐标向量

private:

    Size _gridSize; //格子数

private:

    virtual ~MapUtil();

};


#endif /* defined(__CarrotFantasy__MapUtil__) */
