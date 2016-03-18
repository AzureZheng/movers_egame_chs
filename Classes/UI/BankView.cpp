#include "BankView.h"
#include "FilePathDefine.h"
#include "SDKManage/EgamePay.h"
#include "SDKManage/Umeng.h"

//初始化
bool BankView::init()
{
	if (!Layer::init())
	{
		return false;
	}

	m_visibleSize = Director::getInstance()->getVisibleSize();

	setContentSize(m_visibleSize);

	m_isInMoreChanceView = false;

	m_isInShopView = false;

	m_isInUnlockView = false;

	m_diamond = 0;

	//支付面额
	m_payIndex = 0;

	//支付中
	m_inPay = false;

	_addMoreChance();
	_addUnlockMode();

	m_blackBack = ui::Layout::create();
	m_blackBack->setContentSize(m_visibleSize);
	m_blackBack->setBackGroundColorType(ui::Layout::BackGroundColorType::SOLID);
	m_blackBack->setBackGroundColor(Color3B::BLACK);
	m_blackBack->setBackGroundColorOpacity(255 * 6 / 10);
	m_blackBack->setTouchEnabled(true);
	addChild(m_blackBack, 1);
	setBlackBackVisible(false);

	_addShop();

	_refreshDiamond();

	return true;
}

//激活/隐藏商店UI
void BankView::activeShopView(bool active)
{
	if (active == m_isInShopView)
	{
		return;
	}

	m_isInShopView = active;

	m_shopView->stopAllActions();

	if (active)
	{
		_refreshDiamond();
		m_buttonsForShop.setSelectedButton(m_buyDiamond[0]);
		m_shopView->runAction(Sequence::create(EaseElasticOut::create(MoveTo::create(0.5f, Vec2(0, 0))), CallFunc::create([this]()
		{
			m_buttonsForShop.setButtonsEnabled(true);
			m_buttonsForShop.resumeKeyListener();
		}), nullptr));
	}
	else
	{
		m_buttonsForShop.setButtonsEnabled(false);
		m_buttonsForShop.pauseKeyListener();
		m_shopView->runAction(MoveTo::create(0.1f, Vec2(0, m_visibleSize.height)));
	}
}

//激活/隐藏再来一次UI
void BankView::activeMoreChanceView(bool active)
{
	if (active == m_isInMoreChanceView)
	{
		return;
	}

	m_isInMoreChanceView = active;

	m_moreChanceView->stopAllActions();

	if (active)
	{
		_refreshDiamond();
		m_moreChanceView->setScale(0);
		m_moreChanceView->setVisible(true);
		m_moreChanceView->runAction(Sequence::create(
			EaseElasticOut::create(ScaleTo::create(0.5f,1)),
			CallFunc::create([this](){
			m_buttonsForMoreChance.setButtonsEnabled(true);
			m_buttonsForMoreChance.resumeKeyListener();
		}),nullptr));
	}
	else
	{
		m_buttonsForMoreChance.setButtonsEnabled(false);
		m_buttonsForMoreChance.pauseKeyListener();
		m_moreChanceView->runAction(Sequence::create(
			ScaleTo::create(0.1f, 0),
			CallFunc::create(CC_CALLBACK_0(Node::setVisible, m_moreChanceView,false)), nullptr));
	}
}

//激活/隐藏模式解锁UI
void BankView::activeUnlockView(bool active)
{
	if (active == m_isInUnlockView)
	{
		return;
	}

	m_isInUnlockView = active;

	m_unlockView->stopAllActions();

	if (active)
	{
		m_unlockView->setScale(0);
		m_unlockView->setVisible(true);
		m_unlockView->runAction(Sequence::create(
			EaseElasticOut::create(ScaleTo::create(0.5f, 1)),
			CallFunc::create([this](){
			m_buttonsForUnlockMode.setButtonsEnabled(true);
			m_buttonsForUnlockMode.resumeKeyListener();
		}), nullptr));
	}
	else
	{
		m_buttonsForUnlockMode.setButtonsEnabled(false);
		m_buttonsForUnlockMode.pauseKeyListener();
		m_unlockView->runAction(Sequence::create(
			ScaleTo::create(0.1f, 0),
			CallFunc::create(CC_CALLBACK_0(Node::setVisible, m_unlockView, false)), nullptr));
	}
}

//获取返回按钮
SpriteButton * BankView::getButtonBack()
{
	return m_buttonBack;
}

//获取解锁取消按钮
SpriteButton * BankView::getButtonUnlockCancel()
{
	return m_buttonUnlockCancel;
}

//获取复活取消按钮
SpriteButton * BankView::getButtonHealCancel()
{
	return m_buttonHealCancel;
}

//获取复活按钮
SpriteButton * BankView::getButtonMoreChance()
{
	return m_buttonHeal;
}

//显示/隐藏黑底
void BankView::setBlackBackVisible(bool isVisible)
{
	m_blackBack->setVisible(isVisible);
}


