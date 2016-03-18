/*----------------------------
�̳���ͼ
2016-03-06 by Azure Zheng
------------------------------*/

#ifndef __BANK_VIEW_H__
#define __BANK_VIEW_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "GlobalUtils/KeyButtonsPackage.h"


class BankView : public Layer
{
public:
	
	//��ʼ��
	virtual bool init();

	//����ʵ��
	CREATE_FUNC(BankView);

	//����/�����̵�UI
	void activeShopView(bool active);

	//����/��������һ��UI
	void activeMoreChanceView(bool active);

	//����/����ģʽ����UI
	void activeUnlockView(bool active);

	//��ȡ���ذ�ť
	SpriteButton * getButtonBack();

	//��ȡ����ȡ����ť
	SpriteButton * getButtonUnlockCancel();

	//��ȡ����ȡ����ť
	SpriteButton * getButtonHealCancel();

	//��ȡ���ť
	SpriteButton * getButtonMoreChance();

	//��ȡ������ť
	SpriteButton * getButtonUnlock();

	//��ʾ/���غڵ�
	void setBlackBackVisible(bool isVisible);

	//���úڵײ㼶
	void setBlackBackZOrder(int zOrder);

	//��ȡ�Ƿ�����ʾ�̵���ͼ
	bool isInShopView();

	//��ȡ�Ƿ�����ʾ����һ����ͼ
	bool isInMoreChanceView();

	//ˢ����ʯ��ʾ
	void _refreshDiamond();

	//��ȡ��ʯ
	int getDiamond();

	//��ʾ���ض���Shop
	void showHideSubShop(bool show);

	//�����̵��Ƿ��ڶ���ģʽ��
	bool isSubShop();

protected:

	//�����̵�
	void _addShop();

	//��������һ��
	void _addMoreChance();

	//��������ģʽ
	void _addUnlockMode();

	//��ʯ��ť�ص�
	void _buyDiamond(Ref * ref, int index);

	//����Ƿ��ѽ���ģʽ
	bool _checkUnlockMode();

	//����ģʽ(�����Ƿ�����ɹ�)
	bool _unlockMode();

	//֧��������
	void _checkPayResult(float dt);

	//---------------------------------------------------------------------------------

	//�Ƿ�����ʾ�̵���ͼ
	bool m_isInShopView;

	//�Ƿ�����ʾ����һ����ͼ
	bool m_isInMoreChanceView;

	//�Ƿ�����ʾ������ͼ
	bool m_isInUnlockView;

	//�ڵ�
	ui::Layout * m_blackBack;

	//�̵���ͼ
	Layer * m_shopView;

	//����һ����ͼ
	Layer * m_moreChanceView;

	//������ͼ
	Layer * m_unlockView;

	//�̵갴ť��
	KeyButtonsPackage m_buttonsForShop;

	//����һ�ΰ�ť��
	KeyButtonsPackage m_buttonsForMoreChance;

	//����ģʽ��ť��
	KeyButtonsPackage m_buttonsForUnlockMode;

	//����ʯ��ť
	SpriteButton *m_buyDiamond[3];

	//���ذ�ť
	SpriteButton * m_buttonBack;

	//���ť
	SpriteButton * m_buttonHeal;

	//������ť
	SpriteButton * m_buttonUnlock;

	//����ȡ����ť
	SpriteButton * m_buttonUnlockCancel;

	//����ȡ����ť
	SpriteButton * m_buttonHealCancel;

	//������ʯ��ʾ
	LabelAtlas * m_healDiamondView;

	//�̳���ʯ��ʾ
	LabelAtlas * m_shopDiamondView;

	//��ʯ����
	int m_diamond;

	//��Ļ��С
	Size m_visibleSize;

	//֧�����
	int m_payIndex;

	//֧����
	bool m_inPay;

};












#endif
