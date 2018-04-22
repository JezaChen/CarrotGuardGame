/**
 * @brief 设置场景的数据统计图层
 * @details 什么通关数目，打怪数目之类的
 * @todo 需要新增一个文件来存储用户的数据，这个先搁置一下
 * @version 0.9Alpha
 * @author 陈建彰
 * @date 20180411
 * */
#ifndef DATASTATISTICS_H
#define DATASTATISTICS_H

#include "CommonDefine.h"

class DataStatLayer : public Layer
{
public:
    CREATE_FUNC(DataStatLayer);

protected:
    bool init() override;

    /**
     * @brief 创建该图层的背景
     */
    void createBg();

    /**
     * @brief 读取用户通关数据
     */
    void loadData();

    /**
     * @brief 创建数字精灵
     */
    void createNumSprite();

    //冒险模式通关数目
    int _iAdventureModeClearance; 
    
    //隐藏关卡通关数目
    int _iCrypticModeClearance; 
    
    //BOSS模式通关数目
    int _iBossModeClearance;
    
    //总金钱
    int _iTotalMoney;
    
    //打死怪物数目
    int _iTotalBoss;
    
    //打死BOSS数目
    int _iTotalMonster;
    
    //清除障碍物数目
    int _iTotalBarriers;
};

#endif //DATASTATISTICS_H
