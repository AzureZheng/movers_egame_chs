#include "OpeningScene.h"
#include "FilePathDefine.h"
#include "Scene/MoversHomeScene.h"
#include "Objects/RabbitHamal.h"
#include "Objects/ThrowableObject.h"
#include "GlobalUtils/SpriteButton.h"


USING_NS_CC;

//音效加载完毕
bool OpeningScene::m_effectLoadFinished = false;

//获取音效是否加载完毕
bool OpeningScene::isEffectLoadFinished()
{
	return m_effectLoadFinished;
}

//设置音效加载完毕
void OpeningScene::effectLoadFinished()
{
	m_effectLoadFinished = true;
}

Scene* OpeningScene::createScene()
{
	auto scene = Scene::create();

	auto layer = OpeningScene::create();

	scene->addChild(layer);

	return scene;
}

bool OpeningScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//获取屏幕大小
	m_visibleSize = Director::getInstance()->getVisibleSize();

	//流程计数置零
	m_progressIndex = 0;

	//流程等待
	m_progressWait = true;

	//开始第一次计数
	countProgressIndex();

	//开启流程监控
	scheduleUpdate();

	return true;
}


//显示开场动画
void OpeningScene::showOpeningAnim()
{
	m_openingAnimLayer = Layer::create();

	addChild(m_openingAnimLayer);

	m_openingAnimLayer->setOpacity(0);
	m_openingAnimLayer->setCascadeOpacityEnabled(true);

	//加载Loading背景图
	Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA8888);
	auto logo = Sprite::create(MOVERS_START_LOGO);
	logo->setNormalizedPosition(Vec2::ANCHOR_MIDDLE);
	m_openingAnimLayer->addChild(logo);
	Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA4444);

	//执行开场动画
	auto act1 = FadeIn::create(0.3f);
	auto act2 = CallFunc::create(std::bind(&OpeningScene::countProgressIndex, this));

	m_openingAnimLayer->runAction(Sequence::create(act1, act2, nullptr));
}


//预加载资源
void OpeningScene::preloadRes()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(THROWABLE_OBJECTS_PLI, createTexture(THROWABLE_OBJECTS_BIG));
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(BUILDING_OBJECTS_PLI, createTexture(BUILDING_OBJECTS_BIG));
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile(WORLD_BACKGROUNDS_PLI, createTexture(WORLD_BACKGROUNDS_BIG));
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(MOVERS_VIDEO_ARARD_PLI, createTexture(MOVERS_VIDEO_ARARD_BIG));

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(MOVERS_HOME_PAGE_PLI, createTexture(MOVERS_HOME_PAGE_BIG));
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(MOVERS_HOME_BACK_PLI, createTexture(MOVERS_HOME_BACK_BIG));
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(MOVERS_GAME_UI_PLI, createTexture(MOVERS_GAME_UI_BIG));

	RabbitHamal::preloadAllViewTypes();

	ThrowableObject::prepareObjectFrames();

	preloadSound();

	//加载按钮默认声音
	SpriteButton::setAllButtonsDefaultSound(SOUND_EFFECT_BUTTON);

	//若没有需要预载的资源，直接进入下一步骤
	countProgressIndex();
}


//预载音乐
void OpeningScene::preloadSound()
{
	PRELOAD_MUSIC(movers_bgm_home);
	PRELOAD_MUSIC(movers_bgm_result);
	PRELOAD_EFFECT(movers_sfx_click);
	PRELOAD_EFFECT(SOUND_EFFECT_ZOOM_IN);
	PRELOAD_EFFECT(SOUND_EFFECT_ZOOM_OUT);

	PRELOAD_EFFECT(movers_bgm_index_01);
	PRELOAD_EFFECT(movers_bgm_index_02);
	PRELOAD_EFFECT(movers_bgm_index_03);
	PRELOAD_EFFECT(movers_bgm_index_04);
	PRELOAD_EFFECT(movers_bgm_index_05);
	PRELOAD_EFFECT(movers_bgm_index_06);

	PRELOAD_EFFECT(SOUND_EFFECT_SCORE);
	PRELOAD_EFFECT(SOUND_EFFECT_COUNT_DOWN_0);
	PRELOAD_EFFECT(SOUND_EFFECT_COUNT_DOWN_1);

	PRELOAD_EFFECT(movers_story_stopcar);
	PRELOAD_EFFECT(movers_story_talk);
	PRELOAD_EFFECT(movers_story_walk);
	PRELOAD_EFFECT(movers_sfx_gameover);
	PRELOAD_EFFECT(movers_story_opendoor);
	PRELOAD_EFFECT(movers_story_goods);
}


//关闭开场动画
void OpeningScene::closeOpeningAnim()
{
	//若没有需要关闭的开场动画，直接进入下一步骤
	countProgressIndex();
}


//切换到下一场景
void OpeningScene::enterNextScene()
{
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, MoversHomeScene::createScene()));
}


//监控流程
void OpeningScene::update(float dt)
{
	if (m_progressWait)
	{
		return;
	}

	m_progressWait = true;

	switch (m_progressIndex)
	{
	case 1:
		showOpeningAnim();
		break;
	case 2:
		preloadRes();
		break;
	case 3:
		closeOpeningAnim();
		break;
	case 4:
		enterNextScene();
		break;
	}
}


//流程计数加1
void OpeningScene::countProgressIndex()
{
	m_progressIndex++;
	m_progressWait = false;
}


//单项预加载资源完成回调
void OpeningScene::preloadResCallback(cocos2d::Texture2D * tex, const std::string & plistPath)
{
	if (!plistPath.empty())
	{
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plistPath, tex);
	}

	m_resPreloadCount++;
	if (m_resPreloadCount >= m_resPreloadTotalCount)
	{
		countProgressIndex();
	}
}


//结束时移除资源
void OpeningScene::onExit()
{
	Layer::onExit();

	auto tc = Director::getInstance()->getTextureCache();

	tc->removeUnusedTextures();
}
