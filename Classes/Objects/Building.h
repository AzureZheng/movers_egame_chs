/****************************************
建筑类
2016-02-02 by Azure Zheng
*****************************************/

#ifndef __BUILDING_H__
#define __BUILDING_H__


#include "cocos2d.h"
#include "Objects/BuildingStage.h"
USING_NS_CC;


class Building : public Node
{
public:
	
	//创建实例
	CREATE_FUNC(Building);

	//初始化
	virtual bool init();

	//添加一层
	void addStage();

	//移除底层
	void removeBottomStage();

	//获取楼层组
	const Vector<BuildingStage*> & getBuildingStages() const;

	//获取高层计数
	int getHighFloorIndex(){ return m_highFloor; }

	//清空楼层
	void clearFloors();

	//楼层整体移动
	void moveAllFloors(float height);

	//获取抛物层
	BuildingStage * getThrowStage();

	//获取接手层
	BuildingStage * getRecvStage();

	//设置角色标记
	void setPlayerFlag(int flag){ m_playerFlag = flag; }

	//获取角色标记
	int getPlayerFlag(){ return m_playerFlag; }

protected:

	//楼层组
	Vector<BuildingStage*> m_buildingStages;

	//最大缓存楼层数
	int m_maxStagesCache;

	//高层计数
	int m_highFloor;

	//角色标记
	int m_playerFlag;
};



#endif
