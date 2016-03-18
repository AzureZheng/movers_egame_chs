//***********************************************

// ThrowableObject

//***********************************************
#ifndef _RABBIT_HAMAL_MOVER_H_
#define _RABBIT_HAMAL_MOVER_H_

#include "cocos2d.h"

USING_NS_CC;


struct HamalViewType;

class HeadShaker : public Sprite
{
protected:

	Sprite * _head;

	Sprite * _body;
	
	static std::vector<HeadShaker*> _allShakers;

public:

	void flipX();

	void onExit();

	static void shakeAllHeads();

	void setHead( SpriteFrame * sf , int _zorder = 2 );

	void setBody( SpriteFrame * sf , int _zorder = 1 );

	void setHead( const char * sf_name , int _zorder = 2 );

	void setBody( const char * sf_name , int _zorder = 1 );

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC( HeadShaker );

	virtual void shakeHead();

};

// the basic class of all throwable objects
class RabbitHamal : public HeadShaker 
{
protected:

	//Sprite * _head;

	//Sprite * _body;

	static std::vector<HamalViewType> RabbitHamalTypes;

	HamalViewType * viewType;

	bool _normal;

	bool _ko;

public:

	void reLife();

	void goKO();

	void goNormal( float dt = 0 );

	void doNormal();

	void goCatch( float speed , SpriteFrame * sf );

	void goMissBomb( float speed );

	void goThrow();

	void goEmpty( float dt = 0 );

	void goMiss( float speed );

	void shakeHead();

	void award100();

	static void preloadAllViewTypes();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC( RabbitHamal );

	void goTalk();

	void setKO(bool ko){ _ko = ko; }

	bool isKO(){ return _ko; }

	bool isNormal(){ return _normal; }
};

class RabbitHamalBoss : public RabbitHamal
{
protected:

public:

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC( RabbitHamalBoss );

};

#endif // _RABBIT_HAMAL_MOVER_H_
