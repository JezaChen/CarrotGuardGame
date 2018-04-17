/**
 * @brief 怪物管理类
 * @details 上帝视角管理
 * @authors 何泓兵 x 陈建彰
 * */
#pragma once
#ifndef __CarrotFantasy__MonsterManager__
#define __CarrotFantasy__MonsterManager__


#include "CommonDefine.h"

class Entity;

class MonsterManager : public Ref
{
public:
    /**
     * @brief cocos里的宏
     * @details 单例设计模式
     */
    CREATE_INSTANCE_FUNCTION(MonsterManager);

    DESTROY_INSTANCE_FUNCTION();

    /**
     * @brief 获取怪物vector的引用
     */
    virtual MonsterVec &getMonsterVec();

    /**
     * @brief 添加怪物到图层的设置函数
     */
    virtual void setFuncAddMonsterToLayer(const std::function<void(Entity *)> &rFuncAddMonsterToLayer);

    /**
     * @brief 清除管理类
     */
    virtual void clearManager();

    /**
     * @brief 清除被攻击的锁定状态
     */
    virtual void clearBeAtkLockState();

protected:
    /**
    * @brief 声明友元类
    */
    friend class MonsterBase;

    /**
    * @brief 检查游戏是否结束开关
    */
    virtual void openCheckGameEnd(Ref *pSender);

    /**
    * @brief 添加怪物
    */
    virtual void addMonster(MonsterBase *pBullet);

    /**
    * @brief 初始化函数
    * @return true 初始化成功，否则返回false
    */
    virtual bool init();

    /**
    * @brief 注册死亡事件
    */
    virtual void registerDeadEvent();

    /**
    * @brief 从manager中删去怪物
    */
    virtual void removeMonsterFromManager(Ref *pMonster);

private:
    //怪物vector容器指针；
    MonsterVec *_pMonsterVec = nullptr;

    std::function<void(Entity *)> _funcAddMonsterToLayer;

    bool _bIsOpenCheckGameEnd = false;

private:

    MonsterManager();

    virtual ~MonsterManager();

    MonsterManager(const MonsterManager &) = delete;

    MonsterManager &operator=(const MonsterManager &) = delete;

};


#endif /* defined(__CarrotFantasy__MonsterManager__) */
