#include "System_analizer.h"
#include "Gui_manager.h"
#include <iostream>
#include <Windows.h>

using part = System_analizer::DevicePart;

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define WHITE "\033[37m"
#define DEGREES "\370"
#define PROCENTS " %"
#define DIVIDER " / "

string paint(string metrics);

int main(void)
{
    Gui_manager gui;
    System_analizer analizer;

    gui.build_top_console_window();

    while (true)
    {
        string ram = analizer.analize(part::ram);
        string gpu = analizer.analize(part::gpu);
        string gpu_temp = analizer.analize(part::gpu_temp);
        string cpu = analizer.analize(part::cpu);

        string ram_p = paint(ram) + PROCENTS;
        string gpu_p = paint(gpu) + PROCENTS;
        string gpu_temp_p = paint(gpu_temp) + DEGREES;
        string cpu_p = paint(cpu) + PROCENTS;

        Sleep(3000);
        system("cls");

        cout
            << WHITE << "RAM: " << ram_p << endl
            << WHITE << "GPU: " << gpu_p << DIVIDER << gpu_temp_p << endl
            << WHITE << "CPU: " << cpu_p << endl;
    }

    getchar();
    return 0;
}

string paint(string metrics)
{
    int i = stoi(metrics);
    string result;

    if (i < 33)
    {
        result = GREEN + metrics;
    }
    else if (i >= 33 && i < 66)
    {
        result = YELLOW + metrics;
    }
    else if (i >= 66)
    {
        result = RED + metrics;
    }
    else
    {
        result = WHITE + metrics;
    }

    return result;
}