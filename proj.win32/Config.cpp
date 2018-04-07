//
//  Config.cpp
//  newCardDefence
//
//  Created by ºÎãü±ø on 18-3-30.
//  ==
//

#include "Config.h"
#include "SoundUtil.h"


Config *Config::_gInstance;

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
		_sConfigFileName = FileUtils::getInstance()->getWritablePath() + CONFIGFILE;

		_configValueMap = FileUtils::getInstance()->getValueMapFromFile(_sConfigFileName);

		_bIsLoadSource = false;

		checkBuildLevelData();

		bRet = true;
	} while (0);

	return bRet;
}

void Config::checkBuildLevelData()
{
	auto tRet = _configValueMap[BUILDLEVELDATAKEY].asString();
	auto tIsBuildLevelData = 0;
	if (tRet.size()) tIsBuildLevelData = _configValueMap[BUILDLEVELDATAKEY].asInt();
	if (!tRet.size() && !tIsBuildLevelData)
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

	auto tColumn = std::get<0>(tColumnRow);
	auto tRow = std::get<1>(tColumnRow);
	auto tValue = FileUtils::getInstance()->getValueMapFromFile(tLevelDataFileName);

	for (int i = 1; i < tRow; ++i)
	{
		auto tThemeIndex = pCsvUtil->getInt(i, 0, LEVELCSVFILE);
		auto tLevelIndex = pCsvUtil->getInt(i, 1, LEVELCSVFILE);
		auto tCarrotType = pCsvUtil->getInt(i, tColumn - 2, LEVELCSVFILE);
		auto tBarrierClean = pCsvUtil->getInt(i, tColumn - 1, LEVELCSVFILE);

		tValue[StringUtils::format("%d_%02d", tThemeIndex, tLevelIndex)] = StringUtils::format("%d%d", tCarrotType, tBarrierClean);
	}

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





