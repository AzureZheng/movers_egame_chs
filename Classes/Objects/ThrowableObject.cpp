#include "ThrowableObject.h"

#define BASE_SIZE_TIME 0.0167f//0.0166666666666667f // one second = BASE_SIZE_TIME * 60
#define BASE_SIZE_LENGTH 0.01f // 1M = 100p 

#include "..\Scene\BuildingScene.h"
#include "..\FilePathDefine.h"
#include "..\Info\GameInfo.h"
#include "Objects/StageSide.h"

unsigned int ThrowableObject::rabbit_mover_catch_index = 9527;
unsigned int ThrowableObject::rabbit_mover_missbomb_index = 9527;

std::vector<SpriteFrame*> ThrowableObject::_objectFrames;

Vec2 ThrowableObject::_worldGravity( 0 , -10.0f );

float ThrowableObject::_timeScale( 1.0f );

std::vector<ThrowableObject*> ThrowableObject::flyingObjects;


void ThrowableObject::doAcceptTarget()
{
	GameInfo::getInstance()->catchGoods(getOwner());
	inactiveMotion();
	//CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(rabbit_mover_catch_index);
	//CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(rabbit_mover_missbomb_index);
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
		//if( rabbit_mover_catch_index != BuildingScene::m_bgmIndex ) STOP_EFFECT(rabbit_mover_catch_index);
	#endif
	PLAY_EFFECT( movers_sfx_catch );
	//auto xl = -32;
	//if( _beginVelocity.x > 0 ) xl = 32;
	//runAction( EaseElasticOut::create( MoveBy::create( 0.1f , Vec2( xl , -42 ) ) ) );
	//runAction( EaseElasticInOut::create( ScaleTo::create( 0.5f , 0 ) ) );
	//scheduleOnce( schedule_selector( ThrowableObject::delayClear ) , 1 );
	catcher->goCatch( _beginVelocity.x , getSpriteFrame() );
	setVisible( true );
	setSpriteFrame( "score_award_100.png" );
	catcher->award100();
	BuildingScene::staticAwardScore(getOwner());
	runAction( CallFunc::create( CC_CALLBACK_0 ( ThrowableObject::doClear , this ) ) );
}

void ThrowableObject::delayClear( float dt )
{
	doClear();
}

void ThrowableObject::doClear()
{
	stopAllActions();
	removeFromParentAndCleanup( true );
}

void ThrowableObject::doMissTarget()
{
	if( _missed ) return;
	_missed = true;
	PLAY_EFFECT( movers_sfx_miss );

	auto * _toremove = this;
	for( auto Iter = flyingObjects.begin(); ; Iter++ ) 
	{ 
		if( *Iter == _toremove ) 
		{ 
			 flyingObjects.erase(Iter);
			 break;
		}
		if( Iter == flyingObjects.end() ) break;
	}
	inactiveMotion();
	//runAction( EaseElasticOut::create( MoveBy::create( 1.0f , Vec2( 0 , 240 ) ) ) );
	//runAction( EaseElasticOut::create( ScaleTo::create( 1.0f , 0 ) ) );
	setVisible( true );
	runAction( Sequence::create( 
		Animate::create( missEffect ),
		CallFunc::create( CC_CALLBACK_0 ( ThrowableObject::doClear , this ) ) ,
		NULL
		) );
	catcher->goMiss( _beginVelocity.x );

	catcher->stopActionByTag(258);

	auto ca = catcher;
	catcher->runAction(Sequence::create(DelayTime::create(1), CallFunc::create([this,ca]()
	{
		if (ca->isNormal())
		{
			return;
		}

		ca->goNormal();

	}), nullptr))->setTag(258);;

	BuildingScene::getInstance()->gameOver(getOwner(), dynamic_cast<StageSide*>(catcher->getParent())->getSide());
}

Animation * ThrowableObject::missEffect;

