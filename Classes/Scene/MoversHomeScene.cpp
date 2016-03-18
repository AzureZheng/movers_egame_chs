#include "MoversHomeScene.h"
#include "Scene/BuildingScene.h"
#include "ui/CocosGUI.h"
#include "SDKManage/EgamePay.h"
#include "SDKManage/Umeng.h"
using namespace ui;

// there's no 'id' in cpp, so we recommend returning the class instance pointer
Scene* MoversHomeScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MoversHomeScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

void MoversHomeScene::swapCloud(float dt)
{
	auto cloud = Sprite::create();
	cloud->setSpriteFrame("world_home_cloud.png");
	if (random(0, 1) == 1) cloud->setFlippedX(true);
	cloud->setPosition(10 * random(-32, 192), 10 * random(0, 110));
	addChild(cloud, 2);
	cloud->setOpacity(0);
	cloud->runAction(FadeTo::create(4, 255));
	cloud->runAction(Sequence::create(
		MoveBy::create(random(28, 36), Vec2(2340, 0)),
		RemoveSelf::create(),
		NULL
		));
}

//void moversVoidStartGame(void *obj)
//{
//	((MoversHomeScene*)obj)->goToGame(1);
//}
//
//void buttonShowAbout(void *obj)
//{
//	((MoversHomeScene*)obj)->showAbout();
//}
//
//void buttonShowRecoed(void *obj)
//{
//	((MoversHomeScene*)obj)->showRecord();
//}

// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
bool MoversHomeScene::init()
{
	if (!Layer::init()) return false;

	GameInfo::loadMoney();
	GameInfo::loadModeUnlock();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile(WORLD_MOVERS_CAR_PLI, createTexture(WORLD_MOVERS_CAR_BIG));
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile(WORLD_MOVERS_HWORLD_PLI, createTexture(WORLD_MOVERS_HWORLD_BIG));

	addBackWorld();

	//-------------------------------测试钻石-----------------------------
	UserDefault::getInstance();
	auto ud = UserDefault::getInstance();
	if (ud->getIntegerForKey("Diamond", -1) < 0)
	{
		//Umeng::pay(5,500,7);
		//Umeng::buy("Diamond",100,0.01);
		//Umeng::use("Diamond",100,0.01);
		//Umeng::userEvent("death_level","96");
		//ud->setIntegerForKey("Diamond", 280);
	}
	

	////////////////////
	inOption = false;
	inMenu = true;
	_bv = 0.3f;
	//CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_EFFECT_BUTTON);
	//CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_EFFECT_ZOOM_IN);
	//CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_EFFECT_ZOOM_OUT);

	uiHolder = Node::create();
	uiHolder->setContentSize(visibleSize);
	addChild(uiHolder, 40);

	auto about = Sprite::createWithSpriteFrameName("home_aboutxq.png");
	about->setScale(1.8f);
	about->setPosition(visibleSize.width + 1010, 532);
	uiHolder->addChild(about);

	auto title = Sprite::createWithSpriteFrameName("home_logo.png");
	title->setPosition(1369, 832);
	uiHolder->addChild(title);

	addShop();

	m_exitGameView = ExitGameUI::create();
	m_exitGameView->getButtonCancel()->setCallback(CC_CALLBACK_1(MoversHomeScene::hideExitGame,this));
	uiHolder->addChild(m_exitGameView,99);

	auto sfc = SpriteFrameCache::getInstance();

	buttonGame = SpriteButtonZooming::create("home_bt_start.png");
	buttonGame->setNormalSpriteFrame(sfc->getSpriteFrameByName("home_bt_start_s.png"), true);
	buttonGame->setPosition(Vec2(1362, 422));
	uiHolder->addChild(buttonGame, 2);
	buttonGame->setCallback(std::bind(&MoversHomeScene::goToGame, this, std::placeholders::_1, 1));
	buttonGame->setLogicPosition(3, 0);
	m_buttonsList1.pushBackButton(buttonGame);

	buttonAbout = SpriteButton::create("home_bt_about.png");
	buttonAbout->setNormalSpriteFrame(sfc->getSpriteFrameByName("home_bt_about_s.png"), true);
	buttonAbout->setPosition(205, 890);
	uiHolder->addChild(buttonAbout, 2);
	buttonAbout->setCallback(std::bind(&MoversHomeScene::showAbout, this, std::placeholders::_1));
	buttonAbout->setLogicPosition(0, 1);
	m_buttonsList1.pushBackButton(buttonAbout);

	buttonRecord = SpriteButton::create("home_bt_record.png");
	buttonRecord->setNormalSpriteFrame(sfc->getSpriteFrameByName("home_bt_record_s.png"), true);
	buttonRecord->setPosition(495, 870);
	uiHolder->addChild(buttonRecord, 2);
	buttonRecord->setCallback(std::bind(&MoversHomeScene::showRecord, this, std::placeholders::_1));
	buttonRecord->setLogicPosition(1, 1);
	m_buttonsList1.pushBackButton(buttonRecord);

	buttonBank = SpriteButton::create("home_bt_bank.png");
	buttonBank->setNormalSpriteFrame(sfc->getSpriteFrameByName("home_bt_bank_s.png"), true);
	buttonBank->setPosition(782, 890);
	uiHolder->addChild(buttonBank, 2);
	buttonBank->setCallback(std::bind(&MoversHomeScene::showShop, this, std::placeholders::_1));
	buttonBank->setLogicPosition(2, 1);
	m_buttonsList1.pushBackButton(buttonBank);

	m_buttonsList1.setSelectedButton(buttonGame);

	//-----------------------------------------------------------------------------------------

	buttonBack = SpriteButton::create("home_bt_back.png");
	buttonBack->setNormalSpriteFrame(sfc->getSpriteFrameByName("home_bt_back_s.png"), true);
	buttonBack->setPosition(1373, 183);
	uiHolder->addChild(buttonBack, 1);
	buttonBack->setCallback(std::bind(&MoversHomeScene::backHome, this, std::placeholders::_1));
	buttonBack->setEnabled(false);
	buttonBack->setScale(0);
	buttonBack->setLogicPosition(1, 0);
	m_buttonsList2.pushBackButton(buttonBack);

	buttonMod1 = SpriteButton::create("home_bt_single.png");
	buttonMod1->setNormalSpriteFrame(sfc->getSpriteFrameByName("home_bt_single_s.png"), true);
	buttonMod1->setPosition(Vec2(1165, 469));
	uiHolder->addChild(buttonMod1, 1);
	buttonMod1->setCallback(std::bind(&MoversHomeScene::goToGame1, this, std::placeholders::_1));
	buttonMod1->setEnabled(false);
	buttonMod1->setScale(0);
	buttonMod1->setLogicPosition(0, 1);
	m_buttonsList2.pushBackButton(buttonMod1);

	buttonMod2 = SpriteButton::create("home_bt_multiL.png");
	buttonMod2->setNormalSpriteFrame(sfc->getSpriteFrameByName("home_bt_multiL_s.png"), true);
	buttonMod2->setPosition(Vec2(1596, 469));
	uiHolder->addChild(buttonMod2, 1);
	buttonMod2->setEnabled(false);
	buttonMod2->setScale(0);
	buttonMod2->setLogicPosition(3, 1);
	m_buttonsList2.pushBackButton(buttonMod2);

	m_buttonsList2.setSelectedButton(buttonMod1);
	m_buttonsList2.setBackButtonCallbackButton(buttonBack);

	addHighScoreUI();

	/**/
	_listener = EventListenerTouchOneByOne::create();
	// 注册触摸监听
	_listener = EventListenerTouchOneByOne::create();
	_listener->onTouchBegan = CC_CALLBACK_2(MoversHomeScene::onTouchBegan, this);
	_listener->onTouchEnded = CC_CALLBACK_2(MoversHomeScene::onTouchEnded, this);
	_listener->setSwallowTouches(true);//不向下传递触摸
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_listener, this);

	SET_MUSIC_VOLUME(0.3f);
	PLAY_MUSIC(movers_bgm_home);

	auto ourInfo = Sprite::create("xchange_soft_ltd.pvr.ccz");
	ourInfo->setPosition(Vec2(960, 12));
	addChild(ourInfo, 9);

	auto curVersion = Sprite::create("version_code_current.pvr.ccz");
	curVersion->setPosition(origin + Vec2(4 + curVersion->getContentSize().width / 2, visibleSize.height - 4 - curVersion->getContentSize().height / 2));
	addChild(curVersion, 9);


	//创建自定义键盘派发器
	m_customKeyEventDispatcher = CustomKeyEventDispatcher::create();
	addChild(m_customKeyEventDispatcher);

	enableButtonsSelect(1, true);

	m_buttonsList1.setButtonExtraCallback(CC_CALLBACK_2(MoversHomeScene::keyExtraCallback,this));
	m_buttonsList1.setTag(1);
	m_buttonsList2.setTag(2);

	refreshMultiModeButton();

	return true;
}

