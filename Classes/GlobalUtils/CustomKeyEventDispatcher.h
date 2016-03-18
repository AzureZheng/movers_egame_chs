/****************************************
�û������¼��ɷ���
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

	//��ͣ�¼��ɷ�
	void pauseDispatch();

	//�ָ��¼��ɷ�
	void resumeDispatch();

	//����������ʱ����ʱ��
	void setAutoReleaseTimeDelay(float dt);

	//�Ƿ���������ʱ����Ϊ��������
	void setAutoReleaseEnable(bool enable);

	//�ɷ����������¼�
	void dispatchPressEvent(EventKeyboard::KeyCode keycode);

	//�ɷ������ͷ��¼�
	void dispatchReleaseEvent(EventKeyboard::KeyCode keycode);

	//�����¼�����
	virtual void update(float dt);

	//���һ������ɷ�����Ӧ���û����̼�����(callback�еĵ�һ������ȥgetUserDataת��CustomKeyEvent*���Ի�ȡ��ؼ�ֵ)
	EventListenerCustom * addCustomKeyListener(const std::function<void(EventCustom*)> & callback);

	//�������ɷ�����Ӧ���û����̼�����
	void clearEventListener();

	//�Ƴ�һ������ɷ�����Ӧ���û����̼�����
	void removeEventListener(EventListenerCustom * listener);

protected:

	//��ͨ�����ص�
	void onKeyPress(EventKeyboard::KeyCode keycode, Event * e);
	void onKeyRelease(EventKeyboard::KeyCode keycode, Event * e);

	//����������
	Vector<EventListenerCustom*> m_eventListenersList;

	//�¼�����
	Vector<CustomKeyEvent*> m_eventList;

	//������ʱ��
	std::map<int, float> m_buttonTimerList;

	//�Ƿ���ͣ�¼��ɷ�
	bool m_isPauseDispatch;

	//�Ƿ�ֻ�ɷ������¼�
	bool m_isOnlyDispatchPress;

	//�Ƿ���������ʱ����Ϊ����
	bool m_isEnableAutoRelease;

	//����ʱ��������������Ϊ����
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

	//��ȡ��������
	char getLifeTime(){ return m_lifeTime; }

	//�������ڼ�1�������Ƿ�������
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

	//��ȡ��ֵ
	EventKeyboard::KeyCode getKeyCode(){ return m_keyCode; }

	//��ȡ��������(true:����;flase:̧��)
	bool getKeyAction(){ return m_keyAction; }

	//��ȡ�ɷ���
	CustomKeyEventDispatcher * getDispatcher(){ return m_dispatcher; }

protected:

	//��������
	char m_lifeTime;

	//��ֵ
	EventKeyboard::KeyCode m_keyCode;

	//��������
	bool m_keyAction;

	//�ɷ���
	CustomKeyEventDispatcher * m_dispatcher;
};


#endif
