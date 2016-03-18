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

	//��һ�鰴ť
	KeyButtonsPackage m_buttonsList1;
	SpriteButton *buttonGame, *buttonAbout, *buttonRecord, *buttonBank;

	//�ڶ��鰴ť
	KeyButtonsPackage m_buttonsList2;
	SpriteButton *buttonMod1, *buttonMod2, *buttonBack;

	//�û������¼��ɷ���
	CustomKeyEventDispatcher * m_customKeyEventDispatcher;

	//�̳���ͼ
	BankView * m_bankView;

	//�˳���ϷUI
	ExitGameUI * m_exitGameView;

	int _playerCount;

public:
	//�����رյڼ�����ť���ѡ�����
	void enableButtonsSelect(int index,bool enable);

	//���ⰴť�ص�
	void keyExtraCallback(KeyButtonsPackage * package, CustomKeyEvent * e);

	//����̳�
	void addShop();

	//��ʾ�̳�
	void showShop(Ref * ref);

	//�����̳�
	void hideShop(Ref * ref);

	//����˫��ģʽ
	void showUnlockMode(Ref * ref);

	//����˫��ģʽ
	void hideUnlockMode(Ref * ref);

	//ˢ��˫��ģʽ��ť
	void refreshMultiModeButton();

	//�˳���Ϸ
	void exitGame();

	//ȡ���˳���Ϸ
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

	//��Ӹ߷ּ������UI
	void addHighScoreUI();

	//��ӱ���ͼ
	void addBackWorld();

};

#endif // _MOVERS_HOME_SCENE_H_