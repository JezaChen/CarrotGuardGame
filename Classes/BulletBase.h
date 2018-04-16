/**
<<<<<<< HEAD
 * @brief 子弹基类
 * @details 有一些炮塔的攻击逻辑是炮塔基类和子弹基类分离开来的，因而对于一些炮塔而言，子弹基类负责真正的攻击逻辑
 * @author 陈建彰 x 何泓兵
 * @date 20180410
 * */
=======
* @brief 子弹基类
* @details 子弹的公共父类
* @authors 何泓兵
* @date 20180410
* */
>>>>>>> 2b54e38197accaaf381028f2c3f0fdfb3905acdb
#pragma once
#ifndef __CarrotFantasy__BulletBase__
#define __CarrotFantasy__BulletBase__

#include "Entity.h"
#include "DynamicPropertyInterface.h"

class BulletBase : public Entity, public DynamicPropertyInterface
{

public:
<<<<<<< HEAD
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
    /**
     * @brief 初始化函数
     * @retails 获取子弹攻击状态，子弹类型，死亡动画数目，并把设计好的子弹加入树中
     * @param rId 子弹ID
     * @param rVictimEntity 子弹面对的攻击目标
     */
    virtual bool init(const int &rId, VictimEntityBase *rVictimEntity);
    /**
     * @brief 如果塔防是防御类，那么攻速变低
     */
    CC_SYNTHESIZE_PASS_BY_REF(int, _iAtkState, IAtkState);

    CC_SYNTHESIZE_PASS_BY_REF(int, _iBulletType, IBulletType);

    CC_SYNTHESIZE_PASS_BY_REF(int, _iDeadActCount, IDeadActCount);
    //攻击目标指针；
    VictimEntityBase *_pAtkTarget = nullptr;

    std::set<int> *_IdMap = nullptr;
=======
	//
	std::set<int>& getIdMap();
	/**
	* @brief 子弹的移动函数
	* @details 需要确认子弹攻击目标是否死亡，计算子弹的移动方向和移动距离
	*/
	virtual void doMove();
	/**
	* @brief 初始化子弹函数
	* @param rIId 子弹的id
	* @param rVictimEntity 子弹的攻击目标（实体基类）
	*/
	static BulletBase *create(const int &rIId, VictimEntityBase *rVictimEntity);
	/**
	* @brief 子弹攻击参数
	* @details 子弹的攻击类型，攻击力，子弹种类，攻击持续时间
	*/
	virtual AtkProperty getAtkPro();
	/**
	* @brief 执行死亡动画
	* @extends VictimEntityBase
	* @param rSDeadImageFile 死亡动画帧图片
	* @see 实质可见的死亡动画是用Entity类的方法执行
	*/
	virtual void deadAction(const std::string &rSDeadImageFile = "");

	/**
	* @brief 模型精灵做动作
	* @extends DynamicPropertyInterface
	* @param rDt 调度器需要的参数
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
>>>>>>> 2b54e38197accaaf381028f2c3f0fdfb3905acdb
};

#endif /* defined(__CarrotFantasy__BulletBase__) */