//创建商店
void BankView::_addShop()
{
	m_shopView = Layer::create();
	addChild(m_shopView,2);

	m_shopView->setContentSize(m_visibleSize);

	m_shopView->setPosition(Vec2(0,m_visibleSize.height));

	auto panel = Sprite::createWithSpriteFrameName("ui_panel_shop.png");
	panel->setPosition(Vec2(960,555));
	m_shopView->addChild(panel,0);

	m_buyDiamond[0] = SpriteButton::create("ui_bt_d100.png");
	m_buyDiamond[0]->setNormalSpriteFrame("ui_bt_d100_s.png", true);
	m_buyDiamond[0]->setLogicPosition(0,3);
	m_buyDiamond[0]->setPosition(Vec2(956,725));
	m_buyDiamond[0]->setCallback(CC_CALLBACK_1(BankView::_buyDiamond,this,1));
	m_buyDiamond[0]->setScaleDiff(0.05f);
	m_shopView->addChild(m_buyDiamond[0],1);
	m_buttonsForShop.pushBackButton(m_buyDiamond[0]);

	m_buyDiamond[1] = SpriteButton::create("ui_bt_d500.png");
	m_buyDiamond[1]->setNormalSpriteFrame("ui_bt_d500_s.png", true);
	m_buyDiamond[1]->setLogicPosition(0, 2);
	m_buyDiamond[1]->setPosition(Vec2(956, 575));
	m_buyDiamond[1]->setCallback(CC_CALLBACK_1(BankView::_buyDiamond, this, 2));
	m_buyDiamond[1]->setScaleDiff(0.05f);
	m_shopView->addChild(m_buyDiamond[1], 1);
	m_buttonsForShop.pushBackButton(m_buyDiamond[1]);

	m_buyDiamond[2] = SpriteButton::create("ui_bt_d1000.png");
	m_buyDiamond[2]->setNormalSpriteFrame("ui_bt_d1000_s.png", true);
	m_buyDiamond[2]->setLogicPosition(0, 1);
	m_buyDiamond[2]->setPosition(Vec2(956, 424));
	m_buyDiamond[2]->setCallback(CC_CALLBACK_1(BankView::_buyDiamond, this, 3));
	m_buyDiamond[2]->setScaleDiff(0.05f);
	m_shopView->addChild(m_buyDiamond[2], 1);
	m_buttonsForShop.pushBackButton(m_buyDiamond[2]);

	m_buttonBack = SpriteButton::create("ui_bt_back.png");
	m_buttonBack->setNormalSpriteFrame("ui_bt_back_s.png",true);
	m_buttonBack->setLogicPosition(0,0);
	m_buttonBack->setPosition(Vec2(1230, 247));
	m_shopView->addChild(m_buttonBack, 1);
	m_buttonsForShop.pushBackButton(m_buttonBack);

	m_shopDiamondView = LabelAtlas::create("0123456789","UI/History_High_Score.png",20,24,'0');
	m_shopDiamondView->setString("0");
	m_shopDiamondView->setScale(1.4f);
	m_shopDiamondView->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	m_shopDiamondView->setPosition(Vec2(862,251));
	m_shopView->addChild(m_shopDiamondView, 1);

	m_buttonsForShop.setSelectedButton(m_buyDiamond[0]);
	m_buttonsForShop.setBackButtonCallbackButton(m_buttonBack);
}


//创建再来一次
void BankView::_addMoreChance()
{
	m_moreChanceView = Layer::create();
	addChild(m_moreChanceView, 0);

	m_moreChanceView->setContentSize(m_visibleSize);

	auto panel = Sprite::createWithSpriteFrameName("ui_panel_more_chance.png");
	panel->setPosition(Vec2(953, 630));
	m_moreChanceView->addChild(panel, 0);

	m_buttonHeal = SpriteButton::create("ui_bt_heal.png");
	m_buttonHeal->setNormalSpriteFrame("ui_bt_heal_s.png", true);
	m_buttonHeal->setLogicPosition(0, 0);
	m_buttonHeal->setPosition(Vec2(759, 569));
	m_moreChanceView->addChild(m_buttonHeal, 1);
	m_buttonsForMoreChance.pushBackButton(m_buttonHeal);

	m_buttonHealCancel = SpriteButton::create("ui_bt_cancel.png");
	m_buttonHealCancel->setNormalSpriteFrame("ui_bt_cancel_s.png", true);
	m_buttonHealCancel->setLogicPosition(1, 0);
	m_buttonHealCancel->setPosition(Vec2(1143, 569));
	m_moreChanceView->addChild(m_buttonHealCancel, 1);
	m_buttonsForMoreChance.pushBackButton(m_buttonHealCancel);

	m_healDiamondView = LabelAtlas::create("0123456789", "UI/History_High_Score.png", 20, 24, '0');
	m_healDiamondView->setString("0");
	m_healDiamondView->setScale(1.4f);
	m_healDiamondView->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	m_healDiamondView->setPosition(Vec2(882, 390));
	m_moreChanceView->addChild(m_healDiamondView, 1);

	m_buttonsForMoreChance.setSelectedButton(m_buttonHeal);
	m_buttonsForMoreChance.setBackButtonCallbackButton(m_buttonHealCancel);

	m_moreChanceView->setVisible(false);
}


