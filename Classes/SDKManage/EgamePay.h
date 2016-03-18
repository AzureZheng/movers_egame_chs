/*-----------------------------
爱游戏支付
	2016-03-02  by Azure Zheng
-------------------------------*/

#ifndef __EGAME_PAY_H__
#define __EGAME_PAY_H__

#include <string>
#include <vector>

class EgamePay
{
public:
	
	struct ItemDetailsMap
	{
		int packageID;
		std::string itemID;
		std::string fee;
		std::string description;
	};

	//初始化支付
	static void init();

	//开始支付
	static void callPay(int itemID);

	//获取支付结果
	static int getPayResult();

private:

	//是否已经初始化支付
	static bool m_isAlreadyInit;

	//储存道具ID与费用和描述之间的关系
	static std::vector<EgamePay::ItemDetailsMap> m_itemList;

};





#endif


