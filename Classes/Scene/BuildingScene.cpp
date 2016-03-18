#include "BuildingScene.h"
#include "FilePathDefine.h"
#include "Objects/ThrowableObject.h"
#include "Scene/MoversHomeScene.h"
#include "Scene/OpeningScene.h"
#include "SDKManage/Umeng.h"

#define MOVERS_CAR_Y 145
#define MOVERS_BOSS_Y 90

//游戏模式（默认竞技模式）
int BuildingScene::m_gameMode = 0;

//玩家对应关系(设备ID->玩家ID)
std::map<int, int> BuildingScene::m_playersIDMap;

unsigned int BuildingScene::m_sfxIndex = 9527;

unsigned int BuildingScene::m_bgmIndex = 9527;

//静态实例
BuildingScene * BuildingScene::m_instance = nullptr;

//释放资源
BuildingScene::~BuildingScene()
{

}


//初始化实例
bool BuildingScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	m_visibleSize = Director::getInstance()->getVisibleSize();
	m_centerPoint = m_visibleSize / 2;

	m_rabbitSide = 0;

	m_listener = nullptr;

	m_isLeaving = false;

	m_isBegan = false;

	m_isOvered = false;

	//初始化游戏逻辑
	m_logicInfo = GameInfo::getInstance();
	m_logicInfo->reSet();

	//世界固定器
	m_worldHolder = Node::create();
	m_worldHolder->setAnchorPoint(Vec2::ZERO);
	m_worldHolder->setContentSize(m_visibleSize);
	addChild(m_worldHolder, 1);

	//世界的背景固定器
	m_backOfWorldHolder = SpriteBatchNode::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey(MOVERS_HOME_BACK_BIG));
	m_backOfWorldHolder->setAnchorPoint(Vec2::ZERO);
	m_backOfWorldHolder->setContentSize(m_visibleSize);
	m_worldHolder->addChild(m_backOfWorldHolder, 0);

	//世界的楼层固定器
	m_buildingsOfWorldHolder = Node::create();
	m_buildingsOfWorldHolder->setAnchorPoint(Vec2::ZERO);
	m_buildingsOfWorldHolder->setContentSize(m_visibleSize);
	m_worldHolder->addChild(m_buildingsOfWorldHolder, 1);

	//世界的前景固定器
	m_frontOfWorldHolder = Node::create();
	m_frontOfWorldHolder->setAnchorPoint(Vec2::ZERO);
	m_frontOfWorldHolder->setContentSize(m_visibleSize);
	m_worldHolder->addChild(m_frontOfWorldHolder, 2);

	//UI固定器
	m_uiHolder = Node::create();
	m_uiHolder->setAnchorPoint(Vec2::ZERO);
	m_uiHolder->setContentSize(m_visibleSize);
	addChild(m_uiHolder, 3);

	//创造云朵
	schedule(schedule_selector(BuildingScene::createClouds), 0.3f);
	createClouds(0);
	createClouds(0);
	createClouds(0);
	createClouds(0);

	//预载音效
	preloadEffect();

	//添加暂停事件
	Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("BackgroundPause");
	Director::getInstance()->getEventDispatcher()->addCustomEventListener("BackgroundPause", [this](EventCustom*){pauseGame(); });

	//添加自定义键盘控制器
	m_customKeyEventDispatcher = CustomKeyEventDispatcher::create();
	addChild(m_customKeyEventDispatcher);

	//添加游戏键盘控制器
	m_keyEventTrigger.setButtonExtraCallback(CC_CALLBACK_2(BuildingScene::keyboardControl,this));

	m_instance = this;

	return true;
}


//以人数初始化游戏
void BuildingScene::initWithPlayerCount(int playerCount, bool startStory)
{
	//如果游戏模式是竞技模式
	m_playerCount = playerCount;


	//如果是多人游戏，打开多人游戏操控监控
	//if (m_playerCount > 1 || m_gameMode != 0)
	//{
	//	schedule(schedule_selector(BuildingScene::loopCheckMultiPlayerInput));
	//}


	//创建背景层
	addBackWorld();

	//创建前景层
	addFrontWorld();

	createPlayerLayers();

	setupTouchListener();

	addUILayer();

	//锁定所有玩家的输入直到游戏开始
	for (auto & i : m_playerLayers)
	{
		i->setControlLocked(true);
		i->setControlLockedSide2(true);
	}

	if (startStory)
	{
		runWithStory();
	}
	else
	{
		quicklyStartGame();
	}
}

//创建场景
Scene * BuildingScene::createScene(int playerCount)
{
	auto ly = BuildingScene::create();
	ly->initWithPlayerCount(playerCount, false);
	auto scene = Scene::create();
	scene->addChild(ly);
	return scene;
}


//从故事模式创建场景
Scene * BuildingScene::createSceneWithStory(int playerCount)
{
	auto ly = BuildingScene::create();
	ly->initWithPlayerCount(playerCount);
	auto scene = Scene::create();
	scene->addChild(ly);
	return scene;
}


//创建玩家层组
void BuildingScene::createPlayerLayers()
{
	if (m_playerCount == 1)
	{
		createSinglePlayerLayer();
	}
	else if (m_playerCount == 2)
	{
		createDoublePlayersLayers();
	}
	else
	{
		createMultiPlayersLayers();
	}
}


//创建单人玩家层
void BuildingScene::createSinglePlayerLayer()
{
	auto ly = PlayerLayer::create();
	ly->setClippingEnabled(false);
	ly->setPosition(Vec2(m_visibleSize.width / 2, m_visibleSize.height / 2));
	ly->setPlayerID(0);
	ly->initBuilding();
	m_playerLayers.pushBack(ly);
	m_buildingsOfWorldHolder->addChild(ly, 1);
}


//创建双人玩家层
void BuildingScene::createDoublePlayersLayers()
{
	auto ly1 = PlayerLayer::create();
	ly1->setPosition(Vec2(m_visibleSize.width / 4, m_visibleSize.height / 2));
	ly1->setPlayerID(0);
	ly1->initBuilding();
	m_playerLayers.pushBack(ly1);
	m_buildingsOfWorldHolder->addChild(ly1, 1);

	auto ly2 = PlayerLayer::create();
	ly2->setPosition(Vec2(m_visibleSize.width / 4 * 3, m_visibleSize.height / 2));
	ly2->setPlayerID(1);
	ly2->initBuilding();
	m_playerLayers.pushBack(ly2);
	m_buildingsOfWorldHolder->addChild(ly2, 1);
}


//创建多人玩家层
void BuildingScene::createMultiPlayersLayers()
{
	PlayerLayer * ly = nullptr;

	for (int i = 0; i < m_playerCount; i++)
	{
		ly = PlayerLayer::create();
		ly->setPosition(Vec2((2 * i + 1) * m_visibleSize.width / (m_playerCount * 2), m_visibleSize.height / 2));
		ly->setPlayerID(i);
		ly->initBuilding();
		m_playerLayers.pushBack(ly);
		m_buildingsOfWorldHolder->addChild(ly, 1);
	}
}


