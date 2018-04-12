/**
 * @brief 关卡配置工具类
 * @details 用于读写关卡配置文件，给外部类进行调用
 * @author 陈建彰
 * @date 20180412
 * */

#ifndef LEVELCONFIGUTIL_H
#define LEVELCONFIGUTIL_H

#include "CommonDefine.h"

class LevelConfigUtil : public Ref
{
public:
    CREATE_INSTANCE_FUNCTION(LevelConfigUtil);

    DESTROY_INSTANCE_FUNCTION();

    /**
     * @brief 读取当前关卡的配置文件
     * */
    virtual void loadLevelConfig();

    /**
     * @brief 获取当前关卡的配置
     * @details 以供外部对象使用
     * @return 一个包含当前关卡所有配置的元组
     * */
    virtual std::tuple<int, int, int, std::vector<std::string>> getLevelConfig() const;

    /**
     * @brief 获取当前关卡能够使用的塔的类型集合
     * @return 在当前关卡中能够使用的炮塔类型的集合
     * */
    virtual std::vector<std::string> getCurrentTowersInfo() const;

    /**
     * @brief 获取当前关卡中怪兽的波数
     * @return 当前关卡中怪兽的波数
     * */
    virtual int getCurrentMonsterBatchCount() const;

    /**
     * @brief 获取当前关卡初始金钱
     * @return 当前关卡初始的金钱
     * */
    virtual int getCurrentLevelInitialMoney() const;

protected:
    /**
     * @brief 初始化函数
     * */
    virtual bool init();

    int _iCurThemeIndex = 0; //当前主题索引
    int _iCurLevelIndex = 0; //当前关卡索引
    int _iCurLevelInitialMoney = 0; //当前关卡的初始金钱
    int _iMonsterBatchCount = 0; //当前怪兽波数
    std::vector<std::string> *_pEffectTowers = nullptr; //当前关卡可以使用的炮塔集合

private:
    LevelConfigUtil() = default;

    ~LevelConfigUtil() override
    {
        CC_SAFE_DELETE(_pEffectTowers);
    }

    LevelConfigUtil(const LevelConfigUtil &) = delete;

    LevelConfigUtil &operator=(const LevelConfigUtil &) = delete;
};

#endif //LEVELCONFIGUTIL_H
