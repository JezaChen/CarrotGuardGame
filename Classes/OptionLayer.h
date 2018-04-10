/**
 * @brief 设置场景的游戏设置图层
 * @details 设置声音开关、音效开关等等
 * @author 陈建彰
 * @date 20180411
 * **/

#ifndef OPTIONLAYER_H
#define OPTIONLAYER_H

#include "CommonDefine.h"

class OptionLayer : public Layer
{
public:
    CREATE_FUNC(OptionLayer);
protected:
    bool init() override;
    /**
     * @brief 加载图层资源并加在图层中
     * */
    virtual void loadSource();
};

#endif //OPTIONLAYER_H