//显示商城
void MoversHomeScene::showShop(Ref * ref)
{
	PLAY_EFFECT(SOUND_EFFECT_ZOOM_IN);
	if (m_bankView->isSubShop())
	{
		m_bankView->showHideSubShop(true);
	}
	else
	{
		m_buttonsList1.pauseKeyListener();
		m_bankView->activeShopView(true);
		m_bankView->setBlackBackVisible(true);
		m_bankView->setBlackBackZOrder(1);
	}
}

//隐藏商城
void MoversHomeScene::hideShop(Ref * ref)
{
	PLAY_EFFECT(SOUND_EFFECT_ZOOM_OUT);
	if (m_bankView->isSubShop())
	{
		m_bankView->showHideSubShop(false);
	}
	else
	{
		m_bankView->activeShopView(false);
		runAction(Sequence::create(DelayTime::create(0.1f), CallFunc::create([this]()
		{
			m_bankView->setBlackBackVisible(false);
			m_buttonsList1.resumeKeyListener();
		}), nullptr));
	}
}

//添加商城
void MoversHomeScene::addShop()
{
	m_bankView = BankView::create();
	uiHolder->addChild(m_bankView,3);

	m_bankView->getButtonBack()->setCallback(std::bind(&MoversHomeScene::hideShop, this, std::placeholders::_1));

	m_bankView->getButtonUnlock()->setCallback(std::bind(&MoversHomeScene::unlockMode, this, std::placeholders::_1));

	m_bankView->getButtonUnlockCancel()->setCallback(std::bind(&MoversHomeScene::hideUnlockMode, this, std::placeholders::_1));
}


//添加背景图
void MoversHomeScene::addBackWorld()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();


	//天空背景
	auto _sky = Sprite::createWithSpriteFrameName("home_sky_bg1.png");
	_sky->setAnchorPoint(Vec2::ZERO);
	_sky->setScale(visibleSize.width / _sky->getContentSize().width, visibleSize.height / _sky->getContentSize().height);
	addChild(_sky, 1);

	//背景圈
	auto _circle = Sprite::create(WORLD_SKY_CIRCLE_BIG);
	_circle->setPosition(Vec2(visibleSize.width / 2, visibleSize.height + 200));
	_circle->setScale(1.25f);
	addChild(_circle, 2);
	_circle->runAction(RepeatForever::create(RotateBy::create(1.0, Vec3(0, 0, -60))));

	//公路背景承载
	downHolder = Node::create();
	addChild(downHolder, 3);

	//公路背景
	auto glbg1 = Sprite::createWithSpriteFrameName("home_gonglu_bg1.png");
	glbg1->setAnchorPoint(Vec2::ZERO);
	glbg1->setScaleX(visibleSize.width / glbg1->getContentSize().width);
	downHolder->addChild(glbg1, 0);

	//卡车
	_car = MoversTruck::create();
	addChild(_car, 5);
	_car->setPosition(511, 261);


	//背景草树云的移动
	for (int i = -500; i <= 4000; i += 400)
	{
		landGrass1(i);
	}

	for (int i = -500; i <= 4000; i += 800)
	{
		landGrass2(i);
	}

	for (int i = -1000; i <= 4000; i += 800)
	{
		landMountain(i);
	}

	swapCloud();
	swapCloud();
	swapCloud();
	swapCloud();
	swapCloud();
	swapCloud();

	schedule(schedule_selector(MoversHomeScene::loodGrass1), 0.75f);
	schedule(schedule_selector(MoversHomeScene::loodGrass2), 1);
	schedule(schedule_selector(MoversHomeScene::loodMountain), 5);
	schedule(schedule_selector(MoversHomeScene::swapCloud), 2);

}

