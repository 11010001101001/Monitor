#include "Gui_manager.h"
#include <Windows.h>
#include <string>
#include <iostream>

void Gui_manager::build_top_console_window()
{
    HWND hwndConsole = GetConsoleWindow();
    RECT desktop;
    const HWND hdesktop = GetDesktopWindow();

    GetWindowRect(hdesktop, &desktop);

    int right = desktop.right;
    int top = desktop.top;
    int width = 250;
    int height = 110;
    int x = right - width;
    int y = top + 32;

    SetWindowPos(
        hwndConsole,
        HWND_TOPMOST,
        x,
        y,
        width,
        height,
        SWP_SHOWWINDOW);
}
