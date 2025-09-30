#include "system_analizer.h"
#include <Windows.h>
#include <string>

using part = SystemAnalizer::DevicePart;

class GuiManager
{
public:
    enum AttributesType
    {
        _default,
        gpu_fan
    };
    void start();

private:
    void showStats(SystemAnalizer, COORD);
    void buildTopConsoleWindow();
    void hideCursor();
    void setBoldFont();
    void show(SystemAnalizer::DevicePart, string);
    void checkIsAchtung(string, string, string);
    int convertToInt(string);
    string buildProgressBar(string);
    string rpm(string);
    WORD getWAttributes(string);
    COORD buildCoord();
};