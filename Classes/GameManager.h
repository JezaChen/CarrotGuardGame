#pragma once
/**
 * @brief 游戏管理类
 * @details 功能目前比较鸡肋，只是提供一些游戏的参数而已
 * @author 陈建彰
 * @date 20180410
 * @version 1.2
 * @update 1.2 针对数据统计功能进行升级
 * @update 1.1 针对BOSS模式进行改造
 */

#ifndef __CarrotFantasy__GameManager__
#define __CarrotFantasy__GameManager__

#include "CommonDefine.h"

class GameManager :public Ref
{
public:

	CREATE_INSTANCE_FUNCTION(GameManager);

	DESTROY_INSTANCE_FUNCTION();

    /**
     * @brief 更新用户数据
     * @details  将本关卡的数据更新到用户配置文件里面
     * @since 1.2
     */
    void updateUserStatistics();
protected:
	/*
	* @brief 不暂停？你在干嘛呢
	*/
	virtual bool init();

	CC_SYNTHESIZE_PASS_BY_REF(int, _iCarrotHp, ICarrotHp);

	CC_SYNTHESIZE_PASS_BY_REF(int, _iMonsterBatch, IMonsterBatch);

	CC_SYNTHESIZE_PASS_BY_REF(bool, _bIsPause, IsPause);

    CC_SYNTHESIZE_PASS_BY_REF(GameType, _gmCurrGameType, CurrGameType);

    /**
     * @brief 游戏是否赢了
     * @details 用于数据统计
     * @since 1.2
     */
    CC_SYNTHESIZE_PASS_BY_REF(bool, _bIsWin, IsWin); 

    /**
     * @brief BOSS模式下的剩余时间
     * @details 只对BOSS模式起作用
     * @since 1.1
     */
    CC_SYNTHESIZE_PASS_BY_REF(int, _iTime, ICurrTime);

    /**
     * @brief BOSS模式下的BOSS生命值
     * @details 只对BOSS模式起作用
     * @since 1.1
     */
    CC_SYNTHESIZE_PASS_BY_REF(int, _iBossHp, IBossHp);

    /**
     * @brief 增加监听器
     * @datils 用于更新用户历史数据
     * @details 在初始化函数里面调用
     * @since 1.2
     */
    void addObserver();
    
    ~GameManager();

    /**
    * @brief 更新本次关卡的增加金钱数
    * @details 用于数据统计用的
    * @since 1.2
    * @param pData 要增加的金钱
    */
    void updateIncreasedMoney(Ref *pData);

    /**
    * @brief 增加一个被消灭的怪物
    * @details 用于数据统计用的
    * @since 1.2
    */
    void addOneEliminatedMonster(Ref *pData);

    /**
    * @brief 增加一个被消灭的BOSS
    * @details 用于数据统计用的
    * @since 1.2
    */
    void addOneEliminatedBoss(Ref *pData);

    /**
    * @brief 增加一个被清除的障碍物
    * @details 用于数据统计用的
    * @since 1.2
    */
    void addOneClearedBarrier(Ref *pData);

private:

	GameManager() {}

	GameManager(const GameManager&) = delete;

	GameManager &operator=(const GameManager&) = delete;


    int _iIncreasedMoney; //本次关卡所增加的金钱
    int _iEliminatedMonster; //本次关卡打死怪物总数
    int _iEliminatedBoss; //本次关卡打死BOSS总数
    int _iClearedBarriers; //本次关卡清除障碍物总数
};

#endif /* defined(__CarrotFantasy__GameManager__) */
