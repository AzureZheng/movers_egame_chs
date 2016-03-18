/****************************************
全局设定
2016-01-11 by Azure Zheng
*****************************************/

#ifndef __GLOBAL_SETTING_H__
#define __GLOBAL_SETTING_H__


//------------------------------------------------ 通用设定 -------------------------------------------------

//屏幕大小
#define GS_VISIBLE_SIZE (Director::getInstance()->getVisibleSize())

//屏幕中点
#define GS_SCREEN_MID_POINT cocos2d::Vec2(GS_VISIBLE_SIZE.width/2,GS_VISIBLE_SIZE.height/2);

//播放音效
//#define PLAY_EFFECT(file) CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(file);



#endif
