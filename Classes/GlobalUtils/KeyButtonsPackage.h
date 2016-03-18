/****************************************
���鰴���ϼ�
2016-03-04 by Azure Zheng
*****************************************/


#ifndef __KEY_BUTTONS_PACKAGE_H__
#define __KEY_BUTTONS_PACKAGE_H__

#include "cocos2d.h"
#include "SpriteButton.h"
#include "CustomKeyEventDispatcher.h"

USING_NS_CC;


class KeyButtonsPackage
{
public:
	
	//����(һ��ʼ����������ͣ��)
	KeyButtonsPackage();

	//����(һ��ʼ����������ͣ��)
	KeyButtonsPackage(const Vector<SpriteButton*> & buttons, SpriteButton * firstButton = nullptr);

	//��ʼ��
	void init();

	//����
	~KeyButtonsPackage();

	//��ȡ��ǰѡ��İ�ť
	SpriteButton * getSelectedButton();

	//��һ����ť���Ϊѡ��״̬
	void setSelectedButton(SpriteButton * button);

	//���һ����ť
	void pushBackButton(SpriteButton * button);

	//�Ƴ�һ����ť
	void removeButton(SpriteButton * button);

	//���һ�鰴ť
	void pushBackButton(const Vector<SpriteButton*> & buttons);

	//�����ֲ���һ����ť
	SpriteButton * findButtonByName(const std::string & name);

	//������а�ť��ѡ��״̬
	void clearAllButtonsSelectedStatus();

	//��ͣ���̼���
	void pauseKeyListener();

	//�ָ�����
	void resumeKeyListener();

	//����Ƿ���ͣ����
	bool isPausedKeyListener();

	//���ð������ӻص�(������ͣ״̬)
	void setButtonExtraCallback(const std::function<void(KeyButtonsPackage*,CustomKeyEvent*)> & buttonExtraCallback);

	//���÷��ؼ������õİ���
	void setBackButtonCallbackButton(SpriteButton * bt);

	//�����Ƿ�����ť��β����
	void setButtonsDirectionLooped(bool enable);

	//��ȡ��ť��
	const Vector<SpriteButton*> & getButtons();

	//��ȡ���
	int getTag();

	//���ñ��
	void setTag(int tag);

	//���ð�ť�ص���ʱ
	void setButtonCallbackDelayTime(float time);

	//����/������ť��
	void setButtonsEnabled(bool enable);

protected:

	//��ť�ص���ʱ
	float m_buttonCallbackDelayTime;

	//���
	int m_tag;

	//�û������¼��������ص�
	void _onCustomKeyPress(EventCustom * e);

	//�û����̼�����
	EventListenerCustom * m_customKeyListener;

	//��ǰѡ�еİ�ť
	SpriteButton * m_selectedButton;

	//���ؼ�����Ӧ�İ�ť
	SpriteButton * m_backButton;

	//��ť��
	Vector<SpriteButton*> m_buttons;

	//��ť���Ƿ���λ����
	bool m_isButtonsDirectionLooped;

	//�������ӻص�
	std::function<void(KeyButtonsPackage*, CustomKeyEvent*)> m_buttonExtraCallback;

	//�Ƿ���ͣ������
	bool m_isPauseListener;

};






#endif
