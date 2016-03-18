/*--------------------------------
退出游戏UI
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
	
	//初始化
	virtual bool init();

	//创建实例
	CREATE_FUNC(ExitGameUI);

	//显示/隐藏界面
	void activePanel(bool active);

	//获取取消按钮
	SpriteButton * getButtonCancel();

protected:

	//退出游戏回调
	void _exitGameCallback(Ref * ref);

	//黑色背景
	ui::Layout * m_blackBack;

	//窗体视图
	Layer * m_exitPanelView;

	//退出游戏按钮
	SpriteButton * m_buttonExit;

	//取消按钮
	SpriteButton * m_buttonCancel;

	//按钮组
	KeyButtonsPackage m_buttons;

	//是否处于激活状态
	bool m_isActived;
};






#endif
