/*-----------------------------
����ͳ��
	2016-03-10  by Azure Zheng
-------------------------------*/

#ifndef __UMENG_H__
#define __UMENG_H__

#include <string>

class Umeng
{
public:
	
	//��ʵ����ͳ��
	static void pay(double money, double coin, int source);

	//��������ͳ��
	static void buy(const std::string & item, int number, double price);

	//��Ʒ����ͳ��
	static void use(const std::string & item, int number, double price);

	//�Զ������������¼�
	static void userEvent(const std::string & eventName, const std::string & eventNumber);


};





#endif