void ThrowableObject::prepareObjectFrames()
{
	auto sCache = SpriteFrameCache::getInstance();
	_objectFrames.clear();
	_objectFrames.push_back( sCache->getSpriteFrameByName( "throw_object_01.png" ) );
	_objectFrames.push_back( sCache->getSpriteFrameByName( "throw_object_02.png" ) );
	_objectFrames.push_back( sCache->getSpriteFrameByName( "throw_object_03.png" ) );
	_objectFrames.push_back( sCache->getSpriteFrameByName( "throw_object_04.png" ) );
	_objectFrames.push_back( sCache->getSpriteFrameByName( "throw_object_05.png" ) );
	_objectFrames.push_back( sCache->getSpriteFrameByName( "throw_object_06.png" ) );
	_objectFrames.push_back( sCache->getSpriteFrameByName( "throw_object_07.png" ) );
	_objectFrames.push_back( sCache->getSpriteFrameByName( "throw_object_08.png" ) );
	_objectFrames.push_back( sCache->getSpriteFrameByName( "throw_object_09.png" ) );
	_objectFrames.push_back( sCache->getSpriteFrameByName( "throw_object_10.png" ) );
	_objectFrames.push_back( sCache->getSpriteFrameByName( "throw_object_11.png" ) );
	_objectFrames.push_back( sCache->getSpriteFrameByName( "throw_object_12.png" ) );
	_objectFrames.push_back( sCache->getSpriteFrameByName( "throw_object_13.png" ) );
	_objectFrames.push_back( sCache->getSpriteFrameByName( "throw_object_14.png" ) );
	_objectFrames.push_back( sCache->getSpriteFrameByName( "throw_object_15.png" ) );
	_objectFrames.push_back( sCache->getSpriteFrameByName( "throw_object_16.png" ) );
	_objectFrames.push_back( sCache->getSpriteFrameByName( "throw_object_17.png" ) );
	_objectFrames.push_back( sCache->getSpriteFrameByName( "throw_object_18.png" ) );
	_objectFrames.push_back( sCache->getSpriteFrameByName( "throw_object_19.png" ) );
	_objectFrames.push_back( sCache->getSpriteFrameByName( "throw_object_20.png" ) );
	_objectFrames.push_back( sCache->getSpriteFrameByName( "throw_object_21.png" ) );
	_objectFrames.push_back( sCache->getSpriteFrameByName( "throw_object_22.png" ) );
	_objectFrames.push_back( sCache->getSpriteFrameByName( "throw_object_23.png" ) );
	_objectFrames.push_back( sCache->getSpriteFrameByName( "throw_object_24.png" ) );
	_objectFrames.push_back( sCache->getSpriteFrameByName( "throw_object_25.png" ) );
	_objectFrames.push_back( sCache->getSpriteFrameByName( "throw_object_26.png" ) );
	_objectFrames.push_back( sCache->getSpriteFrameByName( "throw_object_27.png" ) );
	_objectFrames.push_back( sCache->getSpriteFrameByName( "throw_object_28.png" ) );
	_objectFrames.push_back( sCache->getSpriteFrameByName( "throw_object_29.png" ) );
	_objectFrames.push_back( sCache->getSpriteFrameByName( "throw_object_30.png" ) );
	_objectFrames.push_back( sCache->getSpriteFrameByName( "throw_object_31.png" ) );

	missEffect = Animation::create();
	missEffect->addSpriteFrame( sCache->getSpriteFrameByName( "object_catch_miss_effect_01.png" ) );
	missEffect->addSpriteFrame( sCache->getSpriteFrameByName( "object_catch_miss_effect_02.png" ) );
	missEffect->addSpriteFrame( sCache->getSpriteFrameByName( "object_catch_miss_effect_03.png" ) );
	missEffect->addSpriteFrame( sCache->getSpriteFrameByName( "object_catch_miss_effect_04.png" ) );
	missEffect->setDelayPerUnit( 0.04f );
	missEffect->setRestoreOriginalFrame(false);
	missEffect->setLoops(1);//重复次数 （-1:无限循环）
	AnimationCache::getInstance()->addAnimation( missEffect , "object_catch_miss_effect" );

	ThrowableBomb::preloadBoomAnimation();
}

