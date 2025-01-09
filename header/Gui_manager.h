#include "System_analizer.h"
#include <Windows.h>
#include <string>

using namespace std;
using part = System_analizer::DevicePart;

class Gui_manager
{
private:
    void show_stats(System_analizer, COORD);
    void build_top_console_window();
    void hide_cursor();
    void set_bold_font();
    void show(part, string);
    void check_is_achtung(string, string, string);
    int convert_to_int(string);
    WORD get_wAttributes(string);
    WORD get_wAttributes_gpu_fan(string);
    COORD build_coord();

public:
    void start();
};