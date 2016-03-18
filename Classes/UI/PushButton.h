/*
////////////////////////////////////////////////////////

按钮

* 惊悚帝 *

////////////////////////////////////////////////////////
*/
#ifndef _GAME_PUSHBUTTON_H_
#define _GAME_PUSHBUTTON_H_

#include "cocos2d.h"

USING_NS_CC;

// 按钮
class PushButton : public Sprite
{
	EventListenerTouchOneByOne * _listener;
	
	// 按钮按下回调
	//void * pressDown_object;
	//void (*pressDown_callBack)( void * _object );

	bool _pressed , _released,_canceled;//,_automove;

	bool inScrollView;

	bool _silent;

	bool _locked;

	SpriteFrame * frameNormal;

	SpriteFrame * frameLock;

	// call back bind

	std::function<void ()> _function_Press;
	std::function<void ()> _function_Hold;
	std::function<void ()> _function_Release;

	int taouchable_l,taouchable_r,taouchable_t,taouchable_b;
	bool _inbox;

	float _pressScale;
public:

	void setPressScale( float scale ){ _pressScale = scale; }

	void putIntoBox( int l , int r , int t , int b );

	void putOutFromBox();

	void setFrameNormal( SpriteFrame * frame ){ frameNormal = frame;setSpriteFrame(frameNormal); }

	void setFrameLocked( SpriteFrame * frame ){ frameLock = frame; }

	void setFrameNormal( std::string _frameName ){ setFrameNormal( SpriteFrameCache::getInstance()->getSpriteFrameByName( _frameName ) ); }

	void setFrameLocked( std::string _frameName ){ setFrameLocked( SpriteFrameCache::getInstance()->getSpriteFrameByName( _frameName ) ); }

	void lockButton();

	void unlockButton();

	void setSilent( bool silent ){ _silent = silent; }

	void putIntoScrollView(){ inScrollView = true; }

	void putOutFromScrollView(){ inScrollView = false; }

	void testString( const std::string & str ){}

	void doNothing(){}

	//void activeAutoMotion();

	PushButton();

	void doCallBack();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // create();
    CREATE_FUNC( PushButton );

	// 创建按钮
	static PushButton * createByFrameName( const char * _FrameName );

	// 创建按钮
	static PushButton * createByFrame( SpriteFrame * _frame );

	// 初始化 
	void setUp( SpriteFrame * _frame );

	// 退出回调
	void onExit();

	/* 触摸响应 */

	virtual void goNormal();

	void doGoNormal(){ goNormal(); }

	virtual void goPress();

	bool onTouchBegan( Touch *touch , Event *event );

	void onTouchMoved( Touch *touch , Event *event );
	
	void onTouchEnded( Touch *touch , Event *event );
	
	void onTouchCancelled( Touch *touch , Event *event );

	// 设置按钮按下回调
	void setPressDownCallBack( std::function<void ()> _callBack )
	{ _function_Press = _callBack; }

	void setPressReleaseCallBack( std::function<void ()> _callBack )
	{ _function_Release = _callBack; }

};

class PushButtonZoomimng : public PushButton
{
public:

	virtual bool init();

	void goNormal();

	virtual void goPress();

	bool _isNoGoNormal;

	// create();
    CREATE_FUNC( PushButtonZoomimng );

	// 创建按钮
	static PushButtonZoomimng * createByFrameName( const char * _FrameName );

	// 创建按钮
	static PushButtonZoomimng * createByFrame( SpriteFrame * _frame );
};


#endif // _GAME_PUSHBUTTON_H_