float ThrowableObject::getTimeScale()
{
	return _timeScale;
}

ThrowableObject::ThrowableObject():
_actived( false ),
_beginVelocity( 0 , 0 ),
_beginTime( 0 ),
_lifeTime( 0 ),
_rotationVelocity( 0 ),
_beginPosition( 0 , 0 ),
_targetPosition( 0 , 0 )
{
}

bool ThrowableObject::init()
{
	if( !Sprite::init() ) return false;

	setSpriteFrame( _objectFrames[random(0 , 30)] );

	_owner = 0;

	_side = 0;

	return true;
}

// use this if you want to slow down the time
void ThrowableObject::setTimeScale( float _scale )
{
	_timeScale = _scale;
}

// set the _beginPosition and _targetPosition;
void ThrowableObject::setTwoPoints( Vec2 _bP , Vec2 _tP , float _motionTime )
{
	auto _h = ( _tP.y - _bP.y ) * BASE_SIZE_LENGTH;

	//if( _h < 0 ) return; 
	auto _w = ( _tP.x - _bP.x ) * BASE_SIZE_LENGTH;


	_beginPosition = _bP;
    _targetPosition = _tP;

	auto _g_y = _worldGravity.y;

	/*
	auto _minVelocity = _g_y * sqrt( 2 * _h / _g_y );
	
	auto _v_y = _minVelocity + ( random( 2 , 40 ) / 10.0f );

	auto _t_1 = _v_y / _g_y;
	auto _h_1 = ( _g_y * _t_1 * _t_1 ) / 2;// -_worldGravity.y * _t_1 * _t_1;
	auto _h_2 = _h_1 - _h;
	auto _t_2 = sqrt( 2 * _h_2 / _g_y );
	auto _v_x =  _w / ( _t_1 + _t_2 );
	_beginVelocity = Vec2( _v_x , _v_y  );
	_totalTime = 0;
	*/

	auto _v_y = ( _h / _motionTime ) - ( _g_y * _motionTime / 2 );
	auto _v_x = _w / _motionTime;
	_beginVelocity = Vec2( _v_x , _v_y  );
	_beginTime = 0;
	//scheduleOnce( schedule_selector( ThrowableObject::doAcceptTarget ) , _motionTime );
	_lifeTime = _motionTime;
}

void ThrowableBomb::motionStep( float dt )
{
	float _totalTime = GameInfo::getInstance()->getCurrentGameTime() - _beginTime;
	//_totalTime += BASE_SIZE_TIME * _timeScale;
	if( _lifeTime < _totalTime )
	{
		if( _achived )
		{
			doAcceptTarget();
			_rotationVelocity = 0;
			_totalTime = _lifeTime;
		}
		else 
		{
			if( _onMark )
			{
				_onMark = false;
				//CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(rabbit_mover_catch_index);
	            //CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(rabbit_mover_missbomb_index);
				#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
					//if( rabbit_mover_catch_index != BuildingScene::m_bgmIndex ) STOP_EFFECT(rabbit_mover_catch_index);
				#endif
	            PLAY_EFFECT( movers_sfx_miss_bomb );
			}
			if( _lifeTime + HALF_METER_LIFE_AFTER < _totalTime ) doMissTarget();	
			//_totalTime = _lifeTime;
		}	
	}
	 

	auto _p_y = ( ( _totalTime * _beginVelocity.y ) + ( _totalTime * _totalTime * _worldGravity.y / 2 ) ) ;
	auto _p_x = ( ( _totalTime * _beginVelocity.x ) + ( _totalTime * _totalTime * _worldGravity.x / 2 ) ) ;

	setPosition( _beginPosition + Vec2( _p_x , _p_y ) / BASE_SIZE_LENGTH );
	setRotation( _totalTime * _rotationVelocity  );
}
// motion step with time scale 
void ThrowableObject::motionStep( float dt )
{
	float _totalTime = GameInfo::getInstance()->getCurrentGameTime() - _beginTime;
	//_totalTime += BASE_SIZE_TIME * _timeScale;
	if( _lifeTime < _totalTime )
	{
		setVisible( false );
		if( _achived )
		{
			doAcceptTarget();
			_rotationVelocity = 0;
		}
		else if( _lifeTime + HALF_METER_LIFE_AFTER < _totalTime )
		{
			doMissTarget();
		}
		_totalTime = _lifeTime;
	}
	 

	auto _p_y = ( ( _totalTime * _beginVelocity.y ) + ( _totalTime * _totalTime * _worldGravity.y / 2 ) ) ;
	auto _p_x = ( ( _totalTime * _beginVelocity.x ) + ( _totalTime * _totalTime * _worldGravity.x / 2 ) ) ;

	setPosition( _beginPosition + Vec2( _p_x , _p_y ) / BASE_SIZE_LENGTH );
	setRotation( _totalTime * _rotationVelocity  );
}

