/**
* @brief Boss模式中的怪物波生成类
* @details 注意，只支持Boss模式
* @details 游戏场景中一波波汹涌而来的怪物生成
* @author 陈建彰
* @date 20180414
* */

#ifndef BM_MONSTERBUILDER_H
#define BM_MONSTERBUILDER_H

#include "CommonDefine.h"

class BM_MonsterBuilder : public Node
{
public:
    CREATE_FUNC(BM_MonsterBuilder);


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

    /**
     * @brief 读取当前关卡的主题编号和关卡编号
     * @details 供初始化函数调用，为了生成对应关卡特定的BOSS
     */
    void loadData();

    ~BM_MonsterBuilder() override;

protected:
    float _fDelayTime; //每一波怪物出现的间隔时间
    int _iCurrNumber; //当前怪物出现的数目
    int _iTotalNumber; //怪物总数目
    Animation* _createMonsterAnimation; //生成动画

    int _iCurrTheme = 1; //目前主题
    int _iCurrLevel = 1; //目前关卡
    /**************|FBI Warning|*************/
    /**要注意Boss关卡的编号是每个主题的13~16关**/
    /***************************************/

    static const int DELAY_TIME = 8.5;

    int _iFirstMonsterType; //第一波小怪的类型
    int _iSecondMonsterType; //第二波小怪的类型
    int _iBossType; //大BOSS的类型
};

#endif //BM_MONSTERBUILDER_H
