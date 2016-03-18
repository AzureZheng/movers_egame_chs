#include "OpeningScene.h"
#include "FilePathDefine.h"
#include "Scene/MoversHomeScene.h"
#include "Objects/RabbitHamal.h"
#include "Objects/ThrowableObject.h"
#include "GlobalUtils/SpriteButton.h"


USING_NS_CC;

//��Ч�������
bool OpeningScene::m_effectLoadFinished = false;

//��ȡ��Ч�Ƿ�������
bool OpeningScene::isEffectLoadFinished()
{
	return m_effectLoadFinished;
}

//������Ч�������
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

	//��ȡ��Ļ��С
	m_visibleSize = Director::getInstance()->getVisibleSize();

	//���̼�������
	m_progressIndex = 0;

	//���̵ȴ�
	m_progressWait = true;

	//��ʼ��һ�μ���
	countProgressIndex();

	//�������̼��
	scheduleUpdate();

	return true;
}


//��ʾ��������
void OpeningScene::showOpeningAnim()
{
	m_openingAnimLayer = Layer::create();

	addChild(m_openingAnimLayer);

	m_openingAnimLayer->setOpacity(0);
	m_openingAnimLayer->setCascadeOpacityEnabled(true);

	//����Loading����ͼ
	Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA8888);
	auto logo = Sprite::create(MOVERS_START_LOGO);
	logo->setNormalizedPosition(Vec2::ANCHOR_MIDDLE);
	m_openingAnimLayer->addChild(logo);
	Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA4444);

	//ִ�п�������
	auto act1 = FadeIn::create(0.3f);
	auto act2 = CallFunc::create(std::bind(&OpeningScene::countProgressIndex, this));

	m_openingAnimLayer->runAction(Sequence::create(act1, act2, nullptr));
}


//Ԥ������Դ
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

	//���ذ�ťĬ������
	SpriteButton::setAllButtonsDefaultSound(SOUND_EFFECT_BUTTON);

	//��û����ҪԤ�ص���Դ��ֱ�ӽ�����һ����
	countProgressIndex();
}


//Ԥ������
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


//�رտ�������
void OpeningScene::closeOpeningAnim()
{
	//��û����Ҫ�رյĿ���������ֱ�ӽ�����һ����
	countProgressIndex();
}


//�л�����һ����
void OpeningScene::enterNextScene()
{
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, MoversHomeScene::createScene()));
}


//�������
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


//���̼�����1
void OpeningScene::countProgressIndex()
{
	m_progressIndex++;
	m_progressWait = false;
}


//����Ԥ������Դ��ɻص�
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


//����ʱ�Ƴ���Դ
void OpeningScene::onExit()
{
	Layer::onExit();

	auto tc = Director::getInstance()->getTextureCache();

	tc->removeUnusedTextures();
}
