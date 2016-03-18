#include "GameInfo.h"
#include "cocos2d.h"

USING_NS_CC;

bool GameInfo::_gameMode[2] = { false , false };

bool GameInfo::checkModeUnlock( int idx )
{
	return _gameMode[idx];
}

void GameInfo::loadModeUnlock()
{
	for( auto i = 0 ; i < 2 ; i ++ )
	{
		std::string mod_key = "GAMOD_KEY_";
		mod_key += int2str(i);
		_gameMode[i] = UserDefault::getInstance()->getBoolForKey( mod_key.c_str() , false );
	}
}

void GameInfo::unlockMode( int idx )
{
	_gameMode[idx] = true;
	std::string mod_key = "GAMOD_KEY_";
	mod_key += int2str(idx);
	UserDefault::getInstance()->setBoolForKey( mod_key.c_str() , true );
}
//////////////

int GameInfo::_money;

int GameInfo::getMoney()
{
	return _money;
}

void GameInfo::loadMoney()
{
	_money = UserDefault::getInstance()->getIntegerForKey( "KEY_PLAYER_MONEY" , 0 );
}

bool GameInfo::useMoney( int _mm )
{
	if( _money >= _mm )
	{
		_money -= _mm;
		UserDefault::getInstance()->setIntegerForKey( "KEY_PLAYER_MONEY" , _money );
		return true;
	}
	else return false;
}

void GameInfo::awardMoney( int _mm )
{
	_money += _mm;
	UserDefault::getInstance()->setIntegerForKey( "KEY_PLAYER_MONEY" , _money );
}

std::function<long()> GameInfo::getCurrentMillSecond = std::bind( &getCurrentMillSecond_5 );

void GameInfo::setUpon5()
{
	getCurrentMillSecond = std::bind( &getCurrentMillSecond_5 );
}

long getCurrentMillSecond_0()  // get current mill second
{
	
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
	long st = clock();
#elif ( CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
	long st = clock() / 1000;
#elif ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS )
	long st;
	struct timeval stCurrentTime;
	gettimeofday( &stCurrentTime ,NULL );
	st = stCurrentTime.tv_sec * 1000 + stCurrentTime.tv_usec * 0.001; //millseconds
#endif

	return st; 
	/*
	long lLastTime;
	struct timeval stCurrentTime;

	gettimeofday( &stCurrentTime ,NULL );
	lLastTime = stCurrentTime.tv_sec * 1000 + stCurrentTime.tv_usec * 0.001; //millseconds
	return lLastTime;
	struct timeval now;
    gettimeofday(&now, NULL);
    long tmpLL = ((long)now.tv_sec)*1000;
    return tmpLL + now.tv_usec/1000; //都转化为毫秒*/
}
long getCurrentMillSecond_5()  // get current mill second
{
	
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
	long st = clock();
#else
	long st;
	struct timeval stCurrentTime;
	gettimeofday( &stCurrentTime ,NULL );
	st = stCurrentTime.tv_sec * 1000 + stCurrentTime.tv_usec * 0.001; //millseconds
#endif

	return st; 
}

MeterOnce::MeterOnce( int _beginMeters , int _endMeters ):
beginMeters( _beginMeters ),
endMeters( _endMeters )
{
}

int MeterOnce::meterLength()
{
	return ( endMeters - beginMeters );
}

std::string int2str(int i)
{
	std::string s;
	std::stringstream ss(s);
	ss << i;
	return ss.str();
}

GameInfo::GameInfo():
ModeCode(""),
_paused( false ),
_currentSecond( 0 ),
_gameBeginTime( 0 ),
_pauseBeginTime( 0 ),
_healthPoint( 0 ),
_currentFloor( 0 )
{
}

void GameInfo::timeCheckGameBegin()
{
	_paused = false;
	_currentMillSecond = 0;
	_currentSecond = 0;
	_gameBeginTime = getCurrentMillSecond() - _currentMillSecond;
}

void GameInfo::switchGameMode( int mod_code )
{
	if (mod_code == 1)
	{
		ModeCode = "M1";
	}
	else if(mod_code == 2)
	{
		ModeCode = "A1";
	}
	else if (mod_code == 3)
	{
		ModeCode = "A2";
	}
	else
	{
		ModeCode = "";
	}
}