bool ThrowableObject::checkAchive()
{
	auto checkTime = _lifeTime - GameInfo::getInstance()->getCurrentGameTime() + _beginTime;
	if( checkTime < HALF_METER_LIFE_BEFORE /*&& checkTime > -HALF_METER_LIFE*/ )
	{
		_achived = true;
		auto * _toremove = this;
		for( auto Iter = flyingObjects.begin(); ; Iter++ ) 
		{ 
			if( *Iter == _toremove ) 
			{ 
				 flyingObjects.erase(Iter);
				 break;
			}
			if( Iter == flyingObjects.end() ) break;
		}
	}
	return _achived;
}

// throw out this object
void ThrowableObject::activeMotion()
{
	_achived = false;
	_actived = true;
	_missed = false;
	
	//_beginTime = GameInfo::getInstance()->getCurrentGameTime();
	_rotationVelocity = random( 400 , 900 );
	if( random( 0 ,1 ) == 0 ) _rotationVelocity = -_rotationVelocity;
	setPosition( _beginPosition );
	schedule( schedule_selector( ThrowableObject::motionStep ) );
	runAction( EaseElasticInOut::create( ScaleTo::create( _lifeTime / 2 , 1 ) ) );
}


void ThrowableObject::setBeginTime( float _time )
{
	_beginTime = _time;
}

// stop this object
void ThrowableObject::inactiveMotion()
{
	_actived = false;
	unschedule( schedule_selector( ThrowableObject::motionStep ) );
	//setRotation( 0 );
	//setPosition( 0 , 0 );
	setOpacity( 255 );
}






////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// boom!

// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
bool ThrowableBomb::init()
{
	if( !Sprite::init() ) return false;

	setSpriteFrame( "throw_object_bomb.png" );
	_fire = ParticleSystemQuad::create( PARTICLE_BOMB_FIRE );
	addChild( _fire );
	_onMark = true;
	//auto _smoke = ParticleSmoke::create();
	//addChild( _smoke );
	return true;
}


Animation * ThrowableBomb::_boom;

