/*-----------------------------
����Ϸ֧��
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

	//��ʼ��֧��
	static void init();

	//��ʼ֧��
	static void callPay(int itemID);

	//��ȡ֧�����
	static int getPayResult();

private:

	//�Ƿ��Ѿ���ʼ��֧��
	static bool m_isAlreadyInit;

	//�������ID����ú�����֮��Ĺ�ϵ
	static std::vector<EgamePay::ItemDetailsMap> m_itemList;

};





#endif


