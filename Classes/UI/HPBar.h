/*----------------------------
血量UI
2016-03-01 by Azure Zheng
------------------------------*/

#ifndef __HP_BAR_H__
#define __HP_BAR_H__

#include "cocos2d.h"

USING_NS_CC;

#define MAX_HP_COUNT 3

class HPBar : public Sprite
{
public:
	
	//初始化
	bool init(const std::string & block, const Size & hpBarSize, const Vec2 & hpBlockOffset, const Vec2 & firstBlockPos);

	//创建实例
	static HPBar * create(const std::string & block, const Size & hpBarSize, const Vec2 & hpBlockOffset, const Vec2 & firstBlockPos);
	static HPBar * createWithFormat(bool isRed, bool hpBlockReverse);

	//获取血量
	int getHP();

	//设置血量
	void setHP(int hp);

	//血量减1（返回是否死亡）
	bool cutHP();

	//恢复
	void heal();

protected:

	//刷新显示
	void _refreshView();

	//血量块储存
	Vector<Sprite*> m_hpBlocks;

	//血量
	int m_hp;

	//血量总量
	int m_maxHP;

};














#endif



