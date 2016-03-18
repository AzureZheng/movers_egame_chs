#include "KeyButtonsPackage.h"

//创建
KeyButtonsPackage::KeyButtonsPackage()
{
	init();
}


KeyButtonsPackage::KeyButtonsPackage(const Vector<SpriteButton*> & buttons, SpriteButton * firstButton)
{
	init();
	pushBackButton(buttons);
	setSelectedButton(firstButton);
}


//析构
KeyButtonsPackage::~KeyButtonsPackage()
{
	Director::getInstance()->getEventDispatcher()->removeEventListener(m_customKeyListener);
}


//初始化
void KeyButtonsPackage::init()
{
	//用户键盘监听器
	m_customKeyListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener("CustomKeyboard", std::bind(&KeyButtonsPackage::_onCustomKeyPress,this, std::placeholders::_1));

	//当前选中的按钮
	m_selectedButton = nullptr;

	//返回键所对应的按钮
	m_backButton = nullptr;

	//按钮组是否首位相连
	m_isButtonsDirectionLooped = true;

	//是否暂停监听器
	m_isPauseListener = true;

	//按键附加回调
	m_buttonExtraCallback = [](KeyButtonsPackage*, CustomKeyEvent*){};

	//标记
	m_tag = -1;

	//按钮回调延时
	m_buttonCallbackDelayTime = 0.15f;
}


//获取当前选择的按钮
SpriteButton * KeyButtonsPackage::getSelectedButton()
{
	return m_selectedButton;
}


//将一个按钮标记为选择状态
void KeyButtonsPackage::setSelectedButton(SpriteButton * button)
{
	if (m_selectedButton == button)
	{
		return;
	}

	if (m_selectedButton)
	{
		m_selectedButton->setSelectedStatus(false);
	}
	
	m_selectedButton = button;

	if (m_selectedButton)
	{
		m_selectedButton->setSelectedStatus(true);
	}
}


//添加一个按钮
void KeyButtonsPackage::pushBackButton(SpriteButton * button)
{
	m_buttons.pushBack(button);
}


//移除一个按钮
void KeyButtonsPackage::removeButton(SpriteButton * button)
{
	if (button == m_selectedButton)
	{
		setSelectedButton(nullptr);
	}

	m_buttons.eraseObject(button);
}


//添加一组按钮
void KeyButtonsPackage::pushBackButton(const Vector<SpriteButton*> & buttons)
{
	m_buttons.pushBack(buttons);
}


//按名字查找一个按钮
SpriteButton * KeyButtonsPackage::findButtonByName(const std::string & name)
{
	for (auto & i:m_buttons)
	{
		if (i->getName() == name)
		{
			return i;
		}
	}
	return nullptr;
}


//清空所有按钮的选择状态
void KeyButtonsPackage::clearAllButtonsSelectedStatus()
{
	for (auto & i:m_buttons)
	{
		i->setSelectedStatus(false);
	}
	m_selectedButton = nullptr;
}


//暂停键盘监听
void KeyButtonsPackage::pauseKeyListener()
{
	m_isPauseListener = true;
}


//恢复监听
void KeyButtonsPackage::resumeKeyListener()
{
	m_isPauseListener = false;
}

//检查是否暂停监听
bool KeyButtonsPackage::isPausedKeyListener()
{
	return m_isPauseListener;
}

//设置按键附加回调
void KeyButtonsPackage::setButtonExtraCallback(const std::function<void(KeyButtonsPackage*, CustomKeyEvent*)> & buttonExtraCallback)
{
	m_buttonExtraCallback = buttonExtraCallback;
}


//设置是否允许按钮首尾相连
void KeyButtonsPackage::setButtonsDirectionLooped(bool enable)
{
	m_isButtonsDirectionLooped = enable;
}


//用户键盘事件被触发回调
void KeyButtonsPackage::_onCustomKeyPress(EventCustom * e)
{
	auto nd = (CustomKeyEvent*)e->getUserData();

	if (m_isPauseListener || !nd->getKeyAction())
	{
		m_buttonExtraCallback(this,nd);
		return;
	}

	auto keycode = nd->getKeyCode();

	SpriteButton * nearest = nullptr;

	switch (keycode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	case cocos2d::EventKeyboard::KeyCode::KEY_DPAD_RIGHT:
		if (m_selectedButton)
		{
			nearest = m_selectedButton->getNearestButtonWithDirection(m_buttons, SpriteButton::Direction::RIGHT, m_isButtonsDirectionLooped);
		}
		else if (!m_buttons.empty())
		{
			setSelectedButton(m_buttons.front());
		}
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case cocos2d::EventKeyboard::KeyCode::KEY_DPAD_LEFT:
		if (m_selectedButton)
		{
			nearest = m_selectedButton->getNearestButtonWithDirection(m_buttons, SpriteButton::Direction::LEFT, m_isButtonsDirectionLooped);
		}
		else if (!m_buttons.empty())
		{
			setSelectedButton(m_buttons.back());
		}
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
	case cocos2d::EventKeyboard::KeyCode::KEY_DPAD_UP:
		if (m_selectedButton)
		{
			nearest = m_selectedButton->getNearestButtonWithDirection(m_buttons, SpriteButton::Direction::UP, m_isButtonsDirectionLooped);
		}
		else if (!m_buttons.empty())
		{
			setSelectedButton(m_buttons.back());
		}
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	case cocos2d::EventKeyboard::KeyCode::KEY_DPAD_DOWN:
		if (m_selectedButton)
		{
			nearest = m_selectedButton->getNearestButtonWithDirection(m_buttons, SpriteButton::Direction::DOWN, m_isButtonsDirectionLooped);
		}
		else if (!m_buttons.empty())
		{
			setSelectedButton(m_buttons.front());
		}
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_DPAD_CENTER:
	case cocos2d::EventKeyboard::KeyCode::KEY_ENTER:
	case cocos2d::EventKeyboard::KeyCode::KEY_KP_ENTER:
		if (m_selectedButton)
		{
			m_selectedButton->activeButton(m_buttonCallbackDelayTime);
		}
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_BACK:
		if (m_backButton)
		{
			m_backButton->activeButton(m_buttonCallbackDelayTime);
		}
		break;
	}


	if (nearest && nearest != m_selectedButton)
	{
		m_selectedButton->setSelectedStatus(false);
		m_selectedButton = nearest;
		m_selectedButton->setSelectedStatus(true);
	}

	m_buttonExtraCallback(this,nd);
}


//获取按钮组
const Vector<SpriteButton*> & KeyButtonsPackage::getButtons()
{
	return m_buttons;
}


//获取标记
int KeyButtonsPackage::getTag()
{
	return m_tag;
}


//设置标记
void KeyButtonsPackage::setTag(int tag)
{
	m_tag = tag;
}


//设置按钮回调延时
void KeyButtonsPackage::setButtonCallbackDelayTime(float time)
{
	m_buttonCallbackDelayTime = time;
}


//锁定/解锁按钮组
void KeyButtonsPackage::setButtonsEnabled(bool enable)
{
	for (auto & i:m_buttons)
	{
		i->setEnabled(enable);
	}
}


//设置返回键所调用的按键
void KeyButtonsPackage::setBackButtonCallbackButton(SpriteButton * bt)
{
	m_backButton = bt;
}
