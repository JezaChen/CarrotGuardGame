/**
 * @brief 子弹基类
 * @details 有一些炮塔的攻击逻辑是炮塔基类和子弹基类分离开来的，因而对于一些炮塔而言，子弹基类负责真正的攻击逻辑
 * @author 陈建彰 x 何泓兵
 * @date 20180410
 * */

#pragma once
#ifndef __CarrotFantasy__BulletBase__
#define __CarrotFantasy__BulletBase__

#include "Entity.h"
#include "DynamicPropertyInterface.h"

class BulletBase : public Entity, public DynamicPropertyInterface
{

public:
    /**
     * @todo 废弃，好像没啥用
     * */
    std::set<int> &getIdMap();

    /**
     * @brief 移动函数，虚函数
     * @details 子弹移动动作处理及游戏逻辑处理
     * @details 继承的子类可根据需要重写移动函数
     * */
    virtual void doMove();

    /**
     * @brief 根据子弹ID和选定怪物基类创造子弹基类
     * @details 设计模式中的工厂模式，根据条件生产子弹
     * @param rIId 子弹ID
     * @param rVictimEntity 选定的目标怪物基类
     * @return 生产出来的子弹基类
     * */
    static BulletBase *create(const int &rIId, VictimEntityBase *rVictimEntity);

    /**
     * @brief 获取子弹攻击属性
     * @return 该子弹基类的攻击属性
     */
    virtual AtkProperty getAtkPro();

    /**
     * @brief 死亡动画
     * @extends Entity
     * @details 子弹消亡后的动作处理
     * @param rSDeadImageFile 消亡动画帧路径前缀
     */
    virtual void deadAction(const std::string &rSDeadImageFile = "");

    /**
     * @brief 子弹本身在动的动画
     * @details 供调度器使用的函数
     * @param rDt 调度器要求引入的调度时间
     */
    virtual void doAction(const float &rDt);

protected:
	/*
	* @brief 确认公共父类的init的实现，即初始化
	* @retails 获取子弹攻击状态，子弹类型，死亡动画数目，并把设计好的子弹加入管理类中
	* @param rId 子弹id
	* @param rVictimEntity 受伤害实体等同于攻击目标
	*/
	virtual bool init(const int &rId, VictimEntityBase *rVictimEntity);
	/*
	* @brief 攻击类型
	*/
	CC_SYNTHESIZE_PASS_BY_REF(int, _iAtkState, IAtkState);
	/**
	* @brief 子弹类型
	*/
	CC_SYNTHESIZE_PASS_BY_REF(int, _iBulletType, IBulletType);
	/**
	* @brief 死亡动画数
	*/
	CC_SYNTHESIZE_PASS_BY_REF(int, _iDeadActCount, IDeadActCount);
	//攻击目标指针；
	VictimEntityBase *_pAtkTarget = nullptr;

	std::set<int> *_IdMap = nullptr;
};

#endif /* defined(__CarrotFantasy__BulletBase__) */