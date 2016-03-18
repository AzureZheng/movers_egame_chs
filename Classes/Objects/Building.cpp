#include "Objects/Building.h"
#include "Info/GameInfo.h"

//初始化
bool Building::init()
{
	if (!Node::init())
	{
		return false;
	}

	m_highFloor = 0;

	m_maxStagesCache = 5;

	return true;
}


//添加一层
void Building::addStage()
{
	m_highFloor++;

	BuildingStage * bs = nullptr;

	if (m_highFloor == 1)
	{
		bs = BuildingStage::createFirstFloor(m_playerFlag == 1);
	}
	else
	{
		if (m_buildingStages.size() >= m_maxStagesCache)
		{
			removeBottomStage();
		}

		bs = BuildingStage::createNormalFloor(m_highFloor);
		bs->setPosition(Vec2(0, m_buildingStages.back()->getPosition().y + m_buildingStages.back()->getStageSize().height));

		//双人模式中添加中间的窗户
		if ((GameInfo::getInstance()->getModeCode() == "A1" || GameInfo::getInstance()->getModeCode() == "A2") && m_playerFlag == 1)
		{
			auto wd = Sprite::createWithSpriteFrameName("building_windows.png");
			wd->setPositionX(-313 - 173);
			bs->addChild(wd);
		}

	}

	m_buildingStages.pushBack(bs);
	addChild(bs);
}


//移除底层
void Building::removeBottomStage()
{
	if (m_buildingStages.empty()) return;

	auto iter = m_buildingStages.begin();
	(*iter)->removeFromParent();
	m_buildingStages.erase(iter);
}


//获取楼层组
const Vector<BuildingStage*> & Building::getBuildingStages() const
{
	return m_buildingStages;
}


//清空楼层
void Building::clearFloors()
{
	if (m_buildingStages.empty()) return;

	for (auto i = m_buildingStages.begin(); i != m_buildingStages.end();)
	{
		(*i)->removeFromParent();
		i = m_buildingStages.erase(i);
	}
}


//楼层整体移动
void Building::moveAllFloors(float height)
{
	for (auto & i : m_buildingStages)
	{
		i->setPositionY(i->getPositionY() + height);
	}
}


//获取抛物层
BuildingStage * Building::getThrowStage()
{
	if (m_buildingStages.size() < m_maxStagesCache)
	{
		return m_buildingStages.at(0);
	}
	else
	{
		return m_buildingStages.at(1);
	}
}


//获取接手层
BuildingStage * Building::getRecvStage()
{
	if (m_buildingStages.size() < m_maxStagesCache)
	{
		return m_buildingStages.at(1);
	}
	else
	{
		return m_buildingStages.at(2);
	}
}
