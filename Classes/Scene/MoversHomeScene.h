//***********************************************

// MoversHomeScene ----- home scene of game

//***********************************************

#ifndef _MOVERS_HOME_SCENE_H_
#define _MOVERS_HOME_SCENE_H_

#include "cocos2d.h"

USING_NS_CC;

#include "FilePathDefine.h"
#include "Info/GameInfo.h"
#include "UI/MoverGameUI.h"
#include "UI/BankView.h"
#include "UI/ExitGameUI.h"
#include "GlobalUtils/SpriteButton.h"
#include "Info/GameInfo.h"
#include "Objects/MoversTruck.h"
#include "GlobalUtils/KeyButtonsPackage.h"


class MoversHomeScene : public Layer
{
	MoversTruck * _car;

	Node * downHolder;

	Node * uiHolder;

	bool inOption;
	bool inMenu;

	EventListenerTouchOneByOne * _listener;

	std::function<void(Ref*)> doIntoGame;

	//第一组按钮
	KeyButtonsPackage m_buttonsList1;
	SpriteButton *buttonGame, *buttonAbout, *buttonRecord, *buttonBank;

	//第二组按钮
	KeyButtonsPackage m_buttonsList2;
	SpriteButton *buttonMod1, *buttonMod2, *buttonBack;

	//用户键盘事件派发器
	CustomKeyEventDispatcher * m_customKeyEventDispatcher;

	//商城视图
	BankView * m_bankView;

	//退出游戏UI
	ExitGameUI * m_exitGameView;

	int _playerCount;

public:
	//开启关闭第几个按钮组的选择控制
	void enableButtonsSelect(int index,bool enable);

	//额外按钮回调
	void keyExtraCallback(KeyButtonsPackage * package, CustomKeyEvent * e);

	//添加商城
	void addShop();

	//显示商城
	void showShop(Ref * ref);

	//隐藏商城
	void hideShop(Ref * ref);

	//弹出双手模式
	void showUnlockMode(Ref * ref);

	//隐藏双手模式
	void hideUnlockMode(Ref * ref);

	//刷新双手模式按钮
	void refreshMultiModeButton();

	//退出游戏
	void exitGame();

	//取消退出游戏
	void hideExitGame(Ref * ref);

	void unlockMode(Ref * ref);
	void intoMod1(Ref * ref);

	void intoMod2(Ref * ref);

	void confirmMenu(){ inMenu = true; }

	void confirmAbout(){ inOption = true; }

	bool onTouchBegan( Touch *touch , Event *event );

	void onTouchEnded( Touch *touch , Event *event );

	void onExit();

	void showAbout(Ref * ref);

	void hideOptions();

	void showRecord(Ref * ref);

	void intoGame();

	void blackScreen();

	void goToGame(Ref * ref,int playerCount);

	void goToGame1(Ref * ref);

	void goToGame2(Ref * ref);

	void goToGame3();

	void backHome(Ref * ref);

	float _bv;

	void swapCloud( float dt = 0 );

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC( MoversHomeScene );

	void loodGrass1( float dt );

	void landGrass1( float PX );

	void loodGrass2( float dt );

	void landGrass2( float PX );

	void loodMountain( float dt );

	void landMountain( float PX );

	void subBgmV( float dt );

	//添加高分计数面板UI
	void addHighScoreUI();

	//添加背景图
	void addBackWorld();

};

#endif // _MOVERS_HOME_SCENE_H_