//创建背景层
void BuildingScene::addBackWorld()
{
	//背景天空
	m_backSky = Sprite::createWithSpriteFrameName("home_sky_bg1.png");
	m_backSky->setAnchorPoint(Vec2::ZERO);
	m_backSky->setScale(m_visibleSize.width / m_backSky->getContentSize().width, m_visibleSize.height / m_backSky->getContentSize().height);
	m_backOfWorldHolder->addChild(m_backSky, 1);


	//创建群山
	m_backMountain = Sprite::createWithSpriteFrameName("back_shan1.png");
	m_backMountain->setAnchorPoint(Vec2::ZERO);
	m_backMountain->setContentSize(m_visibleSize);
	m_backMountain->setCascadeOpacityEnabled(false);
	m_backMountain->setOpacity(0);
	m_backOfWorldHolder->addChild(m_backMountain, 2);

	//创建建筑
	m_backBuildings = Sprite::createWithSpriteFrameName("back_house1.png");
	m_backBuildings->setAnchorPoint(Vec2::ZERO);
	m_backBuildings->setContentSize(m_visibleSize);
	m_backBuildings->setCascadeOpacityEnabled(false);
	m_backBuildings->setOpacity(0);
	m_backOfWorldHolder->addChild(m_backBuildings, 4);


	Sprite * tempSP = nullptr;

	if (m_playerCount <= 1)
	{
		//-------------------------- 山 ------------------------------
		//左
		tempSP = Sprite::createWithSpriteFrameName("back_shan1.png");
		tempSP->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
		tempSP->setPosition(Vec2(0, 0));
		m_backMountain->addChild(tempSP, 2);

		//中
		tempSP = Sprite::createWithSpriteFrameName("back_shan2.png");
		tempSP->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
		tempSP->setPosition(Vec2(960, 0));
		m_backMountain->addChild(tempSP, 1);

		tempSP = Sprite::createWithSpriteFrameName("back_shan1.png");
		tempSP->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
		tempSP->setPosition(Vec2(960, 0));
		m_backMountain->addChild(tempSP, 2);

		//右
		tempSP = Sprite::createWithSpriteFrameName("back_shan2.png");
		tempSP->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
		tempSP->setPosition(Vec2(1676, 0));
		m_backMountain->addChild(tempSP, 1);

		tempSP = Sprite::createWithSpriteFrameName("back_shan1.png");
		tempSP->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
		tempSP->setPosition(Vec2(1964, 0));
		m_backMountain->addChild(tempSP, 2);

		//-------------------------- 建筑 ------------------------------
		//左
		tempSP = Sprite::createWithSpriteFrameName("back_house2.png");
		tempSP->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
		tempSP->setPosition(Vec2(65, 110));
		m_backBuildings->addChild(tempSP, 2);

		//中
		tempSP = Sprite::createWithSpriteFrameName("back_house1.png");
		tempSP->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
		tempSP->setPosition(Vec2(811, 110));
		m_backBuildings->addChild(tempSP, 1);

		tempSP = Sprite::createWithSpriteFrameName("back_house2.png");
		tempSP->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
		tempSP->setPosition(Vec2(1034, 110));
		m_backBuildings->addChild(tempSP, 2);

		//右
		tempSP = Sprite::createWithSpriteFrameName("back_house2.png");
		tempSP->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
		tempSP->setPosition(Vec2(1856, 110));
		m_backBuildings->addChild(tempSP, 2);

		//-------------------------- 树 ------------------------------
		m_backTrees = Sprite::createWithSpriteFrameName("back_tree1.png");
		m_backTrees->setAnchorPoint(Vec2::ZERO);
		m_backOfWorldHolder->addChild(m_backTrees, 5);
	}
	else
	{
		//-------------------------- 山 ------------------------------
		//左
		tempSP = Sprite::createWithSpriteFrameName("back_shan2.png");
		tempSP->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
		tempSP->setPosition(Vec2(465, 0));
		m_backMountain->addChild(tempSP, 1);

		tempSP = Sprite::createWithSpriteFrameName("back_shan1.png");
		tempSP->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
		tempSP->setPosition(Vec2(465, 0));
		m_backMountain->addChild(tempSP, 2);

		//右
		tempSP = Sprite::createWithSpriteFrameName("back_shan2.png");
		tempSP->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
		tempSP->setPosition(Vec2(1528, 0));
		m_backMountain->addChild(tempSP, 1);

		tempSP = Sprite::createWithSpriteFrameName("back_shan1.png");
		tempSP->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
		tempSP->setPosition(Vec2(1528, 0));
		m_backMountain->addChild(tempSP, 2);

		//-------------------------- 建筑 ------------------------------
		//左
		tempSP = Sprite::createWithSpriteFrameName("back_house2.png");
		tempSP->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
		tempSP->setPosition(Vec2(545, 110));
		m_backBuildings->addChild(tempSP, 1);

		tempSP = Sprite::createWithSpriteFrameName("back_house1.png");
		tempSP->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
		tempSP->setPosition(Vec2(317, 110));
		m_backBuildings->addChild(tempSP, 2);

		//右
		tempSP = Sprite::createWithSpriteFrameName("back_house2.png");
		tempSP->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
		tempSP->setPosition(Vec2(1530, 110));
		m_backBuildings->addChild(tempSP, 1);

		tempSP = Sprite::createWithSpriteFrameName("back_house1.png");
		tempSP->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
		tempSP->setPosition(Vec2(1295, 110));
		m_backBuildings->addChild(tempSP, 2);

		//-------------------------- 树 ------------------------------
		m_backTrees = Sprite::createWithSpriteFrameName("back_tree2.png");
		m_backTrees->setAnchorPoint(Vec2::ZERO);
		m_backOfWorldHolder->addChild(m_backTrees, 5);
	}

}


//创建前景层
void BuildingScene::addFrontWorld()
{
	//创建公路
	auto _road = Sprite::createWithSpriteFrameName("front_road.png");
	_road->setAnchorPoint(Vec2::ZERO);
	_road->setScaleX(m_visibleSize.width / _road->getContentSize().width);
	m_frontOfWorldHolder->addChild(_road, 0);


	if (m_playerCount <= 1)
	{
		//创建大窗
		auto dachuang = Sprite::createWithSpriteFrameName("back_window.png");
		dachuang->setPosition(472, 375);
		m_frontOfWorldHolder->addChild(dachuang, 0);

		dachuang = Sprite::createWithSpriteFrameName("back_window.png");
		dachuang->setPosition(1451, 375);
		m_frontOfWorldHolder->addChild(dachuang, 0);

		//创建栏杆
		auto langan = Sprite::createWithSpriteFrameName("building_langan.png");
		langan->setPosition(Vec2(472, 118));
		m_frontOfWorldHolder->addChild(langan, 0);

		langan = Sprite::createWithSpriteFrameName("building_langan.png");
		langan->setPosition(Vec2(1451, 118));
		m_frontOfWorldHolder->addChild(langan, 0);

		//创建盆景
		auto penjing = Sprite::createWithSpriteFrameName("front_penjing.png");
		penjing->setPosition(328, 144);
		m_frontOfWorldHolder->addChild(penjing, 0);

		penjing = Sprite::createWithSpriteFrameName("front_penjing.png");
		penjing->setPosition(615, 144);
		m_frontOfWorldHolder->addChild(penjing, 0);

		penjing = Sprite::createWithSpriteFrameName("front_penjing.png");
		penjing->setPosition(1303, 144);
		m_frontOfWorldHolder->addChild(penjing, 0);

		penjing = Sprite::createWithSpriteFrameName("front_penjing.png");
		penjing->setPosition(1590, 144);
		m_frontOfWorldHolder->addChild(penjing, 0);
	}
	else
	{
		//创建大窗
		auto dachuang = Sprite::createWithSpriteFrameName("back_window.png");
		dachuang->setPosition(960, 375);
		m_frontOfWorldHolder->addChild(dachuang, 0);

		//创建栏杆
		auto langan = Sprite::createWithSpriteFrameName("building_langan.png");
		langan->setPosition(Vec2(957, 118));
		m_frontOfWorldHolder->addChild(langan, 0);

		langan = Sprite::createWithSpriteFrameName("building_langan.png");
		langan->setPosition(Vec2(0, 118));
		m_frontOfWorldHolder->addChild(langan, 0);

		langan = Sprite::createWithSpriteFrameName("building_langan.png");
		langan->setPosition(Vec2(1920, 118));
		m_frontOfWorldHolder->addChild(langan, 0);

		//创建盆景
		auto penjing = Sprite::createWithSpriteFrameName("front_penjing.png");
		penjing->setPosition(812, 144);
		m_frontOfWorldHolder->addChild(penjing, 0);

		penjing = Sprite::createWithSpriteFrameName("front_penjing.png");
		penjing->setPosition(1097, 144);
		m_frontOfWorldHolder->addChild(penjing, 0);
	}


	//创建卡车
	m_car = MoversTruck::create();
	m_car->setScale(0.67f);
	m_frontOfWorldHolder->addChild(m_car, 4);

	//创建兔子
	for (int i = 0; i < m_playerCount; i++)
	{
		m_rabbitBosses.pushBack(RabbitHamalBoss::create());
		m_frontOfWorldHolder->addChild(m_rabbitBosses.back(), 5);
	}
}

