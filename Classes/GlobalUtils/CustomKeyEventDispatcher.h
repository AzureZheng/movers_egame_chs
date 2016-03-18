/****************************************
用户键盘事件派发器
2016-03-04 by Azure Zheng
*****************************************/


#ifndef __CUSTOM_KEY_EVENT_DISPATCHER_H__
#define __CUSTOM_KEY_EVENT_DISPATCHER_H__

#include "cocos2d.h"

USING_NS_CC;

class CustomKeyEvent;


class CustomKeyEventDispatcher : public Node
{
public:
	
	virtual bool init();

	CREATE_FUNC(CustomKeyEventDispatcher);

	virtual void onExit();

	//暂停事件派发
	void pauseDispatch();

	//恢复事件派发
	void resumeDispatch();

	//设置连发延时修正时间
	void setAutoReleaseTimeDelay(float dt);

	//是否开启连发延时修正为长按功能
	void setAutoReleaseEnable(bool enable);

	//派发按键按下事件
	void dispatchPressEvent(EventKeyboard::KeyCode keycode);

	//派发按键释放事件
	void dispatchReleaseEvent(EventKeyboard::KeyCode keycode);

	//处理事件队列
	virtual void update(float dt);

	//添加一个这个派发器对应的用户键盘监听器(callback中的第一个参数去getUserData转成CustomKeyEvent*可以获取相关键值)
	EventListenerCustom * addCustomKeyListener(const std::function<void(EventCustom*)> & callback);

	//清空这个派发器对应的用户键盘监听器
	void clearEventListener();

	//移除一个这个派发器对应的用户键盘监听器
	void removeEventListener(EventListenerCustom * listener);

protected:

	//普通按键回调
	void onKeyPress(EventKeyboard::KeyCode keycode, Event * e);
	void onKeyRelease(EventKeyboard::KeyCode keycode, Event * e);

	//监听器队列
	Vector<EventListenerCustom*> m_eventListenersList;

	//事件队列
	Vector<CustomKeyEvent*> m_eventList;

	//按键计时表
	std::map<int, float> m_buttonTimerList;

	//是否暂停事件派发
	bool m_isPauseDispatch;

	//是否只派发按下事件
	bool m_isOnlyDispatchPress;

	//是否开启连发延时修正为长按
	bool m_isEnableAutoRelease;

	//多少时间内连发会修正为长按
	float m_timeForAutoRelease;

};




class CustomKeyEvent : public Node
{
public:

	bool init(EventKeyboard::KeyCode keycode, bool keyAction, CustomKeyEventDispatcher * dispatcher)
	{
		if (!Node::init()) return false;
		m_lifeTime = 2;
		m_keyCode = keycode;
		m_keyAction = keyAction;
		m_dispatcher = dispatcher;
		setTag((int)keycode);
		return true;
	}

	static CustomKeyEvent * create(EventKeyboard::KeyCode keycode, bool keyAction, CustomKeyEventDispatcher * dispatcher)
	{
		auto ret = new (std::nothrow) CustomKeyEvent();

		if (ret->init(keycode, keyAction, dispatcher))
		{
			ret->autorelease();
		}
		else
		{
			delete ret;
			return nullptr;
		}
		return ret;
	}

	//获取生命周期
	char getLifeTime(){ return m_lifeTime; }

	//生命周期减1（返回是否死亡）
	bool cutLifeTime()
	{
		m_lifeTime--;
		if (m_lifeTime <= 0)
		{
			m_lifeTime = 0;
			return true;
		}
		return false;
	}

	//获取键值
	EventKeyboard::KeyCode getKeyCode(){ return m_keyCode; }

	//获取按键动作(true:按下;flase:抬起)
	bool getKeyAction(){ return m_keyAction; }

	//获取派发器
	CustomKeyEventDispatcher * getDispatcher(){ return m_dispatcher; }

protected:

	//生命周期
	char m_lifeTime;

	//键值
	EventKeyboard::KeyCode m_keyCode;

	//按键动作
	bool m_keyAction;

	//派发器
	CustomKeyEventDispatcher * m_dispatcher;
};


#endif