void ThrowableBomb::preloadBoomAnimation()
{
	auto sfCache = SpriteFrameCache::getInstance();
	_boom = Animation::create();
	_boom->addSpriteFrame( sfCache->getSpriteFrameByName( "particle_explotion_sky_001.png" ) );
	_boom->addSpriteFrame( sfCache->getSpriteFrameByName( "particle_explotion_sky_002.png" ) );
	_boom->addSpriteFrame( sfCache->getSpriteFrameByName( "particle_explotion_sky_003.png" ) );
	_boom->addSpriteFrame( sfCache->getSpriteFrameByName( "particle_explotion_sky_004.png" ) );
	_boom->addSpriteFrame( sfCache->getSpriteFrameByName( "particle_explotion_sky_005.png" ) );
	_boom->addSpriteFrame( sfCache->getSpriteFrameByName( "particle_explotion_sky_006.png" ) );
	_boom->addSpriteFrame( sfCache->getSpriteFrameByName( "particle_explotion_sky_007.png" ) );
	_boom->addSpriteFrame( sfCache->getSpriteFrameByName( "particle_explotion_sky_008.png" ) );
	_boom->addSpriteFrame( sfCache->getSpriteFrameByName( "particle_explotion_sky_009.png" ) );
	_boom->addSpriteFrame( sfCache->getSpriteFrameByName( "particle_explotion_sky_010.png" ) );
	_boom->addSpriteFrame( sfCache->getSpriteFrameByName( "particle_explotion_sky_011.png" ) );
	_boom->addSpriteFrame( sfCache->getSpriteFrameByName( "particle_explotion_sky_012.png" ) );
	_boom->addSpriteFrame( sfCache->getSpriteFrameByName( "particle_explotion_sky_013.png" ) );
	_boom->addSpriteFrame( sfCache->getSpriteFrameByName( "particle_explotion_sky_014.png" ) );
	_boom->addSpriteFrame( sfCache->getSpriteFrameByName( "particle_explotion_sky_015.png" ) );
	_boom->addSpriteFrame( sfCache->getSpriteFrameByName( "particle_explotion_sky_016.png" ) );
	_boom->addSpriteFrame( sfCache->getSpriteFrameByName( "particle_explotion_sky_017.png" ) );
	_boom->addSpriteFrame( sfCache->getSpriteFrameByName( "particle_explotion_sky_018.png" ) );
	_boom->addSpriteFrame( sfCache->getSpriteFrameByName( "particle_explotion_sky_019.png" ) );
	_boom->addSpriteFrame( sfCache->getSpriteFrameByName( "particle_explotion_sky_020.png" ) );
	//_boom->addSpriteFrame( sfCache->getSpriteFrameByName( "particle_explotion_sky_021.png" ) );
	//_boom->addSpriteFrame( sfCache->getSpriteFrameByName( "particle_explotion_sky_022.png" ) );
	//_boom->addSpriteFrame( sfCache->getSpriteFrameByName( "particle_explotion_sky_023.png" ) );
	//_boom->addSpriteFrame( sfCache->getSpriteFrameByName( "particle_explotion_sky_024.png" ) );
	//_boom->addSpriteFrame( sfCache->getSpriteFrameByName( "particle_explotion_sky_025.png" ) );
	//_boom->addSpriteFrame( sfCache->getSpriteFrameByName( "particle_explotion_sky_026.png" ) );
	_boom->setDelayPerUnit( 0.024f );
	_boom->setRestoreOriginalFrame(false);
	_boom->setLoops(1);//重复次数 （-1:无限循环）
	AnimationCache::getInstance()->addAnimation( _boom , "rabbit_ko_boom" );
}

void ThrowableBomb::doAcceptTarget()
{
	inactiveMotion();
	//setVisible( false );
	removeChild( _fire , true );
	//scheduleOnce( schedule_selector( ThrowableObject::delayClear ) , 1 );
	setScale( 1.5 );
	PLAY_EFFECT( movers_sfx_catch_bomb );
	runAction( Sequence::create( 
		Animate::create( _boom ) ,
		FadeTo::create( 0.1f , 0 ) ,
		CallFunc::create( CC_CALLBACK_0 ( ThrowableObject::doClear , this ) ) ,
		NULL
		) );
	catcher->goKO();
	BuildingScene::getInstance()->shakeScreen();
	BuildingScene::getInstance()->gameOver(getOwner());
}

void ThrowableBomb::activeMotion()
{
	ThrowableObject::activeMotion();
	//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect( movers_sfx_throwB );
}

void ThrowableBomb::doMissTarget()
{
	if( _missed ) return;
	GameInfo::getInstance()->missBomb(getOwner());
	_missed = true;
	auto * _toremove = this;
	for( auto Iter = flyingObjects.begin(); ; Iter++ ) 
	{ 
		if( *Iter == _toremove ) 
		{ 
			 flyingObjects.erase(Iter);
			 break;
		}
		if( Iter == flyingObjects.end() ) break;
	}
	//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect( movers_sfx_miss_bomb );
	scheduleOnce( schedule_selector( ThrowableObject::delayClear ) , 2 );
	BuildingScene::staticAwardScore(getOwner());
	catcher->goMissBomb( _beginVelocity.x );
	catcher->award100();
}

