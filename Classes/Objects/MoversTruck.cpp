#include "MoversTruck.h"

bool MoversTruck::init()
{
	if (!Node::init()) return false;

	_carBody = Sprite::createWithSpriteFrameName("mover_home_car_body.png");
	addChild(_carBody, 2);

	_carCircle_1 = Sprite::createWithSpriteFrameName("mover_home_car_roll.png");
	_carCircle_2 = Sprite::createWithSpriteFrameName("mover_home_car_roll.png");

	_carCircle_1->setPosition(convertToNodeSpace(_carBody->convertToWorldSpace(Vec2(214, 131))));
	_carCircle_2->setPosition(convertToNodeSpace(_carBody->convertToWorldSpace(Vec2(532, 131))));
	addChild(_carCircle_1, 3);
	addChild(_carCircle_2, 3);
	_carCircle_1->runAction(RepeatForever::create(RotateBy::create(0.1, Vec3(0, 0, -180))));
	_carCircle_2->runAction(RepeatForever::create(RotateBy::create(0.1, Vec3(0, 0, -180))));

	_rabbitHead = Sprite::createWithSpriteFrameName("mover_home_rabbit_head.png");
	_rabbitHead->setPosition(208, 380);
	_carBody->addChild(_rabbitHead, 2);
	_rabbitHead->runAction(RepeatForever::create(Sequence::create(
		RotateTo::create(0.2, 6),
		RotateTo::create(0.4, -6),
		RotateTo::create(0.2, 0),
		NULL
		)));
	_rabbitHead->runAction(RepeatForever::create(Sequence::create(
		MoveBy::create(0.2, Vec2(0, -6)),
		MoveBy::create(0.2, Vec2(0, 6)),
		NULL
		)));

	auto _shadow = Sprite::createWithSpriteFrameName("mover_home_car_shadow.png");
	addChild(_shadow, 1);

	shakeCar();

	return true;
}

void MoversTruck::shakeCar()
{
	_carBody->runAction(Sequence::create(
		MoveTo::create(((float)random(8, 14)) / 100, Vec2(0, random(0, 6))),
		MoveTo::create(((float)random(8, 14)) / 100, Vec2(0, -random(0, 3))),
		CallFunc::create(CC_CALLBACK_0(MoversTruck::shakeCar, this)),
		NULL
		));
}


void MoversTruck::stopCar()
{
	_carCircle_1->stopAllActions();
	_carCircle_2->stopAllActions();
	_carBody->stopAllActions();
	_carBody->setPositionY(0);
}

