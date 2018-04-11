/**
 * @brief 游戏设置场景
 * @author 陈建彰
 * @date 20180411
 * */

#ifndef SETTINGSCENE_H
#define SETTINGSCENE_H

#include "CommonDefine.h"

class GameSettingScene : public Scene
{
public:
    CREATE_FUNC(GameSettingScene);

    ~GameSettingScene() override;

protected:
    bool init() override;

    void onEnter() override;

private:
    Layer *_pPanelLayer = nullptr;
};

#endif //SETTINGSCENE_H
