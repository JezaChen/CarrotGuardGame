//  游戏公有定义类
//  CommonDefine.h
//   newCardDefence
//
//  Created by 何泓兵 on 18-3-30
//  
//

#pragma once
#ifndef COMMON_DEFINE_H
#define COMMON_DEFINE_H

#include"cocos2d.h"
#include"VisibleRect.h"
#include"CommonSource.h"
#include"CsvUtil.h"

using namespace cocos2d;

class VictimEntityBase;  //受害实体基类
class MonsterBase;//怪物基类
class BarrierBase;//屏障基类
class BulletBase;//子弹基类
class TowerBase;//塔防基类

using MonsterVec = Vector<MonsterBase *>;
using BarrierVec = Vector<BarrierBase *>;
using BulletVec = Vector<BulletBase *>;
using TowerVec = Vector<TowerBase *>;

//宏定义创建新实例；
//如果创建成功并且调用init方法初始化成功;
//将对象加入到自动释放池中，并返回；
//否则，创建对象失败，释放对象；
#define CREATE_INSTANCE_FUNCTION(__CLASS__)                       \
private:                                                          \
    static __CLASS__ *_gInstance;                                 \
public:                                                           \
static __CLASS__* getInstance()                                   \
{                                                                 \
    if(!_gInstance)                                               \
    {                                                             \
        _gInstance = new __CLASS__();                             \
        if(_gInstance && _gInstance->init())                      \
        {                                                         \
            _gInstance->autorelease();                            \
            _gInstance->retain();                                 \
        }                                                         \
        else                                                      \
        {                                                         \
            CC_SAFE_DELETE(_gInstance);                           \
        }                                                         \
    }                                                             \
    return _gInstance;                                            \
}                                                                 
//宏定义销毁新实例；
#define DESTROY_INSTANCE_FUNCTION()                               \
static void destroyInstance()                                     \
{                                                                 \
    CC_SAFE_RELEASE_NULL(_gInstance);                             \
}                                                                 
//宏定义通知；
#define NOTIFY cocos2d::NotificationCenter::getInstance()
#define NOTIFICATION_CENTER cocos2d::NotificationCenter::getInstance()
//枚举公有属性；
enum CsvPublicProperty
{
    en_Name = 1,//名字
    en_ModelName,//模型名，一般为名字后加编号；
    en_Value,
    en_AnimationCount,//动画数；
    en_Level//关卡
};
//枚举塔的属性；
enum CsvTowerProperty
{
    en_Range = 6,//范围大小；
    en_Space,//攻击间隔；
    en_BulletId, //子弹编号；
    en_UpGradeCost,//升级成本；
    en_TowerBase,//塔基；
    en_IsRotation,  //取消；
    en_CreateCost  //创建成本；
};
//枚举受伤属性；
enum CsvVictimProperty
{
    en_Hp = 6,//基础生命值；
    en_Speed,//速度；
    en_Atk,//攻击力；
};
//枚举子弹属性；
enum CsvBulletProperty
{
    en_AtkState = 6,//攻击类型；
    en_Duration = 9,//持续时间；
    en_BulletType,//子弹类型；
    en_DeadActCount//死亡动画数；
};
//枚举boss属性；
enum CsvBossProperty
{
    en_BossName = 1,
    en_BossModelName,
    en_BossValue,
    en_BossAnimationCount,
    en_BossLevel,
    en_BossHp,
    en_BossSpeed,
    en_BossAtk,
    en_BossTime
};

/**
 * @breif 用户数据枚举
 * @details 什么通关总数的统计之类的
 * @author 陈建彰
 */
enum StatisticType
{
    en_Stat_Adventure,
    en_Stat_Cryptic,
    en_Stat_BossMode,
    en_Stat_Money,
    en_Stat_BossAttack,
    en_Stat_MonsterAttack,
    en_Stat_BarrierClear
};

/**
* @brief 攻击类型；
*/
enum AtkState
{
    en_Normal = 1,
    en_Slow = en_Normal << 1,
    en_Stop = en_Normal << 2,
    en_Poison = en_Normal << 3,//毒；
    en_Slow_And_Shrink = en_Normal << 4 //缩小并减速
};
//攻击属性；
class AtkProperty
{
public:
    int _enAtkState = 0;
    int _iDuration = 0;
    int _iAtk = 0;
    int _iBulletsType = 0;
};

//SceneType
enum SceneType
{
    en_WelcomeScene,//欢迎场景；
    en_GameSettingScene,//游戏设置场景；
    en_GameHelpScene,//游戏帮助场景；
    en_ThemeSelectScene,//主题选择场景；
    en_LevelSelectScene,//关卡选择场景；
    en_GameScene,//游戏场景；
    en_BossModeScene//boss模式场景；
};

//塔类
enum TowerType
{
    en_StarTower,//星星
    en_FanTower,//风扇
    en_GreenTower,//绿色瓶
    en_ShitTower,//粑粑
    en_BallTower,//电球
    en_FireBottleTower,//汽油瓶
    en_BlueStarTower,//蓝星星
    en_SunTower,//太阳
    en_PinTower,//毒针
    en_RocketTower,//火箭
    en_SnowTower,//雪花
    en_PlaneTower,//飞机
    en_AnchorTower,//锚
	en_MushroomTower,//蘑菇
	en_FishTower,//鱼骨头
	en_CuttleTower//大章鱼
};

//怪物类型
enum MonsterType
{
    en_Land_Pink = 1,
    en_Land_Star,
    en_Land_Nima,
    en_Fly_Yellow,
    en_Fly_Blue,
    en_Fat_Green,
    en_Land_Boss_Pink,
    en_Land_Boss_Star,
    en_Land_Boss_Nima,
    en_Fly_Boss_Yellow,
    en_Fly_Boss_Blue,
    en_Fat_Boss_Green,
    en_Big_Oldboss,
    en_Fat_Oldboss,
    en_Fly_Oldboss,
    en_Land_Oldboss,
    en_Boss_Big,
    en_Boss_Woowala = 19, //bug fixed 序号少了
    en_Boss_PinkyNinja,
    en_Boss_TwistyFork,
    en_Boss_FlyDevils,
    en_Boss_Cyclops,
    en_Boss_Popbowling,
    en_Boss_Gremlins,
    en_Boss_Sadgeezer,
    en_Boss_FireFeet,
    en_Boss_Unicorn,
    en_Boss_DarkAngle,
    en_Boss_FatMummy,
    en_Boss_ConchKing,
    en_Boss_Hotstar,
    en_Boss_DrOctopus,
    en_Boss_HugeChela
};

//子弹类型
enum BulletType
{
    en_NormalBullet = 1,//普通子弹
    en_NoDisspper,//无限旋转类子弹
    en_GunBullet,//枪类子弹
    en_StarBullet//星星类子弹
};

/**
* @brief 障碍物类型
* @details 后面主题的障碍物直接用这四个名字
*/
enum BarrierType
{
    en_CloudType,
    en_BalloonType,
    en_StoneType,
    en_TreeType
};

enum GameEndType
{
    en_GameWin,//赢
    en_GameLose//输
};

enum GameType
{
    en_Adventure, //冒险模式
    en_BossMode //Boss模式
};

//关卡状态
#define LEVEL_LOCK 0
#define LEVEL_UNLOCK_BUT_NO_PASS 1
#define LEVEL_STAR1 2
#define LEVEL_STAR2 3
#define LEVEL_STAR3 4

//关卡障碍物状态
#define BARRIERS_ALL_CLEARED 1
#define BARRIERS_NOT_ALL_CLEAR 0

#endif 
