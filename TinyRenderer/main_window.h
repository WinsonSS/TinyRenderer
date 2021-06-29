#pragma once
#include "base_window.h"
#include <functional>

class MainWindow : public BaseWindow<MainWindow>
{
public:
	PCWSTR  ClassName() const { return L"Main Window"; }
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	std::function<void(UINT, WPARAM, LPARAM)> temp_cb;
};
