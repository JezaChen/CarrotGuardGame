/**
 * @brief 实体基类
 * @details 游戏场景中一切活动物品的公共父类
 * @todo  CC_SYNTHESIZE_PASS_BY_REF 变量和变量的设置和获取函数命名规则没有统一，需要后期修补
 * @authors 何泓兵 x 陈建彰
 * @date 20180406
 * */
#pragma once
#ifndef __newCardDefence__Entity__
#define __newCardDefence__Entity__

#include "CommonDefine.h"
#include "cocos2d.h"

class Entity : public Node
{
public:
    /**
    *@brief 析构函数
    *@author 何泓兵
    **/
    virtual ~Entity();

public:
    static unsigned long ID;

    /**
    * @获取mID；
    * @brief mID为隐式查看实体初始化是否成功；
    */
    unsigned int getmID();

    /**
     * @brief 初始化函数
     * @details 读取CSV表格文件对应的行，初始化该对象
     * @param rId 该实体的id，其实就是表格对应的行
     * @param rSCsvFileName 该实体所处的表格文件
     * @see 实体有挺多种，同个id的实体不一定是同种类型的
     * @return true 设置成功，否则设置失败；
     */
    virtual bool init(const int &rId, const std::string &rSCsvFileName);

    /**
     * @brief 获取该精灵范围大小；
     */
    virtual const Size &getContentSize() const;

    /**
     *@brief 实体已经死亡后需要执行的函数
     */
    virtual void doDead() final;

    /**
     *
     *  @brief 每个实体需要绑定一个Sprite，用于显示；
     *  @param pSprite 待绑定的精灵；
     */
    virtual void bindSprite(Sprite *pSprite);

    /**
     * @brief 获取绑定精灵；
     */
    virtual Sprite *getSprite();

    /**
     *  @brief 获取精灵的大小
     *  @see 精灵大小设置完毕
     *  @return Rect 重置的矩形
     */
    Rect getBoundingBox() const override;

protected:
    /**
     *  @brief 死亡动画；
     *  @param rSDeadImageFile 死亡动画图片文件字符串，若采用默认参数，意味着使用默认的死亡动画
     *  @details 记住，这个函数一定要自下而上调用
     */
    virtual void deadAction(const std::string &rSDeadImageFile = "");

    /**
     * @brief 初始化实体的属性
     * @details
     * @param rId 实体对应的Id号，就是表格文件的行
     * @param rSCsvFileName csv文件名
     * @return: 空
     */
    virtual void initProperty(const int &rId, const std::string &rSCsvFileName);
    /**
    *  @brief 实体 id
    */
CC_SYNTHESIZE_PASS_BY_REF(int, _iId, IId);
    /**
    *  @brief 实体名
    */
CC_SYNTHESIZE_PASS_BY_REF(std::string, _sName, SName);
    /**
    *  @brief 实体绑定精灵模型图像文件名称
    */
CC_SYNTHESIZE_PASS_BY_REF(std::string, _sModelName, SModelName);
    /**
    *  Entity values
    */
CC_SYNTHESIZE_PASS_BY_REF(int, _iValue, IValue);
    /**
    *  flag Entity is dead
    */
CC_SYNTHESIZE_PASS_BY_REF(bool, _bIsDead, IsDead);
    /**
    *  @brief 动画帧数
    */
CC_SYNTHESIZE_PASS_BY_REF(int, _IAnimationFrameCount, AnimationFrameCount);
    /**
    *  Entity 等级
    */
CC_SYNTHESIZE_PASS_BY_REF(int, _iLevel, ILevel);
private:
    /**
    *  @brief 图片精灵，使用绑定精灵并获得精灵
    */
    Sprite *_pSprite = nullptr;

    unsigned long _myID;

};

#endif /* defined(__newCardDefence__Entity__) */
