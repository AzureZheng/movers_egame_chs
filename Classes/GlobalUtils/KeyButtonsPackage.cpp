#include "KeyButtonsPackage.h"

//����
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


//����
KeyButtonsPackage::~KeyButtonsPackage()
{
	Director::getInstance()->getEventDispatcher()->removeEventListener(m_customKeyListener);
}


//��ʼ��
void KeyButtonsPackage::init()
{
	//�û����̼�����
	m_customKeyListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener("CustomKeyboard", std::bind(&KeyButtonsPackage::_onCustomKeyPress,this, std::placeholders::_1));

	//��ǰѡ�еİ�ť
	m_selectedButton = nullptr;

	//���ؼ�����Ӧ�İ�ť
	m_backButton = nullptr;

	//��ť���Ƿ���λ����
	m_isButtonsDirectionLooped = true;

	//�Ƿ���ͣ������
	m_isPauseListener = true;

	//�������ӻص�
	m_buttonExtraCallback = [](KeyButtonsPackage*, CustomKeyEvent*){};

	//���
	m_tag = -1;

	//��ť�ص���ʱ
	m_buttonCallbackDelayTime = 0.15f;
}


//��ȡ��ǰѡ��İ�ť
SpriteButton * KeyButtonsPackage::getSelectedButton()
{
	return m_selectedButton;
}


//��һ����ť���Ϊѡ��״̬
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


//���һ����ť
void KeyButtonsPackage::pushBackButton(SpriteButton * button)
{
	m_buttons.pushBack(button);
}


//�Ƴ�һ����ť
void KeyButtonsPackage::removeButton(SpriteButton * button)
{
	if (button == m_selectedButton)
	{
		setSelectedButton(nullptr);
	}

	m_buttons.eraseObject(button);
}


//���һ�鰴ť
void KeyButtonsPackage::pushBackButton(const Vector<SpriteButton*> & buttons)
{
	m_buttons.pushBack(buttons);
}


//�����ֲ���һ����ť
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


//������а�ť��ѡ��״̬
void KeyButtonsPackage::clearAllButtonsSelectedStatus()
{
	for (auto & i:m_buttons)
	{
		i->setSelectedStatus(false);
	}
	m_selectedButton = nullptr;
}


//��ͣ���̼���
void KeyButtonsPackage::pauseKeyListener()
{
	m_isPauseListener = true;
}


//�ָ�����
void KeyButtonsPackage::resumeKeyListener()
{
	m_isPauseListener = false;
}

//����Ƿ���ͣ����
bool KeyButtonsPackage::isPausedKeyListener()
{
	return m_isPauseListener;
}

//���ð������ӻص�
void KeyButtonsPackage::setButtonExtraCallback(const std::function<void(KeyButtonsPackage*, CustomKeyEvent*)> & buttonExtraCallback)
{
	m_buttonExtraCallback = buttonExtraCallback;
}


//�����Ƿ�����ť��β����
void KeyButtonsPackage::setButtonsDirectionLooped(bool enable)
{
	m_isButtonsDirectionLooped = enable;
}


//�û������¼��������ص�
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


//��ȡ��ť��
const Vector<SpriteButton*> & KeyButtonsPackage::getButtons()
{
	return m_buttons;
}


//��ȡ���
int KeyButtonsPackage::getTag()
{
	return m_tag;
}


//���ñ��
void KeyButtonsPackage::setTag(int tag)
{
	m_tag = tag;
}


//���ð�ť�ص���ʱ
void KeyButtonsPackage::setButtonCallbackDelayTime(float time)
{
	m_buttonCallbackDelayTime = time;
}


//����/������ť��
void KeyButtonsPackage::setButtonsEnabled(bool enable)
{
	for (auto & i:m_buttons)
	{
		i->setEnabled(enable);
	}
}


//���÷��ؼ������õİ���
void KeyButtonsPackage::setBackButtonCallbackButton(SpriteButton * bt)
{
	m_backButton = bt;
}
