package org.cocos2dx.cpp;

import com.umeng.analytics.game.UMGameAgent;

import android.content.Context;
import android.util.Log;

public class Umeng {

	private static Context context = null;
	
	public static void init(Context c)
	{
		context = c;
        UMGameAgent.setDebugMode(true);//�����������ʱ��־
        UMGameAgent.init(c);
	}
	
	//��ʵ����ͳ��
	public static void pay(double money, double coin, int source)
	{
		Log.d("Umeng Pay:",money+"");
		UMGameAgent.pay(money,coin,source);
	}
	
	//��������ͳ��
	public static void buy(String item, int number,double price) 
	{
		Log.d("Umeng Buy:",item);
		UMGameAgent.buy(item, number,price);
	}
	
	//��Ʒ����ͳ��
	public static void use(String item, int number,double price)
	{
		Log.d("Umeng Use:",item);
		UMGameAgent.use(item, number,price);
	}
	
	//�Զ������������¼�
	public static void userEvent(String eventName,String eventNumber)
	{
		Log.d("Umeng Event:",eventName);
		UMGameAgent.onEvent(context, eventName, eventNumber);
	}
}
