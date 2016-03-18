#include "RabbitHamal.h"

#include "FilePathDefine.h"
#include "Info\GameInfo.h"


struct HamalViewType
{
	SpriteFrame * HeadKO;
	SpriteFrame * HeadNormal;
	SpriteFrame * BodyNormal;
	SpriteFrame * ThrowObject;
	SpriteFrame * CatchEmpty;
	SpriteFrame * CatchMiss;
	SpriteFrame * BombMiss;
	SpriteFrame * CatchAccept[2];
};

std::vector<HamalViewType> RabbitHamal::RabbitHamalTypes;

void RabbitHamal::preloadAllViewTypes()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile( THROWER_CHARACTERS_PLI , createTexture( THROWER_CHARACTERS_BIG ) );
	auto sfCache = SpriteFrameCache::getInstance();
	RabbitHamalTypes.clear();
	//-------------------------------------------------  Type 01
	RabbitHamalTypes.push_back( HamalViewType() );
	RabbitHamalTypes.back().HeadKO         = sfCache->getSpriteFrameByName( "anim_rb_ko_head_m.png" );
	RabbitHamalTypes.back().HeadNormal     = sfCache->getSpriteFrameByName( "anim_rb01_head.png" );
	RabbitHamalTypes.back().BodyNormal     = sfCache->getSpriteFrameByName( "anim_rb01_body.png" );
	RabbitHamalTypes.back().ThrowObject    = sfCache->getSpriteFrameByName( "anim_rb01_throw.png" );
	RabbitHamalTypes.back().CatchEmpty     = sfCache->getSpriteFrameByName( "anim_rb01_empty.png" );
	RabbitHamalTypes.back().CatchMiss      = sfCache->getSpriteFrameByName( "anim_rb01_miss.png" );
	RabbitHamalTypes.back().CatchAccept[0] = sfCache->getSpriteFrameByName( "anim_rb01_catch_01.png" );
	RabbitHamalTypes.back().CatchAccept[1] = sfCache->getSpriteFrameByName( "anim_rb01_catch_02.png" );
	RabbitHamalTypes.back().BombMiss       = sfCache->getSpriteFrameByName( "anim_rb01_missB.png" );
	//-------------------------------------------------  Type 02
	RabbitHamalTypes.push_back( HamalViewType() );
	RabbitHamalTypes.back().HeadKO         = sfCache->getSpriteFrameByName( "anim_rb_ko_head_f.png" );
	RabbitHamalTypes.back().HeadNormal     = sfCache->getSpriteFrameByName( "anim_rb02_head.png" );
	RabbitHamalTypes.back().BodyNormal     = sfCache->getSpriteFrameByName( "anim_rb02_body.png" );
	RabbitHamalTypes.back().ThrowObject    = sfCache->getSpriteFrameByName( "anim_rb02_throw.png" );
	RabbitHamalTypes.back().CatchEmpty     = sfCache->getSpriteFrameByName( "anim_rb02_empty.png" );
	RabbitHamalTypes.back().CatchMiss      = sfCache->getSpriteFrameByName( "anim_rb02_miss.png" );
	RabbitHamalTypes.back().CatchAccept[0] = sfCache->getSpriteFrameByName( "anim_rb02_catch_01.png" );
	RabbitHamalTypes.back().CatchAccept[1] = sfCache->getSpriteFrameByName( "anim_rb02_catch_02.png" );
	RabbitHamalTypes.back().BombMiss       = sfCache->getSpriteFrameByName( "anim_rb02_missB.png" );
	//-------------------------------------------------  Type 03
	RabbitHamalTypes.push_back( HamalViewType() );
	RabbitHamalTypes.back().HeadKO         = sfCache->getSpriteFrameByName( "anim_rb_ko_head_m.png" );
	RabbitHamalTypes.back().HeadNormal     = sfCache->getSpriteFrameByName( "anim_rb03_head.png" );
	RabbitHamalTypes.back().BodyNormal     = sfCache->getSpriteFrameByName( "anim_rb03_body.png" );
	RabbitHamalTypes.back().ThrowObject    = sfCache->getSpriteFrameByName( "anim_rb03_throw.png" );
	RabbitHamalTypes.back().CatchEmpty     = sfCache->getSpriteFrameByName( "anim_rb03_empty.png" );
	RabbitHamalTypes.back().CatchMiss      = sfCache->getSpriteFrameByName( "anim_rb03_miss.png" );
	RabbitHamalTypes.back().CatchAccept[0] = sfCache->getSpriteFrameByName( "anim_rb03_catch_01.png" );
	RabbitHamalTypes.back().CatchAccept[1] = sfCache->getSpriteFrameByName( "anim_rb03_catch_02.png" );
	RabbitHamalTypes.back().BombMiss       = sfCache->getSpriteFrameByName( "anim_rb03_missB.png" );
	//-------------------------------------------------  Type 04
	RabbitHamalTypes.push_back( HamalViewType() );
	RabbitHamalTypes.back().HeadKO         = sfCache->getSpriteFrameByName( "anim_rb_ko_head_m.png" );
	RabbitHamalTypes.back().HeadNormal     = sfCache->getSpriteFrameByName( "anim_rb04_head.png" );
	RabbitHamalTypes.back().BodyNormal     = sfCache->getSpriteFrameByName( "anim_rb04_body.png" );
	RabbitHamalTypes.back().ThrowObject    = sfCache->getSpriteFrameByName( "anim_rb04_throw.png" );
	RabbitHamalTypes.back().CatchEmpty     = sfCache->getSpriteFrameByName( "anim_rb04_empty.png" );
	RabbitHamalTypes.back().CatchMiss      = sfCache->getSpriteFrameByName( "anim_rb04_miss.png" );
	RabbitHamalTypes.back().CatchAccept[0] = sfCache->getSpriteFrameByName( "anim_rb04_catch_01.png" );
	RabbitHamalTypes.back().CatchAccept[1] = sfCache->getSpriteFrameByName( "anim_rb04_catch_02.png" );
	RabbitHamalTypes.back().BombMiss       = sfCache->getSpriteFrameByName( "anim_rb04_missB.png" );
	//-------------------------------------------------  Type 05
	RabbitHamalTypes.push_back( HamalViewType() );
	RabbitHamalTypes.back().HeadKO         = sfCache->getSpriteFrameByName( "anim_rb_ko_head_f.png" );
	RabbitHamalTypes.back().HeadNormal     = sfCache->getSpriteFrameByName( "anim_rb05_head.png" );
	RabbitHamalTypes.back().BodyNormal     = sfCache->getSpriteFrameByName( "anim_rb05_body.png" );
	RabbitHamalTypes.back().ThrowObject    = sfCache->getSpriteFrameByName( "anim_rb05_throw.png" );
	RabbitHamalTypes.back().CatchEmpty     = sfCache->getSpriteFrameByName( "anim_rb05_empty.png" );
	RabbitHamalTypes.back().CatchMiss      = sfCache->getSpriteFrameByName( "anim_rb05_miss.png" );
	RabbitHamalTypes.back().CatchAccept[0] = sfCache->getSpriteFrameByName( "anim_rb05_catch_01.png" );
	RabbitHamalTypes.back().CatchAccept[1] = sfCache->getSpriteFrameByName( "anim_rb05_catch_02.png" );
	RabbitHamalTypes.back().BombMiss       = sfCache->getSpriteFrameByName( "anim_rb05_missB.png" );
	
}


// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
bool RabbitHamal::init()
{
	if( !HeadShaker::init() ) return false;
	int tS = RabbitHamalTypes.size();
	if( tS == 0 ) return false;
	_normal = true;
	_ko = false;
	//--------------------------------
	viewType = &(RabbitHamalTypes[random(0 , tS-1 )]);
	_head->setSpriteFrame( viewType->HeadNormal );
	//addChild( _head , 2 );
	_body->setSpriteFrame( viewType->BodyNormal );
	//addChild( _body , 1 );
	//--------------------------------
	return true;
}

// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
bool RabbitHamalBoss::init()
{
	if( !HeadShaker::init() ) return false;
	int tS = RabbitHamalTypes.size();
	if( tS == 0 ) return false;
	_normal = true;
	_ko = false;
	//--------------------------------
	viewType = &(RabbitHamalTypes[0]);
	_head->setSpriteFrame( viewType->HeadNormal );
	//addChild( _head , 2 );
	_body->setSpriteFrame( viewType->BodyNormal );
	//addChild( _body , 1 );
	//--------------------------------
	return true;
}

void RabbitHamal::shakeHead()
{
	if( _ko ) return;
	_head->stopAllActions();
	_head->runAction( Sequence::create( 
		MoveTo::create( 0.02f , Vec2( 0 , -6 ) ) ,
		MoveTo::create( 0.1f , Vec2( 0 , 0 ) ) ,
		NULL
	) );
}

void RabbitHamal::reLife()
{
	_ko = false;
	_head->setSpriteFrame( viewType->HeadNormal );
	goNormal();
}

void RabbitHamal::goKO()
{
	_normal = false;
	_body->setFlippedX( false );
	_head->setVisible( true );
	_body->stopAllActions();
	_body->setSpriteFrame( viewType->BodyNormal );
	_head->setSpriteFrame( viewType->HeadKO );
}

