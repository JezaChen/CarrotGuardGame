//
//  SceneBase.h
//  CarrotFantasy
//
//  Created by ºÎãü±ø on 18-3-30.
//
//
#pragma once
#ifndef __CarrotFantasy__SceneBase__
#define __CarrotFantasy__SceneBase__

#include "CommonDefine.h"

class SceneBase : public Scene
{

protected:

	virtual void sourceManager(const std::vector<std::string> &rSourceNameVec, const bool &rBLoad);

};

#endif /* defined(__CarrotFantasy__SceneBase__) */