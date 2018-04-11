/**
 * @brief 小关卡选择图层
 * @author 陈建彰
 * */
#ifndef LEVELSELECTLAYER_H
#define LEVELSELECTLAYER_H

#include "CommonDefine.h"

/**
 * @class LevelSelectLayer
 * @brief 关卡选择图层
 * */
class LevelSelectLayer : public Layer
{
public:
    CREATE_FUNC(LevelSelectLayer);

    virtual ~LevelSelectLayer();

protected:
    /**
     * @brief 初始化函数
     * */
    virtual bool init();

    /**
     * @brief 加载资源
     * */
    virtual void loadSource();

    /**
     * @brief 加载关卡按钮
     * @details 也就是中间那些关卡的缩略图，其实也是个进去游戏画面的按钮
     * */
    virtual void loadLevelButton();

    /**
     * @brief 加载菜单等功能性按键的函数
     * @ps //TODO 以后可能会独立出一个头文件，减少代码的耦合度
     * */
    virtual void loadMenuItem();

    /**
     * @brief 获取某个关卡的通关情况
     * @param rLevelIndex 关卡索引号
     * @return 返回一个tuple，第一个是通关荣誉，也就是萝卜星数，什么金萝卜、银萝卜之类的；第二个是是否消灭所有的障碍物
     * */
    virtual std::tuple<int, bool> getLevelData(const int &rLevelIndex);

    /**
     * @brief 切换到游戏界面的函数
     * */
    virtual void changeToGameScene();

    /**
     * @brief 加载资源
     * @details 其实就是加载所有关卡的通关数据，放在一个属性里
     * */
    virtual void loadData();

private:
    int _iCurPageIndex = 0;
    int _iCurLevelIndex = 0;
    ValueMap _DataValueMap;

private:
    Sprite *_pLockBtn = nullptr;
    MenuItemSprite *_pStartBtn = nullptr;
};

#endif //LEVELSELECTLAYER_H
