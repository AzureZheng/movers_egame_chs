package org.cocos2dx.cpp;

import com.egame.tvfee.Fee;

import android.app.Activity;


public class PayEgameFee {

	private static String gameId,gameName,toolId,price,cpcodeStr,desc,serialStr;
	
	private static int payResult = -1;
	
	private static Activity context = null;
	
	public static void init(Activity c) {
		context = c;
	}
	
    public static void pay(String itemID,String fee,String description) {

       payResult = -1;
    	
        // ��Ϸid���걨��Ʒʱ����Ϸ�ṩ��
       gameId = "5097323";

        // ��Ϸ����
       gameName = "����ã����˹�";

        // ����id���걨��Ʒʱ����Ϸ�ṩ��������Ϸ�ش���������Ϸ��"-1"�ַ�����
       toolId = itemID;

        // �۸񣨸õ��ߵļ۸񣬵�λ"Ԫ"��
       price = fee;

        // cp ��id���걨��Ʒʱ����Ϸ�ṩ��
       cpcodeStr = "C50017";

        // ���������ڴ˵��ߵ�������Ϣ������֧��ҳ����ʾ�û���
       desc = description;

        // ��ˮ��( �ص�cp��������Ψһ��ʶ �� ������Ϸ���봫��������Ϸ�����ַ���)
       serialStr = "";
       
       // ���üƷѽӿ� (�����߳��е���)
       context.runOnUiThread(new Runnable(){
		@Override
		public void run() {
			// TODO Auto-generated method stub
			Fee.pay(context, gameId, gameName, toolId, price, cpcodeStr, desc, serialStr);
		}});
       
    }
    
    public static int getPayResult() {
    	return payResult;
    }
    
    public static void setPayResult(int result) {
    	payResult = result;
    }
	
}
