/*----------------------------
商城视图
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
	
	//初始化
	virtual bool init();

	//创建实例
	CREATE_FUNC(BankView);

	//激活/隐藏商店UI
	void activeShopView(bool active);

	//激活/隐藏再来一次UI
	void activeMoreChanceView(bool active);

	//激活/隐藏模式解锁UI
	void activeUnlockView(bool active);

	//获取返回按钮
	SpriteButton * getButtonBack();

	//获取解锁取消按钮
	SpriteButton * getButtonUnlockCancel();

	//获取复活取消按钮
	SpriteButton * getButtonHealCancel();

	//获取复活按钮
	SpriteButton * getButtonMoreChance();

	//获取解锁按钮
	SpriteButton * getButtonUnlock();

	//显示/隐藏黑底
	void setBlackBackVisible(bool isVisible);

	//设置黑底层级
	void setBlackBackZOrder(int zOrder);

	//获取是否在显示商店视图
	bool isInShopView();

	//获取是否在显示再来一次视图
	bool isInMoreChanceView();

	//刷新钻石显示
	void _refreshDiamond();

	//获取钻石
	int getDiamond();

	//显示隐藏二级Shop
	void showHideSubShop(bool show);

	//返回商店是否在二级模式打开
	bool isSubShop();

protected:

	//创建商店
	void _addShop();

	//创建再来一次
	void _addMoreChance();

	//创建解锁模式
	void _addUnlockMode();

	//钻石按钮回调
	void _buyDiamond(Ref * ref, int index);

	//检查是否已解锁模式
	bool _checkUnlockMode();

	//解锁模式(返回是否解锁成功)
	bool _unlockMode();

	//支付结果检查
	void _checkPayResult(float dt);

	//---------------------------------------------------------------------------------

	//是否在显示商店视图
	bool m_isInShopView;

	//是否在显示再来一次视图
	bool m_isInMoreChanceView;

	//是否在显示解锁视图
	bool m_isInUnlockView;

	//黑底
	ui::Layout * m_blackBack;

	//商店视图
	Layer * m_shopView;

	//再来一次视图
	Layer * m_moreChanceView;

	//解锁视图
	Layer * m_unlockView;

	//商店按钮组
	KeyButtonsPackage m_buttonsForShop;

	//再来一次按钮组
	KeyButtonsPackage m_buttonsForMoreChance;

	//解锁模式按钮组
	KeyButtonsPackage m_buttonsForUnlockMode;

	//买钻石按钮
	SpriteButton *m_buyDiamond[3];

	//返回按钮
	SpriteButton * m_buttonBack;

	//复活按钮
	SpriteButton * m_buttonHeal;

	//解锁按钮
	SpriteButton * m_buttonUnlock;

	//解锁取消按钮
	SpriteButton * m_buttonUnlockCancel;

	//复活取消按钮
	SpriteButton * m_buttonHealCancel;

	//复活钻石显示
	LabelAtlas * m_healDiamondView;

	//商城钻石显示
	LabelAtlas * m_shopDiamondView;

	//钻石数量
	int m_diamond;

	//屏幕大小
	Size m_visibleSize;

	//支付面额
	int m_payIndex;

	//支付中
	bool m_inPay;

};












#endif
