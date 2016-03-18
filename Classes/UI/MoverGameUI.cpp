#include "MoverGameUI.h"
#include "Scene/BuildingScene.h"


void MoverGameplayUI::updateScoreView(float dt)
{
	auto game = BuildingScene::getInstance();

	PlayerLayer * player = nullptr;

	player = game->getPlayerLayer(0);

	player->gainViewScore((player->getScore() - player->getViewScore()) / 20);

	if (player->getViewScore() < player->getScore())
	{
		player->gainViewScore(1);
		_current_Score->setString(int2str(player->getViewScore()));
	}

	if (game->getPlayerCount() > 1)
	{
		player = game->getPlayerLayer(1);
		player->gainViewScore((player->getScore() - player->getViewScore()) / 20);

		if (player->getViewScore() < player->getScore())
		{
			player->gainViewScore(1);
			_current_Score2->setString(int2str(player->getViewScore()));
		}
	}
}

// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
bool MoverGameplayUI::init()
{
	if (!Layer::init()) return false;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	_ui = ui::Layout::create();
	_ui->setContentSize(Director::getInstance()->getVisibleSize());
	addChild(_ui, 0);


	_best_Holder = Sprite::create("UI/ui_best_score.png");
	_best_Score = LabelAtlas::create("0123456789", MOVERS_GAME_SOCRE_ATLAS, 30, 31, '0');
	_best_Score->setAnchorPoint(Vec2::ZERO);
	_best_Score->setPosition(Vec2(145, 0));
	_best_Holder->addChild(_best_Score);
	_best_Holder->setPosition(Vec2(960, 1051));
	addChild(_best_Holder);

	_current_Score = LabelAtlas::create("0123456789", MOVERS_HOME_PAGE_ATLAS, 29, 37, '0');
	_current_Score->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_current_Score->setString("0");
	_current_Score->setScale(1.2f);
	addChild(_current_Score, 1);

	if (GameInfo::getInstance()->getModeCode() == "A1" || GameInfo::getInstance()->getModeCode() == "A2")
	{
		_best_Holder->setVisible(false);

		_current_Score->setPosition(Vec2(466, 943));

		_current_Score2 = LabelAtlas::create("0123456789", MOVERS_HOME_PAGE_ATLAS, 29, 37, '0');
		_current_Score2->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		_current_Score2->setString("0");
		addChild(_current_Score2, 1);

		_current_Score2->setScale(1.2f);
		_current_Score2->setPosition(Vec2(1453, 943));

	}
	else
	{
		_current_Score->setPosition(Vec2(960, 995));
	}

	_addHpBar();


	_button_Pause = SpriteButton::create("ui_bt_pause.png");
	_button_Pause->setPosition(Vec2(90, 990));
	addChild(_button_Pause, 0);

	_countDown = Sprite::create();
	addChild(_countDown, 2);
	_countDown->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);

	_countDown->setVisible(false);
	resetBestScore();

	_viewScore = 0;
	_targetScore = 0;

	schedule(schedule_selector(MoverGameplayUI::updateScoreView));

	return true;
}

void MoverGameplayUI::resetBestScore()
{
	_best_Score->setString(int2str(GameInfo::getInstance()->getHighScore()));
	_best_Holder->setContentSize(Size(145 + _best_Score->getBoundingBox().size.width, 34));
}

void MoverGameplayUI::awardScore(int playerID, int _score)
{
	BuildingScene::getInstance()->getPlayerLayer(playerID)->gainScore(_score);
}

void MoverGameplayUI::lockControl()
{
	_ui->setTouchEnabled(true);
	_button_Pause->setVisible(false);
}

void MoverGameplayUI::unlockControl()
{
	_button_Pause->setVisible(true);
	_countDown->setVisible(false);
	_ui->setTouchEnabled(false);
}

