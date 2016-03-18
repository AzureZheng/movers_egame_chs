#include "ExitGameUI.h"

//初始化
bool ExitGameUI::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();

	setContentSize(visibleSize);

	m_blackBack = ui::Layout::create();
	m_blackBack->setContentSize(visibleSize);
	m_blackBack->setBackGroundColorType(ui::Layout::BackGroundColorType::SOLID);
	m_blackBack->setBackGroundColor(Color3B::BLACK);
	m_blackBack->setBackGroundColorOpacity(255 * 6 / 10);
	m_blackBack->setTouchEnabled(true);
	addChild(m_blackBack, 0);


	m_exitPanelView = Layer::create();
	addChild(m_exitPanelView, 1);

	m_exitPanelView->setContentSize(visibleSize);

	auto panel = Sprite::createWithSpriteFrameName("ui_panel_exit.png");
	panel->setPosition(Vec2(953, 630));
	m_exitPanelView->addChild(panel, 0);

	m_buttonExit = SpriteButton::create("ui_bt_comfirm.png");
	m_buttonExit->setNormalSpriteFrame("ui_bt_comfirm_s.png", true);
	m_buttonExit->setLogicPosition(0, 0);
	m_buttonExit->setPosition(Vec2(759, 569));
	m_buttonExit->setCallback(CC_CALLBACK_1(ExitGameUI::_exitGameCallback,this));
	m_exitPanelView->addChild(m_buttonExit, 1);
	m_buttons.pushBackButton(m_buttonExit);

	m_buttonCancel = SpriteButton::create("ui_bt_cancel_g.png");
	m_buttonCancel->setNormalSpriteFrame("ui_bt_cancel_g_s.png", true);
	m_buttonCancel->setLogicPosition(1, 0);
	m_buttonCancel->setPosition(Vec2(1143, 569));
	m_exitPanelView->addChild(m_buttonCancel, 1);
	m_buttons.pushBackButton(m_buttonCancel);

	m_buttons.setSelectedButton(m_buttonCancel);
	m_buttons.setBackButtonCallbackButton(m_buttonCancel);
	m_buttons.setButtonsEnabled(false);
	m_isActived = false;

	m_exitPanelView->setVisible(false);
	setVisible(false);
	return true;
}


//显示/隐藏界面
void ExitGameUI::activePanel(bool active)
{
	if (active == m_isActived)
	{
		return;
	}

	m_isActived = active;

	m_exitPanelView->stopAllActions();

	if (active)
	{
		setVisible(true);
		m_exitPanelView->setScale(0);
		m_exitPanelView->setVisible(true);
		m_exitPanelView->runAction(Sequence::create(
			EaseElasticOut::create(ScaleTo::create(0.5f, 1)),
			CallFunc::create([this](){
			m_buttons.setButtonsEnabled(true);
			m_buttons.resumeKeyListener();
		}), nullptr));
	}
	else
	{
		m_buttons.setButtonsEnabled(false);
		m_buttons.pauseKeyListener();
		m_exitPanelView->runAction(Sequence::create(
			ScaleTo::create(0.1f, 0),
			CallFunc::create(CC_CALLBACK_0(Node::setVisible, m_exitPanelView, false)), 
			CallFunc::create(CC_CALLBACK_0(Node::setVisible, this, false)),nullptr));
	}
}


//获取取消按钮
SpriteButton * ExitGameUI::getButtonCancel()
{
	return m_buttonCancel;
}


//退出游戏回调
void ExitGameUI::_exitGameCallback(Ref * ref)
{
	Director::getInstance()->end();
}
