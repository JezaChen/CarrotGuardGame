/**
 * @breif 怪兽帮助图层
 * @details 帮助场景中的怪兽页面
 * @author 陈建彰
 * @date 20180410
 * */

#ifndef MONSTERHELPLAYER_H
#define MONSTERHELPLAYER_H

#include "CommonDefine.h"

class MonsterHelpLayer : public Layer
{
public:
    CREATE_FUNC(MonsterHelpLayer);
protected:
    bool init() override;
    void createMonsterHelpLayer();
};

#endif //MONSTERHELPLAYER_H
