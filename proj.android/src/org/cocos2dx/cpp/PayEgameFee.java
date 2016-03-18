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
    	
        // 游戏id（申报产品时爱游戏提供）
       gameId = "5097323";

        // 游戏名称
       gameName = "囧囧兔：搬运工";

        // 道具id（申报产品时爱游戏提供，单机游戏必传，网络游戏传"-1"字符串）
       toolId = itemID;

        // 价格（该道具的价格，单位"元"）
       price = fee;

        // cp 的id（申报产品时爱游戏提供）
       cpcodeStr = "C50017";

        // 描述（关于此道具的描述信息，会在支付页面提示用户）
       desc = description;

        // 流水号( 回调cp服务器的唯一标识 ， 网络游戏必须传，单机游戏传空字符串)
       serialStr = "";
       
       // 调用计费接口 (在主线程中调用)
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
