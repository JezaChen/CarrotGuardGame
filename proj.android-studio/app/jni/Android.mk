LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos/audio/include)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := $(LOCAL_PATH)/hellocpp/main.cpp \
                   $(LOCAL_PATH)/../../../Classes/AppDelegate.cpp \
                   $(LOCAL_PATH)/../../../Classes/HelloWorldScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/HelloWorldScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/AboutUsLayer.cpp \
                   $(LOCAL_PATH)/../../../Classes/AdvertisementLayer.cpp \
                   $(LOCAL_PATH)/../../../Classes/AppDelegate.cpp \
                   $(LOCAL_PATH)/../../../Classes/BarrierBase.cpp \
                   $(LOCAL_PATH)/../../../Classes/BarrierBuilder.cpp \
                   $(LOCAL_PATH)/../../../Classes/BarrierFactory.cpp \
                   $(LOCAL_PATH)/../../../Classes/BarrierManager.cpp \
                   $(LOCAL_PATH)/../../../Classes/BarriersLayer.cpp \
                   $(LOCAL_PATH)/../../../Classes/BM_GameEndLayer.cpp \
                   $(LOCAL_PATH)/../../../Classes/BM_MonsterBuilder.cpp \
                   $(LOCAL_PATH)/../../../Classes/BM_ScoreAndControlLayer.cpp \
                   $(LOCAL_PATH)/../../../Classes/BossModeLevelSelectLayer.cpp \
                   $(LOCAL_PATH)/../../../Classes/BossModeLevelSelectScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/BulletAnchor.cpp \
                   $(LOCAL_PATH)/../../../Classes/BulletBase.cpp \
                   $(LOCAL_PATH)/../../../Classes/BulletBlueStar.cpp \
                   $(LOCAL_PATH)/../../../Classes/BulletFactory.cpp \
                   $(LOCAL_PATH)/../../../Classes/BulletFish.cpp \
                   $(LOCAL_PATH)/../../../Classes/BulletLayer.cpp \
                   $(LOCAL_PATH)/../../../Classes/BulletLittleAnchor.cpp \
                   $(LOCAL_PATH)/../../../Classes/BulletManager.cpp \
                   $(LOCAL_PATH)/../../../Classes/BulletPin.cpp \
                   $(LOCAL_PATH)/../../../Classes/BulletRocket.cpp \
                   $(LOCAL_PATH)/../../../Classes/BulletStar.cpp \
                   $(LOCAL_PATH)/../../../Classes/Carrot.cpp \
                   $(LOCAL_PATH)/../../../Classes/CollisionManager.cpp \
                   $(LOCAL_PATH)/../../../Classes/Config.cpp \
                   $(LOCAL_PATH)/../../../Classes/CountDownLayer.cpp \
                   $(LOCAL_PATH)/../../../Classes/CsvUtil.cpp \
                   $(LOCAL_PATH)/../../../Classes/DataCollectLayer.cpp \
                   $(LOCAL_PATH)/../../../Classes/DataStatisticsLayer.cpp \
                   $(LOCAL_PATH)/../../../Classes/DesignLayer.cpp \
                   $(LOCAL_PATH)/../../../Classes/DynamicPropertyInterface.cpp \
                   $(LOCAL_PATH)/../../../Classes/Entity.cpp \
                   $(LOCAL_PATH)/../../../Classes/EntityLayerBase.cpp \
                   $(LOCAL_PATH)/../../../Classes/GameEndLayer.cpp \
                   $(LOCAL_PATH)/../../../Classes/GameManager.cpp \
                   $(LOCAL_PATH)/../../../Classes/GameScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/GameSceneII.cpp \
                   $(LOCAL_PATH)/../../../Classes/HelloWorldScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/HelpLayer.cpp \
                   $(LOCAL_PATH)/../../../Classes/HelpMenuPanelLayer.cpp \
                   $(LOCAL_PATH)/../../../Classes/HelpScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/HpSlot.cpp \
                   $(LOCAL_PATH)/../../../Classes/LevelConfigUtil.cpp \
                   $(LOCAL_PATH)/../../../Classes/LevelSelectLayer.cpp \
                   $(LOCAL_PATH)/../../../Classes/LevelSelectScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/LoadingScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/LoadingSourceLayer.cpp \
                   $(LOCAL_PATH)/../../../Classes/LocalLevelDataUtil.cpp \
                   $(LOCAL_PATH)/../../../Classes/MapUtil.cpp \
                   $(LOCAL_PATH)/../../../Classes/MenusLayer.cpp \
                   $(LOCAL_PATH)/../../../Classes/MonsterBase.cpp \
                   $(LOCAL_PATH)/../../../Classes/MonsterBuilder.cpp \
                   $(LOCAL_PATH)/../../../Classes/MonsterFactory.cpp \
                   $(LOCAL_PATH)/../../../Classes/MonsterHelpLayer.cpp \
                   $(LOCAL_PATH)/../../../Classes/MonsterLayer.cpp \
                   $(LOCAL_PATH)/../../../Classes/MonsterManager.cpp \
                   $(LOCAL_PATH)/../../../Classes/MoveControllerBase.cpp \
                   $(LOCAL_PATH)/../../../Classes/NumSprite.cpp \
                   $(LOCAL_PATH)/../../../Classes/OptionLayer.cpp \
                   $(LOCAL_PATH)/../../../Classes/OptLayer.cpp \
                   $(LOCAL_PATH)/../../../Classes/PageViewLayer.cpp \
                   $(LOCAL_PATH)/../../../Classes/PauseLayer.cpp \
                   $(LOCAL_PATH)/../../../Classes/SceneBase.cpp \
                   $(LOCAL_PATH)/../../../Classes/SceneFactory.cpp \
                   $(LOCAL_PATH)/../../../Classes/SceneManager.cpp \
                   $(LOCAL_PATH)/../../../Classes/ScoreAndControlLayer.cpp \
                   $(LOCAL_PATH)/../../../Classes/SelectSceneMenuPanelLayer.cpp \
                   $(LOCAL_PATH)/../../../Classes/SettingMenuPanelLayer.cpp \
                   $(LOCAL_PATH)/../../../Classes/SettingScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/SharedMenu.cpp \
                   $(LOCAL_PATH)/../../../Classes/SoundUtil.cpp \
                   $(LOCAL_PATH)/../../../Classes/SpritesLayer.cpp \
                   $(LOCAL_PATH)/../../../Classes/ThemeSelectScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/TiledMapLayer.cpp \
                   $(LOCAL_PATH)/../../../Classes/TowerAnchor.cpp \
                   $(LOCAL_PATH)/../../../Classes/TowerArrow.cpp \
                   $(LOCAL_PATH)/../../../Classes/TowerBall.cpp \
                   $(LOCAL_PATH)/../../../Classes/TowerBase.cpp \
                   $(LOCAL_PATH)/../../../Classes/TowerBlueStar.cpp \
                   $(LOCAL_PATH)/../../../Classes/TowerCuttle.cpp \
                   $(LOCAL_PATH)/../../../Classes/TowerFactory.cpp \
                   $(LOCAL_PATH)/../../../Classes/TowerFireBottle.cpp \
                   $(LOCAL_PATH)/../../../Classes/TowerFish.cpp \
                   $(LOCAL_PATH)/../../../Classes/TowerHelpLayer.cpp \
                   $(LOCAL_PATH)/../../../Classes/TowerManager.cpp \
                   $(LOCAL_PATH)/../../../Classes/TowerMushroom.cpp \
                   $(LOCAL_PATH)/../../../Classes/TowerOptBtn.cpp \
                   $(LOCAL_PATH)/../../../Classes/TowerPin.cpp \
                   $(LOCAL_PATH)/../../../Classes/TowerPlane.cpp \
                   $(LOCAL_PATH)/../../../Classes/TowerRocket.cpp \
                   $(LOCAL_PATH)/../../../Classes/TowersLayer.cpp \
                   $(LOCAL_PATH)/../../../Classes/TowerSnow.cpp \
                   $(LOCAL_PATH)/../../../Classes/TowerStar.cpp \
                   $(LOCAL_PATH)/../../../Classes/TowerSun.cpp \
                   $(LOCAL_PATH)/../../../Classes/VictimEntityBase.cpp \
                   $(LOCAL_PATH)/../../../Classes/VisibleRect.cpp \
                   $(LOCAL_PATH)/../../../Classes/WelcomeScene.cpp \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes \
                    $(LOCAL_PATH)/../../cocos2d/extensions \

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,extensions)


# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
