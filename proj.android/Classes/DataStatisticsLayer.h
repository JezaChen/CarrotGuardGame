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

    void createBg();
};

#endif //DATASTATISTICS_H
