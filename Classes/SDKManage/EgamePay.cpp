#include "EgamePay.h"

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#endif

USING_NS_CC;

//是否已经初始化支付
bool EgamePay::m_isAlreadyInit = false;

//储存道具ID与费用和描述之间的关系
std::vector<EgamePay::ItemDetailsMap> EgamePay::m_itemList;

//初始化支付
void EgamePay::init()
{
	m_isAlreadyInit = true;

	EgamePay::ItemDetailsMap idm;

	idm.packageID = 1;
	idm.itemID = "5395118";
	idm.fee = "1";
	idm.description = FileUtils::getInstance()->getStringFromFile("Tables/0001.dat");
	m_itemList.push_back(idm);


	idm.packageID = 2;
	idm.itemID = "5395119";
	idm.fee = "5";
	idm.description = FileUtils::getInstance()->getStringFromFile("Tables/0002.dat");
	m_itemList.push_back(idm);


	idm.packageID = 3;
	idm.itemID = "5395120";
	idm.fee = "10";
	idm.description = FileUtils::getInstance()->getStringFromFile("Tables/0003.dat");
	m_itemList.push_back(idm);
}



//开始支付
void EgamePay::callPay(int itemID)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	if (!m_isAlreadyInit) init();

	JniMethodInfo minfo;

	JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/cpp/PayEgameFee", "pay", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");

	auto env = JniHelper::getEnv();
	std::string itemStr("");
	std::string itemFee("");
	std::string itemDesc("");

	for (auto & i:m_itemList)
	{
		if (i.packageID == itemID)
		{
			itemStr = i.itemID;
			itemFee = i.fee;
			itemDesc = i.description;
			break;
		}
	}

	if (itemStr.empty()) return;

	env->CallStaticVoidMethod(minfo.classID, minfo.methodID, env->NewStringUTF(itemStr.c_str()),
		env->NewStringUTF(itemFee.c_str()), env->NewStringUTF(itemDesc.c_str()));

	env->DeleteLocalRef(minfo.classID);
#endif
}



//获取支付结果
int EgamePay::getPayResult()
{
	int result = -1;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

	JniMethodInfo minfo;

	JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/cpp/PayEgameFee", "getPayResult", "()I");

	result = JniHelper::getEnv()->CallStaticIntMethod(minfo.classID,minfo.methodID);
	JniHelper::getEnv()->DeleteLocalRef(minfo.classID);

	if(result > -1)
	{
		JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/cpp/PayEgameFee", "setPayResult", "(I)V");
		JniHelper::getEnv()->CallStaticVoidMethod(minfo.classID, minfo.methodID,-1);
		JniHelper::getEnv()->DeleteLocalRef(minfo.classID);
	}

#endif
	return result;
}
