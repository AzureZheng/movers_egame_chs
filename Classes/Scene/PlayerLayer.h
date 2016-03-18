/****************************************
玩家游戏层
2016-02-01 by Azure Zheng
*****************************************/

#ifndef __PLAYER_LAYER_H__
#define __PLAYER_LAYER_H__

#include "cocos2d.h"
#include "Objects/Building.h"

USING_NS_CC;


class PlayerLayer : public ClippingRectangleNode
{
public:

	//创建实例
	CREATE_FUNC(PlayerLayer);

	//初始化实例
	virtual bool init();

	//设置玩家序号
	void setPlayerID(int id){ m_playerID = id; }

	//获取玩家序号
	int getPlayerID(){ return m_playerID; }

	//添加一个楼层
	void addBuildingStage();

	//获取当前楼层计数
	int getStageCount(){ return m_stageCount; }

	//获取楼层
	Building * getBuilding(){ return m_building; }

	//创建初始楼层
	void initBuilding();

	//设置裁剪大小
	void setClippingArea(const Size & size);

	//增加楼层计数
	void gainStageCount(){ m_stageCount++; }

	//延时增加层级
	void delayUpFloor(float dt);

	//增加层级
	void upFloor();

	//刷新视野
	void refreshView();

	//层级增加完毕
	virtual void upFloorFinish();

	//设置楼层视角位置
	virtual void setFloorCameraPos(const Vec2 & pos);

	//设置楼层视角偏移
	virtual void setFloorCameraOffset(const Vec2 & offset);

	//获取楼层视角位置
	virtual const Vec2 & getFloorCameraPos() const;

	//设置该玩家是否阵亡
	void setOver(bool isOver){ m_isOver = isOver; }

	//获取该玩家是否阵亡
	bool getOver(){ return m_isOver; }

	//设置锁定操作
	void setControlLocked(bool lock){ m_lockControl = lock; }
	void setControlLockedSide2(bool lock){ m_lockControl2 = lock; }

	//获取当前玩家是否被锁定操作
	bool isLockedControl(){ return m_lockControl; }
	bool isLockedControlSide2(){ return m_lockControl2; }

	//获取显示分数
	int getViewScore(){ return m_viewScore; }

	//获取目标分数
	int getScore(){ return m_score; }

	//设置显示分数
	void setViewScore(int score){ m_viewScore = score; }

	//设置目标分数
	void setSocre(int score){ m_score = score; }

	//增减目标分数
	void gainScore(int score){ m_score += score; }

	//增减显示分数
	void gainViewScore(int score){ m_viewScore += score; }

protected:

	//玩家序号
	int m_playerID;

	//楼层计数
	int m_stageCount;

	//玩家是否阵亡
	bool m_isOver;

	//锁定操作
	bool m_lockControl;
	bool m_lockControl2;

	//玩家显示分数
	int m_viewScore;

	//玩家目标分数
	int m_score;

	//------------------ 精灵固定器 --------------------
	//楼层物体固定器
	Node * m_objectsHolder;

	//楼层
	Building * m_building;


	//------------------- UI固定器 ----------------------


};



#endif
