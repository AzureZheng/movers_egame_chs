/****************************************
楼层一边
2016-02-01 by Azure Zheng
*****************************************/


#ifndef __STAGE_SIDE_H__
#define __STAGE_SIDE_H__

#include "cocos2d.h"
#include "Objects/RabbitHamal.h"

USING_NS_CC;

class StageSide : public Node
{
public:

	//按模板来创建实例(0:右普通;1:左普通;2:右一层;3:左一层)
	static StageSide * createWithType(int type);

	//创建实例
	CREATE_FUNC(StageSide);

	//初始化
	virtual bool init();

	//获取兔子实例
	RabbitHamal * getRabbit();

	//设置兔子实例
	void setRabbit(RabbitHamal * rabbit);

	//清空兔子
	void clearRabbit();

	//获取左右
	int getSide(){ return m_side; }

	//设置左右
	void setSide(int side,bool flipped = true);

	//设置建筑翻转
	void setBuildingFlipped(bool flipped);

	//设置栏杆图形
	void setRail(Sprite * rail);

	//设置墙壁图形
	void setWall(Sprite * wall);

	//兔子出现
	void showRabbit(float dt = 0.5f);

	//隐藏兔子
	void hideRabbit();

	//设置兔子方位
	void refreshRabbitPos();

	//获取兔子是否隐藏
	bool isRabbitHide(){ return m_hideRabbit; }

	//获取墙壁大小
	Size getWallSize();

	//显示你
	void showYou(bool fourPlayer = false);

	//隐藏你
	void hideYou();

protected:

	//位于(0:左；1:右)
	int m_side;
	
	//是否翻转
	bool m_isFlipped;

	//兔子实例
	RabbitHamal * m_rabbit;

	//栏杆
	Sprite * m_rail;

	//墙壁
	Sprite * m_wall;

	//兔子是否隐藏
	bool m_hideRabbit;

	//墙壁大小
	Size m_wallSize;

};


#endif
