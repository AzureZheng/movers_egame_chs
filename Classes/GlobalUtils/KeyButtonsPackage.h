/****************************************
精灵按键合集
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
	
	//创建(一开始监听器是暂停的)
	KeyButtonsPackage();

	//创建(一开始监听器是暂停的)
	KeyButtonsPackage(const Vector<SpriteButton*> & buttons, SpriteButton * firstButton = nullptr);

	//初始化
	void init();

	//析构
	~KeyButtonsPackage();

	//获取当前选择的按钮
	SpriteButton * getSelectedButton();

	//将一个按钮标记为选择状态
	void setSelectedButton(SpriteButton * button);

	//添加一个按钮
	void pushBackButton(SpriteButton * button);

	//移除一个按钮
	void removeButton(SpriteButton * button);

	//添加一组按钮
	void pushBackButton(const Vector<SpriteButton*> & buttons);

	//按名字查找一个按钮
	SpriteButton * findButtonByName(const std::string & name);

	//清空所有按钮的选择状态
	void clearAllButtonsSelectedStatus();

	//暂停键盘监听
	void pauseKeyListener();

	//恢复监听
	void resumeKeyListener();

	//检查是否暂停监听
	bool isPausedKeyListener();

	//设置按键附加回调(无视暂停状态)
	void setButtonExtraCallback(const std::function<void(KeyButtonsPackage*,CustomKeyEvent*)> & buttonExtraCallback);

	//设置返回键所调用的按键
	void setBackButtonCallbackButton(SpriteButton * bt);

	//设置是否允许按钮首尾相连
	void setButtonsDirectionLooped(bool enable);

	//获取按钮组
	const Vector<SpriteButton*> & getButtons();

	//获取标记
	int getTag();

	//设置标记
	void setTag(int tag);

	//设置按钮回调延时
	void setButtonCallbackDelayTime(float time);

	//锁定/解锁按钮组
	void setButtonsEnabled(bool enable);

protected:

	//按钮回调延时
	float m_buttonCallbackDelayTime;

	//标记
	int m_tag;

	//用户键盘事件被触发回调
	void _onCustomKeyPress(EventCustom * e);

	//用户键盘监听器
	EventListenerCustom * m_customKeyListener;

	//当前选中的按钮
	SpriteButton * m_selectedButton;

	//返回键所对应的按钮
	SpriteButton * m_backButton;

	//按钮组
	Vector<SpriteButton*> m_buttons;

	//按钮组是否首位相连
	bool m_isButtonsDirectionLooped;

	//按键附加回调
	std::function<void(KeyButtonsPackage*, CustomKeyEvent*)> m_buttonExtraCallback;

	//是否暂停监听器
	bool m_isPauseListener;

};






#endif
