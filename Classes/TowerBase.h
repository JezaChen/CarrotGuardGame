/**
 * @brief 炮塔基类
 * @details 用于封装所有炮塔的共同属性
 * @details 由于每个炮塔之间存在者一些差异，所以这个基类不同于障碍物基类、怪物积累，它还需要不同的子类来封装属于自己的特殊功能
 * @authors 何泓兵 x 陈建彰
 * @date 20180409
 * */
#pragma once
#ifndef __CarrotFantasy__TowerBase__
#define __CarrotFantasy__TowerBase__

#include "Entity.h"

class VictimEntityBase;


class TowerBase : public Entity
{
public:

    static TowerBase *create(const int &rId);

    /**
     * @brief 控制炮塔旋转的函数
     * @details 该函数用于调度器使用，以时刻更新炮塔的旋转状态
     * @param dt 调度器需要引入的参数，调度时间
     * */
    virtual void doRotation(float dt);

    ~TowerBase() override;

    /**
     * @brief 获取塔升级的成本
     * @details 塔升级毕竟要钱的嘛
     * @return 升级需要的成本，整型数
     * */
    virtual int getTowerGradeCost();

    /**
     * @brief 设置该炮塔基类的攻击目标
     * @param pVictimEntity 攻击目标，一个伤害实体
     * */
    virtual void setAtkTarget(VictimEntityBase *pVictimEntity);

    /**
     * @brief 显示可升级等级标志
     * @details 就是钱够了，就显示那个上升的箭头
     * @todo 这个名字要改啊，太容易混淆了
     */
    virtual void showGradeMark();

    /**
     * @brief 隐藏可升级等级标志
     */
    virtual void hideGradeMark();

    /**
     * @brief 检查怪物或者障碍物是否在攻击范围
     * @param rPos 攻击目标位置
     * @return true 在攻击范围内，否则返回false
     */
    virtual bool isInAtkRange(const Vec2 &rPos);

    /**
     * @brief 升级塔
     */
    virtual void upGrade();

protected:
    /**
     * @brief 死亡动画函数执行
     * @extends Entity
     * @details 做出一些死亡后的处理，并调用父类的死亡动画执行函数
     * @details 记住，这个函数一定要自下而上调用
     * @details 利用给定的参数生成死亡动画；如果参数为空字符串，则使用默认的死亡动画
     * @param rSDeadImageFile 死亡动画帧具体路径
     */
    virtual void deadAction(const std::string &rSDeadImageFile = "") override;

    /**
     * @brief 检查攻击目标
     * @details 用于调度器使用的调度函数
     * @param rDt 调度时间
     */
    virtual void checkAtkTarget(float dt);

    /**
     * @brief 选择攻击目标
     * @details 目前的方案是遍历怪物向量，找到第一个符合范围要求的怪物进行攻击
     */
    virtual void chooseAtkTarget();

    /**
     * @brief 检查攻击目标是否出了范围
     * @details 就是判断指定的攻击目标_pAtkTarget是否超出了范围
     */
    virtual void checkTargetIsOutOfRange();

    /**
     * @brief 放弃攻击目标
     * @details 适用场合是当攻击目标超过范围后，就放弃攻击目标
     * @todo 测试工程师帮忙看看当工具目标又出现在范围里，是否还能进行工具
     */
    virtual void missAtkTarget();

    /**
     * @brief 二营长开火了
     * @details 选定当然是干它一炮啊
     * @param dt 调度时间
     * @details 这个也是调度器使用的函数
     */
    virtual void fire(float dt);

    /**
     * @brief 炮塔第二层初始化函数
     * @details 升级的时候调用这个函数进行高级炮塔的初始化，不用调用第一层了
     */
    virtual void initTower();

    /**
     * @brief 炮塔第一层初始化函数
     * @details 根据炮塔ID初始化该实例
     * @details 果然是老母猪戴胸罩，一套一套的
     * @param rId 炮塔ID号
     */
    virtual bool init(const int &rId);

    /**
     * @brief 塔攻击动画显示
     * @details 注意的是，这个攻击动画函数只关注炮塔本身的动作
     * @see 而子弹的动画显示请看fire()函数
     */
    virtual void fireAction();

    /**
     * @brief 塔关联子弹的id
     */
    CC_SYNTHESIZE_PASS_BY_REF(int, _iBulletId, IBulletId);

    /**
     * @brief 子弹攻击范围
     */
    CC_SYNTHESIZE_PASS_BY_REF(int, _iAtkRange, IAtkRange);

    /**
     * @brief 塔的攻击间隔
     * @details 开炮之间的时间间隔
     */
    CC_SYNTHESIZE_PASS_BY_REF(double, _iAtkInterval, IAtkInterval);

    /**
     * @brief 塔升级的成本费用
     */
    CC_SYNTHESIZE_PASS_BY_REF(std::string, _sUpgradeCost, SUpgradeCose);

    /**
     * @brief 塔的级别数
     */
    CC_SYNTHESIZE_PASS_BY_REF(int, _iUpgradeCount, IUpgradeCount);

    /**
     * @brief 是否旋转
     */
    CC_SYNTHESIZE_PASS_BY_REF(bool, _bIsRotation, BIsRotation);

    /**
     * @brief 各炮塔建塔花费成本
     */
    CC_SYNTHESIZE_PASS_BY_REF(int, _iCreateCost, ICreateCost);

    /**
     * @brief 攻击目标是否已经选定了攻击目标
     */
    CC_SYNTHESIZE_PASS_BY_REF(bool, _bIsHaveAtkTarget, IsHaveAtkTarget);

protected:
    /**
     * @brief 等级标志
     */
    Sprite *_pGradeMark = nullptr;

    /**
     * @brief 塔的面板
     */
    Sprite *_pTowerPanel = nullptr;

    /**
     * @brief 攻击目标
     */
    VictimEntityBase *_pAtkTarget = nullptr;
};

#endif /* defined(__CarrotFantasy__TowerBase__) */
