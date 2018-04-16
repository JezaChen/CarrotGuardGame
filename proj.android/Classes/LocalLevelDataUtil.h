/**
 * @brief 关卡数据工具类
 * @author 陈建彰
 * @date 20180309
 * */

#ifndef MYGAME_LOCALLEVELDATAUTIL_H
#define MYGAME_LOCALLEVELDATAUTIL_H

#include "CommonDefine.h"

/**
 * @class LocalLevelDataUtil
 * @brief 关卡数据工具类
 * @details 用户是否通关、通关情况如何、通关数据读写
 * @author 陈建彰
 * */
class LocalLevelDataUtil : public Ref
{
public:
    CREATE_INSTANCE_FUNCTION(LocalLevelDataUtil);

    DESTROY_INSTANCE_FUNCTION();

    /**
     * @brief 获取关卡数据
     * @return ValueMap& 返回关卡数据(哈希表)的引用
     * */
    virtual ValueMap &getLevelData();

    /**
     * @brief 设置关卡数据
     * @param rValueMap 要设置的关卡数据
     * */
    virtual void setLevelData(const ValueMap &rValueMap);

protected:
    /**
     * @brief 初始化
     * */
    virtual bool init();

    /**
     * @brief 向通知中心注册监听事件
     * */
    virtual void registerLevelDataChangesEvent();

    /**
     * @brief 监听事件所用到的处理函数
     * @param pData 传入该处理函数的一些数据
     * @details 一旦有东西要修改，该函数会打开数据文件，更新key值对应的value值，并再次写入和保存
     * */
    virtual void levelDataChange(Ref *pData);

private:
    ValueMap _levelData; //关卡数据，用哈希表表示

    std::string _sLevelDataFilePath = ""; //数据文件的路径，绝对路径

    LocalLevelDataUtil()
    {}

    virtual ~LocalLevelDataUtil();

    LocalLevelDataUtil(const LocalLevelDataUtil &) = delete;

    LocalLevelDataUtil &operator=(const LocalLevelDataUtil &) = delete;
};

#endif //MYGAME_LOCALLEVELDATAUTIL_H