//快速开始游戏
void BuildingScene::quicklyStartGame()
{
	int count = 0;
	for (auto & i : m_rabbitBosses)
	{
		i->setPosition(Vec2(getPlayerLayerPosInFrontLayer(count++).x, MOVERS_BOSS_Y));
	}

	auto carX = getPlayerLayerPosInFrontLayer(0).x;

	m_car->setPosition(Vec2(carX - 350, MOVERS_CAR_Y));
	m_car->stopCar();

	Node * goodsLayer = nullptr;

	for (int i = 0; i < m_playerCount; i++)
	{
		goodsLayer = Node::create();
		m_frontOfWorldHolder->addChild(goodsLayer);

		goodsLayer->setPosition(getPlayerLayerPosInFrontLayer(i));
		goodsLayer->setPositionY(270);

		auto box = Sprite::createWithSpriteFrameName("throw_object_14.png");
		box->setPosition(-77, -3 * 67);
		goodsLayer->addChild(box, 4);

		box = Sprite::createWithSpriteFrameName("throw_object_14.png");
		box->setPosition(0, -3 * 67);
		goodsLayer->addChild(box, 4);

		box = Sprite::createWithSpriteFrameName("throw_object_14.png");
		box->setPosition(77, -3 * 67);
		goodsLayer->addChild(box, 4);

		box = Sprite::createWithSpriteFrameName("throw_object_14.png");
		box->setPosition(-0.5 * 77, -2 * 67);
		goodsLayer->addChild(box, 4);

		box = Sprite::createWithSpriteFrameName("throw_object_14.png");
		box->setPosition(0.5 * 77, -2 * 67);
		goodsLayer->addChild(box, 4);

		box = Sprite::createWithSpriteFrameName("throw_object_14.png");
		box->setPosition(0, -1 * 67);
		goodsLayer->addChild(box, 4);
	}

	startNewRound();
}

//故事：开始故事
void BuildingScene::runWithStory()
{
	for (auto & i : m_rabbitBosses)
	{
		i->setCascadeOpacityEnabled(true);
		i->setOpacity(0);
	}

	m_car->setPosition(2170, MOVERS_CAR_Y);
	scheduleOnce(schedule_selector(BuildingScene::moveCar), 0.5f);
}

//故事：移车
void BuildingScene::moveCar(float dt)
{
	auto carX = getPlayerLayerPosInFrontLayer(0).x;

	m_car->runAction(Sequence::create(
		EaseBackInOut::create(MoveTo::create(3.4f, Vec2(carX - 350, MOVERS_CAR_Y))),
		CallFunc::create(CC_CALLBACK_0(BuildingScene::pushGoods, this)),
		NULL
		));
	PLAY_EFFECT(movers_story_stopcar);
}

//故事：放货
void BuildingScene::pushGoods()
{
	m_car->stopCar();
	PLAY_EFFECT(movers_story_goods);

	Node * goodsLayer = nullptr;

	auto ed = Director::getInstance()->getEventDispatcher();

	for (int i = 0; i < m_playerCount; i++)
	{
		goodsLayer = Node::create();
		m_frontOfWorldHolder->addChild(goodsLayer);

		goodsLayer->setPosition(getPlayerLayerPosInFrontLayer(i));

		goodsLayer->setPositionY(270);

		auto delayTime = 0.14f;

		auto box = Sprite::createWithSpriteFrameName("throw_object_14.png");
		box->setPosition(-77, -3 * 67);
		box->setOpacity(0);
		goodsLayer->addChild(box, 4);
		box->runAction(Sequence::create(
			FadeTo::create(delayTime * 1, 0),
			FadeTo::create(0.1, 255),
			NULL
			));
		box = Sprite::createWithSpriteFrameName("throw_object_14.png");
		box->setPosition(0, -3 * 67);
		box->setOpacity(0);
		goodsLayer->addChild(box, 4);
		box->runAction(Sequence::create(
			FadeTo::create(delayTime * 2, 0),
			FadeTo::create(0.1, 255),
			NULL
			));
		box = Sprite::createWithSpriteFrameName("throw_object_14.png");
		box->setPosition(77, -3 * 67);
		box->setOpacity(0);
		goodsLayer->addChild(box, 4);
		box->runAction(Sequence::create(
			FadeTo::create(delayTime * 3, 0),
			FadeTo::create(0.1, 255),
			NULL
			));
		box = Sprite::createWithSpriteFrameName("throw_object_14.png");
		box->setPosition(-0.5 * 77, -2 * 67);
		box->setOpacity(0);
		goodsLayer->addChild(box, 4);
		box->runAction(Sequence::create(
			FadeTo::create(delayTime * 4, 0),
			FadeTo::create(0.1, 255),
			NULL
			));
		box = Sprite::createWithSpriteFrameName("throw_object_14.png");
		box->setPosition(0.5 * 77, -2 * 67);
		box->setOpacity(0);
		goodsLayer->addChild(box, 4);
		box->runAction(Sequence::create(
			FadeTo::create(delayTime * 5, 0),
			FadeTo::create(0.1, 255),
			NULL
			));
		box = Sprite::createWithSpriteFrameName("throw_object_14.png");
		box->setPosition(0, -1 * 67);
		box->setOpacity(0);
		goodsLayer->addChild(box, 4);
		box->runAction(Sequence::create(
			FadeTo::create(delayTime * 6, 0),
			FadeTo::create(0.1, 255),
			FadeTo::create(0.6, 255),
			CallFunc::create([ed]()
		{
			ed->dispatchCustomEvent("PushBoxFinished");
		}),
			NULL
			));
	}

	ed->addCustomEventListener("PushBoxFinished", [this, ed](EventCustom * e)
	{
		ed->removeCustomEventListeners("PushBoxFinished");

		openDoor();
	});

}

//故事：开门
void BuildingScene::openDoor()
{
	PLAY_EFFECT(movers_story_opendoor);

	auto ed = Director::getInstance()->getEventDispatcher();

	for (int i = 0; i < m_playerCount; i++)
	{
		auto boss = m_rabbitBosses.at(i);

		boss->setPosition(Vec2(m_car->getPosition().x - 60, MOVERS_BOSS_Y));

		boss->runAction(Sequence::create(
			DelayTime::create(1.2f),
			FadeTo::create(0.2f, 255),
			CallFunc::create([ed, boss]()
		{
			boss->runAction(RepeatForever::create(Sequence::create(
				RotateTo::create(0.06f, 6),
				RotateTo::create(0.06f, -6),
				NULL)))->setTag(22);
			ed->dispatchCustomEvent("OpenDoorFinished");
		}),
			NULL
			));
	}

	ed->addCustomEventListener("OpenDoorFinished", [this, ed](EventCustom * e)
	{
		ed->removeCustomEventListeners("OpenDoorFinished");

		moveOut();
	});
}


