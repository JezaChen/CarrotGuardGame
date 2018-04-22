//
//  TowerBlueStar.cpp
//  CarrotFantasy
//
//  Created by 陈建彰 on 18-3-12.
//  
//
#include "WelcomeScene.h"
#include "SpritesLayer.h"
#include "MenusLayer.h"
#include "LoadingSourceLayer.h"
#include "Config.h"

WelcomeScene::~WelcomeScene()
{
    CC_SAFE_RELEASE_NULL(_pMenuLayer); //安全释放MenuLayer
    CC_SAFE_RELEASE_NULL(_pSpritesLayer); //安全释放SpriteLayer
}

bool WelcomeScene::init()
{
    bool bRet = false;
    do {
        CC_BREAK_IF(!Scene::init());
        //创建欢迎界面精灵们的图层
        _pSpritesLayer = SpritesLayer::create();
        _pSpritesLayer->retain();

        //创建欢迎界面菜单的图层
        _pMenuLayer = MenusLayer::create();
        _pMenuLayer->retain();

        bRet = true;
    } while (0);

    return bRet;
}

void WelcomeScene::onEnter()
{
    Scene::onEnter();
    addChild(_pSpritesLayer); //无论加载是否完成，那几个怪物萝卜都显示出来
    if (!Config::getInstance()->getIsLoadSource()) //如果加载资源完成后
    {
        auto pLoadingLayer = LoadingSourceLayer::create();
        pLoadingLayer->setFuncShowMenuPanel(CC_CALLBACK_0(WelcomeScene::showMenu, this)); //传递一个回调函数，用于加载资源完毕后回调showMenu
        pLoadingLayer->setName("loadingLayer");
        addChild(pLoadingLayer);
    }
    else
    {
        addChild(_pMenuLayer);
    }

	showVideo();
}

void WelcomeScene::showMenu()
{
    getChildByName("loadingLayer")->removeFromParent(); //去除加载进度条
    addChild(_pMenuLayer);
    Config::getInstance()->setIsLoadSource(true);
}


//贪玩蓝月启动
void WelcomeScene::showVideo()
{
	//获取可见屏幕大小；
	Size size = Director::getInstance()->getVisibleSize();
	//如果是安卓和ios；
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)  
	auto videoPlayer = cocos2d::experimental::ui::VideoPlayer::create();
	//设置坐标；
	videoPlayer->setPosition(Point(size.width / 2, size.height / 2));
	//设置锚点；
	videoPlayer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	//设置当前视频屏幕大小；
	videoPlayer->setContentSize(Size(size.width, size.height));
	this->addChild(videoPlayer);

	if (videoPlayer)
	{
		videoPlayer->setFileName("twly.mp4");
		videoPlayer->play();
	}
	videoPlayer->addEventListener(CC_CALLBACK_2(WelcomeScene::videoEventCallback, this));
#endif  
}

void WelcomeScene::videoPlayOverCallback()
{
	//ToDo；
}

/**
* @brief 视频播放的状态
* @detai注意这里的代码，此处代码只有在android平台和Ios平台有效
*/
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)  
void WelcomeScene::videoEventCallback(Ref* sender, cocos2d::experimental::ui::VideoPlayer::EventType eventType) {
	switch (eventType) {
	case cocos2d::experimental::ui::VideoPlayer::EventType::PLAYING:
		break;
	case cocos2d::experimental::ui::VideoPlayer::EventType::PAUSED:
		break;
	case cocos2d::experimental::ui::VideoPlayer::EventType::STOPPED:
		break;
	case cocos2d::experimental::ui::VideoPlayer::EventType::COMPLETED:
		videoPlayOverCallback();
		break;
	default:
		break;
	}
}
#endif  
