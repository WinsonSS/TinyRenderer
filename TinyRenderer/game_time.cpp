#include "game_time.h"

GameTime::GameTime() : game_start_time_(0) {}


GameTime::~GameTime() {}


void GameTime::Init()
{
	game_start_time_ = time(0);
}


time_t GameTime::game_time()
{
	return time(0) - game_start_time_;
}
