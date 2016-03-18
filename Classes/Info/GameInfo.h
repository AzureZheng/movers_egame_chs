//***********************************************

// GameInfo

//***********************************************

#ifndef _GAME_LOGIC_INFO_H_
#define _GAME_LOGIC_INFO_H_

#define MIN_METER_TIME 0.225f

#define HALF_METER_LIFE_BEFORE 0.112f
#define HALF_METER_LIFE_AFTER 0.112f


#include <string>
#include <functional>  


// get current mill second
long getCurrentMillSecond_0(); 
long getCurrentMillSecond_5();  

struct MeterOnce
{
	int beginMeters;

	int endMeters;

    MeterOnce( int _beginMeters , int _endMeters ); 

	int meterLength();

};

// input a number , out put a strihg
std::string int2str(int i);

class GameInfo
{
	std::string ModeCode;

	static std::function<long()> getCurrentMillSecond;

	static GameInfo _single;
	GameInfo();

	int _currentFloor;

	long _gameBeginTime;

	long _pauseBeginTime;

	long _currentMillSecond;

	bool _paused;

	double _currentSecond;
	
	int _healthPoint;

	static const char * getMusic16();

	int _count;

	int _currentScore;

	int _bombMissed;

	int _goodsCatched; 

	int _highScore;

	int _highFloor;

	int _highGoods;

	int _highBomb;

	int _winner_playerID;

    static int _money;

    static bool _gameMode[2];

	int _goodsCatchedForMatch[2];

	int _bombMissedForMatch[2];

public:

	static bool checkModeUnlock( int idx );

	static void loadModeUnlock();

	static void unlockMode( int idx );

	static int getMoney();

	static void loadMoney();

	static bool useMoney( int _mm );

	static void awardMoney( int _mm );

	void switchGameMode( int mod_code );

	static void setUpon5();

	int getWinnerID(){ return _winner_playerID; }
	void setWinnerID(int id){ _winner_playerID = id; }

	int getHighFloor(){ return _highFloor; }

	void setGoods(int n){ _goodsCatched = n; }

	void catchGoods(int playerID){ _goodsCatchedForMatch[playerID]++; }

	void refreshGoodsCatchedFromMatchData(int playerID){ _goodsCatched = _goodsCatchedForMatch[playerID]; }

	int getGoodsCatched(){ return _goodsCatched; }

	void setBomb(int n){ _bombMissed = n; }

	void missBomb(int playerID){ _bombMissedForMatch[playerID]++; }

	void refreshBombMissedFromMatchData(int playerID){ _bombMissed = _bombMissedForMatch[playerID]; }

	int getMissedBomb(){ return _bombMissed; } 

	int getHighScore(){ return _highScore; }

	void fullCount(){ _count = 4; }

	void countDown(){ _count--; }

	int getCountDown(){ return _count; }

	int getCurrentScore();

	void addScore( int _score );

	void upFloor();
	
	int getBombRandom();

	static std::string getFullMusic( int _len );

	static std::string getHeadMusic();

	static std::string getHeadMusic1();

	static std::string getHeadMusic2();

	bool useHealth();

	void updateCurrentTime( float dt );

	void timeCheckGameBegin();

	void timeCheckGamePause();

	void timeCheckGameResume();

	// second
	double getCurrentGameTime();

	// return _currentFloor
	int getCurrentFloor(){ return _currentFloor; }

	// _currentFloor ++
	void nextFloor(){ _currentFloor++; }

	// get the only one instance
	static GameInfo * getInstance();

	//  before a new game , it should be called
	void reSet();

	// if now have a better score , the recored will be updated
	bool checkHighScore();

	bool checkHighFloor();

	bool checkHighGoods();

	bool checkHighBomb();

	const std::string & getModeCode()
	{
		return ModeCode;
	}
};


#endif //_GAME_LOGIC_INFO_H_