//添加高分计数面板UI
void MoversHomeScene::addHighScoreUI()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto ui = Layer::create();
	ui->setContentSize(visibleSize);
	ui->setPosition(uiHolder->convertToNodeSpace(Vec2(-visibleSize.width, 0)));
	uiHolder->addChild(ui);

	Vector<Sprite*> panelList;

	panelList.pushBack(Sprite::createWithSpriteFrameName("history_single_panel.png"));
	panelList.back()->setPosition(Vec2(328 + 300, 568));
	ui->addChild(panelList.back());

	//panelList.pushBack(Sprite::createWithSpriteFrameName("history_match_panel.png"));
	//panelList.back()->setPosition(Vec2(957, 568));
	//ui->addChild(panelList.back());

	panelList.pushBack(Sprite::createWithSpriteFrameName("history_multi_panel.png"));
	panelList.back()->setPosition(Vec2(1592 - 300, 568));
	ui->addChild(panelList.back());


	Vector<LabelAtlas*> tempAtlas;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			tempAtlas.pushBack(LabelAtlas::create("0123456789", MOVERS_HOME_PAGE_ATLAS, 29, 37, '0'));
			tempAtlas.back()->setAnchorPoint(Vec2::ZERO);
			tempAtlas.back()->setScale(1.7f);
			panelList.at(i)->addChild(tempAtlas.back());
		}
	}

	auto ud = UserDefault::getInstance();

	tempAtlas.at(0)->setString(Value(ud->getIntegerForKey("MOVERS_HIGH_FLOOR", 0)).asString());
	tempAtlas.at(1)->setString(Value(ud->getIntegerForKey("MOVERS_HIGH_GOODS", 0)).asString());
	tempAtlas.at(2)->setString(Value(ud->getIntegerForKey("MOVERS_HIGH_BOMB", 0)).asString());
	tempAtlas.at(3)->setString(Value(ud->getIntegerForKey("MOVERS_HIGH_SCORE", 0)).asString());

	tempAtlas.at(0)->setPosition(Vec2(72, 574));
	tempAtlas.at(1)->setPosition(Vec2(72, 402));
	tempAtlas.at(2)->setPosition(Vec2(72, 228));
	tempAtlas.at(3)->setPosition(Vec2(72, 53));


	tempAtlas.at(4)->setString(Value(ud->getIntegerForKey("M1MOVERS_HIGH_FLOOR", 0)).asString());
	tempAtlas.at(5)->setString(Value(ud->getIntegerForKey("M1MOVERS_HIGH_GOODS", 0)).asString());
	tempAtlas.at(6)->setString(Value(ud->getIntegerForKey("M1MOVERS_HIGH_BOMB", 0)).asString());
	tempAtlas.at(7)->setString(Value(ud->getIntegerForKey("M1MOVERS_HIGH_SCORE", 0)).asString());

	tempAtlas.at(4)->setPosition(Vec2(72, 574));
	tempAtlas.at(5)->setPosition(Vec2(72, 402));
	tempAtlas.at(6)->setPosition(Vec2(72, 228));
	tempAtlas.at(7)->setPosition(Vec2(72, 53));
}


void MoversHomeScene::unlockMode(Ref * ref)
{
	auto d = m_bankView->getDiamond();
	if (d < 200)
	{
		showShop(ref);
	}
	else
	{
		Umeng::use("Diamond",200,0.01);
		UserDefault::getInstance()->setIntegerForKey("Diamond",d-200);
		UserDefault::getInstance()->setBoolForKey("MultiMode",true);
		refreshMultiModeButton();
		hideUnlockMode(ref);
	}
}


