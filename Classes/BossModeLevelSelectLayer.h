/**
 * @brief Boss模式关卡选择画面图层
 * @author 陈建彰
 * @date 20180419
 */
#include "CommonDefine.h"
#include "ui/UIPageView.h"

using namespace ui;

#pragma once
#ifndef BOSSMODE_LEVELSELECT_LATER_H
#define BOSSMODE_LEVELSELECT_LAYER_H

class BossModeLevelSelectLayer : public Layer
{
public:
    /**
     * @brief 工厂模式用的生产宏
     */
    CREATE_FUNC(BossModeLevelSelectLayer);

    /**
     * @brief 析构函数
     */
    ~BossModeLevelSelectLayer() override;

protected:
    /**
     * @brief 初始化函数
     */
    virtual bool init();

    virtual void loadSource();

    /**
     * @brief 加载关卡按钮
     * @details 就是中间那些关卡的缩略图，其实也是个进去游戏画面的按钮
     */
    virtual void loadBossLevelButton();

    /**
    * @brief 加载菜单等功能性按键的函数
    * @ps //TODO 以后可能会独立出一个头文件，减少代码的耦合度
    * */
    virtual void loadMenuItem();

    /**
    * @brief 获取某个关卡的通关情况
    * @param rLevelIndex 关卡索引号
    * @return 返回一个tuple，第一个是通关荣誉，也就是萝卜星数，什么金萝卜、银萝卜之类的；第二个是是否消灭所有的障碍物
    * */
    virtual std::tuple<int, bool> getLevelData(const int& rLevelIndex);

    /**
    * @brief 切换到游戏界面的函数
    * */
    virtual void changeToGameScene();

    /**
    * @brief 加载资源
    * @details 其实就是加载所有关卡的通关数据，放在一个属性里
    * */
    virtual void loadData();

    /**
     * @brief 检查每个主题的大Boss是否被解锁了
     * @details 供初始化函数调用
     * @details 只有每个主题的前八关都通关了，对应主题的大Boss才被解锁
     */
    void checkThemeUnlocked();

private:
    int _iCurLevelIndex = 0; //目前页号

    MenuItemSprite* _pStartBtn = nullptr; //开始按钮

    Sprite* _pLockedBtn = nullptr; //锁定精灵

    Sprite* _pBossDetailsSprite = nullptr; //怪物详情精灵，里面有很多孩子

    std::map<int, bool>* _pCheckLockedMap = nullptr; //主题通关情况哈希表

    ValueMap _DataValueMap;
};


#endif //BOSSMODE_LEVELSELECT_LAYER_H
