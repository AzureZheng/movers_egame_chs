/****************************************
文件路径定义
2016-01-28 by Azure Zheng
*****************************************/

#ifndef __FILE_PATH_DEFINE_H__
#define __FILE_PATH_DEFINE_H__

#include "SimpleAudioEngine.h"

//定义游戏设置宏
#define BUILDING_STAGE_W 640
#define BUILDING_STAGE_H 455
#define BUILDING_CAMERA_Y 280
#define BUILDING_BACK_Y 580
#define BUILDING_FRONT_POS cocos2d::Vec2(960,280)


#define MIN_METER_TIME 0.225f

#define HALF_METER_LIFE_BEFORE 0.112f
#define HALF_METER_LIFE_AFTER 0.112f


//空声音索引
#define EMPTY_SOUND_INDEX 9527
#define EMPTY_EFFECT 9527

//播放背景音效
#define BGM_EFEECT( _effect_ ) PLAY_EFFECT( _effect_ )

//音乐音效播放相关
//#define PLAY_EFFECT( _effect_ ) CocosDenshion::SimpleAudioEngine::getInstance()->playEffect( _effect_ );
//#define STOP_EFFECTS CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
//#define STOP_EFFECT( _unsini ) CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect( _unsini );
//#define STOP_MUSIC CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
//#define PAUSE_MUSIC CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
//#define RESUME_MUSIC CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
//#define LOOP_EFFECT( _effect_ ) CocosDenshion::SimpleAudioEngine::getInstance()->playEffect( _effect_ , true );
//#define PLAY_EFFECT( _effect_ ) CocosDenshion::SimpleAudioEngine::getInstance()->playEffect( _effect_ );
//#define PLAY_MUSIC( _effect_ ) CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic( _effect_ , true );
//#define PRELOAD_EFFECT( _effect_ ) CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect( _effect_ );
//#define PRELOAD_MUSIC( _effect_ ) CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic( _effect_ );

//#define PLAY_EFFECT( _effect_ ) MediaPlayerEngine::getInstance()->playEffect( _effect_ )
//#define STOP_EFFECTS MediaPlayerEngine::getInstance()->stopAllEffects()
//
//#define STOP_MUSIC MediaPlayerEngine::getInstance()->stopBackgroundMusic()
//#define PAUSE_MUSIC MediaPlayerEngine::getInstance()->pauseBackgroundMusic()
//#define RESUME_MUSIC MediaPlayerEngine::getInstance()->resumeBackgroundMusic()
//
//#define PLAY_MUSIC( _effect_ ) MediaPlayerEngine::getInstance()->playBackgroundMusic( _effect_ , true )
//#define PLAY_ONCE_MUSIC( _effect_ ) MediaPlayerEngine::getInstance()->playBackgroundMusic( _effect_ , false )
//#define PRELOAD_EFFECT( _effect_ ) MediaPlayerEngine::getInstance()->preloadEffect( _effect_ )
//#define PRELOAD_MUSIC( _effect_ ) MediaPlayerEngine::getInstance()->preloadBackgroundMusic( _effect_ )
//
//#define SET_MUSIC_VOLUME(volume) MediaPlayerEngine::getInstance()->setAllBackgroundMusicsVolume(volume)
//#define SET_EFFECT_VOLUME(volume) MediaPlayerEngine::getInstance()->setAllEffectsVolume(volume)


#define PLAY_EFFECT( _effect_ ) CocosDenshion::SimpleAudioEngine::getInstance()->playEffect( _effect_ )
#define STOP_EFFECTS CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects()
#define PAUSE_EFFECT( _effect_index_ ) CocosDenshion::SimpleAudioEngine::getInstance()->pauseEffect(_effect_index_)
#define RESUME_EFFECT( _effect_index_ ) CocosDenshion::SimpleAudioEngine::getInstance()->resumeEffect(_effect_index_)

#define STOP_MUSIC CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic()
#define PAUSE_MUSIC CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic()
#define RESUME_MUSIC CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic()

#define PLAY_MUSIC( _effect_ ) CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic( _effect_ , true )
#define PLAY_ONCE_MUSIC( _effect_ ) CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic( _effect_ , false )
#define PRELOAD_EFFECT( _effect_ ) CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect( _effect_ )
#define PRELOAD_MUSIC( _effect_ ) CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic( _effect_ )

#define SET_MUSIC_VOLUME(volume) CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(volume)
#define SET_EFFECT_VOLUME(volume) CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(volume)

//加载一张纹理
#define createTexture( _filePath_ ) Director::getInstance()->getTextureCache()->addImage( _filePath_ )


//------------------------------------------ 定义资源文件路径 ------------------------------
//-------------------------------------------------------------------------------------- New
#define MOVERS_HOME_PAGE_BIG    "NewUI/movers_ui_homepage.pvr.ccz"
#define MOVERS_HOME_PAGE_PLI    "NewUI/movers_ui_homepage.plist"
#define MOVERS_HOME_PAGE_ATLAS  "UI/In_Game_Score_View.png"
#define MOVERS_BEST_SCORE_ATLAS  "UI/result_numbers_style2.png"
#define MOVERS_GAME_SOCRE_ATLAS  "UI/game_score_style1.png"

#define MOVERS_HOME_BACK_BIG    "Movers/Objects/movers_homeback.pvr.ccz"
#define MOVERS_HOME_BACK_PLI    "Movers/Objects/movers_homeback.plist"

#define MOVERS_GAME_UI_BIG    "NewUI/movers_ui_game.pvr.ccz"
#define MOVERS_GAME_UI_PLI    "NewUI/movers_ui_game.plist"

