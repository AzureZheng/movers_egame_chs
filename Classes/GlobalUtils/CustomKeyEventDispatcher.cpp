#include "CustomKeyEventDispatcher.h"



bool CustomKeyEventDispatcher::init()
{
	if (!Node::init())
	{
		return false;
	}

	//�Ƿ���ͣ�¼��ɷ�
	m_isPauseDispatch = false;

	//�Ƿ�ֻ�ɷ������¼�
	m_isOnlyDispatchPress = true;

	//�Ƿ���������ʱ����Ϊ����
	m_isEnableAutoRelease = false;

	//����ʱ��������������Ϊ����
	m_timeForAutoRelease = 0.1f;

	auto kl = EventListenerKeyboard::create();

	kl->onKeyPressed = CC_CALLBACK_2(CustomKeyEventDispatcher::onKeyPress,this);
	kl->onKeyReleased = CC_CALLBACK_2(CustomKeyEventDispatcher::onKeyRelease, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(kl,this);

	scheduleUpdate();
	return true;
}


void CustomKeyEventDispatcher::onExit()
{
	Node::onExit();
	clearEventListener();
}


//��ͣ�¼��ɷ�
void CustomKeyEventDispatcher::pauseDispatch()
{
	m_isPauseDispatch = true;
}

//�ָ��¼��ɷ�
void CustomKeyEventDispatcher::resumeDispatch()
{
	m_isPauseDispatch = false;
}

//����������ʱ����ʱ��
void CustomKeyEventDispatcher::setAutoReleaseTimeDelay(float dt)
{
	m_timeForAutoRelease = dt;
}

//�Ƿ���������ʱ����Ϊ��������
void CustomKeyEventDispatcher::setAutoReleaseEnable(bool enable)
{
	if (enable == m_isEnableAutoRelease)
	{
		return;
	}

	m_isEnableAutoRelease = enable;

	m_buttonTimerList.clear();
}


//���»ص�
void CustomKeyEventDispatcher::onKeyPress(EventKeyboard::KeyCode keycode, Event * e)
{
	if (m_isPauseDispatch)
	{
		return;
	}

	if (m_isEnableAutoRelease)
	{
		auto iter = m_buttonTimerList.find((int)keycode);
		if (iter != m_buttonTimerList.end())
		{
			iter->second = m_timeForAutoRelease;
			return;
		}

		m_buttonTimerList.insert(std::make_pair((int)keycode, m_timeForAutoRelease));
	}

	dispatchPressEvent(keycode);
}


//�ͷŻص�
void CustomKeyEventDispatcher::onKeyRelease(EventKeyboard::KeyCode keycode, Event * e)
{
	if (m_isPauseDispatch || m_isOnlyDispatchPress || m_isEnableAutoRelease)
	{
		return;
	}

	dispatchReleaseEvent(keycode);
}


//�ɷ����������¼�
void CustomKeyEventDispatcher::dispatchPressEvent(EventKeyboard::KeyCode keycode)
{
	CustomKeyEvent * e = CustomKeyEvent::create(keycode,true,this);

	m_eventList.pushBack(e);

	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("CustomKeyboard", e);
}


//�ɷ������ͷ��¼�
void CustomKeyEventDispatcher::dispatchReleaseEvent(EventKeyboard::KeyCode keycode)
{
	CustomKeyEvent * e = CustomKeyEvent::create(keycode, false,this);

	m_eventList.pushBack(e);

	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("CustomKeyboard", e);
}


//�����¼�����
void CustomKeyEventDispatcher::update(float dt)
{
	//�����¼���������
	for (auto iter = m_eventList.begin(); iter != m_eventList.end();)
	{
		if ((*iter)->cutLifeTime())
		{
			iter = m_eventList.erase(iter);
		}
		else
		{
			iter++;
		}
	}

	//�����Զ��ͷ��¼�
	if (m_isEnableAutoRelease)
	{
		for (auto iter = m_buttonTimerList.begin(); iter != m_buttonTimerList.end();)
		{
			iter->second -= dt;
			if (iter->second <= 0)
			{
				if (!m_isOnlyDispatchPress)
				{
					dispatchReleaseEvent((EventKeyboard::KeyCode)iter->first);
				}
				iter = m_buttonTimerList.erase(iter);
			}
			else
			{
				iter++;
			}
		}
	}
}


//���һ���û����̼�����(callback�еĵ�һ������ȥgetUserDataת��CustomKeyEvent*���Ի�ȡ��ؼ�ֵ)
EventListenerCustom * CustomKeyEventDispatcher::addCustomKeyListener(const std::function<void(EventCustom*)> & callback)
{
	auto ev = Director::getInstance()->getEventDispatcher()->addCustomEventListener("CustomKeyboard", callback);

	m_eventListenersList.pushBack(ev);

	return ev;
}


//�������ɷ�����Ӧ���û����̼�����
void CustomKeyEventDispatcher::clearEventListener()
{
	for (auto & i : m_eventListenersList)
	{
		Director::getInstance()->getEventDispatcher()->removeEventListener(i);
	}
	m_eventListenersList.clear();
}


//�Ƴ�һ������ɷ�����Ӧ���û����̼�����
void CustomKeyEventDispatcher::removeEventListener(EventListenerCustom * listener)
{
	Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
	m_eventListenersList.eraseObject(listener);
}
