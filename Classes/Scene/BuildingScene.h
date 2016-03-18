/****************************************
建筑场景层
2016-02-01 by Azure Zheng
*****************************************/


#ifndef __BUILDING_SCENE_H__
#define __BUILDING_SCENE_H__

#include "cocos2d.h"
#include "Scene/PlayerLayer.h"
#include "Objects/MoversTruck.h"
#include "Info/GameInfo.h"
#include "UI/MoverGameUI.h"
#include "UI/BankView.h"

USING_NS_CC;



class BuildingScene : public Layer
{
public:

	//释放资源
	virtual ~BuildingScene();

	//创建场景
	static Scene * createScene(int playerCount);

	//从故事模式创建场景
	static Scene * createSceneWithStory(int playerCount);

	//创建实例
	CREATE_FUNC(BuildingScene);

	//初始化实例
	virtual bool init();

	//以人数初始化游戏
	void initWithPlayerCount(int playerCount,bool startStory = true);

	//快速开始游戏
	void quicklyStartGame();

	//创建玩家层组
	void createPlayerLayers();

	//创建单人玩家层
	void createSinglePlayerLayer();

	//创建双人玩家层
	void createDoublePlayersLayers();

	//创建多人玩家层
	void createMultiPlayersLayers();

	//获取游戏人数
	int getPlayerCount(){ return m_playerCount; }

	//创建背景层
	void addBackWorld();

	//创建前景层
	void addFrontWorld();

	//故事：开始故事
	void runWithStory();

	//故事：移车
	void moveCar(float dt = 0);

	//故事：放货
	void pushGoods();

	//故事：开门
	void openDoor();

	//故事：开腔
	void talkStart();

	//故事：走出来
	void moveOut();

	//开始一波
	virtual void startWave(float dt);

	//新开一轮
	virtual void startNewRound();

	//切换模式
	static void setGameMode(int mode){ m_gameMode = mode; }

	//获取模式
	static int getGameMode(){ return m_gameMode; }

	//获取玩家层对应的前景层位置
	Vec2 getPlayerLayerPosInFrontLayer(int layerIndex);

	//获取玩家层对应的UI层位置
	Vec2 getPlayerLayerPosInUILayer(int layerIndex);

	//时钟步骤
	void clockStep(float dt);

	//逻辑步骤
	void logicStep(float dt);

	//从字符串读取音符到音符列表中
	void readStringToGame(const std::string & _A0B);

	//读取新一轮音符
	void newWave();

	//整体爬楼
	void upFloor();

	//整体爬楼结束
	void upFloorFinish();

	//使用一个音符
	void doMeterOnce(int meterIndex);

	//读取节奏头
	void readMusicHead();

	//读取节奏身
	void readMusicBody();

	//玩家1触摸监控
	bool touchControl(Touch * touch, Event * e);

	//其他玩家触摸监控
	void touchControlMulti(int playerID, const Vec2 & touchLocation);

	//解锁玩家操作
	void unlockTouchControl(int playerID);
	void unlockTouchControlSide2(int side,int playerID = 0);

	//注册触摸监听
	void setupTouchListener();

	//预载音效
	void preloadEffect();

	//创建云朵
	void createClouds(float dt);

	//添加UI层
	void addUILayer();

	//主页按钮回调
	void gameHomeButtonCallBack(Ref* sender);

	//重试按钮回调
	void gameRetryButtonCallBack(Ref* sender);

	//暂停按钮回调
	void gamePauseButtonCallBack(Ref* sender);

	//恢复按钮回调
	void gameResumeButtonCallBack(Ref* sender);

	//恢复
	void resumeGame();

	//暂停
	void pauseGame();

	//重试
	void retryPlay();

	//主页
	void returnHome();

	//直接进入主页
	void intoHome();

	//恢复倒数
	void countDown(float dt);

	//静态增加分数
	static void staticAwardScore(int playerID,int score = 100);

