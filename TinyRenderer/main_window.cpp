#include "main_window.h"
#include <cstdio>

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (temp_cb)
		temp_cb(uMsg, wParam, lParam);
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_KEYDOWN:
        return 0;
    case WM_KEYUP:
        return 0;
    /*
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd_, &ps);
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
        EndPaint(hwnd_, &ps);
    }
	return 0;
    */
    }
	return DefWindowProc(hwnd_, uMsg, wParam, lParam);
}