void GameInfo::updateCurrentTime( float dt )
{
	
	if( _paused ) return;
	/*/
	long _now = getCurrentMillSecond();
	long _pass = _now - _gameBeginTime;
	auto change = _pass - _currentMillSecond;
	if( _pass < 0 || change > 50 )
	{
		_currentMillSecond += 17;
		_gameBeginTime = _now - _currentMillSecond;
	}
	else _currentMillSecond = _pass;

	_currentSecond = ((double) _currentMillSecond ) / 1000.0f;
	/*/
	if( dt < 0.01 || dt > 0.05 )
	{
		//_currentMillSecond += 17;
		//_gameBeginTime = _now - _currentMillSecond;
		_currentSecond += 0.016667;
	}
	else _currentSecond += dt;
}

void GameInfo::timeCheckGamePause()
{
	if( _paused ) return;
	_paused = true;
}

void GameInfo::timeCheckGameResume()
{
	if( !_paused ) return;
	_gameBeginTime = getCurrentMillSecond() - _currentMillSecond;
	_paused = false;

}

// second
double GameInfo::getCurrentGameTime()
{
	return _currentSecond;
}

// get the only one instance
GameInfo GameInfo::_single;
GameInfo * GameInfo::getInstance()
{
	return &_single;
}

//  before a new game , it should be called
void GameInfo::reSet()
{
	_paused = true;
	_currentFloor = 1;
	_healthPoint = 1;
	_currentScore = 0;
	_bombMissed = 0;
	_goodsCatched = 0;

	_goodsCatchedForMatch[0] = 0;
	_goodsCatchedForMatch[1] = 0;

	_bombMissedForMatch[0] = 0;
	_bombMissedForMatch[1] = 0;

	_highScore = UserDefault::getInstance()->getIntegerForKey( ( ModeCode + "MOVERS_HIGH_SCORE" ).c_str() , 0 );
	_highFloor = UserDefault::getInstance()->getIntegerForKey( ( ModeCode + "MOVERS_HIGH_FLOOR" ).c_str() , 0 );
	_highGoods = UserDefault::getInstance()->getIntegerForKey( ( ModeCode + "MOVERS_HIGH_GOODS" ).c_str() , 0 );
	_highBomb =  UserDefault::getInstance()->getIntegerForKey( ( ModeCode + "MOVERS_HIGH_BOMB" ).c_str() , 0 );
}

// if now have a better score , the recored will be updated
bool GameInfo::checkHighScore()
{
	if( _currentScore > _highScore )
	{
		UserDefault::getInstance()->setIntegerForKey( ( ModeCode + "MOVERS_HIGH_SCORE" ).c_str() , _currentScore );
		return true;
	}
	else return false;
}

bool GameInfo::checkHighFloor()
{
	if( _currentFloor > _highFloor )
	{
		UserDefault::getInstance()->setIntegerForKey( ( ModeCode + "MOVERS_HIGH_FLOOR" ).c_str() , _currentFloor );
		return true;
	}
	else return false;
}

bool GameInfo::checkHighGoods()
{
	if( _goodsCatched > _highGoods )
	{
		UserDefault::getInstance()->setIntegerForKey( ( ModeCode + "MOVERS_HIGH_GOODS" ).c_str() , _goodsCatched );
		return true;
	}
	else return false;
}

bool GameInfo::checkHighBomb()
{
	if( _bombMissed > _highBomb )
	{
		UserDefault::getInstance()->setIntegerForKey( ( ModeCode + "MOVERS_HIGH_BOMB" ).c_str() , _bombMissed );
		return true;
	}
	else return false;
}

int GameInfo::getCurrentScore()
{
	return _currentScore;
}

void GameInfo::addScore( int _score )
{
	_currentScore += _score;
}

void GameInfo::upFloor()
{
	_currentFloor++;
}

int GameInfo::getBombRandom()
{
	if( _currentFloor < 5 ) return 1;
	else if ( _currentFloor < 8 ) return random( 0 , 10 );
	else if ( _currentFloor < 12 ) return random( 0 , 6 );
	else return random( 0 , 3 );
}