void MoverGameplayUI::countDown(int _count)
{
	_countDown->setVisible(true);
	_countDown->setScale(0);

	switch (_count)
	{
	default: break;
	case 1: _countDown->setSpriteFrame("game_daojishi_go.png"); PLAY_EFFECT(SOUND_EFFECT_COUNT_DOWN_0); break;
	case 2: _countDown->setSpriteFrame("game_daojishi_rd.png"); PLAY_EFFECT(SOUND_EFFECT_COUNT_DOWN_1); break;
	case 3: _countDown->setSpriteFrame("game_daojishi_2.png"); PLAY_EFFECT(SOUND_EFFECT_COUNT_DOWN_1); break;
	case 4: _countDown->setSpriteFrame("game_daojishi_3.png"); PLAY_EFFECT(SOUND_EFFECT_COUNT_DOWN_1); break;
	};

	_countDown->runAction(ScaleTo::create(0.2, 1));
}


//´´½¨Ñª²Û
void MoverGameplayUI::_addHpBar()
{
	//if (GameInfo::getInstance()->getModeCode() == "A1")
	//{
	//	auto p1 = Sprite::createWithSpriteFrameName("ui_p1.png");
	//	p1->setPosition(Vec2(745, 1014));
	//	addChild(p1,1);

	//	auto p2 = Sprite::createWithSpriteFrameName("ui_p2.png");
	//	p2->setPosition(Vec2(1175, 1014));
	//	addChild(p2,1);

	//	auto hp1 = HPBar::createWithFormat(true,true);
	//	hp1->setPosition(Vec2(600, 1014));
	//	m_hpBars.pushBack(hp1);
	//	addChild(hp1);

	//	auto hp2 = HPBar::createWithFormat(false, false);
	//	hp2->setPosition(Vec2(1320, 1014));
	//	m_hpBars.pushBack(hp2);
	//	addChild(hp2);

	//}
	//else if (GameInfo::getInstance()->getModeCode() == "M1")
	//{
	//	auto p1 = Sprite::createWithSpriteFrameName("ui_p1.png");
	//	p1->setPosition(Vec2(366, 995));
	//	addChild(p1, 1);

	//	auto p2 = Sprite::createWithSpriteFrameName("ui_p2.png");
	//	p2->setPosition(Vec2(1361, 995));
	//	addChild(p2, 1);

	//	auto hp1 = HPBar::createWithFormat(true, true);
	//	hp1->setPosition(Vec2(511, 995));
	//	m_hpBars.pushBack(hp1);
	//	addChild(hp1);

	//	auto hp2 = HPBar::createWithFormat(false, false);
	//	hp2->setPosition(Vec2(1506, 995));
	//	m_hpBars.pushBack(hp2);
	//	addChild(hp2);
	//}
	//else if (GameInfo::getInstance()->getModeCode() == "A2")
	//{
	//	auto p1 = Sprite::createWithSpriteFrameName("ui_p1.png");
	//	p1->setPosition(Vec2(215, 1014));
	//	addChild(p1,1);

	//	auto p2 = Sprite::createWithSpriteFrameName("ui_p2_red.png");
	//	p2->setPosition(Vec2(745, 1014));
	//	addChild(p2,1);

	//	auto p3 = Sprite::createWithSpriteFrameName("ui_p3.png");
	//	p3->setPosition(Vec2(1175, 1014));
	//	addChild(p3,1);

	//	auto p4 = Sprite::createWithSpriteFrameName("ui_p4.png");
	//	p4->setPosition(Vec2(1709, 1014));
	//	addChild(p4,1);

	//	auto hp1 = HPBar::createWithFormat(true, false);
	//	hp1->setPosition(Vec2(360, 1014));
	//	m_hpBars.pushBack(hp1);
	//	addChild(hp1);

	//	auto hp2 = HPBar::createWithFormat(true, true);
	//	hp2->setPosition(Vec2(600, 1014));
	//	m_hpBars.pushBack(hp2);
	//	addChild(hp2);

	//	auto hp3 = HPBar::createWithFormat(false, false);
	//	hp3->setPosition(Vec2(1320, 1014));
	//	m_hpBars.pushBack(hp3);
	//	addChild(hp3);

	//	auto hp4 = HPBar::createWithFormat(false, true);
	//	hp4->setPosition(Vec2(1560, 1014));
	//	m_hpBars.pushBack(hp4);
	//	addChild(hp4);

	//}
	//else
	{
		auto hp1 = HPBar::createWithFormat(true, true);
		hp1->setPosition(Vec2(1828, 1032));
		m_hpBars.pushBack(hp1);
		addChild(hp1);
	}

}


