#pragma once
#ifndef CONFIG_H
#define CONFIG_H

#include "CommonDefine.h"

//
//  Config.h
//  newCardDefence
//
//  Created by 何泓兵 on 18-3-30.
//
//


#include "CommonDefine.h"

class SoundUtil;

class Config :public Ref
{
public:

    CREATE_INSTANCE_FUNCTION(Config);

    DESTROY_INSTANCE_FUNCTION();
    /**
    *  flag source be loading
    */
    CC_SYNTHESIZE_PASS_BY_REF(bool, _bIsLoadSource, IsLoadSource);

    virtual void saveSoundConfig();

    virtual void setSoundConfig();

protected:

    virtual bool init();

    virtual void checkBuildLevelData();

    virtual void createLevelDataFile();
private:

    std::string _sConfigFileName = "";

    std::string _sLevelDataFileName = "";

    ValueMap _configValueMap;

private:

    Config();

    virtual ~Config();

    Config &operator=(const Config &) = delete;

    Config(const Config &) = delete;
};

#endif
