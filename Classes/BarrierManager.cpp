//
//  BarrierManager.cpp
//  CarrotFantasy
//
//  Created by 何泓兵 on 18-4-7.
//  存在不懂问题
//

#include "BarrierManager.h"
#include "BarrierBase.h"
#include "SceneManager.h"

BarrierManager *BarrierManager::_gInstance;

BarrierManager::BarrierManager()
{}

BarrierManager::~BarrierManager()
{
    CC_SAFE_DELETE(_pBarrierVec);
}


bool BarrierManager::init()
{
    bool bRet = false;

    do
    {
        _pBarrierVec = new Vector<BarrierBase *>(); //new一个向量
        registerBarrierDeadEvent(); //注册事件

        bRet = true;
    } while (0);

    return bRet;
}

Vector<BarrierBase *> &BarrierManager::getBarrierVec()
{
    return *_pBarrierVec;
}

void BarrierManager::addBarrier(BarrierBase *pBarrier)
{
    //注册障碍物流程
    if (_pBarrierVec) _pBarrierVec->pushBack(pBarrier); //塞进向量
    _funcAddBarrierToLayer(pBarrier); //塞进图层
}

void BarrierManager::setFuncAddBarrierToLayer(const std::function<void(Entity *)> &rFuncAddBarrierToLayer)
{
    _funcAddBarrierToLayer = rFuncAddBarrierToLayer;
}

void BarrierManager::registerBarrierDeadEvent()
{
    //注册障碍物被清理之后的处理函数，用本类的removeBarrierFromManager方法来处理
    NOTIFY->addObserver(this, callfuncO_selector(BarrierManager::removeBarrierFromManager), "BarrierDead", nullptr);
}


void BarrierManager::removeBarrierFromManager(Ref *pBarrier)
{
    //障碍物清理流程

    if (!(_pBarrierVec && _pBarrierVec->size())) return;
    _pBarrierVec->eraseObject(reinterpret_cast<BarrierBase *>(pBarrier)); //向量中找到并删除

    //如果障碍物全部被清理了
    //得修改一下通关数据
    if (!_pBarrierVec->size())
    {
        //构造通知信息
        auto aThemeIndex = SceneManager::getInstance()->getCurrentPageIndex() + 1;
        auto aLevelIndex = SceneManager::getInstance()->getCurrentLevelIndex() + 1;
        auto aLevelData = std::make_tuple(1, 1, aThemeIndex, aLevelIndex);
        //把信息广播出去
        NOTIFY->postNotification(LEVELDATACHANGE, reinterpret_cast<Ref *>(&aLevelData));
    }
}

void BarrierManager::clearManager()
{
    _pBarrierVec->clear();
}

void BarrierManager::clearBeAtkLockState()
{
    //清除标记
    for (auto &iterBarrier : *_pBarrierVec)
        iterBarrier->setAtkTarget(false);
}
