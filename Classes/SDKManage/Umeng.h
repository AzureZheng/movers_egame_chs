/*-----------------------------
友盟统计
	2016-03-10  by Azure Zheng
-------------------------------*/

#ifndef __UMENG_H__
#define __UMENG_H__

#include <string>

class Umeng
{
public:
	
	//真实消费统计
	static void pay(double money, double coin, int source);

	//虚拟消费统计
	static void buy(const std::string & item, int number, double price);

	//物品消耗统计
	static void use(const std::string & item, int number, double price);

	//自定义数字属性事件
	static void userEvent(const std::string & eventName, const std::string & eventNumber);


};





#endif


