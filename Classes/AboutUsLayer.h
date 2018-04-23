/**
 * @brief 设置场景的关于我们图层
 * @todo 当然是写我们的名字啦
 * @version 0.9Alpha
 * @author 陈建彰
 * @date 20180411
 * */
#ifndef ABOUTUS_LAYER_H
#define ABOUTUS_LAYER_H

#include "CommonDefine.h"

class AboutUsLayer : public Layer
{
public:
    CREATE_FUNC(AboutUsLayer);

protected:
    /**
     * @brief 初始化函数
     * */
    bool init() override;

    /**
     * @brief 创建背景函数
     * @details 它是实质创造该图层一切可见对象的函数
     * */
    virtual void createBg();
};

#endif //ABOUTUS_LAYER_H
