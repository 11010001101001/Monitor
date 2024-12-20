#include "System_analizer.h"
#include <Windows.h>
#include <string>

using namespace std;

class Gui_manager
{
private:
    void show_stats(System_analizer, COORD);
    void build_top_console_window();
    void hide_cursor();
    void set_bold_font();
    void show(System_analizer::DevicePart, string);
    int convert_to_int(string);
    WORD get_wAttributes(string);
    COORD build_coord();

public:
    void start();
};