void MoversHomeScene::intoGame()
{
	STOP_MUSIC;

	doIntoGame(this);
}

void MoversHomeScene::intoMod1(Ref * ref)
{
	if (_playerCount > 1)
	{
		if (BuildingScene::getGameMode() == 2)
		{
			GameInfo::getInstance()->switchGameMode(3);
		}
		else
		{
			GameInfo::getInstance()->switchGameMode(2);
		}
	}
	else
	{
		GameInfo::getInstance()->switchGameMode(0);
	}


	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, BuildingScene::createSceneWithStory(_playerCount)));
}

void MoversHomeScene::intoMod2(Ref * ref)
{
	GameInfo::getInstance()->switchGameMode(1);
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, BuildingScene::createSceneWithStory(1)));
}

void MoversHomeScene::blackScreen()
{
	schedule(schedule_selector(MoversHomeScene::subBgmV));
	auto _black = LayerColor::create();
	addChild(_black, 20);
	_black->setOpacity(0);
	_black->runAction(Sequence::create(
		FadeTo::create(0.25, 255),
		FadeTo::create(0.05, 255),
		CallFunc::create(CC_CALLBACK_0(MoversHomeScene::intoGame, this)),
		nullptr
		));
}

void MoversHomeScene::goToGame(Ref * ref, int playerCount)
{
	((SpriteButtonZooming*)buttonGame)->eraseNormalScaleOnce();
	enableButtonsSelect(1, false);
	runAction(Sequence::create(DelayTime::create(0.2f), CallFunc::create(std::bind(&MoversHomeScene::enableButtonsSelect, this, 2, true)), nullptr));

	buttonGame->setEnabled(false);
	buttonAbout->setEnabled(false);
	buttonRecord->setEnabled(false);
	buttonBank->setEnabled(false);
	buttonBack->setEnabled(false);
	buttonMod1->setEnabled(false);
	buttonMod2->setEnabled(false);

	_playerCount = playerCount;

	buttonBack->runAction(Sequence::create(
		ScaleTo::create(0.2f, 1),
		CallFunc::create(CC_CALLBACK_0(SpriteButton::setEnabled, buttonBack, true)),
		nullptr));

	buttonMod1->runAction(Sequence::create(
		ScaleTo::create(0.2f, 1),
		CallFunc::create(CC_CALLBACK_0(SpriteButton::setEnabled, buttonMod1, true)),
		nullptr));

	buttonMod2->runAction(Sequence::create(
		ScaleTo::create(0.2f, 1),
		CallFunc::create(CC_CALLBACK_0(SpriteButton::setEnabled, buttonMod2, true)),
		nullptr));

	buttonGame->runAction(ScaleTo::create(0.2f, 0));
	buttonAbout->runAction(ScaleTo::create(0.2f, 0));
	buttonRecord->runAction(ScaleTo::create(0.2f, 0));
	buttonBank->runAction(ScaleTo::create(0.2f, 0));
}

void MoversHomeScene::goToGame1(Ref * ref)
{
	BuildingScene::setGameMode(0);
	buttonBack->setEnabled(false);
	buttonMod1->setEnabled(false);
	buttonMod2->setEnabled(false);

	doIntoGame = std::bind(&MoversHomeScene::intoMod1, this, std::placeholders::_1);

	uiHolder->runAction(MoveBy::create(0.2f, Vec2(0, 1080)));
	_car->runAction(Sequence::create(
		MoveBy::create(1.0f, Vec2(-1920, 0)),
		CallFunc::create(CC_CALLBACK_0(MoversHomeScene::blackScreen, this)),
		NULL
		));
}


