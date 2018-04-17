/** @Copyright   保卫萝卜
*   @author      陈建彰
*   @date        2018/3/30 
*   @brief       加载资源layer
*/
#ifndef LOADING_SOURCE_LAYER_H
#define LOADING_SOURCE_LAYER_H


#include "CommonDefine.h"

class LoadingSourceLayer : public Layer
{
public:
    CREATE_FUNC(LoadingSourceLayer);

    virtual void setFuncShowMenuPanel(const std::function<void()> &rFuncShowMenuPanel);

protected:
    void onEnter() override;

    bool init() override;

    virtual void loadSource();

    std::function<void()> _funcShowMenuPanel;
    Label *_pLoadingTitle = nullptr;
}; //bug

#endif // LOADING_SOURCE_LAYER_H