//***********************************************

// MoverGameUI

//***********************************************

#ifndef _MOVER_GAMEPLAY_UI_H_
#define _MOVER_GAMEPLAY_UI_H_

#include "cocos2d.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GlobalUtils/KeyButtonsPackage.h"
#include "HPBar.h"

USING_NS_CC;

#include "..\FilePathDefine.h"
#include "..\Info\GameInfo.h"

using namespace ui;

class MoverGameplayUI : public Layer
{
protected:
	Widget * _ui;
	Sprite * _best_Holder;
	Sprite * _countDown;
	SpriteButton * _button_Pause;
	LabelAtlas * _best_Score;

	LabelAtlas * _current_Score;
	LabelAtlas * _current_Score2;

	int _viewScore;
	int _targetScore;


	//血槽
	Vector<HPBar*> m_hpBars;

public:

	//获取血槽(第几个)
	HPBar * getHpBar(int index){ return m_hpBars.at(index); }
	
	//创建血槽
	void _addHpBar();

	void updateScoreView( float dt );

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC( MoverGameplayUI );

	SpriteButton * getPauseButton(){ return _button_Pause; }

	void resetBestScore();

	void awardScore(int playerID, int _score );

	
	void lockControl();

	void unlockControl();

	void countDown( int _count );

};


//*******************************************************************************************************************

class MoverGamepauseUI : public Layer
{
protected:
	Layout * _ui;
	SpriteButton * _button_Retry;
	SpriteButton * _button_Continue;
	SpriteButton * _button_Home;

	KeyButtonsPackage m_buttons;

public:

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC( MoverGamepauseUI );

	SpriteButton * getContinueButton(){ return _button_Continue; }

	SpriteButton * getRetryButton(){ return _button_Retry; }

	SpriteButton * getHomeButton(){ return _button_Home; }

	void setLocked(bool lock);

	void resetSelectButton(){ m_buttons.setSelectedButton(_button_Continue); }

};

//*******************************************************************************************************************

class MoverResultUI : public Layer
{
protected:

	Layout * _ui;
	SpriteButton * _button_Retry;
	SpriteButton * _button_Home;

	KeyButtonsPackage m_buttons;

	Widget * _top_View;
	Widget * _back_View;

	Sprite * _record_Score;
	Sprite * _record_Level;
	Sprite * _record_Goods;
	Sprite * _record_Bomb;

	LabelAtlas * _levels;
	LabelAtlas * _goods;
	LabelAtlas * _bombs;
	LabelAtlas * _score;

    int _toAdd;

	int _viewValue;
	int _targetValue;

public:

	void scoreEffectLoop( float dt );

	void lockButtons();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC( MoverResultUI );

	SpriteButton * getHomeButton(){ return _button_Home; }

	SpriteButton * getRetryButton(){ return _button_Retry; }

	Node * getBackView(){ return _back_View; };

	void popUpView();

	void hideDownView();

	void delayViewResult( float dt );

	void updateLevels( float dt );

	void updateGoods( float dt );

	void updateBombs( float dt );

	void updateScore( float dt );

};

#endif // _MOVER_GAMEPLAY_UI_H_
