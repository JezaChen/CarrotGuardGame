//
//  BM_GameEndLayer.h
//  CarrotFantasy
//
//  Created by ºÎãü±ø on 18-4-16.
//
//
#pragma once
#ifndef __CarrotFantasy__BM_GameEndLayer__
#define __CarrotFantasy__BM_GameEndLayer__

#include "CommonDefine.h"

class BM_GameEndLayer : public Layer
{

public:

    static BM_GameEndLayer *create(const GameEndType &rEnGameEndType);

protected:

    virtual bool init(const GameEndType &rEnGameEndType);

    virtual void createMenu();

    virtual void loadInfo();

    void onEnter()override;

    void onExit()override;

    virtual void registerNoTouch();

    virtual void saveLevelData();

    virtual void playGameEndSound();

    virtual void checkCarrotType();

private:

    GameEndType _enGameEndType = en_GameWin;

    int _iCarrotType = 0;

    std::string _sCarrotType = "";

};

#endif /* defined(__CarrotFantasy__BM_GameEndLayer__) */
