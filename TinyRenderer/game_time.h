#pragma once
#include <ctime>
#include "singleton.h"

class GameTime
{
private:
	friend class Singleton<GameTime>;
	time_t game_start_time_;
	GameTime();
	~GameTime();
public:
	void Init();
	time_t game_time();
};