//******************************************************************************************************************************************************

bool MoverGamepauseUI::init()
{
	if (!Layer::init()) return false;

	_ui = ui::Layout::create();
	_ui->setContentSize(Director::getInstance()->getVisibleSize());
	_ui->setTouchEnabled(true);
	_ui->setBackGroundColorType(ui::Layout::BackGroundColorType::SOLID);
	_ui->setBackGroundColorOpacity(255 * 6 / 10);
	_ui->setBackGroundColor(Color3B::BLACK);

	addChild(_ui);

	Sprite * pauseTips = Sprite::createWithSpriteFrameName("ui_tips_pause.png");
	pauseTips->setPosition(Vec2(960, 780));
	_ui->addChild(pauseTips);

	_button_Retry = SpriteButton::create("ui_bt_restart.png");
	_button_Retry->setNormalSpriteFrame("ui_bt_restart_s.png",true);
	_button_Continue = SpriteButton::create("ui_bt_continue.png");
	_button_Continue->setNormalSpriteFrame("ui_bt_continue_s.png",true);
	_button_Home = SpriteButton::create("ui_bt_home.png");
	_button_Home->setNormalSpriteFrame("ui_bt_home_s.png",true);

	_ui->addChild(_button_Retry);
	_ui->addChild(_button_Continue);
	_ui->addChild(_button_Home);

	_button_Retry->setPosition(Vec2(1280, 394));
	_button_Continue->setPosition(Vec2(960, 394));
	_button_Home->setPosition(Vec2(638, 394));

	_button_Home->setLogicPosition(0,0);
	m_buttons.pushBackButton(_button_Home);

	_button_Continue->setLogicPosition(1, 0);
	m_buttons.pushBackButton(_button_Continue);

	_button_Retry->setLogicPosition(2, 0);
	m_buttons.pushBackButton(_button_Retry);

	m_buttons.setBackButtonCallbackButton(_button_Continue);
	m_buttons.setSelectedButton(_button_Continue);

	return true;
}


void MoverGamepauseUI::setLocked(bool lock)
{
	if (lock)
	{
		m_buttons.pauseKeyListener();
		_button_Retry->setEnabled(false);
		_button_Continue->setEnabled(false);
		_button_Home->setEnabled(false);
		setVisible(false);
	}
	else
	{
		m_buttons.resumeKeyListener();
		_button_Retry->setEnabled(true);
		_button_Continue->setEnabled(true);
		_button_Home->setEnabled(true);
		setVisible(true);
	}
}

//***********************************************************************************************************************

