#include "PlayerLayer.h"
#include "FilePathDefine.h"


//初始化
bool PlayerLayer::init()
{
	if (!ClippingRectangleNode::init())
	{
		return false;
	}

	//玩家序号
	m_playerID = 0;

	//楼层计数
	m_stageCount = 0;

	//楼层
	m_objectsHolder = nullptr;
	m_building = nullptr;

	//玩家分数
	m_viewScore = 0;
	m_score = 0;

	setClippingEnabled(false);

	setAnchorPoint(Vec2::ANCHOR_MIDDLE);

	//玩家没有阵亡
	m_isOver = false;

	//玩家没有锁定操作
	m_lockControl = false;
	m_lockControl2 = false;

	return true;
}


//创建初始楼层
void PlayerLayer::initBuilding()
{
	m_objectsHolder = Node::create();
	addChild(m_objectsHolder,0);
	m_building = Building::create();
	m_building->setPlayerFlag(m_playerID);
	m_objectsHolder->addChild(m_building, 0);
	m_building->setPositionY(-200);


	addBuildingStage();
	addBuildingStage();
	addBuildingStage();
	addBuildingStage();
}


//添加一个楼层
void PlayerLayer::addBuildingStage()
{
	m_building->addStage();
}


//设置裁剪大小
void PlayerLayer::setClippingArea(const Size & size)
{
	setContentSize(size);
	setClippingRegion(Rect(0,0,size.width,size.height));
	setClippingEnabled(true);
}


//延时增加层级
void PlayerLayer::delayUpFloor(float dt)
{
	auto act1 = EaseElasticInOut::create(MoveBy::create(1.0, Vec2(0, -BUILDING_STAGE_H)));
	auto act2 = CallFunc::create([](){Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("UpFloorFinished"); });
	auto act = Sequence::create(act1,act2,nullptr);

	m_objectsHolder->runAction(act);
}


//增加层级
void PlayerLayer::upFloor()
{
	gainStageCount();
	scheduleOnce(schedule_selector(PlayerLayer::delayUpFloor), 0.5f);
}


//刷新视野
void PlayerLayer::refreshView()
{
	auto bottomStage = m_building->getBuildingStages().at(0);
	if (bottomStage->getPosition().y >= BUILDING_STAGE_H)
	{
		m_building->moveAllFloors(-BUILDING_STAGE_H);
		m_objectsHolder->setPositionY(m_objectsHolder->getPositionY() + BUILDING_STAGE_H);
	}
}


//层级增加完毕
void PlayerLayer::upFloorFinish()
{
	m_building->addStage();
	refreshView();
}


//设置楼层视角位置
void PlayerLayer::setFloorCameraPos(const Vec2 & pos)
{
	m_objectsHolder->setPosition(pos);
}


//获取楼层视角位置
const Vec2 & PlayerLayer::getFloorCameraPos() const
{
	return m_objectsHolder->getPosition();
}


//设置楼层视角偏移
void PlayerLayer::setFloorCameraOffset(const Vec2 & offset)
{
	m_objectsHolder->setPosition(m_objectsHolder->getPosition() + offset);
}


