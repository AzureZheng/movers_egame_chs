//***********************************************

// ThrowableObject

//***********************************************
#ifndef _THROEABLE_OBJECT_H_
#define _THROEABLE_OBJECT_H_

#include "cocos2d.h"
#include "RabbitHamal.h"

USING_NS_CC;


// the basic class of all throwable objects
class ThrowableObject : public Sprite
{
protected:
	static unsigned int rabbit_mover_catch_index;

	static unsigned int rabbit_mover_missbomb_index;

	static Animation * missEffect;

	bool _actived;

	static std::vector<SpriteFrame*> _objectFrames;

	static Vec2  _worldGravity;

	static float _timeScale;

	double _beginTime;

	float _lifeTime;

	Vec2 _beginVelocity; 

	float _rotationVelocity;

	Vec2 _beginPosition;

	Vec2 _targetPosition;
	
	bool  _achived;

	bool  _missed;

	RabbitHamal *catcher;

	int _owner;

	int _side;

public:

	float getVX(){ return _beginVelocity.x; }

	void setCatcher( RabbitHamal *_catcher ){ catcher = _catcher; }

	void delayClear( float dt );

	void doClear();

	virtual void doMissTarget();

	virtual void doAcceptTarget();

	bool checkAchive();

	void setOwner(int owner){ _owner = owner; }

	int getOwner(){ return _owner; }

	void setSide(int side){ _side = side; }

	int getSide(){ return _side; }

	static std::vector<ThrowableObject*> flyingObjects;

	void setBeginTime( float _time );

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	static float getTimeScale();

	static void prepareObjectFrames();

	// use this if you want to slow down the time
	static void setTimeScale( float _scale );

    ThrowableObject();

	// set the _beginPosition and _targetPosition £¬then a parabolic curve is done
	void setTwoPoints( Vec2 _bP , Vec2 _tP , float _motionTime = 1.0f );

    // implement the "static create()" method manually
    CREATE_FUNC(ThrowableObject);

	// motion step with time scale
	virtual void motionStep( float dt );

	// throw out this object
	virtual void activeMotion();

	// stop this object
	virtual void inactiveMotion();

};

// the bomb
class ThrowableBomb : public ThrowableObject
{
protected:

	static Animation * _boom;
	ParticleSystemQuad * _fire;

	bool _onMark;
public:

	static void preloadBoomAnimation();

	void doMissTarget();

	void doAcceptTarget();

	void motionStep( float dt );

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(ThrowableBomb);

	void activeMotion();
};




#endif // _THROEABLE_OBJECT_H_
