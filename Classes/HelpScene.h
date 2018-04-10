/**
 * @brief 帮助场景
 * @author 陈建彰
 * @date 20180410
 * */
#ifndef HELPSCENE_H
#define HELPSCENE_H

#include "CommonDefine.h"

class HelpScene : public Scene
{
public:
    CREATE_FUNC(HelpScene);

    ~HelpScene() override;

protected:
    bool init() override;

    void onEnter() override;

private:
    Layer *_pMenuPanelLayer = nullptr;
};

#endif //HELPSCENE_H