//故事：开腔
void BuildingScene::talkStart()
{
	for (int i = 0; i < m_playerCount; i++)
	{
		auto boss = m_rabbitBosses.at(i);

		boss->stopActionByTag(22);
		boss->setRotation(0);
		PLAY_EFFECT(movers_story_talk);

		boss->goTalk();
	}

	Director::getInstance()->getEventDispatcher()->addCustomEventListener("RabbitTalkFinish", [this](cocos2d::EventCustom * e)
	{
		Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("RabbitTalkFinish");
		startNewRound();
	});

}


//故事：走出来
void BuildingScene::moveOut()
{
	PLAY_EFFECT(movers_story_walk);

	auto ed = Director::getInstance()->getEventDispatcher();

	for (int i = 0; i < m_playerCount; i++)
	{
		auto boss = m_rabbitBosses.at(i);

		boss->runAction(Sequence::create(
			MoveTo::create(1.1, Vec2(getPlayerLayerPosInFrontLayer(i).x, MOVERS_BOSS_Y)),
			CallFunc::create([ed](){ed->dispatchCustomEvent("MoveOutFinished"); }),
			NULL
			));
	}

	ed->addCustomEventListener("MoveOutFinished", [this, ed](EventCustom * e)
	{
		ed->removeCustomEventListeners("MoveOutFinished");
		talkStart();
	});
}


//开始一轮
void BuildingScene::startWave(float dt)
{
	m_rabbitSide = !m_rabbitSide;

	//显示接手兔子
	BuildingStage * stage = nullptr;
	StageSide * stageSide = nullptr;
	for (auto & i : m_playerLayers)
	{
		stage = i->getBuilding()->getRecvStage();

		if (m_gameMode == 0)
		{
			stageSide = stage->getStageSide(m_rabbitSide);
			stageSide->showRabbit();
			stageSide->showYou();
		}
		else
		{
			stage->getStageSide(0)->showRabbit();
			//stage->getStageSide(0)->showYou(i->getPlayerID() == 1);
			stage->getStageSide(1)->showRabbit();
			//stage->getStageSide(1)->showYou(i->getPlayerID() == 1);
		}
	}

	m_beginStep = 0;
	m_meterStep = 0;
	m_endStep = 0;
	m_bgmStep = 1;

	m_isBegan = true;

	ThrowableObject::flyingObjects.clear();

	m_logicInfo->timeCheckGameBegin();

	schedule(schedule_selector(BuildingScene::logicStep));
	schedule(schedule_selector(BuildingScene::clockStep));

	//开启玩家控制
	for (auto & i : m_playerLayers)
	{
		i->setControlLocked(false);
		i->setControlLockedSide2(false);
	}
}



//新开一轮
void BuildingScene::startNewRound()
{
	//随机决定左右兔子
	m_rabbitSide = cocos2d::random(0, 1);

	startWave(0);
}


//获取玩家层对应的前景层位置
Vec2 BuildingScene::getPlayerLayerPosInFrontLayer(int layerIndex)
{
	auto layer = m_playerLayers.at(layerIndex);

	auto tempPos = layer->getParent()->convertToWorldSpace(layer->getPosition());

	tempPos = m_frontOfWorldHolder->convertToNodeSpace(tempPos);

	tempPos.y = 0;

	return tempPos;
}


//获取玩家层对应的UI层位置
Vec2 BuildingScene::getPlayerLayerPosInUILayer(int layerIndex)
{
	auto layer = m_playerLayers.at(layerIndex);

	auto tempPos = layer->getParent()->convertToWorldSpace(layer->getPosition());

	tempPos = m_uiHolder->convertToNodeSpace(tempPos);

	tempPos.y = 0;

	return tempPos;
}


void BuildingScene::clockStep(float dt)
{
	m_logicInfo->updateCurrentTime(dt);
}


void BuildingScene::logicStep(float dt)
{
	if (m_logicInfo->getCurrentGameTime() >= m_meterStep * MIN_METER_TIME)
	{

		//当节奏为单数时，晃动脑袋
		if (m_meterStep % 2 == 1)
		{
			HeadShaker::shakeAllHeads();
		}


		//----------------------------------- 音乐播放 --------------------------------------

		//当节奏为1时，播放开头音乐
		if (m_meterStep == 1)
		{
			m_bgmIndex=PLAY_EFFECT(movers_bgm_index_01);
			m_meterStep++;
			return;
		}

		//当节奏到了下一段时，播放下一段音乐
		if (m_meterStep % 16 == 1)
		{
			switch (m_bgmStep)
			{
			default: break;
			case 1:m_bgmIndex = PLAY_EFFECT(movers_bgm_index_02); break;
			case 2:m_bgmIndex = PLAY_EFFECT(movers_bgm_index_03); break;
			case 3:m_bgmIndex = PLAY_EFFECT(movers_bgm_index_02); break;
			case 4:m_bgmIndex = PLAY_EFFECT(movers_bgm_index_04); break;
			case 5:m_bgmIndex = PLAY_EFFECT(movers_bgm_index_05); break;
			case 6:m_bgmIndex = PLAY_EFFECT(movers_bgm_index_06); break;
			}
			m_bgmStep++;
			if (m_bgmStep > 6) m_bgmStep = 1;
		}


		////--------------------------------- 节奏控制 -----------------------------------------

		//读取第一层（除去前奏16）的32+8个节奏
		if (m_meterStep == 17)
		{
			newWave();
			readMusicHead();
		}

		//读取第二层（除去第一层16*4）开始的32 + 8个节奏
		else if ((m_meterStep - 64) % 48 == 1)
		{
			newWave();
			readMusicBody();
		}


		////--------------------------------- 爬楼控制 ------------------------------------------

		//如果结束步骤等于音符步骤，提升楼层
		if (m_endStep > 3 && m_endStep == m_meterStep)
		{
			upFloor();
		}


		////--------------------------------- 抛物控制 ------------------------------------------
		//当前音符步骤减去开始步骤得到本次音符序号
		doMeterOnce(m_meterStep - m_beginStep);

		m_meterStep++;
	}
}


//从字符串读取音符到音符列表中
void BuildingScene::readStringToGame(const std::string & _A0B)
{
	std::vector<MeterOnce> MeterLoader;
	std::vector<int> BList;
	MeterLoader.clear();
	BList.clear();
	m_lastLen = _A0B.length();
	for (auto i = 0; i < m_lastLen; i++)
	{
		if (_A0B.at(i) == 'A')
		{
			MeterLoader.push_back(MeterOnce(i, 2));
		}
		else if (_A0B.at(i) == 'B')
		{
			BList.push_back(i);
		}
	}
	auto bSize = BList.size();

	for (auto i = 0; i < bSize; i++)
	{
		MeterLoader[i].endMeters = BList[i];
	}
	m_meterList.clear();
	while (MeterLoader.size() > 0)
	{
		m_meterList.push_back(MeterLoader.back());
		MeterLoader.pop_back();
	}

	m_endStep = m_beginStep + m_lastLen;
}



//读取新一轮音符
void BuildingScene::newWave()
{
	if (m_endStep > 3) upFloorFinish();
	m_beginStep = m_meterStep;
}


