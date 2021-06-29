#include "game_controller.h"

void GameController::Init(HWND handle_window, int fps)
{
	last_frame_time_ = 0;
	fps_ = fps;
	frame_time_ = 1000 / fps_;
	handle_window_ = handle_window;
}

bool GameController::CanNextFrame()
{
	clock_t cur_time = clock();
	clock_t elapse_time = cur_time - last_frame_time_;
	if (elapse_time >= frame_time_)
	{
		last_frame_time_ = cur_time;
		return true;
	}
	return false;
}

void GameController::Update()
{
	if (CanNextFrame())
		SendMessage(handle_window_, WM_PAINT, 0, 0);
}

int GameController::fps()
{
	return fps_;
}

void GameController::set_fps(int fps)
{
	fps_ = fps;
	frame_time_ = 1.f / fps_;
}
