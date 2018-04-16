#pragma once
#ifndef CONFIG_H
#define CONFIG_H

#include "CommonDefine.h"

/**
 * @brief 设置和配置工具类
 * @details 获取声音配置、保存声音配置、创建关卡数据等等，用于游戏全局配置的读取和保存
 * @author 何泓兵
 * @version 1.0
 * @co_author 陈建彰
 * @todo 用户通关数据（杀怪数等等）还没有加上去
 * */


#include "CommonDefine.h"

class SoundUtil;

class Config :public Ref
{
public:

    CREATE_INSTANCE_FUNCTION(Config);

    DESTROY_INSTANCE_FUNCTION();
    /**
    *  flag source be loading
    */
    CC_SYNTHESIZE_PASS_BY_REF(bool, _bIsLoadSource, IsLoadSource);

    /**
     * @brief 保存游戏当前设置中的声音配置到文件中
     * */
    virtual void saveSoundConfig();

    /**
     * @brief 读取文件中的声音配置并设置当前游戏的声音状态
     * */
    virtual void setSoundConfig();

protected:

    /**
     * @brief 初始化函数
     * */
    virtual bool init();

    /**
     * @brief 检查关卡数据是否有建立好了
     * @details 一开始玩游戏的时候，因为关卡数据并没有生成，需要一个函数判断关卡数据的生成
     * */
    virtual void checkBuildLevelData();

    /**
     * @brief 创建关卡数据
     * @details 用于一开始玩保卫萝卜的时候生成一个关卡数据，用于保存玩家的通关情况
     * */
    virtual void createLevelDataFile();
private:

    std::string _sConfigFileName = ""; //配置文件的绝对路径

    std::string _sLevelDataFileName = ""; //关卡数据文件的绝对路径

    ValueMap _configValueMap; //从配置文件读取出来的哈希表

private:

    Config();

    virtual ~Config();

    Config &operator=(const Config &) = delete;

    Config(const Config &) = delete;
};

#endif
