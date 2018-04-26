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
    NOTIFICATION_CENTER->addObserver(this, callfuncO_selector(LocalLevelDataUtil::statDataChange), STATDATACHANGE,
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

        //bug fixed BOSS模式的解锁逻辑在这里实现

        if (iLevelIndex == 8 && iCurrentLevelType == LEVEL_UNLOCK_BUT_NO_PASS) //如果原第十二关被锁住了而现在被解锁了
        {
            //激活BOSS模式关卡
            for(int i = 13; i <= 16; i++)
            {

                auto tmpLevelKey = StringUtils::format(LEVELKEY, iThemeIndex, i);
                _levelData[tmpLevelKey] = "10";
            }
        }
    }
    FileUtils::getInstance()->writeToFile(_levelData, _sLevelDataFilePath); //重新写入文件
}

void LocalLevelDataUtil::statDataChange(Ref *pData)
{
    auto aData = *(reinterpret_cast<std::vector<std::tuple<StatisticType, int>> *>(pData)); //先转型
                                                                                    //根据约定，第一个是数据表项类型，第二个是增加的Value值
    for(auto datum : aData)
    {
        StatisticType type = std::get<0>(datum);
        int value = std::get<1>(datum);

        std::string key = USER_STATISTICS[type];

        if(type == en_Stat_Adventure && value == 1)
        {
            int res = 0;
            //todo 目前只有开三个主题
            for (int theme = 1; theme <= 3; theme++)
            {
                for (int level = 1; level <= 8; level++)
                {
                    auto aLevelKey = StringUtils::format(LEVELKEY, theme, level);

                    int iCurrentLevelData = (_levelData[aLevelKey]).asInt();
                    int iCurrentLevelType = iCurrentLevelData / 10;

                    if (iCurrentLevelType > 1)
                        res++;
                    else
                        break;
                }
                _levelData[key] = res;
            }
        }
        else if (type == en_Stat_BossMode && value == 1)
        {
            int res = 0;
            //todo 目前只有开三个主题
            for (int theme = 1; theme <= 3; theme++)
            {
                for (int level = 13; level <= 16; level++)
                {
                    auto aLevelKey = StringUtils::format(LEVELKEY, theme, level);

                    int iCurrentLevelData = (_levelData[aLevelKey]).asInt();
                    int iCurrentLevelType = iCurrentLevelData / 10;

                    if (iCurrentLevelType > 1)
                        res++;
                    else
                        break;
                }
                _levelData[key] = res;
            }
        }
        else if (type == en_Stat_Cryptic && value == 1)
        {
            int res = 0;
            //todo 目前只有开三个主题
            for (int theme = 1; theme <= 3; theme++)
            {
                for (int level = 9; level <= 12; level++)
                {
                    auto aLevelKey = StringUtils::format(LEVELKEY, theme, level);

                    int iCurrentLevelData = (_levelData[aLevelKey]).asInt();
                    int iCurrentLevelType = iCurrentLevelData / 10;

                    if (iCurrentLevelType > 1)
                        res++;
                    else
                        break;
                }
                _levelData[key] = res;
            }
        }
        else
        {
            int oldVal = _levelData[key].asInt();
            int newVal = oldVal + value;
            _levelData[key] = newVal;
        }
    }

    //重新写回去
    FileUtils::getInstance()->writeToFile(_levelData, _sLevelDataFilePath);
}

