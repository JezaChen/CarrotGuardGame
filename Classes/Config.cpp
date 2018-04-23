//
//  Config.cpp
//  newCardDefence
//
//  Created by 何泓兵 on 18-3-30.
//  ==
//todo 好像没有办法实时更新 


#include "Config.h"
#include "SoundUtil.h"


Config* Config::_gInstance;

Config::~Config()
{
}

Config::Config()
{
}

bool Config::init()
{
    bool bRet = false;
    do
    {
		//获取文件可写路径；
        _sConfigFileName = FileUtils::getInstance()->getWritablePath() + CONFIGFILE;

        _configValueMap = FileUtils::getInstance()->getValueMapFromFile(_sConfigFileName);

        _bIsLoadSource = false;
		//检查关卡数据是否加载完成
        checkBuildLevelData();

        bRet = true;
    }
    while (0);

    return bRet;
}

void Config::checkBuildLevelData()
{
    auto tRet = _configValueMap[BUILDLEVELDATAKEY].asString();
    auto tIsBuildLevelData = 0;
    if (tRet.size()) tIsBuildLevelData = _configValueMap[BUILDLEVELDATAKEY].asInt(); //bug fixed 不能是与
    if (!tRet.size() || !tIsBuildLevelData)
    {
        log("123");
        _configValueMap[BUILDLEVELDATAKEY] = "1";
        FileUtils::getInstance()->writeToFile(_configValueMap, _sConfigFileName);
        createLevelDataFile();
    }
}

void Config::createLevelDataFile()
{
    auto tLevelDataFileName = FileUtils::getInstance()->getWritablePath() + DATAFILE;

    auto pCsvUtil = CsvUtil::getInstance();
    auto tColumnRow = pCsvUtil->getFileRowColNum(LEVELCSVFILE);

    auto tColumn = std::get<1>(tColumnRow); //bug fixed
    auto tRow = std::get<0>(tColumnRow); //bug fixed
    auto tValue = FileUtils::getInstance()->getValueMapFromFile(tLevelDataFileName);

    for (int i = 1; i < tRow; ++i)
    {
        auto tThemeIndex = pCsvUtil->getInt(i, 0, LEVELCSVFILE);
        auto tLevelIndex = pCsvUtil->getInt(i, 1, LEVELCSVFILE);
        auto tCarrotType = pCsvUtil->getInt(i, tColumn - 2, LEVELCSVFILE);
        auto tBarrierClean = pCsvUtil->getInt(i, tColumn - 1, LEVELCSVFILE);

        tValue[StringUtils::format("%d_%02d", tThemeIndex, tLevelIndex)] = StringUtils::format(
            "%d%d", tCarrotType, tBarrierClean);
    }

    /***********************************************/
    /*******************游戏数据*********************/
    /***********************************************/
   
    /*
    //冒险模式通关数
    tValue[DATA_ADVENTURE_MAP_CLEARANCE] = "0";
    //隐藏关卡通关数
    tValue[DATA_CRYPTIC_MAP_CLEARANCE] = "0";
    //BOSS模式通关数
    tValue[DATA_BOSS_MAP_CLEARANCE] = "0";
    //金钱总数
    tValue[DATA_TOTAL_MONEY] = "0";
    //BOSS打死数
    tValue[DATA_TOTAL_BOSS_ATTACK] = "0";
    //怪物打死数
    tValue[DATA_TOTAL_MONSTER_ATTACK] = "0";
    //障碍物消除数
    tValue[DATA_TOTAL_BARRIER_CLEARANCE] = "0";
    */

    for (int i = 0; i < USER_STATISTICS.size(); i++)
    {
        tValue[USER_STATISTICS.at(i)] = "0";
    }
    /************************************************/
    /*************这时候，数据初始化成功啦**************/
    /************************************************/

    FileUtils::getInstance()->writeToFile(tValue, tLevelDataFileName);
    saveSoundConfig();
}

void Config::saveSoundConfig()
{
    auto tBackGroundSoundFlag = SoundUtil::getInstance()->getIsBackgroundSoundOpen() ? 1 : 0;
    _configValueMap[CONFIGBACKGROUND] = tBackGroundSoundFlag;

    auto tEffectSoundFlag = SoundUtil::getInstance()->getIsEffectSoundOpen() ? 1 : 0;
    _configValueMap[CONFIGEFFECTSOUND] = tEffectSoundFlag;
    FileUtils::getInstance()->writeToFile(_configValueMap, _sConfigFileName);
}

void Config::setSoundConfig()
{
    SoundUtil::getInstance()->setIsBackgroundSoundOpen(_configValueMap[CONFIGBACKGROUND].asBool());
    SoundUtil::getInstance()->setIsEffectSoundOpen(_configValueMap[CONFIGEFFECTSOUND].asBool());
}
