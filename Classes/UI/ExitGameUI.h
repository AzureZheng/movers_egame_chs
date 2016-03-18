/*--------------------------------
�˳���ϷUI
2016-03-08    by Azure Zheng
---------------------------------*/

#ifndef __EXIT_GAME_UI__
#define __EXIT_GAME_UI__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "GlobalUtils/KeyButtonsPackage.h"


class ExitGameUI : public Layer
{
public:
	
	//��ʼ��
	virtual bool init();

	//����ʵ��
	CREATE_FUNC(ExitGameUI);

	//��ʾ/���ؽ���
	void activePanel(bool active);

	//��ȡȡ����ť
	SpriteButton * getButtonCancel();

protected:

	//�˳���Ϸ�ص�
	void _exitGameCallback(Ref * ref);

	//��ɫ����
	ui::Layout * m_blackBack;

	//������ͼ
	Layer * m_exitPanelView;

	//�˳���Ϸ��ť
	SpriteButton * m_buttonExit;

	//ȡ����ť
	SpriteButton * m_buttonCancel;

	//��ť��
	KeyButtonsPackage m_buttons;

	//�Ƿ��ڼ���״̬
	bool m_isActived;
};






#endif