//整体爬楼
void BuildingScene::upFloor()
{
	m_logicInfo->upFloor();
	m_rabbitSide = !m_rabbitSide;
	for (auto & i : m_playerLayers)
	{
		i->upFloor();

		if (!i->getOver())
		{
			if (m_gameMode == 0)
			{
				auto stageSide = i->getBuilding()->getBuildingStages().at(i->getStageCount() == 1 ? 2 : 3)->getStageSide(m_rabbitSide);
				stageSide->showRabbit();
			}
			else
			{
				auto stageSide = i->getBuilding()->getBuildingStages().at(i->getStageCount() == 1 ? 2 : 3)->getStageSide(0);
				stageSide->showRabbit();
				stageSide = i->getBuilding()->getBuildingStages().at(i->getStageCount() == 1 ? 2 : 3)->getStageSide(1);
				stageSide->showRabbit();
			}
		}
	}

	//如果当前层为第一层的话，移动前景层
	if (m_playerLayers.at(0)->getStageCount() <= 2)
	{
		auto act1 = DelayTime::create(0.5f);
		auto act2 = EaseElasticInOut::create(MoveBy::create(1.0f, Vec2(0, -BUILDING_STAGE_H)));

		m_frontOfWorldHolder->runAction(Sequence::create(act1, act2, nullptr));
	}

	//同时移动背景的山和建筑
	m_backBuildings->runAction(Sequence::create(DelayTime::create(0.5f),
		EaseElasticInOut::create(MoveBy::create(1.0f, Vec2(0, -BUILDING_STAGE_H / 4))), nullptr));

	m_backMountain->runAction(Sequence::create(DelayTime::create(0.5f),
		EaseElasticInOut::create(MoveBy::create(1.0f, Vec2(0, -BUILDING_STAGE_H / 13))), nullptr));

	m_backTrees->runAction(Sequence::create(DelayTime::create(0.5f),
		EaseElasticInOut::create(MoveBy::create(1.0f, Vec2(0, -BUILDING_STAGE_H))), nullptr));
}


//整体爬楼结束
void BuildingScene::upFloorFinish()
{
	for (auto & i : m_playerLayers)
	{
		i->upFloorFinish();

		auto stageSide = i->getBuilding()->getRecvStage()->getStageSide(m_rabbitSide);


		if (!i->getOver() && i->getStageCount() < 3)
		{
			if (m_gameMode > 0)
			{
				//i->getBuilding()->getRecvStage()->getStageSide(0)->showYou(m_gameMode == 2 && i->getPlayerID() == 1);
				//i->getBuilding()->getRecvStage()->getStageSide(1)->showYou(m_gameMode == 2 && i->getPlayerID() == 1);
			}
			else
			{
				stageSide->showYou();
			}
		}

		if (i->getStageCount() < 4)
		{
			if (m_gameMode == 1)
			{
				//i->getBuilding()->getThrowStage()->getStageSide(0)->hideYou();
				//i->getBuilding()->getThrowStage()->getStageSide(1)->hideYou();
			}
			else
			{
				i->getBuilding()->getThrowStage()->getStageSide(!m_rabbitSide)->hideYou();
			}
		}
	}
}


//使用一个音符
void BuildingScene::doMeterOnce(int meterIndex)
{
	if (m_meterList.size() <= 0)
	{
		return;
	}

	if (meterIndex == m_meterList.back().beginMeters)
	{

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
		//if (m_sfxIndex != m_bgmIndex) STOP_EFFECT(m_sfxIndex);
#endif
		PLAY_EFFECT(movers_sfx_throw);

		ThrowableObject * object = nullptr;

		auto bombRand = m_logicInfo->getBombRandom();

		//为每个玩家创建相同的物件
		for (auto & i : m_playerLayers)
		{
			if (i->getOver()) continue;

			if (bombRand == 0)
			{
				object = ThrowableBomb::create();
			}
			else
			{
				object = ThrowableObject::create();
			}

			m_frontOfWorldHolder->addChild(object, 7);

			int side = 0;

			if (m_gameMode == 0)
			{
				side = m_rabbitSide;
			}
			else
			{
				side = cocos2d::random(0, 1);
			}


			RabbitHamal * r1 = nullptr;
			RabbitHamal * r2 = nullptr;


			r2 = i->getBuilding()->getRecvStage()->getSideRabbit(side);
			if (i->getStageCount() == 0)
			{
				r1 = m_rabbitBosses.at(i->getPlayerID());
			}
			else
			{
				r1 = i->getBuilding()->getThrowStage()->getSideRabbit(!side);
			}

			auto pos1 = r1->getPosition();
			auto pos2 = r2->getPosition();

			pos1 = r1->getParent()->convertToWorldSpace(pos1);
			pos1 = m_frontOfWorldHolder->convertToNodeSpace(pos1);

			pos2 = r2->getParent()->convertToWorldSpace(pos2);
			pos2 = m_frontOfWorldHolder->convertToNodeSpace(pos2);

			object->setSide(side);
			object->setTwoPoints(pos1, pos2, m_meterList.back().meterLength() * MIN_METER_TIME);
			object->setBeginTime(m_meterStep * MIN_METER_TIME);

			object->activeMotion();
			object->setCatcher(r2);
			object->setOwner(i->getPlayerID());
			ThrowableObject::flyingObjects.push_back(object);
			r1->goThrow();
		}

		m_meterList.pop_back();
	}
}


//读取节奏头
void BuildingScene::readMusicHead()
{
	readStringToGame(GameInfo::getHeadMusic());
}


//读取节奏身
void BuildingScene::readMusicBody()
{
	readStringToGame(GameInfo::getFullMusic(2));
}


//玩家1触摸监控
bool BuildingScene::touchControl(Touch * touch, Event * e)
{
	if (!m_isBegan) return false;

	auto player = m_playerLayers.at(0);

	if (player->getOver() || player->isLockedControl()) return false;

	if (m_gameMode == 0)
	{
		for (auto & obj : ThrowableObject::flyingObjects)
		{
			if (obj->getOwner() == 0 && obj->checkAchive()) return false;
		}
		player->getBuilding()->getRecvStage()->getSideRabbit(m_rabbitSide)->goEmpty();

		player->setControlLocked(true);
		auto act1 = DelayTime::create(0.5f);
		auto act2 = CallFunc::create(std::bind(&BuildingScene::unlockTouchControl, this, 0));

		runAction(Sequence::create(act1, act2, nullptr));
	}
	else
	{
		for (auto & obj : ThrowableObject::flyingObjects)
		{
			if (obj->getOwner() == 0 && obj->getSide() == 1 && obj->checkAchive()) return false;
		}
		player->getBuilding()->getRecvStage()->getSideRabbit(1)->goEmpty();

		player->setControlLocked(true);
		auto act1 = DelayTime::create(0.5f);
		auto act2 = CallFunc::create(std::bind(&BuildingScene::unlockTouchControlSide2, this, 1, 0));

		runAction(Sequence::create(act1, act2, nullptr));
	}


	PLAY_EFFECT(movers_sfx_null);

	return false;
}