bool MoverResultUI::init()
{
	if (!Layer::init()) return false;

	//Size visibleSize = Director::getInstance()->getVisibleSize();
	//Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto _ui = ui::Layout::create();
	_ui->setContentSize(Director::getInstance()->getVisibleSize());
	_ui->setTouchEnabled(true);
	_ui->setBackGroundColorType(ui::Layout::BackGroundColorType::SOLID);
	_ui->setBackGroundColorOpacity(255 * 6 / 10);
	_ui->setBackGroundColor(Color3B::BLACK);
	addChild(_ui);

	_top_View = ui::Layout::create();
	_top_View->setContentSize(Director::getInstance()->getVisibleSize());
	addChild(_top_View);
	_back_View = ui::Layout::create();
	_back_View->setContentSize(Director::getInstance()->getVisibleSize());
	addChild(_back_View);

	//auto topPanel = Sprite::createWithSpriteFrameName("ui_gameover.png");
	//topPanel->setPosition(Vec2(960,780));
	//_top_View->addChild(topPanel);

	auto backPanel = Sprite::createWithSpriteFrameName("ui_panel_result.png");
	backPanel->setPosition(Vec2(960, 580));
	_back_View->addChild(backPanel);

	_button_Retry = SpriteButton::create("ui_bt_retry.png");
	_button_Retry->setNormalSpriteFrame("ui_bt_retry_s.png",true);
	_button_Home = SpriteButton::create("ui_bt_homepage.png");
	_button_Home->setNormalSpriteFrame("ui_bt_homepage_s.png", true);

	_button_Home->setPosition(Vec2(713, 370));
	_button_Retry->setPosition(Vec2(1080, 370));

	_back_View->addChild(_button_Home);
	_back_View->addChild(_button_Retry);

	_record_Score = Sprite::createWithSpriteFrameName("ui_new_record.png");
	_record_Level = Sprite::createWithSpriteFrameName("ui_new_record.png");
	_record_Goods = Sprite::createWithSpriteFrameName("ui_new_record.png");
	_record_Bomb = Sprite::createWithSpriteFrameName("ui_new_record.png");

	_back_View->addChild(_record_Score);
	_back_View->addChild(_record_Level);
	_back_View->addChild(_record_Goods);
	_back_View->addChild(_record_Bomb);

	_record_Level->setPosition(Vec2(990, 790));
	_record_Goods->setPosition(Vec2(990, 710));
	_record_Bomb->setPosition(Vec2(990, 630));
	_record_Score->setPosition(Vec2(990, 550));

	_levels = LabelAtlas::create("0123456789", MOVERS_BEST_SCORE_ATLAS, 20, 25, '0');
	_goods = LabelAtlas::create("0123456789", MOVERS_BEST_SCORE_ATLAS, 20, 25, '0');
	_bombs = LabelAtlas::create("0123456789", MOVERS_BEST_SCORE_ATLAS, 20, 25, '0');
	_score = LabelAtlas::create("0123456789", MOVERS_BEST_SCORE_ATLAS, 20, 25, '0');

	_levels->setScale(1.3f);
	_goods->setScale(1.3f);
	_bombs->setScale(1.3f);
	_score->setScale(1.3f);

	_back_View->addChild(_levels);
	_back_View->addChild(_goods);
	_back_View->addChild(_bombs);
	_back_View->addChild(_score);

	_levels->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	_goods->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	_bombs->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	_score->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);

	_levels->setPosition(Vec2(1074,790));
	_goods->setPosition(Vec2(1074,710));
	_bombs->setPosition(Vec2(1074,630));
	_score->setPosition(Vec2(1074, 550));

	setVisible(false);

	_top_View->setPositionY(3600);
	_back_View->setPositionY(3600);

	_button_Home->setLogicPosition(0,0);
	m_buttons.pushBackButton(_button_Home);

	_button_Retry->setLogicPosition(1, 0);
	m_buttons.pushBackButton(_button_Retry);

	return true;
}

void MoverResultUI::lockButtons()
{
	_button_Retry->setEnabled(false);
	_button_Home->setEnabled(false);
}

void MoverResultUI::popUpView()
{
	setVisible(true);

	_top_View->setPositionY(720);
	_back_View->setPositionY(-1080);
	_top_View->runAction(EaseElasticInOut::create(MoveTo::create(1.0, Vec2(0, 0))));
	_back_View->runAction(EaseElasticInOut::create(MoveTo::create(1.0, Vec2(0, 0))));

	_levels->setVisible(false);
	_goods->setVisible(false);
	_bombs->setVisible(false);
	_score->setVisible(false);

	_button_Retry->setVisible(false);
	_button_Home->setVisible(false);
	_record_Score->setVisible(false);
	_record_Level->setVisible(false);
	_record_Goods->setVisible(false);
	_record_Bomb->setVisible(false);

	_button_Retry->setEnabled(false);
	_button_Home->setEnabled(false);

	scheduleOnce(schedule_selector(MoverResultUI::delayViewResult), 1);
}

void MoverResultUI::hideDownView()
{
	_top_View->runAction(EaseElasticInOut::create(MoveTo::create(1.0, Vec2(0, 360))));
	_back_View->runAction(EaseElasticInOut::create(MoveTo::create(1.0, Vec2(0, -720))));
}

