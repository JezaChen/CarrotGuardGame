
<<<<<<< HEAD
#ifndef CONFIG_H
#define CONFIG_H

#include "CommonDefine.h"

USING_NS_CC;
=======
//
//  Config.h
//  newCardDefence
//
//  Created by ºÎãü±ø on 18-3-30.
//
//
#pragma once
#ifndef __newCardDefence__Config__
#define __newCardDefence__Config__

#include "PublicDefine.h"
>>>>>>> 83fcb44c70512683539c4a6290760aa6326fb959

class SoundUtil;

class Config :public Ref
{
public:

<<<<<<< HEAD
    CREATE_INSTANCE_FUNC(Config);

    DESTROY_INSTANCE_FUNC();
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

#endif //CONFIG_H
=======
	CREATE_INSTANCE_FUNC(Config);

	DESTROY_INSTANCE_FUNC();
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

#endif /* defined(__newCardDefence__Config__) */
>>>>>>> 83fcb44c70512683539c4a6290760aa6326fb959