void MoversHomeScene::goToGame2(Ref * ref)
{
	BuildingScene::setGameMode(1);
	buttonBack->setEnabled(false);
	buttonMod1->setEnabled(false);
	buttonMod2->setEnabled(false);
	doIntoGame = std::bind(&MoversHomeScene::intoMod2, this, std::placeholders::_1);
	uiHolder->runAction(MoveBy::create(0.2f, Vec2(0, 1080)));
	_car->runAction(Sequence::create(
		MoveBy::create(1.0f, Vec2(-1920, 0)),
		CallFunc::create(CC_CALLBACK_0(MoversHomeScene::blackScreen, this)),
		NULL
		));
}


void MoversHomeScene::goToGame3()
{
	BuildingScene::setGameMode(2);
	buttonBack->setEnabled(false);
	buttonMod1->setEnabled(false);
	buttonMod2->setEnabled(false);
	doIntoGame = std::bind(&MoversHomeScene::intoMod1, this, std::placeholders::_1);
	uiHolder->runAction(MoveBy::create(0.2f, Vec2(0, 1080)));
	_car->runAction(Sequence::create(
		MoveBy::create(1.0f, Vec2(-1920, 0)),
		CallFunc::create(CC_CALLBACK_0(MoversHomeScene::blackScreen, this)),
		NULL
		));
}

void MoversHomeScene::backHome(Ref * ref)
{
	enableButtonsSelect(2, false);
	runAction(Sequence::create(DelayTime::create(0.2f), CallFunc::create(std::bind(&MoversHomeScene::enableButtonsSelect, this, 1, true)), nullptr));

	buttonGame->setEnabled(false);
	buttonAbout->setEnabled(false);
	buttonRecord->setEnabled(false);
	buttonBank->setEnabled(false);
	buttonBack->setEnabled(false);
	buttonMod1->setEnabled(false);
	buttonMod2->setEnabled(false);

	buttonGame->runAction(Sequence::create(
		ScaleTo::create(0.2f, 1),
		CallFunc::create(CC_CALLBACK_0(SpriteButton::setEnabled, buttonGame, true)),
		nullptr));

	buttonAbout->runAction(Sequence::create(
		ScaleTo::create(0.2f, 1),
		CallFunc::create(CC_CALLBACK_0(SpriteButton::setEnabled, buttonAbout, true)),
		nullptr));

	buttonRecord->runAction(Sequence::create(
		ScaleTo::create(0.2f, 1),
		CallFunc::create(CC_CALLBACK_0(SpriteButton::setEnabled, buttonRecord, true)),
		nullptr));

	buttonBank->runAction(Sequence::create(
		ScaleTo::create(0.2f, 1),
		CallFunc::create(CC_CALLBACK_0(SpriteButton::setEnabled, buttonBank, true)),
		nullptr));

	buttonBack->runAction(ScaleTo::create(0.2f, 0));
	buttonMod1->runAction(ScaleTo::create(0.2f, 0));
	buttonMod2->runAction(ScaleTo::create(0.2f, 0));
}

void MoversHomeScene::loodGrass1(float dt)
{
	landGrass1(-300);
}

void MoversHomeScene::landGrass1(float PX)
{
	auto grass = Sprite::create();//Sprite::createWithSpriteFrameName( "home_guanmu1.png" );
	grass->setSpriteFrame("home_guanmu1.png");

	grass->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	grass->setPositionY(230);

	grass->setPositionX(PX - random(950, 1040));
	if (random(0, 1) == 1) grass->setFlippedX(true);
	if (random(0, 1) == 0)
	{
		auto tree = Sprite::create();
		tree->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
		tree->setPositionY(230);
		downHolder->addChild(tree, 5);
		if (random(0, 1) == 0) tree->setSpriteFrame("home_shu1a.png");
		else tree->setSpriteFrame("home_shu1b.png");
		tree->setPositionX(PX - random(880, 1160));
		tree->runAction(Sequence::create(
			MoveBy::create(9, Vec2(5000, 0)),
			RemoveSelf::create(),
			NULL
			));
	}

	downHolder->addChild(grass, 5);
	grass->runAction(Sequence::create(
		MoveBy::create(9, Vec2(5000, 0)),
		RemoveSelf::create(),
		NULL
		));
}

