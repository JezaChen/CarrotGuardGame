/**
 * @brief 关于塔的菜单类
 * @details 游戏场景中建塔、升级塔的菜单
 * @authors 何泓兵 x 陈建彰
 * @date 20180413
 * */
#pragma once
#ifndef __CarrotFantasy__TowerOptBtn__
#define __CarrotFantasy__TowerOptBtn__

#include "cocos2d.h"

class TowerBase;

using namespace cocos2d;

class TowerOptBtn : public Node
{
public:

    CREATE_FUNC(TowerOptBtn);

    TowerOptBtn();

    virtual ~TowerOptBtn();

    /**
     * @brief 隐藏塔的选项
     */
    virtual void hideTowerOpt();

    /**
     * @brief 显示塔的选项
     */
    virtual void showTowerOpt();

    /**
     * @brief 设置用于检查金钱够不够的函数
     * @details 这个函数是在GameScene那里调用的
     * @param rFuncCheckMoney 用于检查金钱够不够的函数
     */
    virtual void setFuncCheckMoney(const std::function<int()> &rFuncCheckMoney);

    /**
     * @brief 创建塔的菜单栏
     * @details 点击空地时显示的菜单
     * @see 显示出各种塔防的图案
     */
    virtual void createTowerMenu();

    /**
    * @brief 点击塔防展示的菜单
    * @details 展示升级塔防按钮、卖掉这个塔的按钮
    */
    virtual void gradeTowerMenu(TowerBase *touchTower);

    /**
    * @brief 展示创建菜单
    * @details 创建菜单的位置选择
    * @see 各种坐标玄学调参
    */
    virtual void showCreateMenu();

    /**
    * @brief 隐藏创建菜单
    */
    virtual void hideCreateMenu();

protected:
    /**
     * @brief
     * @details 计时器监控变化过程
     */
    virtual bool init();

    /**
     * @brief 创建菜单主入口
     * @details 用于初始化函数调用的创建菜单入口
     */
    virtual void createMenuAndItems();

    /**
    * @brief 不太懂他在干嘛
    */
    virtual void ChangingItem(float dt);

protected:
    bool _bKeySpVisible; //菜单之母是否显示了
    Sprite *_pKeySp; //菜单之母

    Menu *_pCreateMenu1; //点击空地后菜单的第一行菜单
    Menu *_pCreateMenu2; //点击空地后菜单的第二行菜单
    Menu *_pGradeMenu; //点击炮塔后的用于升级或者拆除的菜单
    Sprite *_pTowerRangeSp; //点击炮塔后那个以炮塔为中心的灰色圈圈

    std::function<int()> _funcCheckMoney;

    /**
     * @brief 两个向量是用于调度器间歇性检查金钱够不够买东西
     * @details 当金钱数足够的时候，向量的元素(精灵)会呈高亮状态
     */
    Vector<MenuItemSprite *> *_pCreateTowerItemSpVec = nullptr;
    Vector<MenuItemSprite *> *_pGradeTowerItemSpVec = nullptr;
};


#endif /* defined(__CarrotFantasy__TowerOptBtn__) */