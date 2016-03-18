#include "PushButton.h"
#include "SimpleAudioEngine.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS )
#include "FilePathDefine.h"
#else
#include "..\FilePathDefine.h"
#endif

void emptyControlCallBack( void * _object )
{
	cocos2d::log("CALL AN EMPTY FUNCTION");
}

PushButton::PushButton():
_pressScale( 1.1 ),
_function_Press( std::bind( &PushButton::doNothing , this ) ),
_function_Hold( std::bind( &PushButton::doNothing , this ) ),
_function_Release( std::bind( &PushButton::doNothing , this ) ),
_pressed( false ),
_released( false ),
_canceled( false ),
_locked( false ),
_inbox( false ),
inScrollView( false )
{}


void PushButton::putIntoBox( int l , int r , int t , int b )
{
	_inbox = true;
	taouchable_l = l;
	taouchable_r = r;
	taouchable_t = t;
	taouchable_b = b;
}

void PushButton::putOutFromBox()
{
	_inbox = false;
}

// 创建按钮
PushButton * PushButton::createByFrameName( const char * _FrameName )
{
	auto button = PushButton::create();
	auto _frame = SpriteFrameCache::getInstance()->getSpriteFrameByName( _FrameName );
	button->setFrameNormal( _frame );
	button->setFrameLocked( _frame );
	return button;
}

// 创建按钮
PushButton * PushButton::createByFrame( SpriteFrame * _frame )
{
	auto button = PushButton::create();
	button->setFrameNormal( _frame );
	button->setFrameLocked( _frame );
	return button;
}

// 退出回调
void PushButton::onExit()
{
	Sprite::onExit();
	Director::getInstance()->getEventDispatcher()->removeEventListener( _listener );
}

void PushButton::lockButton()
{
	if( _locked ) return;
	_locked = true;
	setSpriteFrame( frameLock );
	Director::getInstance()->getEventDispatcher()->removeEventListener( _listener );
	_listener = NULL;
	stopActionByTag(22);
	setScale( 1 );
	setRotation( 0 );
}

void PushButton::unlockButton()
{
	if( !_locked ) return;
	_locked = false;
	_released = true;
	_pressed = false;
	stopActionByTag(22);
	goNormal();
	setSpriteFrame( frameNormal );
	_listener = EventListenerTouchOneByOne::create();
	// 注册触摸监听
	_listener = EventListenerTouchOneByOne::create();  
	_listener->onTouchBegan = CC_CALLBACK_2( PushButton::onTouchBegan , this );
	_listener->onTouchMoved = CC_CALLBACK_2( PushButton::onTouchMoved ,this );
	_listener->onTouchEnded = CC_CALLBACK_2( PushButton::onTouchEnded , this );
	_listener->onTouchCancelled = CC_CALLBACK_2( PushButton::onTouchCancelled ,this );
	_listener->setSwallowTouches( true );//不向下传递触摸
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority( _listener , this );
}

bool PushButton::init()
{
	if( !Sprite::init() ) return false;

	_listener = EventListenerTouchOneByOne::create();
	// 注册触摸监听
	_listener = EventListenerTouchOneByOne::create();  
	_listener->onTouchBegan = CC_CALLBACK_2( PushButton::onTouchBegan , this );
	_listener->onTouchMoved = CC_CALLBACK_2( PushButton::onTouchMoved ,this );
	_listener->onTouchEnded = CC_CALLBACK_2( PushButton::onTouchEnded , this );
	_listener->onTouchCancelled = CC_CALLBACK_2( PushButton::onTouchCancelled ,this );
	_listener->setSwallowTouches( true );//不向下传递触摸
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority( _listener , this );
	goNormal();

	_silent = false;

	return true;
}


/* 触摸响应 */

