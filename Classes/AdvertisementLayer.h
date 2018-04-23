/**
* @brief 广告图层
* @version 0.9Alpha
* @author 陈建彰
* @provided 何泓兵
* @details 贪玩蓝月，船新版本
* */
#ifndef AD_LAYER_H
#define AD_LAYER_H

#include "CommonDefine.h"

class AdvertisementLayer : public Layer
{
public:
    CREATE_FUNC(AdvertisementLayer);
    ~AdvertisementLayer()override;

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

    /**
     * @brief 换广告
     * @details 每隔一段时间换个广告，四大天王轮流露脸
     */
    virtual void changeAdImg();

    /**
     * @brief 播放广告声音
     */
    virtual void createAdMusic();

    void createAd1();
    void createAd2();
    void createAd3();
    void createAd4();
    void createAd5();
    void createAd6();
    void createAd7();
    void createAd8();
};

#endif //AD_LAYER_H
