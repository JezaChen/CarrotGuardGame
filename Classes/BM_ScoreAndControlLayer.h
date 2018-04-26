/**
* @brief BOSS模式的游戏菜单项
* @author 陈建彰
* @date 20180420
*/

#pragma once
#ifndef BM_SCOREANDCONTROL_LAYER_H
#define BM_SCOREANDCONTROL_LAYER_H

#include "CommonDefine.h"
/**
*  BM_ScoreAndControllerLayer use show money,control pause game,back to theme and select level
*/

class BM_ScoreAndControllerLayer : public Layer
{
public:

    CREATE_FUNC(BM_ScoreAndControllerLayer);
    /**
    * @brief 点了菜单按钮的暂停
    */
    virtual void setPauseFlagIsClose();
    /**
    * @brief 点击选择项目
    */
    virtual void clickChooseItem();

protected:
    /**
    * @brief 确认图层init函数实现
    */
    virtual bool init();
    /**
    * @brief 创建顶部面板
    * @datails 暂停按钮、菜单按钮
    * @details 注意BOSS模式不能有加速，因为这个模式毕竟是计时的
    */
    virtual void createTopPanel();

    /**
    * @brief 创建底部面板
    * @details 计时器面板
    * @details 记得BOSS模式是有计时器的哟
    */
    virtual void createBottomPanel();

    /**
    * @brief 顶部面板设计
    * @details 面板背景、金钱显示标签、第几波怪物显示、暂停标签显示
    * @ask //todo 暂停游戏后，顶部面板显示的“暂停中”怎么没写啊？？？？
    */
    virtual void loadBg();



    CC_SYNTHESIZE(int, _iMoney, CurMoney);
    /**
    * @brief 注册通知事件
    */
    virtual void registerNotifyEvent();
    /**
    * @brief 关闭注册通知事件
    */
    virtual void unRegisterNotifyEvent();
    /**
    * @brief 金钱数目变化
    */
    virtual void moneyChange(Ref *pData);

    /**
    * @brief 大BOSS血量发生了变化
    * @details 用于更新上方面板BOSS的血量
    * @param dt 调度器要求传入的参数
    * @version 1.2
    * @update 1.2 删除通知，改为定期监听
    */
    virtual void bossHpChanged(float dt);

    /**
    * @brief 定时器的时间发生了变化
    * @details 供调度器使用，每一秒调度一次，用于定时器时间的变化
    * @param dt 调度器要求传入的参数，间隔时间
    */
    virtual void timeChange(float dt);

    /**
    * @brief 设置金钱数目
    */
    virtual void setMoneyNum(const int &rIMoneyNum);
    /**
    * @brief 叫继续
    */

    virtual void loadData();

    void onExit()override;

    virtual void createNumSprite();

private:
    //BOSS血量进度条
    ProgressTimer * pBossHpBar = nullptr;

    //金钱标签；
    Node *_pMoneyLabel = nullptr;
    //是否打开选择菜单；
    bool _bIsOpenChooseMenu = false;
    //是否暂停；
    bool _bIsPause = false;
    //菜单选择精灵指针；
    MenuItemSprite *_pChooseItem = nullptr;
    //时间数字精灵
    Node *_pTimeSp = nullptr;

    //时间对应的成就精灵
    Sprite* _pHonorSp = nullptr;

    //当前关卡限时
    /*目前版本就是让这个Layer来控制计时器吧，读取直接从csv那儿读取*/
    int _iTimeLimit;

    int _iBossTotalHp;
    int _iBossCurrHp;
};

#endif /* defined(BM_SCOREANDCONTROL_LAYER_H) */