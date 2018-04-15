/**
 * @brief 游戏场景 II
 * @details 调试用场景，到时候会取代
 * @author 陈建彰
 * */

#ifndef GAMESCENEII_H
#define GAMESCENEII_H

#include "SceneBase.h"

class EntityLayerBase;

class Carrot;

class GameSceneII : public SceneBase
{
public:

    CREATE_FUNC(GameSceneII);

    ~GameSceneII() override;

    //virtual Carrot* getCarrot();

    //virtual void clickChooseItem();
protected:

    bool init() override;

    virtual void createLayers();

    virtual void addLayers();

    void onEnter() override;

    void onExit() override;

    virtual void preLoadSource();

    virtual void unLoadSource();

    //virtual void collisionUpDate(float dt);

    virtual void createBarriers();

    virtual void clearAllManager();

    virtual void registerGameEvent();

    //virtual void showGameEndLayer(Ref *pData);

    virtual void startBuildMonster(Ref *pData);

private:

    /**
    *  gamescene包括七个图层：tiledMapLayer，barrierLayer，BulletsLayer，MonsterLayer，TowersLayer，ScoreAndControllerLayer，OptLayer
    */

    std::vector<std::string> *_pSourceVec = nullptr; //所有资源组织成一个向量

    Layer *_pTiledMapLayer = nullptr; //地图图层

    EntityLayerBase *_pBarriersLayer = nullptr; //障碍物图层

    EntityLayerBase *_pBulletsLayer = nullptr;  //子弹图层

    EntityLayerBase *_pMonsterLayer = nullptr; //怪物图层

    EntityLayerBase *_pTowersLayer = nullptr; //炮塔图层

    Layer *_pScoreAndControllerLayer = nullptr; //分数和控制器图层

    Layer *_pOptLayer = nullptr; //设置图层?

    Carrot *_pCarrot = nullptr; //萝卜

    int _iSourceCount = 0; //TODO 该如何改进呢
};

#endif //GAMESCENEII_H