//其他玩家触摸监控
void BuildingScene::touchControlMulti(int playerID, const Vec2 & touchLocation)
{
	if (!m_isBegan) return;

	PlayerLayer * player = nullptr;

	if (m_gameMode == 0)
	{
		player = m_playerLayers.at(playerID);
	}
	else if (m_gameMode == 1)
	{
		player = m_playerLayers.at(0);
	}
	else if (m_gameMode == 2)
	{
		player = m_playerLayers.at(playerID / 2);
	}

	if (player->getOver()) return;


	if (m_gameMode == 0)
	{
		if (player->isLockedControl()) return;

		for (auto & obj : ThrowableObject::flyingObjects)
		{
			if (obj->getOwner() == playerID && obj->checkAchive()) return;
		}
		player->getBuilding()->getRecvStage()->getSideRabbit(m_rabbitSide)->goEmpty();
		player->setControlLocked(true);

		auto act1 = DelayTime::create(0.5f);
		auto act2 = CallFunc::create(std::bind(&BuildingScene::unlockTouchControl, this, playerID));

		runAction(Sequence::create(act1, act2, nullptr));
	}
	else if (m_gameMode == 1)
	{
		if (player->isLockedControlSide2()) return;

		for (auto & obj : ThrowableObject::flyingObjects)
		{
			if (obj->getSide() == 0 && obj->checkAchive()) return;
		}
		player->getBuilding()->getRecvStage()->getSideRabbit(0)->goEmpty();
		player->setControlLockedSide2(true);

		auto act1 = DelayTime::create(0.5f);
		auto act2 = CallFunc::create(std::bind(&BuildingScene::unlockTouchControlSide2, this, 0, 0));

		runAction(Sequence::create(act1, act2, nullptr));
	}
	else if (m_gameMode == 2)
	{
		if (playerID == 2)
		{
			if (player->isLockedControl()) return;

			for (auto & obj : ThrowableObject::flyingObjects)
			{
				if (obj->getOwner() == 1 && obj->getSide() == 1 && obj->checkAchive()) return;
			}
			player->getBuilding()->getRecvStage()->getSideRabbit(1)->goEmpty();
			player->setControlLocked(true);

			auto act1 = DelayTime::create(0.5f);
			auto act2 = CallFunc::create(std::bind(&BuildingScene::unlockTouchControlSide2, this, 1, playerID / 2));

			runAction(Sequence::create(act1, act2, nullptr));
		}
		else
		{
			if (player->isLockedControlSide2()) return;

			for (auto & obj : ThrowableObject::flyingObjects)
			{
				if (obj->getOwner() == playerID / 2 && obj->getSide() == 0 && obj->checkAchive()) return;
			}
			player->getBuilding()->getRecvStage()->getSideRabbit(0)->goEmpty();
			player->setControlLockedSide2(true);

			auto act1 = DelayTime::create(0.5f);
			auto act2 = CallFunc::create(std::bind(&BuildingScene::unlockTouchControlSide2, this, 0, playerID / 2));

			runAction(Sequence::create(act1, act2, nullptr));
		}
	}

	PLAY_EFFECT(movers_sfx_null);
}


//解锁玩家操作
void BuildingScene::unlockTouchControl(int playerID)
{
	if (playerID >= m_playerLayers.size()) return;

	auto player = m_playerLayers.at(playerID);

	player->setControlLocked(false);

	if (!player->getBuilding()->getRecvStage()->getSideRabbit(1)->isKO())
	{
		player->getBuilding()->getRecvStage()->getSideRabbit(1)->goNormal();
	}

	if (!player->getBuilding()->getRecvStage()->getSideRabbit(0)->isKO())
	{
		player->getBuilding()->getRecvStage()->getSideRabbit(0)->goNormal();
	}
}


//解锁合作模式玩家操作
void BuildingScene::unlockTouchControlSide2(int side, int playerID)
{
	auto player = m_playerLayers.at(playerID);

	if (side == 1)
	{
		player->setControlLocked(false);
	}
	else
	{
		player->setControlLockedSide2(false);
	}

	if (!player->getBuilding()->getRecvStage()->getSideRabbit(side)->isKO())
	{
		player->getBuilding()->getRecvStage()->getSideRabbit(side)->goNormal();
	}
}


//注册触摸监听
void BuildingScene::setupTouchListener()
{
	// 注册触摸监听
	m_listener = EventListenerTouchOneByOne::create();
	m_listener->onTouchBegan = CC_CALLBACK_2(BuildingScene::touchControl, this);
	m_listener->setSwallowTouches(true);//不向下传递触摸
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_listener, this);
}


//移除触摸监听
void BuildingScene::removeTouchListener()
{
	if (!m_listener) return;

	Director::getInstance()->getEventDispatcher()->removeEventListener(m_listener);
	m_listener = nullptr;
}

//预载音效
void BuildingScene::preloadEffect()
{
	PRELOAD_EFFECT(movers_sfx_null);
	PRELOAD_EFFECT(movers_sfx_catch);
	PRELOAD_EFFECT(movers_sfx_miss);
	PRELOAD_EFFECT(movers_sfx_catch_bomb);
	PRELOAD_EFFECT(movers_sfx_miss_bomb);
	PRELOAD_EFFECT(movers_sfx_newhigh);
	PRELOAD_EFFECT(movers_sfx_score);
	PRELOAD_EFFECT(movers_sfx_throw);
}


//创建云朵
void BuildingScene::createClouds(float dt)
{
	if (random(0, 20) == 0)
	{
		auto cloud = Sprite::create();

		cloud->setSpriteFrame("world_home_cloud.png");

		cloud->setOpacity(0);

		cloud->runAction(FadeTo::create(1, 255));

		auto lifeTime = random(18, 26);

		cloud->runAction(MoveBy::create(lifeTime, Vec2(-random(960, 1920), 0)));

		cloud->runAction(Sequence::create(DelayTime::create(lifeTime - 1), Sequence::create(
			FadeTo::create(1, 0),
			RemoveSelf::create(),
			nullptr
			), nullptr));

		m_backOfWorldHolder->addChild(cloud, 3);
		cloud->setScale(((float)random(70, 120)) / 100.0f);
		cloud->setPosition(random(0, 1920 + 100), random(0.0f, m_visibleSize.height));
	}
}



//添加UI层
void BuildingScene::addUILayer()
{
	m_gameUI = MoverGameplayUI::create();
	m_uiHolder->addChild(m_gameUI, 0);
	m_gameUI->getPauseButton()->setCallback(std::bind(&BuildingScene::gamePauseButtonCallBack, this, std::placeholders::_1));

	m_pauseUI = MoverGamepauseUI::create();
	m_uiHolder->addChild(m_pauseUI, 1);
	m_pauseUI->setLocked(true);
	m_pauseUI->getContinueButton()->setCallback(std::bind(&BuildingScene::gameResumeButtonCallBack, this, std::placeholders::_1));
	m_pauseUI->getRetryButton()->setCallback(std::bind(&BuildingScene::gameRetryButtonCallBack, this, std::placeholders::_1));
	m_pauseUI->getHomeButton()->setCallback(std::bind(&BuildingScene::gameHomeButtonCallBack, this, std::placeholders::_1));

	m_resultUI = MoverResultUI::create();
	m_uiHolder->addChild(m_resultUI, 2);
	m_resultUI->setVisible(false);
	m_resultUI->getRetryButton()->setCallback(std::bind(&BuildingScene::gameRetryButtonCallBack, this, std::placeholders::_1));
	m_resultUI->getHomeButton()->setCallback(std::bind(&BuildingScene::gameHomeButtonCallBack, this, std::placeholders::_1));

	_addBankView();
}


void BuildingScene::gameHomeButtonCallBack(Ref* sender)
{
	returnHome();
}

void BuildingScene::gameRetryButtonCallBack(Ref* sender)
{
	retryPlay();
}

void BuildingScene::gamePauseButtonCallBack(Ref* sender)
{
	pauseGame();
}

void BuildingScene::gameResumeButtonCallBack(Ref* sender)
{
	resumeGame();
}



void BuildingScene::returnHome()
{
	m_resultUI->lockButtons();
	auto _black = LayerColor::create();
	addChild(_black, 20);
	_black->setOpacity(0);
	_black->runAction(Sequence::create(
		FadeTo::create(0.25, 255),
		CallFuncN::create(CC_CALLBACK_0(BuildingScene::intoHome, this)),
		NULL
		));
}


