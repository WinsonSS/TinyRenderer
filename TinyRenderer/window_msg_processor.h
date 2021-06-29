#pragma once
#include <Windows.h>
#include "singleton.h"
class WindowMsgProcessor
{
private:
	friend class Singleton<WindowMsgProcessor>;
	MSG *msg_;
	bool have_msg_;
	WindowMsgProcessor();
	~WindowMsgProcessor();
public:
	bool Update();
	MSG* msg();
	bool ShouldQuit();
};