void MoverResultUI::delayViewResult(float dt)
{
	_viewValue = 0;
	_targetValue = GameInfo::getInstance()->getCurrentFloor();
	//_toAdd = 1 + (_targetValue/20);
	_levels->setString("0");
	_levels->setVisible(true);
	schedule(schedule_selector(MoverResultUI::updateLevels));
	schedule(schedule_selector(MoverResultUI::scoreEffectLoop), 0.04);
}

void MoverResultUI::updateLevels(float dt)
{
	if (_viewValue < _targetValue)
	{
		_viewValue += (_targetValue - _viewValue) / 20;
		_levels->setString(int2str(++_viewValue));
	}
	else
	{
		unschedule(schedule_selector(MoverResultUI::updateLevels));
		_levels->setString(int2str(_targetValue));

		_viewValue = 0;
		_targetValue = GameInfo::getInstance()->getGoodsCatched();
		_goods->setString("0");
		_goods->setVisible(true);
		schedule(schedule_selector(MoverResultUI::updateGoods));

		if (GameInfo::getInstance()->checkHighFloor()) _record_Level->setVisible(true);
	}
}

void MoverResultUI::scoreEffectLoop(float dt)
{
	PLAY_EFFECT(SOUND_EFFECT_SCORE);
}

void MoverResultUI::updateGoods(float dt)
{
	if (_viewValue < _targetValue)
	{
		_viewValue += (_targetValue - _viewValue) / 20;
		_goods->setString(int2str(++_viewValue));
		//PLAY_EFFECT( SOUND_EFFECT_SCORE );
	}
	else
	{
		unschedule(schedule_selector(MoverResultUI::updateGoods));
		_goods->setString(int2str(_targetValue));

		_viewValue = 0;
		_targetValue = GameInfo::getInstance()->getMissedBomb();
		//_toAdd = 1 + (_targetValue/20);
		_bombs->setString("0");
		_bombs->setVisible(true);
		schedule(schedule_selector(MoverResultUI::updateBombs));

		if (GameInfo::getInstance()->checkHighGoods()) _record_Goods->setVisible(true);
	}
}

void MoverResultUI::updateBombs(float dt)
{
	if (_viewValue < _targetValue)
	{
		_viewValue += (_targetValue - _viewValue) / 20;
		_bombs->setString(int2str(++_viewValue));
		//PLAY_EFFECT( SOUND_EFFECT_SCORE );
	}
	else
	{
		unschedule(schedule_selector(MoverResultUI::updateBombs));
		_bombs->setString(int2str(_targetValue));

		_viewValue = 0;

		_targetValue = GameInfo::getInstance()->getCurrentScore();
		//_toAdd = 1 + (_targetValue/20);
		_score->setString("0");
		_score->setVisible(true);
		schedule(schedule_selector(MoverResultUI::updateScore));

		if (GameInfo::getInstance()->checkHighBomb()) _record_Bomb->setVisible(true);
	}
}

void MoverResultUI::updateScore(float dt)
{
	if (_viewValue < _targetValue)
	{
		_viewValue += (_targetValue - _viewValue) / 20;
		_score->setString(int2str(++_viewValue));
	}
	else
	{
		unschedule(schedule_selector(MoverResultUI::scoreEffectLoop));
		unschedule(schedule_selector(MoverResultUI::updateScore));
		_score->setString(int2str(_targetValue));

		if (GameInfo::getInstance()->checkHighScore()) _record_Score->setVisible(true);
		//scheduleOnce( schedule_selector( MoverResultUI::delayViewAd ) , 0.1*(float)random( 4 , 32 ) );

		_button_Retry->setVisible(true);
		_button_Retry->setEnabled(true);
		_button_Home->setVisible(true);
		_button_Home->setEnabled(true);
		m_buttons.resumeKeyListener();
		m_buttons.setSelectedButton(_button_Retry);
		m_buttons.setBackButtonCallbackButton(_button_Home);
	}
}

