#ifndef __MOVERS_TRUCK_H__
#define __MOVERS_TRUCK_H__

#include "cocos2d.h"

USING_NS_CC;

class MoversTruck : public Node
{
protected:

	Sprite * _carBody;
	Sprite * _carCircle_1;
	Sprite * _carCircle_2;

	Sprite * _rabbitHead;

public:

	void shakeCar();

	Sprite * getRabbitHead(){ return _rabbitHead; }

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(MoversTruck);

	void stopCar();

};



#endif