//-------------------------------------------------------------------------------------- Texture
#define THROWABLE_OBJECTS_BIG   "Movers/Objects/ThrowableObjectsInc.pvr.ccz"
#define THROWABLE_OBJECTS_PLI   "Movers/Objects/ThrowableObjectsInc.plist"
#define BUILDING_OBJECTS_BIG    "Movers/Objects/BuildingObjectsInc.pvr.ccz"
#define BUILDING_OBJECTS_PLI    "Movers/Objects/BuildingObjectsInc.plist"
#define THROWER_CHARACTERS_BIG  "Movers/Objects/ThrowerCharactersInc.pvr.ccz"
#define THROWER_CHARACTERS_PLI  "Movers/Objects/ThrowerCharactersInc.plist"
#define WORLD_BACKGROUNDS_BIG   "Movers/Objects/BackGroundTypeInc.pvr.ccz"
#define WORLD_BACKGROUNDS_PLI   "Movers/Objects/BackGroundTypeInc.plist"
#define NUMBER_BUILDING_FLOOR   "Movers/Objects/number_building_floor.png"
#define WORLD_MOVERS_CAR_BIG    "Movers/Objects/MoversCarInc.pvr.ccz"
#define WORLD_MOVERS_CAR_PLI    "Movers/Objects/MoversCarInc.plist"
#define WORLD_MOVERS_HWORLD_BIG "Movers/Objects/MoversHomeWorldInc.pvr.ccz"
#define WORLD_MOVERS_HWORLD_PLI "Movers/Objects/MoversHomeWorldInc.plist"
#define WORLD_SKY_CIRCLE_BIG    "Movers/Objects/home_sky_bg2.pvr.ccz"
#define MOVERS_START_LOGO       "Movers/movers_start_bg.jpg"

#define MOVERS_VIDEO_ARARD_PLI  "UI/MoverVideoAwardUI.plist"
#define MOVERS_VIDEO_ARARD_BIG  "UI/MoverVideoAwardUI.pvr.ccz"

//-------------------------------------------------------------------------------------- Particle
#define PARTICLE_BOMB_FIRE      "Movers/Particles/Particle_Bomb_Fire.plist"
#define PARTICLE_BOMB_FIRE_SLOW "Movers/Particles/Particle_Bomb_Fire_Slow.plist"

//-------------------------------------------------------------------------------------- Sounds
#define movers_bgm_home         "Sounds/bgm/movers_bgm_home.mp3"
#define movers_bgm_result       "Sounds/bgm/movers_bgm_result.mp3"
#define movers_bgm_index_01     "Sounds/bgm/movers_bgm_index_01.mp3"
#define movers_bgm_index_02     "Sounds/bgm/movers_bgm_index_02.mp3"
#define movers_bgm_index_03     "Sounds/bgm/movers_bgm_index_03.mp3"
#define movers_bgm_index_04     "Sounds/bgm/movers_bgm_index_04.mp3"
#define movers_bgm_index_05     "Sounds/bgm/movers_bgm_index_05.mp3"
#define movers_bgm_index_06     "Sounds/bgm/movers_bgm_index_06.mp3"
#define movers_sfx_click        "Sounds/sfx/movers_sfx_click.mp3"
#define movers_sfx_catch        "Sounds/sfx/movers_sfx_catch.mp3"
#define movers_sfx_miss         "Sounds/sfx/movers_sfx_miss.mp3"
#define movers_sfx_catch_bomb   "Sounds/sfx/movers_sfx_catch_bomb.mp3"
#define movers_sfx_miss_bomb    "Sounds/sfx/movers_sfx_miss_bomb.mp3"
#define movers_sfx_newhigh      "Sounds/sfx/movers_sfx_newhigh.mp3"
#define movers_sfx_null         "Sounds/sfx/movers_sfx_null.wav"
#define movers_sfx_score        "Sounds/sfx/movers_sfx_score.mp3"
#define movers_sfx_throw        "Sounds/sfx/movers_sfx_throw.mp3"
#define movers_sfx_gameover     "Sounds/sfx/movers_sfx_gameover.mp3"

#define movers_story_goods        "Sounds/sfx/movers_story_goods.mp3"
#define movers_story_opendoor     "Sounds/sfx/movers_story_opendoor.mp3"
#define movers_story_stopcar      "Sounds/sfx/movers_story_stopcar.mp3"
#define movers_story_talk         "Sounds/sfx/movers_story_talk.mp3"
#define movers_story_walk         "Sounds/sfx/movers_story_walk.mp3"

#define SOUND_EFFECT_BUTTON     "Sounds/sfx/movers_sfx_click.mp3"
#define SOUND_EFFECT_SCORE      "Sounds/sfx/score_pop.mp3"

#define SOUND_EFFECT_COUNT_DOWN_0 "Sounds/sfx/countDown_0.mp3"
#define SOUND_EFFECT_COUNT_DOWN_1 "Sounds/sfx/countDown_1.mp3"
#define SOUND_EFFECT_ZOOM_IN      "Sounds/sfx/zoom_effext_in.mp3"
#define SOUND_EFFECT_ZOOM_OUT     "Sounds/sfx/zoom_effext_out.mp3"

#define SOUND_EFFECT_WIN          "Sounds/sfx/win.mp3"

//-------------------------------------------------------------------------------------- UI

#define MOVER_UI_GAME_PLAY_EPJ      "UI/MoverGameUI.ExportJson"
#define MOVER_UI_GAME_PAUSE_EPJ     "UI/MoverPauseUI.ExportJson"
#define MOVER_UI_GAME_RESULT_EPJ    "UI/MoverResultUI.ExportJson"
#define MOVER_UI_GAME_RECORD_EPJ    "UI/MoverHighRecordUI.ExportJson"

#endif
