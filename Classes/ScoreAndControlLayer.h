//
//  ScoreAndControlLayer.h
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-13.
//
//
#pragma once
#ifndef __CarrotFantasy__ScoreAndControlLayer__
#define __CarrotFantasy__ScoreAndControlLayer__

#include "CommonDefine.h"
/**
 *  ScoreAndControllerLayer use show money,control pause game,back to theme and select level
 */

class ScoreAndControllerLayer: public Layer
{
public:
    
    CREATE_FUNC(ScoreAndControllerLayer);
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
	* @datails 暂停按钮、加速按钮、菜单按钮
	*/
    virtual void createTopPanel();
    /**
	* @brief 顶部面板设计
	* @details 面板背景、金钱显示标签、第几波怪物显示、暂停标签显示
	* @ask 暂停游戏后，顶部面板显示的“暂停中”怎么没写啊？？？？
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
	* @brief 怪物批量改变
	*/
    virtual void monsterBatchChange(Ref *pData);
    /**
	* @brief 设置怪物批量数目
	*/
    virtual void setMonsterBatchCount(const int &rIMonsterBatchIndex);
    /**
	* @brief 设置金钱数目
	*/
    virtual void setMoneyNum(const int &rIMoneyNum);
    /**
	* @brief 叫继续
	*/
    virtual void onExit()override;
    
private:
    //怪物批量索引；
    Node *_pMonsterBatchIndex = nullptr;
    //金钱标签；
    Node *_pMoneyLabel = nullptr;
    //是否打开选择菜单；
    bool _bIsOpenChooseMenu = false;
    //是否开启加速；
    bool _bIsOpenSpeedUp = false;
    //是否暂停；
    bool _bIsPause = false;
    //菜单选择精灵指针；
    MenuItemSprite *_pChooseItem = nullptr;

};

#endif /* defined(__CarrotFantasy__ScoreAndControlLayer__) */