bool PushButton::onTouchBegan( Touch *touch , Event *event )  // ***************************************************************  触摸开始
{
	if( _inbox )
	{
		auto lt = touch->getLocation();
		if( lt.x < taouchable_l || lt.x > taouchable_r || lt.y < taouchable_b || lt.y > taouchable_t ) return false;
	}
	if(_pressed || _locked ) return false;
	auto tp = convertTouchToNodeSpace( touch );
	if( tp.x < 0 || tp.x > getContentSize().width || tp.y < 0 || tp.y > getContentSize().height ) return false;
	else
	{
		if( !_silent ) PLAY_EFFECT( SOUND_EFFECT_BUTTON );
		_canceled = false;
		_released = false;
		_pressed = true;

		goPress();

		_function_Press();

		return true;
	}
}

void PushButton::onTouchMoved( Touch *touch , Event *event )  // ***************************************************************  触摸滑动
{
	if( _released || _locked ) return;
	auto tp = convertTouchToNodeSpace( touch );

	if( inScrollView )
	{
		if( touch->getStartLocation().distance( touch->getLocation() ) > 16 )
		{
			_canceled = true;
			onTouchEnded( touch , event );
		}
	}
	else if( tp.x < 0 || tp.x > getContentSize().width || tp.y < 0 || tp.y > getContentSize().height )
	{
		_canceled = true;
		onTouchEnded( touch , event );
	}
}
	
void PushButton::onTouchEnded( Touch *touch , Event *event )  // ***************************************************************  触摸结束
{
	if( _released || _locked ) return;
	_released = true;
	_pressed = false;
	stopAllActions();
	
	if( !_canceled )
	{
		runAction( Sequence::create(  
			ScaleTo::create( 0.1 ,1.0 ) ,
			CallFunc ::create( CC_CALLBACK_0 ( PushButton::doCallBack , this )) ,
			CallFunc ::create( CC_CALLBACK_0 ( PushButton::doGoNormal , this )) ,
			NULL
			) );
	}
	else
	{
		goNormal();
	}
}

void PushButton::goNormal()
{
	stopActionByTag(22);
	runAction( EaseSineOut::create( ScaleTo::create( 0.1 ,1.0 ) ) )->setTag(22);
}

void PushButton::goPress()
{
	stopActionByTag(22);
	runAction(EaseSineIn::create(ScaleTo::create(0.1, _pressScale)))->setTag(22);
}

void PushButton::doCallBack()
{
	if( !_locked ) _function_Release();
	//pressDown_callBack( pressDown_object ); // 按下回调
	
}

void PushButton::onTouchCancelled( Touch *touch , Event *event )  // ***************************************************************  触摸中断
{
	_canceled = true;
	onTouchEnded( touch , event );
}



void PushButtonZoomimng::goNormal()
{
	if (_isNoGoNormal)
	{
		_isNoGoNormal = false;
		return;
	}
	stopActionByTag(22);
	runAction(RepeatForever::create(Sequence::create(
		EaseSineOut::create(ScaleTo::create(0.4, 0.9)),
		EaseSineIn::create(ScaleTo::create(0.4, 1.0)),
		NULL)))->setTag(22);
}


// 创建按钮
PushButtonZoomimng * PushButtonZoomimng::createByFrameName( const char * _FrameName )
{
	auto button = PushButtonZoomimng::create();
	auto _frame = SpriteFrameCache::getInstance()->getSpriteFrameByName( _FrameName );
	button->setFrameNormal( _frame );
	button->setFrameLocked( _frame );
	return button;
}

// 创建按钮
PushButtonZoomimng * PushButtonZoomimng::createByFrame( SpriteFrame * _frame )
{
	auto button = PushButtonZoomimng::create();
	button->setFrameNormal( _frame );
	button->setFrameLocked( _frame );
	return button;
}


void PushButtonZoomimng::goPress()
{
	stopActionByTag(22);
}



bool PushButtonZoomimng::init()
{
	_isNoGoNormal = false;

	if (!PushButton::init())
	{
		return false;
	}

	return true;
}