void BuildingScene::resumeGame()
{
	if (m_isBegan) return;

	schedule(schedule_selector(BuildingScene::logicStep));
	schedule(schedule_selector(BuildingScene::clockStep));

	m_gameUI->setVisible(true);
	m_gameUI->getPauseButton()->setEnabled(false);
	m_pauseUI->setLocked(true);
	m_logicInfo->fullCount();
	m_gameUI->lockControl();

	schedule(schedule_selector(BuildingScene::countDown), 1.0f);
	countDown(0);
}


void BuildingScene::pauseGame()
{
	if (!m_isBegan) return;
	m_isBegan = false;

	unschedule(schedule_selector(BuildingScene::logicStep));
	unschedule(schedule_selector(BuildingScene::clockStep));
	m_gameUI->setVisible(false);

	runAction(Sequence::create(DelayTime::create(0.05f), CallFunc::create([this]()
	{
		m_pauseUI->setLocked(false);
		m_pauseUI->resetSelectButton();
	}), nullptr));

	PAUSE_EFFECT(m_bgmIndex);
	m_logicInfo->timeCheckGamePause();
}


void BuildingScene::retryPlay()
{
	if (m_isLeaving)
	{
		return;
	}
	m_isLeaving = true;
	pauseSchedulerAndActions();
	STOP_EFFECTS;
	STOP_MUSIC;
	Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5f, BuildingScene::createScene(m_playerCount)));
}


void BuildingScene::intoHome()
{
	if (m_isLeaving)
	{
		return;
	}
	m_isLeaving = true;
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, MoversHomeScene::createScene()));
}

//恢复倒数
void BuildingScene::countDown(float dt)
{
	int ctd = m_logicInfo->getCountDown();
	if (ctd <= 0)
	{
		if (m_isBegan) return;
		m_isBegan = true;

		m_gameUI->getPauseButton()->setEnabled(true);
		m_gameUI->unlockControl();
		unschedule(schedule_selector(BuildingScene::countDown));

		RESUME_EFFECT(m_bgmIndex);
		m_logicInfo->timeCheckGameResume();
		return;
	}

	m_gameUI->countDown(ctd);
	m_logicInfo->countDown();
}


//静态增加分数
void BuildingScene::staticAwardScore(int playerID, int score)
{
	if (!m_instance)
	{
		return;
	}
	m_instance->awardScore(playerID, score);
}



//增加分数
void BuildingScene::awardScore(int playerID, int score)
{
	m_gameUI->awardScore(playerID, score);
}


//获取实例
BuildingScene * BuildingScene::getInstance()
{
	return m_instance;
}


//震动屏幕
void BuildingScene::shakeScreen()
{
	m_worldHolder->stopAllActions();

	m_worldHolder->runAction(Sequence::create(
		MoveTo::create(0.05, Vec2(0, random(0, 40))),
		MoveTo::create(0.05, Vec2(0, 0)),
		MoveTo::create(0.05, Vec2(0, random(0, 20))),
		MoveTo::create(0.05, Vec2(0, 0)),
		MoveTo::create(0.05, Vec2(0, random(0, 20))),
		MoveTo::create(0.05, Vec2(0, 0)),
		MoveTo::create(0.05, Vec2(0, random(0, 10))),
		MoveTo::create(0.05, Vec2(0, 0)),
		NULL
		));
	m_worldHolder->runAction(Sequence::create(
		ScaleTo::create(0.05, 1.15),
		ScaleTo::create(0.05, 1),
		ScaleTo::create(0.05, 1.08),
		ScaleTo::create(0.05, 1),
		NULL
		));
}




//游戏结束界面
void BuildingScene::gameOver(int playerID, int side)
{
	auto player = m_playerLayers.at(playerID);

	if (player->getOver()) return;

	if (m_gameUI->getHpBar(playerID)->cutHP())
	{
		player->setOver(true);
	}

	//if (m_gameMode == 0)
	//{
	//	if (m_gameUI->getHpBar(playerID)->cutHP())
	//	{
	//		player->setOver(true);
	//	}
	//}
	//else if (m_gameMode == 1)
	//{
	//	if (m_gameUI->getHpBar(side == 0 ? 1 : 0)->cutHP())
	//	{
	//		player->setOver(true);
	//	}
	//}
	//else if (m_gameMode == 2)
	//{
	//	if (m_gameUI->getHpBar(playerID * 2 + (side == 0 ? 1 : 0))->cutHP())
	//	{
	//		player->setOver(true);
	//	}
	//}

	if (!player->getOver())
	{
		return;
	}

	int _cF = m_logicInfo->getCurrentFloor();

	if (_cF <= 1)
	{
		gameTruelyOver();
	}
	else
	{
		moreChance(this);
	}
	
	//for (auto & i : m_playerLayers)
	//{
	//	i->setControlLocked(true);
	//	i->setControlLockedSide2(true);
	//}

	//runAction(Sequence::create(DelayTime::create(0.01f), CallFunc::create([this]()
	//{
	//	gameTruelyOver();
	//}), nullptr));
}



//游戏真正结束界面
void BuildingScene::gameTruelyOver()
{
	if (m_isOvered) return;

	int _cF = m_logicInfo->getCurrentFloor();

	Umeng::userEvent("death_level", Value(_cF).asString());

	STOP_MUSIC;
	PLAY_EFFECT(movers_sfx_gameover);
	m_isOvered = true;
	m_isBegan = false;
	removeTouchListener();

	unschedule(schedule_selector(BuildingScene::logicStep));
	unschedule(schedule_selector(BuildingScene::clockStep));

	for (auto & i : m_playerLayers)
	{
		for (auto & j : i->getBuilding()->getBuildingStages())
		{
			j->getSideRabbit(0)->stopActionByTag(258);
			j->getSideRabbit(1)->stopActionByTag(258);

			if (j->getSideRabbit(0)->isNormal()) j->getSideRabbit(0)->goEmpty();
			if (j->getSideRabbit(1)->isNormal()) j->getSideRabbit(1)->goEmpty();
		}
	}

	for (auto & i : m_rabbitBosses)
	{
		i->goEmpty();
	}


	if (_cF > 1 || m_playerCount > 1)
	{
		runAction(Sequence::create(DelayTime::create(1), CallFunc::create([this]()
		{
			GameInfo::getInstance()->setWinnerID(-1);

			for (auto & i : m_playerLayers)
			{
				if (!i->getOver())
				{
					GameInfo::getInstance()->setWinnerID(i->getPlayerID());
					break;
				}
			}

			int highPlayerID = 0;
			if (GameInfo::getInstance()->getWinnerID() >= 0)
			{
				highPlayerID = GameInfo::getInstance()->getWinnerID();
			}
			else if (m_playerCount == 1)
			{
				highPlayerID = 0;
			}
			else
			{
				highPlayerID = BuildingScene::getInstance()->getPlayerLayer(0)->getScore() > BuildingScene::getInstance()->getPlayerLayer(1)->getScore() ? 0 : 1;
			}

			m_logicInfo->addScore(BuildingScene::getInstance()->getPlayerLayer(highPlayerID)->getScore());
			m_logicInfo->refreshBombMissedFromMatchData(highPlayerID);
			m_logicInfo->refreshGoodsCatchedFromMatchData(highPlayerID);
			
		}), nullptr));
		scheduleOnce(schedule_selector(BuildingScene::pushResult), 1.0f);
	}
	else
	{
		runAction(Sequence::create(DelayTime::create(1.7f), CallFunc::create(std::bind(&BuildingScene::retryPlay, this)), nullptr));
	}
}


