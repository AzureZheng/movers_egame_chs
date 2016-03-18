/****************************************
精灵按键
2016-01-13 by Azure Zheng
*****************************************/


#ifndef __SPRITE_BUTTON_H__
#define __SPRITE_BUTTON_H__


#include "cocos2d.h"

class SpriteButton : public cocos2d::Sprite
{
public:

	//逻辑方向
	enum class Direction : char
	{
		LEFT = 0,
		RIGHT,
		UP,
		DOWN
	};

	//逻辑位置
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

	//析构移除精灵帧与监听器
	virtual ~SpriteButton();

	//创建实例
	CREATE_FUNC(SpriteButton);

	//带参数创建实例
	static SpriteButton * create(const std::string & normalSpriteFrameName, const std::string & pressSpriteFrameName = "", const std::string & disabledSpriteFrameName = "");
	static SpriteButton * create(cocos2d::SpriteFrame * normalSpriteFrame, cocos2d::SpriteFrame * pressSpriteFrame = nullptr, cocos2d::SpriteFrame * disabledSpriteFrame = nullptr);

	//设置所有按钮互斥状态
	static void setAllButtonsMutexStatus(bool isEnabled);

	//转换到按下状态
	virtual void switchToPress();

	//转换到正常状态
	virtual void switchToNormal();

	//转换到禁用状态
	virtual void switchToDisabled();

	//设置可用状态
	void setEnabled(bool enabled);

	//设置高亮状态
	void setBright(bool bright);

	//返回高亮状态
	bool isBright();

	//返回可用状态
	bool isEnabled();

	//设置回调函数
	void setCallback(const std::function<void(cocos2d::Ref*)> callback);

	//设置刚按下时回调函数
	void setCallbackTouchBegan(const std::function<void(cocos2d::Ref*)> callback);

	//设置禁用时的回调函数
	void setCallbackDisabled(const std::function<void(cocos2d::Ref*)> callback);

	//返回回调函数
	const std::function<void(cocos2d::Ref*)> & getCallback() const;

	//设置正常状态精灵帧(第二个参数：是否设置到选择状态中)
	void setNormalSpriteFrame(cocos2d::SpriteFrame * sf,bool isSelectStatus = false);

	//设置正常状态精灵帧(第二个参数：是否设置到选择状态中)
	void setNormalSpriteFrame(const std::string & sfName, bool isSelectStatus = false);

	//设置按下状态精灵帧
	void setPressSpriteFrame(cocos2d::SpriteFrame * sf, bool isSelectStatus = false);

	//设置按下状态精灵帧
	void setPressSpriteFrame(const std::string & sfName, bool isSelectStatus = false);

	//设置禁用状态精灵帧
	void setDisabledSpriteFrame(cocos2d::SpriteFrame * sf, bool isSelectStatus = false);

	//设置禁用状态精灵帧
	void setDisabledSpriteFrame(const std::string & sfName, bool isSelectStatus = false);

	//切换选择状态
	void setSelectedStatus(bool selected);

	//设置按钮按下声音
	void setSound(const std::string & soundFile);

	//设置默认按钮按下的声音
	static void setAllButtonsDefaultSound(const std::string & soundFile);

	//设置触摸吞噬
	void setSwallowTouches(bool needSwallow);

	//触摸取消
	void touchCancel();

	//设置静音状态
	void setMute(bool isMute);

	//获取静音状态
	bool isMute();

	//触发一次按钮(参数：延迟多久触发，在这段时间会播放动画)
	void activeButton(float delayedAnimTime = 0);

	//设置缩放差
	void setScaleDiff(float diff);

	//从一系列按钮中找到一个方向上离该按钮最近的按钮(按钮列表，方向，是否首尾相连)
	SpriteButton * getNearestButtonWithDirection(const cocos2d::Vector<SpriteButton*> & buttons,Direction dire,bool isLooped = true);

	//获取逻辑位置
	const LogicPosition & getLogicPosition();

	//设置逻辑位置
	void setLogicPosition(int x,int y);

	//退出时移除监听器
	virtual void onExit();

	//触摸开始
	virtual bool onTouchBegan(cocos2d::Touch * t, cocos2d::Event * e);

	//触摸移动
	virtual void onTouchMoved(cocos2d::Touch * t, cocos2d::Event * e);

	//触摸结束
	virtual void onTouchEnded(cocos2d::Touch * t, cocos2d::Event * e);

	//触摸取消
	virtual void onTouchCanceled(cocos2d::Touch * t, cocos2d::Event * e);

protected:

	//初始化(请勿手动调用)
	virtual bool init();

	//创建触摸监听器
	void _setupTouchListener();

	//检查是否父节点可见
	bool _isAncensterEnabled(Node * node);

	//-------------------------------------------------------------------

	//默认按钮声音
	static std::string m_defaultSound;

	//按钮声音
	std::string m_sound;

	//互斥状态
	static bool m_mutexStatus;

	//当前状态(0:正常，1:按下，2:禁用，3:触摸取消)
	short m_status;

	//触摸监听器
	cocos2d::EventListenerTouchOneByOne * m_touchListener;

	//正常状态精灵帧
	cocos2d::SpriteFrame * m_normalSpriteFrame;

	//按下状态精灵帧
	cocos2d::SpriteFrame * m_pressSpriteFrame;

	//禁用状态精灵帧
	cocos2d::SpriteFrame * m_disabledSpriteFrame;

	//选择正常状态精灵帧
	cocos2d::SpriteFrame * m_normalSelectedSpriteFrame;

	//选择按下状态精灵帧
	cocos2d::SpriteFrame * m_pressSelectedSpriteFrame;

	//选择禁用状态精灵帧
	cocos2d::SpriteFrame * m_disabledSelectedSpriteFrame;

	//按下回调函数
	std::function<void(cocos2d::Ref*)> m_callback;

	//刚按时回调函数
	std::function<void(cocos2d::Ref*)> m_touchBeganCallback;

	//禁用时回调函数
	std::function<void(cocos2d::Ref*)> m_disabledCallback;

	//逻辑位置
	LogicPosition m_logicPosition;

	//静音状态
	bool m_isMute;

	//高亮状态
	bool m_isBright;

	//选择状态
	bool m_isSelected;

	//可用状态
	bool m_isEnabled;

	//缩放状态
	float m_scaledRateX;
	float m_scaledRateY;

	//缩放差
	float m_scaleDiff;

	//开始触摸状态
	bool m_startToBeTouched;

};


//带有动画缩放效果的按钮
class SpriteButtonZooming : public SpriteButton
{
public:
	CREATE_FUNC(SpriteButtonZooming);

	//初始化
	bool init();

	static SpriteButtonZooming * create(const std::string & normalSpriteFrameName, const std::string & pressSpriteFrameName = "", const std::string & disabledSpriteFrameName = "");

	//转换到正常状态
	void switchToNormal();

	//转换到按下状态
	void switchToPress();

	//转换到禁用状态
	void switchToDisabled();

	//抵消一次转换到正常状态所引起的缩放
	void eraseNormalScaleOnce();

protected:
	//是否抵消一次转换到正常状态的缩放
	bool m_eraseNormalScaleOnce;
};













#endif
