/**
 * @brief 小关卡选择场景
 * @author 陈建彰
 * */

#ifndef LEVELSELECTSCENE_H
#define LEVELSELECTSCENE_H

#include "SceneBase.h"

class LevelSelectScene : public SceneBase
{
public:
    CREATE_FUNC(LevelSelectScene);

    ~LevelSelectScene() override;

protected:

    bool init() override;

    void onEnter() override;

private:
    int _iThemeIndex = 0;
    Layer *_pLevelSelectLayer = nullptr;
};

#endif //LEVELSELECTSCENE_H