void RabbitHamal::goNormal( float dt )
{
	_body->stopAllActions();
	_head->stopAllActions();
	_body->setPosition( 0 , 0 );
	_body->setRotation( 0 );
	_head->setPosition( 0 , 0 );
	_head->setRotation( 0 );
	if( _ko ) return;
	_normal = true;
	_body->setFlippedX( false );
	_head->setVisible( true );
	_head->setSpriteFrame(viewType->HeadNormal);
	_body->setSpriteFrame( viewType->BodyNormal );
}

void RabbitHamal::goMissBomb( float speed )
{
	if( _ko ) return;
	_normal = false;
	_head->setVisible( false );
	_body->stopAllActions();
	_body->setSpriteFrame( viewType->BombMiss );
	if( speed > 0 )
	{
		_body->setFlippedX( true );
		_body->setPositionX( 25 );
		_body->setRotation( 16 );
	}
	else
	{
		_body->setFlippedX( false );
		_body->setPositionX( -25 );
		_body->setRotation( -16 );
	}
	_body->runAction( EaseElasticInOut::create( MoveTo::create( 0.1f , Vec2( 0 , 0 ) ) ) );
	_body->runAction( EaseElasticInOut::create( RotateTo::create( 0.1f , 0 ) ) );
	
	scheduleOnce( schedule_selector( RabbitHamal::goNormal ) , 0.16f );
}

void RabbitHamal::doNormal()
{
	goNormal();
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("RabbitTalkFinish",this);
}

void RabbitHamal::goTalk()
{
	_head->setVisible( false );
	_body->stopAllActions();
	auto loader = Animation::create();
	loader->addSpriteFrame( SpriteFrameCache::getInstance()->getSpriteFrameByName( "anim_rb01_talk_01.png" ) );
	loader->addSpriteFrame( SpriteFrameCache::getInstance()->getSpriteFrameByName( "anim_rb01_talk_02.png" ) );
	loader->setDelayPerUnit( 0.08f );
	loader->setRestoreOriginalFrame(true);
	loader->setLoops(6);//重复次数 （-1:无限循环）

	auto loader1 = Animation::create();
	loader1->addSpriteFrame( SpriteFrameCache::getInstance()->getSpriteFrameByName( "anim_rb01_talk_01.png" ) );
	loader1->setDelayPerUnit( 0.16f );
	loader1->setRestoreOriginalFrame(true);
	loader1->setLoops(1);//重复次数 （-1:无限循环）

	auto loader2 = Animation::create();
	loader2->addSpriteFrame( SpriteFrameCache::getInstance()->getSpriteFrameByName( "anim_rb01_talk_01.png" ) );
	loader2->addSpriteFrame( SpriteFrameCache::getInstance()->getSpriteFrameByName( "anim_rb01_talk_02.png" ) );
	loader2->setDelayPerUnit( 0.12f );
	loader2->setRestoreOriginalFrame(true);
	loader2->setLoops(5);//重复次数 （-1:无限循环）

	_body->runAction( Sequence::create(
		Animate::create( loader ) ,
		Animate::create( loader1 ) ,
		Animate::create( loader2 ) ,
		CallFunc::create( CC_CALLBACK_0 ( RabbitHamal::doNormal , this ) ) ,
		NULL
		) );
}

void RabbitHamal::goCatch( float speed , SpriteFrame * sf )
{
	if( _ko ) return;
	_normal = false;
	_head->setVisible( true );
	_body->stopAllActions();
	auto loader = Animation::create();
	loader->addSpriteFrame( viewType->CatchAccept[0] );
	loader->addSpriteFrame( viewType->CatchAccept[1] );
	loader->setDelayPerUnit( 0.08f );
	loader->setRestoreOriginalFrame(false);
	loader->setLoops(1);//重复次数 （-1:无限循环）
	_body->runAction( Animate::create( loader ) );
	auto xl = -32;
	if( speed > 0 )
	{
		xl = 32;
		_body->setFlippedX( true );
	}
	else
	{
		_body->setFlippedX( false );
	}
	auto obj = Sprite::createWithSpriteFrame( sf );
	addChild( obj , 4 );
	obj->runAction( EaseElasticOut::create( MoveBy::create( 0.1f , Vec2( xl , -48 ) ) ) );
	obj->runAction( EaseElasticInOut::create( ScaleTo::create( 0.5f , 0 ) ) );
	scheduleOnce( schedule_selector( RabbitHamal::goNormal ) , MIN_METER_TIME );

	shakeHead();
}

