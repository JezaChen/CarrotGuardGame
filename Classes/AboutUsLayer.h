/**
 * @brief 设置场景的关于我们图层
 * @todo 当然是写我们的名字啦
 * @version 0.9Alpha
 * @author 陈建彰
 * @date 20180411
 * */
#ifndef MYGAME_ABOUTUSLAYER_H
#define MYGAME_ABOUTUSLAYER_H

#include "CommonDefine.h"

class AboutUsLayer : public Layer
{
public:
    CREATE_FUNC(AboutUsLayer);

protected:
    bool init() override;

    virtual void createBg();
};

#endif //MYGAME_ABOUTUSLAYER_H
