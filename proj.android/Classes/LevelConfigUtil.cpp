//
// Created by jeza on 18-4-12.
//

#include "LevelConfigUtil.h"
#include "../cocos2d/external/tinyxml2/tinyxml2.h"
#include "SceneManager.h"

using namespace tinyxml2;

LevelConfigUtil* LevelConfigUtil::_gInstance;

bool LevelConfigUtil::init()
{
    bool bRet = false;
    do
    {
        _pEffectTowers = new std::vector<std::string>(); //bug fixed 要事先new一个出来呀
        loadLevelConfig();
        bRet = true;
    } while (0);
    return bRet;
}

void LevelConfigUtil::loadLevelConfig()
{
    _pEffectTowers->clear(); //清空一下
    tinyxml2::XMLDocument tXmlDoc; //新建一个XMLDocument文档
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    //tinyxml2::XMLError pError; //?...
    std::string sLevelConfigFilePath = LEVELCONFIGFILENAME;
    //ssize_t *temp = 0; //TODO
    unsigned char* pBuffer = nullptr;
    auto pData = FileUtils::getInstance()->getDataFromFile(sLevelConfigFilePath);
    pBuffer = pData.getBytes();
    if(pBuffer)
    {
        tXmlDoc.Parse(static_cast<const char*>pBuffer);
    }
    else
    {
        CCLOG("[%d]%s %s error", __LINE__, __func__, __FILE__);
    }

#else
    auto sLevelConfigFilePath = FileUtils::getInstance()->fullPathForFilename(LEVELCONFIGFILENAME);
    auto aIndex = sLevelConfigFilePath.find(LEVELCONFIGFILENAME);
    sLevelConfigFilePath = sLevelConfigFilePath.substr(0, aIndex);
    auto aFile = LEVELCONFIGFILENAME;
    sLevelConfigFilePath = sLevelConfigFilePath + aFile;
    CCLOG("[2]config %s  %s %s", LEVELCONFIGFILENAME.c_str(), sLevelConfigFilePath.c_str(),
          ((std::string) aFile).c_str());
#endif

    //开始用DOM方式读取文件
    tXmlDoc.LoadFile(sLevelConfigFilePath.c_str());

    auto aRoot = tXmlDoc.RootElement(); //获取根节点对象
    auto aSceneManager = SceneManager::getInstance();
    auto aLevelElement = aRoot->FirstChildElement(
            StringUtils::format("%d_%02d", aSceneManager->getCurrentPageIndex() + 1,
                                aSceneManager->getCurrentLevelIndex() + 1).c_str()); //在根节点对象中找到关卡对应的孩子
    auto aElement = aLevelElement->FirstChildElement(); //逐个获取属性
    while (aElement)
    {
        if (aElement->Name() == LEVELCONFIGTYPE[0]) //ThemeIndex
            _iCurThemeIndex = aElement->IntAttribute(LEVELCONFIGTYPE[0].c_str());
        else if (aElement->Name() == LEVELCONFIGTYPE[1]) //Level
            _iCurLevelIndex = aElement->IntAttribute(LEVELCONFIGTYPE[1].c_str());
        else if (aElement->Name() == LEVELCONFIGTYPE[2]) //Money
            _iCurLevelInitialMoney = aElement->IntAttribute(LEVELCONFIGTYPE[2].c_str());
        else if (aElement->Name() == LEVELCONFIGTYPE[3]) //MonsterBatch
            _iMonsterBatchCount = aElement->IntAttribute(LEVELCONFIGTYPE[3].c_str());

        if (aElement->Name() == TOWERTYPE)
        {
            auto aTower = aElement->FirstChildElement();
            while (aTower)
            {
                _pEffectTowers->push_back(aTower->Name());
                aTower = aTower->NextSiblingElement();
            }
        }
        aElement = aElement->NextSiblingElement();
    }
}

std::tuple<int, int, int, std::vector<std::string>> LevelConfigUtil::getLevelConfig() const
{
    return std::make_tuple(_iCurThemeIndex, _iCurLevelIndex, _iMonsterBatchCount, *_pEffectTowers);
}

std::vector<std::string> LevelConfigUtil::getCurrentTowersInfo() const
{
    return *_pEffectTowers;
}

int LevelConfigUtil::getCurrentMonsterBatchCount() const
{
    return _iMonsterBatchCount;
}

int LevelConfigUtil::getCurrentLevelInitialMoney() const
{
    return _iCurLevelInitialMoney;
}




