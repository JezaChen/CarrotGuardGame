//
// Created by jeza on 18-4-9.
//

#include "LocalLevelDataUtil.h"

LocalLevelDataUtil *LocalLevelDataUtil::_gInstance;

bool LocalLevelDataUtil::init()
{
    bool bRet = false;
    do
    {
        auto pFileUtil = FileUtils::getInstance();
        _sLevelDataFilePath = pFileUtil->getWritablePath() + DATAFILE;
        _levelData = pFileUtil->getValueMapFromFile(_sLevelDataFilePath);

        registerLevelDataChangesEvent();
        bRet = true;
    } while (0);

    return  bRet;
}

LocalLevelDataUtil::~LocalLevelDataUtil()
{
    NOTIFICATION_CENTER->removeAllObservers(this); //释放所有的监听器
}

ValueMap &LocalLevelDataUtil::getLevelData()
{
    return _levelData;
}

void LocalLevelDataUtil::setLevelData(const ValueMap &rValueMap)
{
    _levelData = rValueMap;
}

void LocalLevelDataUtil::registerLevelDataChangesEvent()
{
    NOTIFICATION_CENTER->addObserver(this, callfuncO_selector(LocalLevelDataUtil::levelDataChange), LEVELDATACHANGE,
        nullptr);
}


void LocalLevelDataUtil::levelDataChange(Ref *pData)
{
    auto aLevelData = *(reinterpret_cast<std::tuple<int, int, int, int> *>(pData)); //先转型
                                                                                    //根据事先约定
                                                                                    //第一个int是关卡当前状态，0是锁住，1表示解锁但没通过,2~4表示已经通过且表示通关的成绩，决定萝卜下面的星数
                                                                                    //第二个int是该关卡是否已经把所有的障碍物清除掉了，0表示没有全部清除掉，1表示全部清楚点
                                                                                    //第三个int是该关卡对应的主题索引
                                                                                    //第四个int是该关卡在对应的主题下对应的索引
    int iLevelType = std::get<0>(aLevelData); //关卡当前状态
    int iLevelBarriersCleared = std::get<1>(aLevelData); //障碍物是否被清楚干净了
    int iThemeIndex = std::get<2>(aLevelData); //主题号
    int iLevelIndex = std::get<3>(aLevelData); //关卡号

                                               //生成key值
    auto aLevelKey = StringUtils::format(LEVELKEY, iThemeIndex, iLevelIndex);
    int iCurrentLevelData = (_levelData[aLevelKey]).asInt();


    int iCurrentLevelType = iCurrentLevelData / 10;
    int iCurrentLevelBarriersCleared = iCurrentLevelData % 10;

    if (iLevelType == LEVEL_LOCK)
    {
        //TODO ???
        _levelData[aLevelKey] = StringUtils::format("%d%d", iLevelType, 0);
    }
    else
    {
        //若当前关卡无论是萝卜星数还是障碍物全部清理情况都有所进步
        if (iLevelType > iCurrentLevelType && iLevelBarriersCleared > iCurrentLevelBarriersCleared)
            _levelData[aLevelKey] = StringUtils::format("%d%d", iLevelType, iLevelBarriersCleared); //全部更新一遍

        else if (iLevelType > iCurrentLevelType) //若只有萝卜星数有所提升
            _levelData[aLevelKey] = StringUtils::format("%d%d", iLevelType, iCurrentLevelBarriersCleared); //只更新星数

        else if (iLevelBarriersCleared > iCurrentLevelBarriersCleared) //若只有障碍物全部清理情况有所进步
            _levelData[aLevelKey] = StringUtils::format("%d%d", iCurrentLevelType, iLevelBarriersCleared); //更新障碍物清理情况
    }
    FileUtils::getInstance()->writeToFile(_levelData, _sLevelDataFilePath); //重新写入文件
}

