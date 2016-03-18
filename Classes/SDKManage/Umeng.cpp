#include "Umeng.h"
#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#endif

USING_NS_CC;

//��ʵ����ͳ��
void Umeng::pay(double money, double coin, int source)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;

	JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/cpp/Umeng", "pay", "(DDI)V");
	auto env = JniHelper::getEnv();
	env->CallStaticVoidMethod(minfo.classID, minfo.methodID, money, coin, source);
	env->DeleteLocalRef(minfo.classID);
#endif
}


//��������ͳ��
void Umeng::buy(const std::string & item, int number, double price)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;

	JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/cpp/Umeng", "buy", "(Ljava/lang/String;ID)V");
	auto env = JniHelper::getEnv();
	env->CallStaticVoidMethod(minfo.classID, minfo.methodID, env->NewStringUTF(item.c_str()), number, price);
	env->DeleteLocalRef(minfo.classID);
#endif
}


//��Ʒ����ͳ��
void Umeng::use(const std::string & item, int number, double price)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;

	JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/cpp/Umeng", "use", "(Ljava/lang/String;ID)V");
	auto env = JniHelper::getEnv();
	env->CallStaticVoidMethod(minfo.classID, minfo.methodID, env->NewStringUTF(item.c_str()), number, price);
	env->DeleteLocalRef(minfo.classID);
#endif
}


//�Զ������������¼�
void Umeng::userEvent(const std::string & eventName, const std::string & eventNumber)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;

	JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/cpp/Umeng", "userEvent", "(Ljava/lang/String;Ljava/lang/String;)V");
	auto env = JniHelper::getEnv();
	env->CallStaticVoidMethod(minfo.classID, minfo.methodID, env->NewStringUTF(eventName.c_str()), env->NewStringUTF(eventNumber.c_str()));
	env->DeleteLocalRef(minfo.classID);
#endif
}
