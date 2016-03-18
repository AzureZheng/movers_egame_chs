/****************************************
���鰴��
2016-01-13 by Azure Zheng
*****************************************/


#ifndef __SPRITE_BUTTON_H__
#define __SPRITE_BUTTON_H__


#include "cocos2d.h"

class SpriteButton : public cocos2d::Sprite
{
public:

	//�߼�����
	enum class Direction : char
	{
		LEFT = 0,
		RIGHT,
		UP,
		DOWN
	};

	//�߼�λ��
	struct LogicPosition
	{
		int x, y;
		LogicPosition():x(0),y(0){}
		void set(int _x, int _y){ x = _x; y = _y; }
		float distance(const LogicPosition & pos)
		{
			return sqrt((x - pos.x)*(x - pos.x) + (y - pos.y) * (y - pos.y));
		}
	};

	//�����Ƴ�����֡�������
	virtual ~SpriteButton();

	//����ʵ��
	CREATE_FUNC(SpriteButton);

	//����������ʵ��
	static SpriteButton * create(const std::string & normalSpriteFrameName, const std::string & pressSpriteFrameName = "", const std::string & disabledSpriteFrameName = "");
	static SpriteButton * create(cocos2d::SpriteFrame * normalSpriteFrame, cocos2d::SpriteFrame * pressSpriteFrame = nullptr, cocos2d::SpriteFrame * disabledSpriteFrame = nullptr);

	//�������а�ť����״̬
	static void setAllButtonsMutexStatus(bool isEnabled);

	//ת��������״̬
	virtual void switchToPress();

	//ת��������״̬
	virtual void switchToNormal();

	//ת��������״̬
	virtual void switchToDisabled();

	//���ÿ���״̬
	void setEnabled(bool enabled);

	//���ø���״̬
	void setBright(bool bright);

	//���ظ���״̬
	bool isBright();

	//���ؿ���״̬
	bool isEnabled();

	//���ûص�����
	void setCallback(const std::function<void(cocos2d::Ref*)> callback);

	//���øհ���ʱ�ص�����
	void setCallbackTouchBegan(const std::function<void(cocos2d::Ref*)> callback);

	//���ý���ʱ�Ļص�����
	void setCallbackDisabled(const std::function<void(cocos2d::Ref*)> callback);

	//���ػص�����
	const std::function<void(cocos2d::Ref*)> & getCallback() const;

	//��������״̬����֡(�ڶ����������Ƿ����õ�ѡ��״̬��)
	void setNormalSpriteFrame(cocos2d::SpriteFrame * sf,bool isSelectStatus = false);

	//��������״̬����֡(�ڶ����������Ƿ����õ�ѡ��״̬��)
	void setNormalSpriteFrame(const std::string & sfName, bool isSelectStatus = false);

	//���ð���״̬����֡
	void setPressSpriteFrame(cocos2d::SpriteFrame * sf, bool isSelectStatus = false);

	//���ð���״̬����֡
	void setPressSpriteFrame(const std::string & sfName, bool isSelectStatus = false);

	//���ý���״̬����֡
	void setDisabledSpriteFrame(cocos2d::SpriteFrame * sf, bool isSelectStatus = false);

	//���ý���״̬����֡
	void setDisabledSpriteFrame(const std::string & sfName, bool isSelectStatus = false);

	//�л�ѡ��״̬
	void setSelectedStatus(bool selected);

	//���ð�ť��������
	void setSound(const std::string & soundFile);

	//����Ĭ�ϰ�ť���µ�����
	static void setAllButtonsDefaultSound(const std::string & soundFile);

	//���ô�������
	void setSwallowTouches(bool needSwallow);

	//����ȡ��
	void touchCancel();

	//���þ���״̬
	void setMute(bool isMute);

	//��ȡ����״̬
	bool isMute();

