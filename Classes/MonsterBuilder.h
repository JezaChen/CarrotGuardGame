/**
 * @brief 怪物波生成类
 * @details 游戏场景中一波波汹涌而来的怪物生成
 * @author 陈建彰
 * @date 20180414
 * */

#ifndef MONSTERBUILDER_H
#define MONSTERBUILDER_H

#include "CommonDefine.h"
class MonsterBuilder : public Node
{
public:
    CREATE_FUNC(MonsterBuilder);

    /**
     * @brief 获取目前波数
     * @return 目前处于第几波怪物的生成
     * */
    int getCurrBatch();

protected:
    /**
     * @brief 初始化函数
     * @return true 初始化成功
     * @return false 初始化失败
     * */
    bool init() override;

    /**
     * @brief 结点被调用的时候使用的函数
     * */
    void onEnter() override;

    /**
     * @brief 创建一波怪物
     * @details 供调度器调用的函数方法
     * @param t 调度器需要的参数，调度的间隔时间
     * */
    void createMonsters(float t);

    /**
     * @brief 调用怪物工厂创建怪物
     * @details createMonsters所调用的实质生成怪物的函数
     * */
    void monsterFactoryControl();

    /**
     * @brief 初始化的时候调用生成怪物创建动画
     * */
    void createCMonsterAnimation();

    ~MonsterBuilder() override;

protected:
    float _fDelayTime; //每一波怪物出现的间隔时间
    int _iMonsterCountsInCurrBatch; //当前波中怪物出现的数目
    int _iMonsterBatch; //当前关卡怪物波数
    int _iNumber;
    int _iCurrBatch; //当前波数
    Animation * _createMonsterAnimation; //生成动画

    static const int DELAY_TIME = 8.5;
};

#endif //MONSTERBUILDER_H
