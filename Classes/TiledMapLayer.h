/**
 * @brief 基于Tiled的地图图层
 * @author 陈建彰
 * @date 20180411
 * */
#ifndef TILEDMAP_H
#define TILEDMAP_H

#include "CommonDefine.h"

class TiledMapLayer : public Layer
{
public:
    CREATE_FUNC(TiledMapLayer);

protected:
    bool init() override;

    /**
     * @brief 加载地图
     * */
    void loadMap();

private:

    TMXTiledMap *_pTiledMap;
};

#endif //TILEDMAP_H
