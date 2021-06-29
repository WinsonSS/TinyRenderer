#pragma once
#include <ctime>
#include "singleton.h"
#include <Windows.h>

class GameController
{
private:
	friend class Singleton<GameController>;
	clock_t last_frame_time_;
	clock_t frame_time_;
	int fps_;
	HWND handle_window_;
public:
	void Init(HWND handle_window, int fps = 60);
	bool CanNextFrame();
	void Update();
	int fps();
	void set_fps(int fps);
};