//刷新钻石显示
void BankView::_refreshDiamond()
{
	m_diamond = UserDefault::getInstance()->getIntegerForKey("Diamond",0);

	m_healDiamondView->setString(Value(m_diamond).asString());
	m_shopDiamondView->setString(Value(m_diamond).asString());
}


//创建解锁模式
void BankView::_addUnlockMode()
{
	m_unlockView = Layer::create();
	addChild(m_unlockView, 0);

	m_unlockView->setContentSize(m_visibleSize);

	auto panel = Sprite::createWithSpriteFrameName("ui_panel_unlock.png");
	panel->setPosition(Vec2(1362, 555));
	m_unlockView->addChild(panel, 0);

	m_buttonUnlock = SpriteButton::create("ui_bt_unlock.png");
	m_buttonUnlock->setNormalSpriteFrame("ui_bt_unlock_s.png", true);
	m_buttonUnlock->setLogicPosition(0, 0);
	m_buttonUnlock->setPosition(Vec2(1182 - 20, 354 + 30));
	m_unlockView->addChild(m_buttonUnlock, 1);
	m_buttonsForUnlockMode.pushBackButton(m_buttonUnlock);

	m_buttonUnlockCancel = SpriteButton::create("ui_bt_cancel.png");
	m_buttonUnlockCancel->setNormalSpriteFrame("ui_bt_cancel_s.png", true);
	m_buttonUnlockCancel->setLogicPosition(1, 0);
	m_buttonUnlockCancel->setPosition(Vec2(1575 - 20, 354 + 30));
	m_unlockView->addChild(m_buttonUnlockCancel, 1);
	m_buttonsForUnlockMode.pushBackButton(m_buttonUnlockCancel);

	m_buttonsForUnlockMode.setSelectedButton(m_buttonUnlock);
	m_buttonsForUnlockMode.setBackButtonCallbackButton(m_buttonUnlockCancel);

	m_unlockView->setVisible(false);
}


//钻石按钮回调
void BankView::_buyDiamond(Ref * ref, int index)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	if(m_inPay) return;
	m_inPay = true;

	//开启支付结果检查
	m_payIndex = index;
	schedule(schedule_selector(BankView::_checkPayResult));
	EgamePay::callPay(index);
#endif
}


//支付结果检查
void BankView::_checkPayResult(float dt)
{
	auto r = EgamePay::getPayResult();
	if (r == 0)
	{
		cocos2d::log("Cocos: Pay Failed!");
		unschedule(schedule_selector(BankView::_checkPayResult));
		m_inPay = false;
	}
	else if (r == 1)
	{
		cocos2d::log("Cocos: Pay Finished!");
		unschedule(schedule_selector(BankView::_checkPayResult));

		auto ud = UserDefault::getInstance();
		_refreshDiamond();

		if (m_payIndex == 1)
		{
			ud->setIntegerForKey("Diamond",m_diamond + 100);
			Umeng::pay(1,100,7);
		}
		else if (m_payIndex == 2)
		{
			ud->setIntegerForKey("Diamond", m_diamond + 500);
			Umeng::pay(5, 500, 7);
		}
		else if (m_payIndex == 3)
		{
			ud->setIntegerForKey("Diamond", m_diamond + 1000);
			Umeng::pay(10, 1000, 7);
		}

		_refreshDiamond();
		m_inPay = false;
	}
}


//获取是否在显示商店视图
bool BankView::isInShopView()
{
	return m_isInShopView;
}


//获取是否在显示再来一次视图
bool BankView::isInMoreChanceView()
{
	return m_isInMoreChanceView;
}


//检查是否已解锁模式
bool BankView::_checkUnlockMode()
{
	return UserDefault::getInstance()->getBoolForKey("MultiMode",false);
}


//解锁模式
bool BankView::_unlockMode()
{
	UserDefault::getInstance()->setBoolForKey("MultiMode", true);

	return UserDefault::getInstance()->getBoolForKey("MultiMode", false);
}


//设置黑底层级
void BankView::setBlackBackZOrder(int zOrder)
{
	m_blackBack->setLocalZOrder(zOrder);
}


//获取解锁按钮
SpriteButton * BankView::getButtonUnlock()
{
	return m_buttonUnlock;
}


//获取钻石
int BankView::getDiamond()
{
	_refreshDiamond();
	return m_diamond;
}


//显示隐藏二级Shop
void BankView::showHideSubShop(bool show)
{
	if (show)
	{
		m_buttonsForMoreChance.pauseKeyListener();
		m_buttonsForUnlockMode.pauseKeyListener();
		setBlackBackZOrder(1);
		activeShopView(true);
	}
	else
	{
		setBlackBackZOrder(-1);
		activeShopView(false);
		runAction(Sequence::create(DelayTime::create(0.1f), CallFunc::create([this]()
		{
			if (m_isInUnlockView)
			{
				m_buttonsForUnlockMode.resumeKeyListener();
			}
			else
			{
				m_buttonsForMoreChance.resumeKeyListener();
			}
		}), nullptr));
	}
}


//返回商店是否在二级模式打开
bool BankView::isSubShop()
{
	return m_isInMoreChanceView || m_isInUnlockView;
}
