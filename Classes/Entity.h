//
//  Entity.h
//  newCardDefence
//
//  Created by 何泓兵 on 18-4-6
//  CC_SYNTHESIZE_PASS_BY_REF 变量和变量的设置和获取函数命名规则没有统一，需要后期修补
//
#pragma once
#ifndef __newCardDefence__Entity__
#define __newCardDefence__Entity__

#include "CommonDefine.h"
#include "cocos2d.h"

class Entity :public Node
{
public:
	/**
	*@析构函数
	*@author 何泓兵
	**/
	virtual ~Entity();

public:
	static unsigned long ID;
	/**
	* @获取mID；
	* @brief mID为隐式查看init实体是否设置成功；
	*/
	unsigned int getmID();
	/*
	* @brief 设置init实体属性并检验是否设置成功；
	* @return true 设置成功，否则设置失败；
	*/
	virtual bool init(const int &rId, const std::string &rSCsvFileName);
	/**
	* @brief 获取原图大小；
	*/
	virtual const Size &getContentSize()const;
	/**
	*@brief 实体已经死亡后需要执行的函数
	*/
	virtual void doDead()final;


	/**
	*  
	*  @brief 每个实体需要绑定一个Sprite，用于显示；
	*  @param pSprite 是一个绑定精灵；
	*/
	virtual void bindSprite(Sprite *pSprite);
	/**
	* @brief 获取绑定精灵；
	*/
	virtual Sprite *getSprite();

	/**
	*  @brief 获取精灵的大小和源
	*  @see 精灵大小设置完毕
	*  @return Rect 重置的矩形
	*/
	virtual Rect getBoundingBox()const;

protected:
	/**
	*  @brief 死亡动画；
	*  @param rSDeadImageFile 死亡动画图片文件字符串；
	*/
	virtual void deadAction(const std::string &rSDeadImageFile = "");

	/*
	* @brief init实体属性
	* @param rId
	* @param rSCsvFileName csv文件名
	* @return: 空
	*/
	virtual void initProperty(const int &rId, const std::string &rSCsvFileName);
	/*
	*  @brief 实体 id
	*/
	CC_SYNTHESIZE_PASS_BY_REF(int, _iId, IId);
	/*
	*  @brief 实体名
	*/
	CC_SYNTHESIZE_PASS_BY_REF(std::string, _sName, SName);
	/*
	*  @brief 实体绑定精灵模型图像文件名称
	*/
	CC_SYNTHESIZE_PASS_BY_REF(std::string, _sModelName, SModelName);
	/*
	*  Entity values
	*/
	CC_SYNTHESIZE_PASS_BY_REF(int, _iValue, IValue);
	/*
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