bool GameInfo::useHealth()
{
	_healthPoint--;
	if( _healthPoint < 1 ) return true;
	else return false;
}



//------------------------------------------------------------------------------

const char * GameInfo::getMusic16()
{
	auto _floor = _single.getCurrentFloor();
	if( _floor < 5 )
	{
		switch( random( 0 , 3 ) )
		{
		default:    break;
		case 0:		return "A000B00000000000";break;
		case 1:		return "A000B000A000B000";break;
		case 2:		return "A0A00000B0B00000";break;
		case 3:		return "A000A000B000B000";break;
		}
	}
	else if( _floor < 8 )
	{
		switch( random( 0 , 14 ) )
		{
		default:    break;
		case 0:		return "A000B00000000000";break;
		case 1:		return "A000B000A000B000";break;
		case 2:		return "A0A00000B0B00000";break;
		case 3:		return "A000A000B000B000";break;
		case 4:		return "AAA0BBB0AAA0BBB0";break;
		case 5:		return "A000B000AA00BB00";break;
		case 6:		return "A000B000A0A0B0B0";break;
		case 7:		return "A0A0B0B0A000B000";break;
		case 8:		return "AA0AA000BB0BB000";break;	
		case 9:	    return "AAAAA000BBBBB000";break;	
		case 10:	return "A000B000AA0BB000";break;
		case 11:	return "A0B0A0B0AA0BB000";break;
		case 12:	return "AAA0A000BBB0B000";break;
		case 13:	return "A0AAA000B0BBB000";break;
		case 14:	return "A0A0AA00B0B0BB00";break;
		}
	}
	else
	{
		switch( random( 0 , 20 ) )
		{
		default:    break;
		case 0:		return "A000B00000000000";break;
		case 1:		return "A000B000A000B000";break;
		case 2:		return "A0A00000B0B00000";break;
		case 3:		return "A000A000B000B000";break;
		case 4:		return "AAA0BBB0AAA0BBB0";break;
		case 5:		return "A000B000AA00BB00";break;
		case 6:		return "AA00BB00A0B0A0B0";break;
		case 7:		return "A000B000A0A0B0B0";break;
		case 8:		return "A0A0B0B0A000B000";break;
		case 9:		return "AA0AA000BB0BB000";break;
		case 10:	return "A0B0A0B0A0B0A0B0";break;
		case 11:	return "A0B0A0B0AA00BB00";break;
		case 12:	return "AAAAA000BBBBB000";break;
		case 13:	return "A0B0A0B0AA0BB000";break;
		case 14:	return "A000B000AA0BB000";break;
		case 15:	return "AAAAAAA0BBBBBBB0";break;
		case 16:	return "A0B0A0B0A000B000";break;
		case 17:	return "A0B0A0B0AA0BB000";break;
		case 18:	return "AAA0A000BBB0B000";break;
		case 19:	return "A0AAA000B0BBB000";break;
		case 20:	return "A0A0AA00B0B0BB00";break;
		}
	}
	return "A0A0AA00B0B0BB00";
}

std::string GameInfo::getHeadMusic1()
{
	std::string gameList = "";
	gameList += "A000B00000000000";
	gameList += "00000000A000B000";
	gameList += "A000B000";
	return gameList;
}


std::string GameInfo::getHeadMusic2()
{
	std::string gameList = "";
	gameList += "00000000A000B000";
	gameList += "A000B00000000000";
	gameList += "A000B000";
	return gameList;
}


std::string GameInfo::getHeadMusic()
{
	std::string gameList = "";
	gameList += "A000B000A000B000";
	gameList += "A000B000A000B000";
	//gameList += "AAAAAAA0BBBBBBB0";
	//gameList += "AAAAAAA0BBBBBBB0";
	gameList += "A000B000";
	return gameList;
}

std::string GameInfo::getFullMusic( int _len )
{
	std::string gameList = "";
	for( auto i = 0 ; i < _len ; i++ )
	{
		gameList += getMusic16();
	}
	auto _floor = _single.getCurrentFloor();
	if( _floor < 5 )
	{
		gameList += "A0A0B0B0";
	}
	else if( _floor < 8 )
	{
		gameList += "AA00BB00";
	}
	else
	{
		gameList += "AAA0BBB0";
	}

	return gameList;
}