	//增加分数
	void awardScore(int playerID, int score = 100);

	//获取实例
	static BuildingScene * getInstance();

	//获取游戏玩家层
	PlayerLayer * getPlayerLayer(int playerID){ return m_playerLayers.at(playerID); }

	//震动屏幕
	void shakeScreen();

	//游戏结束界面
	void gameOver(int playerID, int side = 0);

	//游戏真正结束界面
	void gameTruelyOver();

	//移除触摸监听
	void removeTouchListener();

	//显示游戏结算
	void pushResult(float dt);

	//检查多玩家的输入情况(返回是否有输入)
	bool checkMultiPlayerInput(int * playerIDToBeSaved, Vec2 * posToBeSaved);

	//循环检查多玩家输入情况
	void loopCheckMultiPlayerInput(float dt);

	//通过设备ID获取玩家ID（返回-1为失败）
	int getPlayerIDByDeviceID(int deviceID);

	//键盘控制触屏
	void keyboardControl(KeyButtonsPackage * res, CustomKeyEvent * e);

	//获取玩家对应关系指针
	static std::map<int, int> * getPlayersIDMap(){ return &m_playersIDMap; }

	//添加商城视图
	void _addBankView();

	//显示商城
	void showShop(Ref * ref);

	//隐藏商城
	void hideShop(Ref * ref);

	//再一次机会
	void moreChance(Ref * ref);

	//取消再一次机会
	void moreChanceCancel(Ref * ref);

	//复活
	void heal(Ref * ref);

	//--------------------- 数据区域 ------------------------
	//背景音乐序号
	static unsigned int m_bgmIndex;

	//抛掷音效序号
	static unsigned int m_sfxIndex;

protected:

	//自定义键盘控制器
	CustomKeyEventDispatcher * m_customKeyEventDispatcher;

	//键盘事件分发器
	KeyButtonsPackage m_keyEventTrigger;

	//静态实例
	static BuildingScene * m_instance;

	//音符列表
	std::vector<MeterOnce> m_meterList;

	//玩家对应关系(设备ID->玩家ID)
	static std::map<int, int> m_playersIDMap;

	//音符步数
	int m_meterStep;

	//音乐段步数
	int m_bgmStep;

	//一轮的开始步数
	int m_beginStep;

	//一轮的结束步数
	int m_endStep;

	//持续步数
	int m_lastLen;

	//触摸监听器
	EventListenerTouchOneByOne * m_listener;

	//游戏逻辑
	GameInfo * m_logicInfo;

	//中点
	Vec2 m_centerPoint;

	//屏幕大小
	Size m_visibleSize;

	//游戏人数
	int m_playerCount;

	//玩家层组
	Vector<PlayerLayer*> m_playerLayers;

	//世界固定器
	Node * m_worldHolder;

	//世界的背景固定器
	SpriteBatchNode * m_backOfWorldHolder;
	Sprite * m_backSky;
	Sprite * m_backMountain;
	Sprite * m_backBuildings;
	Sprite * m_backTrees;

	//世界的楼层固定器
	Node * m_buildingsOfWorldHolder;

	//世界的前景固定器
	Node * m_frontOfWorldHolder;

	//UI固定器
	Node * m_uiHolder;
	MoverGameplayUI * m_gameUI;
	MoverGamepauseUI * m_pauseUI;
	MoverResultUI * m_resultUI;

	//卡车
	MoversTruck * m_car;

	//兔子Boss
	Vector<RabbitHamal*> m_rabbitBosses;

	//商城视图
	BankView * m_bankView;

	//统一的兔子在哪边的定义
	int m_rabbitSide;

	//游戏模式(0:竞技模式;1:合作模式)
	static int m_gameMode;

	//是否在退出中
	bool m_isLeaving;

	//是否开始了游戏
	bool m_isBegan;

	//是否结束了游戏
	bool m_isOvered;

};








#endif
