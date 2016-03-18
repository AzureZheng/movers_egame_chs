package org.cocos2dx.cpp;

import com.umeng.analytics.game.UMGameAgent;

import android.content.Context;
import android.util.Log;

public class Umeng {

	private static Context context = null;
	
	public static void init(Context c)
	{
		context = c;
        UMGameAgent.setDebugMode(true);//设置输出运行时日志
        UMGameAgent.init(c);
	}
	
	//真实消费统计
	public static void pay(double money, double coin, int source)
	{
		Log.d("Umeng Pay:",money+"");
		UMGameAgent.pay(money,coin,source);
	}
	
	//虚拟消费统计
	public static void buy(String item, int number,double price) 
	{
		Log.d("Umeng Buy:",item);
		UMGameAgent.buy(item, number,price);
	}
	
	//物品消耗统计
	public static void use(String item, int number,double price)
	{
		Log.d("Umeng Use:",item);
		UMGameAgent.use(item, number,price);
	}
	
	//自定义数字属性事件
	public static void userEvent(String eventName,String eventNumber)
	{
		Log.d("Umeng Event:",eventName);
		UMGameAgent.onEvent(context, eventName, eventNumber);
	}
}
