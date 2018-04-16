//
// Created by jeza on 18-4-15.
//

#ifndef BARRIERBUILDER_H
#define BARRIERBUILDER_H

#include "CommonDefine.h"

class BarrierBuilder : public Node
{
public:
    CREATE_FUNC(BarrierBuilder);

protected:
    bool init() override;

    void onEnter() override;

    void createBarriers();
};

#endif //BARRIERBUILDER_H
