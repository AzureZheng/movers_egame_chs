/****************************************
楼层基类
2016-02-01 by Azure Zheng
*****************************************/

#ifndef __BUILDING_STAGE_H__
#define __BUILDING_STAGE_H__

#include "cocos2d.h"
#include "Objects/StageSide.h"

USING_NS_CC;

class BuildingStage : public Node
{
public:

	//创建楼层
	CREATE_FUNC(BuildingStage);
	
	//初始化楼层
	virtual bool init();

	//获取层别
	int getFloorIndex(){ return m_floorIndex; }

	//设置层别
	void setFloorIndex(int index){ m_floorIndex = index; }

	//创建一个普通层
	static BuildingStage * createNormalFloor(int floorIndex);

	//创建一个第一层
	static BuildingStage * createFirstFloor(bool noLeft = false);

	//获取左右兔子实例(0:右;1:左)
	RabbitHamal * getSideRabbit(int side);

	//获取楼层实例(0:右;1:左)
	StageSide * getStageSide(int side);

	//初始化一个普通层
	void initNormalStage();

	//初始化第一层
	void initFirstStage(bool noLeft = false);

	//获取楼层大小
	virtual Size getStageSize();

	//设置楼层大小
	virtual void setStageSize(Size stageSize);

	//添加楼层牌
	void addFloorBoard();

	//添加新纪录牌
	void addHighFloorMark();

	//隐藏显示楼层牌
	void setFloorBoardVisible(bool visible);

	//添加悬挂线
	void addFloorLine();

	//隐藏显示悬挂线
	void setFloorLineVisible(bool visible);

	//添加衣服线
	void addClothLine();

	//添加床单线
	void addBedSheet();

	//添加鸟线
	void addBirdLine();

	//标记该层的左右边出现兔子
	void signRabbitSide(int side){ m_rabbitSide = side; }

	//获取该层兔子的左右
	int getRabbitSide(){ return m_rabbitSide; }

protected:

	//第几层
	int m_floorIndex;

	//悬挂线
	Node * m_lines;

	//楼层牌
	Sprite * m_floorBoard;

	//新纪录牌
	Sprite * m_highFloorMark;

	//楼层边
	StageSide * m_stageSides[2];

	//楼层大小
	Size m_stageSize;

	//标记左右兔子
	int m_rabbitSide;
};


#endif
