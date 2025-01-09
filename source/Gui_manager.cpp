#define RPM " RPM"
#define DEGREES " °C"
#define RTX_2060_MAX_RPM 3069
#define PROCENTS " %"
#define DELAY 3000
#define DIVIDER " / "
#define SPACER "                                  "
#define CRITICAL 80
#define WHITE FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
#define GREEN FOREGROUND_GREEN | FOREGROUND_INTENSITY
#define YELLOW FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY
#define ORANGE FOREGROUND_RED | FOREGROUND_GREEN
#define RED FOREGROUND_RED | FOREGROUND_INTENSITY

#include "Gui_manager.h"
#include <Windows.h>
#include <string>
#include <iostream>
#include <iomanip>

using part = System_analizer::DevicePart;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void Gui_manager::hide_cursor()
{
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void Gui_manager::set_bold_font()
{
    CONSOLE_FONT_INFOEX fontInfo = {sizeof(CONSOLE_FONT_INFOEX)};
    GetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);
    fontInfo.FontWeight = FW_BOLD;
    SetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);
}

void Gui_manager::build_top_console_window()
{
    HWND hwndConsole = GetConsoleWindow();
    RECT desktop;
    const HWND hdesktop = GetDesktopWindow();

    GetWindowRect(hdesktop, &desktop);

    int right = desktop.right;
    int top = desktop.top;
    int width = 320;
    int height = 120;
    int x = right - width + 4;
    int y = top + 32;

    SetWindowPos(
        hwndConsole,
        HWND_TOPMOST,
        x,
        y,
        width,
        height,
        SWP_NOREDRAW);

    hide_cursor();
    set_bold_font();
    SetConsoleOutputCP(CP_UTF8);
}

COORD Gui_manager::build_coord()
{
    COORD coord;
    coord.X = 0;
    coord.Y = 0;
    return coord;
}

void Gui_manager::show_stats(System_analizer analizer, COORD coord)
{
    string ram = analizer.analize(part::ram);
    string gpu = analizer.analize(part::gpu);
    string gpu_temp = analizer.analize(part::gpu_temp);

    int fan_usage = convert_to_int(analizer.analize(part::gpu_fan_speed));
    int fan_speed = (float(fan_usage) / 100) * RTX_2060_MAX_RPM;
    string gpu_fan_speed_rpm = to_string(fan_speed);

    string cpu = analizer.analize(part::cpu);

    // 'reset' old cout
    SetConsoleCursorPosition(hConsole, coord);

    for (int i = 0; i <= 5; i++)
        cout << SPACER << endl;

    // cout new values with no cls blinking
    SetConsoleCursorPosition(hConsole, coord);

    show(part::ram, ram);
    show(part::gpu, gpu);
    show(part::gpu_temp, gpu_temp);
    show(part::gpu_fan_speed, gpu_fan_speed_rpm);
    show(part::cpu, cpu);

    check_is_achtung(ram, gpu, cpu);

    Sleep(DELAY);
}

void Gui_manager::show(part part, string param)
{
    SetConsoleTextAttribute(hConsole, WHITE);

    switch (part)
    {
    case part::cpu:
        cout << " CPU: " << setw(20);
        SetConsoleTextAttribute(hConsole, get_wAttributes(param));
        cout << param + PROCENTS << endl;
        break;

    case part::ram:
        cout << " RAM: " << setw(20);
        SetConsoleTextAttribute(hConsole, get_wAttributes(param));
        cout << param + PROCENTS << endl;
        break;

    case part::gpu:
        cout << " GPU: " << setw(20);
        SetConsoleTextAttribute(hConsole, get_wAttributes(param));
        cout << param + PROCENTS;
        break;

    case part::gpu_temp:
        SetConsoleTextAttribute(hConsole, get_wAttributes(param));
        cout << DIVIDER << param + DEGREES << endl;
        break;

    case part::gpu_fan_speed:
        cout << " GPU FAN SPEED: " << setw(10);
        SetConsoleTextAttribute(hConsole, get_wAttributes_gpu_fan(param));
        cout << param + RPM << endl;
        break;

    default:
        break;
    }
}

WORD Gui_manager::get_wAttributes(string param)
{
    int i = convert_to_int(param);

    if (i < 25)
    {
        return GREEN;
    }
    else if (i >= 25 && i < 50)
    {
        return YELLOW;
    }
    else if (i >= 50 && i < 75)
    {
        return ORANGE;
    }
    else if (i >= 75)
    {
        return RED;
    }

    return WHITE;
}

WORD Gui_manager::get_wAttributes_gpu_fan(string param)
{
    int i = convert_to_int(param);

    if (i < 1000)
    {
        return GREEN;
    }
    else if (i >= 1000 && i < 1500)
    {
        return YELLOW;
    }
    else if (i >= 1500 && i < 2500)
    {
        return ORANGE;
    }
    else if (i >= 2500)
    {
        return RED;
    }

    return WHITE;
}

int Gui_manager::convert_to_int(string ptr)
{
    try
    {
        return stoi(ptr);
    }
    catch (...)
    {
        return 0;
    }
}

void Gui_manager::start()
{
    System_analizer analizer;
    COORD coord = build_coord();
    build_top_console_window();

    cout << " Loading...";

    while (true)
    {
        show_stats(analizer, coord);
    }
}

void Gui_manager::check_is_achtung(string ram, string gpu, string cpu)
{
    int cpu_i = convert_to_int(cpu);
    int ram_i = convert_to_int(ram);
    int gpu_i = convert_to_int(gpu);

    bool is_ahtung = cpu_i > CRITICAL && ram_i > CRITICAL && gpu_i > CRITICAL;

    if (is_ahtung)
    {
        SetConsoleTextAttribute(hConsole, RED);
        cout << " !!! ACHTUNG !!!";
    }
}