//显示游戏结算
void BuildingScene::pushResult(float dt)
{
	auto fin = [this]()
	{
		m_gameUI->setVisible(false);

		m_resultUI->popUpView();

		SET_MUSIC_VOLUME(0.5f);
		PLAY_MUSIC(movers_bgm_result);
	};

	m_pauseUI->setLocked(true);
	m_gameUI->getPauseButton()->setEnabled(false);

	//显示输赢
	if (m_playerCount > 1 && GameInfo::getInstance()->getWinnerID() >= 0)
	{
		m_gameUI->setVisible(true);

		auto _win_role = Sprite::createWithSpriteFrameName("ui_win.png");
		_win_role->setVisible(false);
		addChild(_win_role, 90);

		if (GameInfo::getInstance()->getWinnerID() == 0)
		{
			_win_role->setPosition(Vec2(466, 762));
		}
		else
		{
			_win_role->setPosition(Vec2(1452, 762));
		}

		_win_role->setVisible(true);
		_win_role->setScale(5);

		PLAY_EFFECT(SOUND_EFFECT_WIN);
		auto act1 = EaseElasticOut::create(ScaleTo::create(0.5f, 1));
		auto act2 = DelayTime::create(1);
		auto act3 = RemoveSelf::create();
		auto act4 = CallFunc::create(fin);
		auto act = Sequence::create(act1, act2, act3, act4, nullptr);

		_win_role->runAction(act);

		auto bv = m_resultUI->getBackView();
		Sprite * p1_p2;

		auto zhang = Sprite::createWithSpriteFrameName("ui_win.png");
		zhang->setScale(0.4f);
		zhang->setPosition(Vec2(1060, 890));

		if (GameInfo::getInstance()->getWinnerID() == 0)
		{
			if (m_gameMode == 2)
			{
				p1_p2 = Sprite::createWithSpriteFrameName("ui_p1.png");
				p1_p2->setPosition(Vec2(1053, 890));

				auto px = Sprite::createWithSpriteFrameName("ui_p2_red.png");
				px->setAnchorPoint(Vec2::ZERO);
				px->setPositionX(p1_p2->getContentSize().width + 30);
				p1_p2->setPositionX(p1_p2->getPosition().x - p1_p2->getContentSize().width - 30);
				p1_p2->addChild(px);

				zhang->setPositionX(zhang->getPositionX() + 100);
			}
			else
			{
				p1_p2 = Sprite::createWithSpriteFrameName("ui_p1.png");
				p1_p2->setPosition(Vec2(953, 890));
			}
		}
		else
		{
			if (m_gameMode == 2)
			{
				p1_p2 = Sprite::createWithSpriteFrameName("ui_p3.png");
				p1_p2->setPosition(Vec2(1053, 890));

				auto px = Sprite::createWithSpriteFrameName("ui_p4.png");
				px->setAnchorPoint(Vec2::ZERO);
				px->setPositionX(p1_p2->getContentSize().width + 30);
				p1_p2->setPositionX(p1_p2->getPosition().x - p1_p2->getContentSize().width - 30);
				p1_p2->addChild(px);

				zhang->setPositionX(zhang->getPositionX() + 100);
			}
			else
			{
				p1_p2 = Sprite::createWithSpriteFrameName("ui_p2.png");
				p1_p2->setPosition(Vec2(953, 890));
			}
		}

		bv->addChild(p1_p2, 10);
		bv->addChild(zhang, 11);
	}
	else
	{
		fin();
	}
}




//检查多玩家的输入情况(返回是否有输入)
bool BuildingScene::checkMultiPlayerInput(int * playerIDToBeSaved, Vec2 * posToBeSaved)
{

	return false;
}



//循环检查多玩家输入情况
void BuildingScene::loopCheckMultiPlayerInput(float dt)
{
	static int playerID;
	static Vec2 touchPos;

	if (m_gameMode <= 1)
	{
		if (checkMultiPlayerInput(&playerID, &touchPos))
		{
			if (!m_isBegan) return;
			touchControlMulti(playerID, touchPos);
		}
	}
	else if (m_gameMode == 2)
	{
		for (int i = 0; i < 3; i++)
		{
			if (checkMultiPlayerInput(&playerID, &touchPos))
			{
				if (!m_isBegan) return;
				touchControlMulti(playerID, touchPos);
			}
		}
	}
}


//通过设备ID获取玩家ID（返回-1为失败）
int BuildingScene::getPlayerIDByDeviceID(int deviceID)
{
	auto iter = m_playersIDMap.find(deviceID);

	if (iter == m_playersIDMap.end())
	{
		return -1;
	}
	else
	{
		return (iter->second);
	}
}


//键盘控制触屏
void BuildingScene::keyboardControl(KeyButtonsPackage * res, CustomKeyEvent * e)
{
	auto keyCode = e->getKeyCode();

	switch (keyCode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_MENU:
	case cocos2d::EventKeyboard::KeyCode::KEY_BACK:
		pauseGame();
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_DPAD_LEFT:
	case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		touchControl(nullptr, nullptr);
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_DPAD_RIGHT:
	case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		if (m_gameMode == 1)
		{
			touchControlMulti(0,Vec2::ZERO);
		}
		else
		{
			touchControl(nullptr, nullptr);
		}
		break;
	default:
		touchControl(nullptr, nullptr);
		break;
	}

}


void BuildingScene::_addBankView()
{
	m_bankView = BankView::create();
	m_uiHolder->addChild(m_bankView, 3);

	m_bankView->getButtonBack()->setCallback(std::bind(&BuildingScene::hideShop, this, std::placeholders::_1));

	m_bankView->getButtonMoreChance()->setCallback(std::bind(&BuildingScene::heal, this, std::placeholders::_1));

	m_bankView->getButtonHealCancel()->setCallback(std::bind(&BuildingScene::moreChanceCancel, this, std::placeholders::_1));
}


//显示商城
void BuildingScene::showShop(Ref * ref)
{
	m_bankView->showHideSubShop(true);
	m_bankView->setBlackBackVisible(true);
}


//隐藏商城
void BuildingScene::hideShop(Ref * ref)
{
	m_bankView->showHideSubShop(false);
	runAction(Sequence::create(DelayTime::create(0.1f), CallFunc::create([this](){m_bankView->setBlackBackVisible(false); }), nullptr));
}


//再一次机会
void BuildingScene::moreChance(Ref * ref)
{
	m_isBegan = false;

	unschedule(schedule_selector(BuildingScene::logicStep));
	unschedule(schedule_selector(BuildingScene::clockStep));

	runAction(Sequence::create(DelayTime::create(1), CallFunc::create([this](){m_bankView->activeMoreChanceView(true); }), nullptr));
	
	PAUSE_EFFECT(m_bgmIndex);
	m_logicInfo->timeCheckGamePause();
}


//取消再一次机会
void BuildingScene::moreChanceCancel(Ref * ref)
{
	m_bankView->activeMoreChanceView(false);
	gameTruelyOver();
}


//复活
void BuildingScene::heal(Ref * ref)
{
	auto d = m_bankView->getDiamond();

	if (d < 40)
	{
		showShop(ref);
	}
	else
	{
		Umeng::use("Diamond", 40, 0.01);
		m_gameUI->getHpBar(0)->heal();
		m_playerLayers.at(0)->setOver(false);
		m_bankView->activeMoreChanceView(false);
		UserDefault::getInstance()->setIntegerForKey("Diamond",d - 40);
		m_bankView->_refreshDiamond();

		for (auto i = ThrowableObject::flyingObjects.begin(); i != ThrowableObject::flyingObjects.end();)
		{
			(*i)->removeFromParent();
			i = ThrowableObject::flyingObjects.erase(i);
		}
		resumeGame();
	}
}
