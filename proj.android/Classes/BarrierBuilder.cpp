//
// Created by jeza on 18-4-15.
//

#include "BarrierBuilder.h"
#include "MapUtil.h"
#include "BarrierBase.h"

bool BarrierBuilder::init()
{
    bool bRet = false;
    do
    {
        createBarriers();
        bRet = true;
    } while (0);
    return bRet;
}

void BarrierBuilder::onEnter()
{
    Node::onEnter();
}

void BarrierBuilder::createBarriers()
{
    //获取障碍物位置
    auto barriersPoses = MapUtil::getInstance()->getBarrierPoses();
    CsvUtil *pCsvUtil = CsvUtil::getInstance();
    for (auto &iter : barriersPoses)
    {
        int iBarrierLine = pCsvUtil->findVal(iter.first, 1, BARRIERCSVFILE);
        Vec2 vPos = iter.second.origin; //获取坐标
        Size sSize = iter.second.size; //获取块大小
        auto aBarrier = BarrierBase::create(iBarrierLine);
        //障碍物锚点在中间
        aBarrier->setPosition(Vec2(vPos.x + sSize.width / 2, vPos.y + sSize.height / 2));
    }
}
