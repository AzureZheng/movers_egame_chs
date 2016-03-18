#include "CustomKeyEventDispatcher.h"



bool CustomKeyEventDispatcher::init()
{
	if (!Node::init())
	{
		return false;
	}

	//是否暂停事件派发
	m_isPauseDispatch = false;

	//是否只派发按下事件
	m_isOnlyDispatchPress = true;

	//是否开启连发延时修正为长按
	m_isEnableAutoRelease = false;

	//多少时间内连发会修正为长按
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


//暂停事件派发
void CustomKeyEventDispatcher::pauseDispatch()
{
	m_isPauseDispatch = true;
}

//恢复事件派发
void CustomKeyEventDispatcher::resumeDispatch()
{
	m_isPauseDispatch = false;
}

//设置连发延时修正时间
void CustomKeyEventDispatcher::setAutoReleaseTimeDelay(float dt)
{
	m_timeForAutoRelease = dt;
}

//是否开启连发延时修正为长按功能
void CustomKeyEventDispatcher::setAutoReleaseEnable(bool enable)
{
	if (enable == m_isEnableAutoRelease)
	{
		return;
	}

	m_isEnableAutoRelease = enable;

	m_buttonTimerList.clear();
}


//按下回调
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


//释放回调
void CustomKeyEventDispatcher::onKeyRelease(EventKeyboard::KeyCode keycode, Event * e)
{
	if (m_isPauseDispatch || m_isOnlyDispatchPress || m_isEnableAutoRelease)
	{
		return;
	}

	dispatchReleaseEvent(keycode);
}


//派发按键按下事件
void CustomKeyEventDispatcher::dispatchPressEvent(EventKeyboard::KeyCode keycode)
{
	CustomKeyEvent * e = CustomKeyEvent::create(keycode,true,this);

	m_eventList.pushBack(e);

	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("CustomKeyboard", e);
}


//派发按键释放事件
void CustomKeyEventDispatcher::dispatchReleaseEvent(EventKeyboard::KeyCode keycode)
{
	CustomKeyEvent * e = CustomKeyEvent::create(keycode, false,this);

	m_eventList.pushBack(e);

	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("CustomKeyboard", e);
}


//处理事件队列
void CustomKeyEventDispatcher::update(float dt)
{
	//处理事件生命周期
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

	//处理自动释放事件
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


//添加一个用户键盘监听器(callback中的第一个参数去getUserData转成CustomKeyEvent*可以获取相关键值)
EventListenerCustom * CustomKeyEventDispatcher::addCustomKeyListener(const std::function<void(EventCustom*)> & callback)
{
	auto ev = Director::getInstance()->getEventDispatcher()->addCustomEventListener("CustomKeyboard", callback);

	m_eventListenersList.pushBack(ev);

	return ev;
}


//清空这个派发器对应的用户键盘监听器
void CustomKeyEventDispatcher::clearEventListener()
{
	for (auto & i : m_eventListenersList)
	{
		Director::getInstance()->getEventDispatcher()->removeEventListener(i);
	}
	m_eventListenersList.clear();
}


//移除一个这个派发器对应的用户键盘监听器
void CustomKeyEventDispatcher::removeEventListener(EventListenerCustom * listener)
{
	Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
	m_eventListenersList.eraseObject(listener);
}