///////////////////////////////////////////////////////////////////

void MoversHomeScene::loodGrass2(float dt)
{
	landGrass2(-300);
}

void MoversHomeScene::landGrass2(float PX)
{
	auto grass = Sprite::create();//Sprite::createWithSpriteFrameName( "home_guanmu1.png" );
	grass->setSpriteFrame("home_guanmu2.png");

	grass->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	grass->setPositionY(267);

	grass->setPositionX(PX - random(950, 1040));
	if (random(0, 1) == 1) grass->setFlippedX(true);
	if (random(0, 1) == 0)
	{
		auto tree = Sprite::create();
		tree->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
		tree->setPositionY(267);
		downHolder->addChild(tree, 3);
		if (random(0, 1) == 0) tree->setSpriteFrame("home_shu2a.png");
		else tree->setSpriteFrame("home_shu2b.png");
		tree->setPositionX(PX - random(880, 1160));
		tree->runAction(Sequence::create(
			MoveBy::create(18, Vec2(5000, 0)),
			RemoveSelf::create(),
			NULL
			));
	}


	downHolder->addChild(grass, 4);
	grass->runAction(Sequence::create(
		MoveBy::create(18, Vec2(5000, 0)),
		RemoveSelf::create(),
		NULL
		));
}

///////////////////////////////////////////

void MoversHomeScene::loodMountain(float dt)
{
	landMountain(-400);
}

void MoversHomeScene::landMountain(float PX)
{
	auto mt = Sprite::create();
	mt->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	mt->setPositionY(230);

	switch (random(0, 2))
	{
	default: break;
	case 0: mt->setSpriteFrame("home_shan1a.png"); break;
	case 1: mt->setSpriteFrame("home_shan1b.png"); break;
	case 2: mt->setSpriteFrame("home_shan1c.png"); break;
	}
	if (random(0, 1) == 1) mt->setFlippedX(true);
	mt->setPositionX(PX - random(928, 1184));
	downHolder->addChild(mt, 2);
	mt->runAction(Sequence::create(
		MoveBy::create(38, Vec2(4000, 0)),
		RemoveSelf::create(),
		NULL
		));

	//////////////////////

	mt = Sprite::create();
	mt->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	mt->setPositionY(230);
	switch (random(0, 1))
	{
	default: break;
	case 0: mt->setSpriteFrame("home_shan2a.png"); break;
	case 1: mt->setSpriteFrame("home_shan2b.png"); break;
	}
	if (random(0, 1) == 1) mt->setFlippedX(true);
	mt->setPositionX(PX - random(928, 1184));
	downHolder->addChild(mt, 1);
	mt->runAction(Sequence::create(
		MoveBy::create(48, Vec2(4000, 0)),
		RemoveSelf::create(),
		NULL
		));
}

void MoversHomeScene::subBgmV(float dt)
{
	_bv -= 0.03;
	SET_MUSIC_VOLUME(_bv);
}

bool MoversHomeScene::onTouchBegan(Touch *touch, Event *event)
{
	return true;
}

void MoversHomeScene::onTouchEnded(Touch *touch, Event *event)
{
	hideOptions();
}

void MoversHomeScene::onExit()
{
	Layer::onExit();
	Director::getInstance()->getEventDispatcher()->removeEventListener(_listener);
	TextureCache::getInstance()->removeUnusedTextures();
}

void MoversHomeScene::showRecord(Ref * ref)
{
	if (inMenu)
	{
		enableButtonsSelect(1, false);
		inMenu = false;
		PLAY_EFFECT(SOUND_EFFECT_ZOOM_IN);
		uiHolder->runAction(Sequence::create(
			MoveBy::create(0.1, Vec2(1920, 0)),
			CallFunc::create(CC_CALLBACK_0(MoversHomeScene::confirmAbout, this)),
			NULL
			));
	}
}

