//
//  HpSlot.h
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-12.
//
//
#pragma once
#ifndef __CarrotFantasy__HpSlot__
#define __CarrotFantasy__HpSlot__

#include "CommonDefine.h"
class VictimEntityBase;

class HpSlot : public Node
{
public:

	virtual ~HpSlot();

	static HpSlot *create(VictimEntityBase *pVictimEntity);
	/**
	* @brief 设置生命值
	* @param rIHp 基础生命值
	*/
	virtual void setHp(const int &rIHp);
	/**
	* @brief 获取当前图的大小
	*/
	virtual const Size &getContentSize()const;


protected:
	/**
	* @brief 炼丹术,玄学设参
	*/
	virtual bool init(VictimEntityBase *pVictimEntity);

private:
	//实体指针;
	VictimEntityBase *_pVictimEntity = nullptr;

public:
	//生命值槽指针;
	ProgressTimer *_pHpSlot = nullptr;

	int _iHpMax = 0;
};

#endif /* defined(__CarrotFantasy__HpSlot__) */