void RabbitHamal::goThrow()
{
	if( _ko ) return;
	_head->setVisible( false );
	_body->stopAllActions();
	_body->setSpriteFrame( viewType->ThrowObject );
	scheduleOnce( schedule_selector( RabbitHamal::goNormal ) , 0.16f );
	_body->setPositionY( 14 );
	_body->runAction( EaseElasticInOut::create( MoveTo::create( 0.1f , Vec2( 0 , 0 ) ) ) );
}

void RabbitHamal::award100()
{
	auto _score = Sprite::create();
	_score->setSpriteFrame( "score_award_100.png" );
	addChild( _score , 5 );
	_score->setScale( 0 );
	_score->runAction( MoveBy::create( 0.1f , Vec2( 0 , 72 ) ) );
	_score->runAction( Sequence::create( 
		ScaleTo::create( 0.1f , 1 ) ,
		FadeTo::create( 0.4f , 0 ) ,
		RemoveSelf::create() ,
		NULL
		) );
}

void RabbitHamal::goEmpty( float dt )
{
	if( _ko ) return;
	if(!_normal) goNormal();

	_head->setVisible( false );
	_body->stopAllActions();
	_body->setSpriteFrame( viewType->CatchEmpty );
	//scheduleOnce( schedule_selector( RabbitHamal::goNormal ) , 0.3 );
	_body->setPositionY( 20 );
	_body->runAction( EaseElasticInOut::create( MoveTo::create( 0.1f , Vec2( 0 , 0 ) ) ) );
}

void RabbitHamal::goMiss(  float speed  )
{
	_normal = false;
	if( _ko ) _head->setVisible( true );
	else
	{	
		_head->setVisible( false );
		_body->setSpriteFrame( viewType->CatchMiss );
		//scheduleOnce( schedule_selector( RabbitHamal::goNormal ) , 0.16 );
	}
	_body->stopAllActions();
	if( speed > 0 )
	{
		_body->setFlippedX( true );
		_body->setPositionX( 25 );
		_body->setRotation( 16 );
		_head->setPositionX( 25 );
		_head->setRotation( 16 );
	}
	else
	{
		_body->setFlippedX( false );
		_body->setPositionX( -25 );
		_body->setRotation( -16 );
		_head->setPositionX( -25 );
		_head->setRotation( -16 );
	}
	_body->runAction( EaseElasticInOut::create( MoveTo::create( 0.1f , Vec2( 0 , 0 ) ) ) );
	_body->runAction( EaseElasticInOut::create( RotateTo::create( 0.1f , 0 ) ) );
	_head->runAction( EaseElasticInOut::create( MoveTo::create( 0.1f , Vec2( 0 , 0 ) ) ) );
	_head->runAction( EaseElasticInOut::create( RotateTo::create( 0.1f , 0 ) ) );
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<HeadShaker*> HeadShaker::_allShakers;

void HeadShaker::shakeAllHeads()
{
	for( auto &shaker : _allShakers )
	{
		shaker->shakeHead();
	}
}

void HeadShaker::onExit()
{
	Sprite::onExit();
	HeadShaker * _toremove = this;
	for( auto Iter = _allShakers.begin(); ; Iter++ ) 
	{ 
		if( *Iter == _toremove ) 
		{ 
			 _allShakers.erase(Iter);
			 break;
		}
		if( Iter == _allShakers.end() ) break;
	}
}


bool HeadShaker::init()
{
	if( !Sprite::init() ) return false;
	_head = Sprite::create();
	addChild( _head , 2 );
	_body = Sprite::create();
	addChild( _body , 1 );
	_allShakers.push_back( this );
	return true;
}

void HeadShaker::flipX()
{
	_head->setFlippedX( true );
	_body->setFlippedX( true );
}

void HeadShaker::setHead( SpriteFrame * sf , int _zorder )
{
	_head->setLocalZOrder( _zorder );
	_head->setSpriteFrame( sf );
	setTexture( _head->getTexture() );
}

void HeadShaker::setBody( SpriteFrame * sf , int _zorder )
{
	_body->setLocalZOrder( _zorder );
	_body->setSpriteFrame( sf );
}

void HeadShaker::setHead( const char * sf_name , int _zorder )
{
	_head->setLocalZOrder( _zorder );
	_head->setSpriteFrame( sf_name );
	setTexture( _head->getTexture() );
}

void HeadShaker::setBody( const char * sf_name , int _zorder )
{
	_body->setLocalZOrder( _zorder );
	_body->setSpriteFrame( sf_name );
}


void HeadShaker::shakeHead()
{
	_head->stopAllActions();
	_head->runAction( Sequence::create( 
		MoveTo::create( 0.02f , Vec2( 0 , -4 ) ) ,
		MoveTo::create( 0.1f , Vec2( 0 , 0 ) ) ,
		NULL
	) );
}