void MoversHomeScene::showAbout(Ref * ref)
{
	if (inMenu)
	{
		enableButtonsSelect(1,false);
		inMenu = false;
		PLAY_EFFECT(SOUND_EFFECT_ZOOM_IN);
		uiHolder->runAction(Sequence::create(
			MoveBy::create(0.1, Vec2(-1920, 0)),
			CallFunc::create(CC_CALLBACK_0(MoversHomeScene::confirmAbout, this)),
			NULL
			));
	}
}

void MoversHomeScene::hideOptions()
{
	if (inOption)
	{
		enableButtonsSelect(1, true);
		inOption = false;
		PLAY_EFFECT(SOUND_EFFECT_ZOOM_OUT);
		int px = 1920;
		if (uiHolder->getPositionX() > 1920 / 2) px = -px;
		uiHolder->runAction(Sequence::create(
			MoveBy::create(0.1, Vec2(px, 0)),
			CallFunc::create(CC_CALLBACK_0(MoversHomeScene::confirmMenu, this)),
			NULL
			));
	}
}


//开启关闭第几个按钮组的选择控制
void MoversHomeScene::enableButtonsSelect(int index, bool enable)
{
	auto & bs = index == 1 ? m_buttonsList1 : m_buttonsList2;

	if (enable)
	{
		bs.resumeKeyListener();
	}
	else
	{
		bs.pauseKeyListener();
	}
}


//额外按钮回调
void MoversHomeScene::keyExtraCallback(KeyButtonsPackage * package, CustomKeyEvent * e)
{
	auto kc = e->getKeyCode();

	switch (kc)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_BACK:
		if (inOption)
		{
			hideOptions();
		}
		else if(!m_buttonsList1.isPausedKeyListener())
		{
			exitGame();
		}

		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_DPAD_CENTER:
	case cocos2d::EventKeyboard::KeyCode::KEY_ENTER:
	case cocos2d::EventKeyboard::KeyCode::KEY_KP_ENTER:
		if (inOption)
		{
			hideOptions();
		}
		break;
	}
}



//弹出双手模式
void MoversHomeScene::showUnlockMode(Ref * ref)
{
	PLAY_EFFECT(SOUND_EFFECT_ZOOM_IN);
	m_buttonsList2.pauseKeyListener();
	m_bankView->setBlackBackZOrder(-1);
	m_bankView->setBlackBackVisible(true);
	m_bankView->activeUnlockView(true);
}


//隐藏双手模式
void MoversHomeScene::hideUnlockMode(Ref * ref)
{
	PLAY_EFFECT(SOUND_EFFECT_ZOOM_OUT);
	m_buttonsList2.resumeKeyListener();
	m_bankView->setBlackBackZOrder(1);
	m_bankView->setBlackBackVisible(false);
	m_bankView->activeUnlockView(false);
}


//刷新双手模式按钮
void MoversHomeScene::refreshMultiModeButton()
{
	auto ud = UserDefault::getInstance();

	auto unlock = ud->getBoolForKey("MultiMode",false);

	if (unlock)
	{
		buttonMod2->setNormalSpriteFrame("home_bt_multi.png");
		buttonMod2->setNormalSpriteFrame("home_bt_multi_s.png",true);
		buttonMod2->setCallback(CC_CALLBACK_1(MoversHomeScene::goToGame2,this));
	}
	else
	{
		buttonMod2->setNormalSpriteFrame("home_bt_multiL.png");
		buttonMod2->setNormalSpriteFrame("home_bt_multiL_s.png", true);
		buttonMod2->setCallback(CC_CALLBACK_1(MoversHomeScene::showUnlockMode, this));
	}
}


//退出游戏
void MoversHomeScene::exitGame()
{
	PLAY_EFFECT(SOUND_EFFECT_ZOOM_IN);
	m_buttonsList1.pauseKeyListener();
	m_exitGameView->activePanel(true);
}


//取消退出游戏
void MoversHomeScene::hideExitGame(Ref * ref)
{
	PLAY_EFFECT(SOUND_EFFECT_ZOOM_OUT);
	m_exitGameView->activePanel(false);
	runAction(Sequence::create(DelayTime::create(0.1f), CallFunc::create([this](){m_buttonsList1.resumeKeyListener(); }), nullptr));
}
