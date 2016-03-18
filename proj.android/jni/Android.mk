LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)





LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/Info/GameInfo.cpp \
                   ../../Classes/Objects/Building.cpp \
                   ../../Classes/Objects/BuildingStage.cpp \
                   ../../Classes/Objects/MoversTruck.cpp \
                   ../../Classes/Objects/RabbitHamal.cpp \
                   ../../Classes/Objects/StageSide.cpp \
                   ../../Classes/Objects/ThrowableObject.cpp \
                   ../../Classes/Scene/BuildingScene.cpp \
                   ../../Classes/Scene/MoversHomeScene.cpp \
                   ../../Classes/Scene/OpeningScene.cpp \
                   ../../Classes/Scene/PlayerLayer.cpp \
                   ../../Classes/SDKManage/EgamePay.cpp \
                   ../../Classes/SDKManage/Umeng.cpp \
                   ../../Classes/UI/MoverGameUI.cpp \
				   ../../Classes/GlobalUtils/SpriteButton.cpp \
				   ../../Classes/GlobalUtils/CustomKeyEventDispatcher.cpp \
				   ../../Classes/GlobalUtils/KeyButtonsPackage.cpp \
                   ../../Classes/UI/PushButton.cpp \
				   ../../Classes/UI/BankView.cpp \
				   ../../Classes/UI/ExitGameUI.cpp \
				   ../../Classes/UI/HPBar.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,./prebuilt-mk)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