	//����һ�ΰ�ť(�������ӳٶ�ô����������ʱ��Ქ�Ŷ���)
	void activeButton(float delayedAnimTime = 0);

	//�������Ų�
	void setScaleDiff(float diff);

	//��һϵ�а�ť���ҵ�һ����������ð�ť����İ�ť(��ť�б������Ƿ���β����)
	SpriteButton * getNearestButtonWithDirection(const cocos2d::Vector<SpriteButton*> & buttons,Direction dire,bool isLooped = true);

	//��ȡ�߼�λ��
	const LogicPosition & getLogicPosition();

	//�����߼�λ��
	void setLogicPosition(int x,int y);

	//�˳�ʱ�Ƴ�������
	virtual void onExit();

	//������ʼ
	virtual bool onTouchBegan(cocos2d::Touch * t, cocos2d::Event * e);

	//�����ƶ�
	virtual void onTouchMoved(cocos2d::Touch * t, cocos2d::Event * e);

	//��������
	virtual void onTouchEnded(cocos2d::Touch * t, cocos2d::Event * e);

	//����ȡ��
	virtual void onTouchCanceled(cocos2d::Touch * t, cocos2d::Event * e);

protected:

	//��ʼ��(�����ֶ�����)
	virtual bool init();

	//��������������
	void _setupTouchListener();

	//����Ƿ񸸽ڵ�ɼ�
	bool _isAncensterEnabled(Node * node);

	//-------------------------------------------------------------------

	//Ĭ�ϰ�ť����
	static std::string m_defaultSound;

	//��ť����
	std::string m_sound;

	//����״̬
	static bool m_mutexStatus;

	//��ǰ״̬(0:������1:���£�2:���ã�3:����ȡ��)
	short m_status;

	//����������
	cocos2d::EventListenerTouchOneByOne * m_touchListener;

	//����״̬����֡
	cocos2d::SpriteFrame * m_normalSpriteFrame;

	//����״̬����֡
	cocos2d::SpriteFrame * m_pressSpriteFrame;

	//����״̬����֡
	cocos2d::SpriteFrame * m_disabledSpriteFrame;

	//ѡ������״̬����֡
	cocos2d::SpriteFrame * m_normalSelectedSpriteFrame;

	//ѡ����״̬����֡
	cocos2d::SpriteFrame * m_pressSelectedSpriteFrame;

	//ѡ�����״̬����֡
	cocos2d::SpriteFrame * m_disabledSelectedSpriteFrame;

	//���»ص�����
	std::function<void(cocos2d::Ref*)> m_callback;

	//�հ�ʱ�ص�����
	std::function<void(cocos2d::Ref*)> m_touchBeganCallback;

	//����ʱ�ص�����
	std::function<void(cocos2d::Ref*)> m_disabledCallback;

	//�߼�λ��
	LogicPosition m_logicPosition;

	//����״̬
	bool m_isMute;

	//����״̬
	bool m_isBright;

	//ѡ��״̬
	bool m_isSelected;

	//����״̬
	bool m_isEnabled;

	//����״̬
	float m_scaledRateX;
	float m_scaledRateY;

	//���Ų�
	float m_scaleDiff;

	//��ʼ����״̬
	bool m_startToBeTouched;

};


//���ж�������Ч���İ�ť
class SpriteButtonZooming : public SpriteButton
{
public:
	CREATE_FUNC(SpriteButtonZooming);

	//��ʼ��
	bool init();

	static SpriteButtonZooming * create(const std::string & normalSpriteFrameName, const std::string & pressSpriteFrameName = "", const std::string & disabledSpriteFrameName = "");

	//ת��������״̬
	void switchToNormal();

	//ת��������״̬
	void switchToPress();

	//ת��������״̬
	void switchToDisabled();

	//����һ��ת��������״̬�����������
	void eraseNormalScaleOnce();

protected:
	//�Ƿ����һ��ת��������״̬������
	bool m_eraseNormalScaleOnce;
};













#endif
