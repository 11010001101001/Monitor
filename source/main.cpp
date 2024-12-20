#define RED "\033[31m"
#define GREEN "\033[32m"
#define ORANGE "\033[38;5;208m"
#define YELLOW "\033[33m"
#define WHITE "\033[37m"
#define DEGREES "\370"
#define PROCENTS " %"
#define DIVIDER " / "
#define CLEAR "cls"
#define DELAY 3000
#define HIDE_CURSOR "\e[?25l"
#define BOLD "\e[1m"
#define SPACER " "

#include "System_analizer.h"
#include "Gui_manager.h"
#include <iostream>
#include <Windows.h>

using part = System_analizer::DevicePart;

void show_stats(System_analizer analizer, Gui_manager gui_manager);
string paint(string metrics);
int convert_to_int(string value);

int main(void)
{
    Gui_manager gui_manager;
    System_analizer analizer;

    while (true)
    {
        show_stats(analizer, gui_manager);
    }

    return 0;
}

void show_stats(System_analizer analizer, Gui_manager gui_manager)
{
    gui_manager.build_top_console_window();

    string ram = analizer.analize(part::ram);
    string gpu = analizer.analize(part::gpu);
    string gpu_temp = analizer.analize(part::gpu_temp);
    string cpu = analizer.analize(part::cpu);
    string ram_p = paint(ram) + PROCENTS;
    string gpu_p = paint(gpu) + PROCENTS;
    string gpu_temp_p = paint(gpu_temp) + DEGREES;
    string cpu_p = paint(cpu) + PROCENTS;

    Sleep(DELAY);
    system(CLEAR);

    cout << BOLD
         << SPACER << WHITE << "RAM: " << ram_p << endl
         << SPACER << WHITE << "GPU: " << gpu_p << DIVIDER << gpu_temp_p << endl
         << SPACER << WHITE << "CPU: " << cpu_p << HIDE_CURSOR;
}

string paint(string metrics)
{
    int i = convert_to_int(metrics);
    string result;

    if (i < 25)
    {
        result = GREEN + metrics;
    }
    else if (i >= 25 && i < 50)
    {
        result = YELLOW + metrics;
    }
    else if (i >= 50 && i < 75)
    {
        result = ORANGE + metrics;
    }
    else if (i >= 75)
    {
        result = RED + metrics;
    }
    else
    {
        result = WHITE + metrics;
    }

    return result;
}

int convert_to_int(string ptr)
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