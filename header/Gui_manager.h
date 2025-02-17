#include "System_analizer.h"
#include <Windows.h>
#include <string>

using part = System_analizer::DevicePart;

class Gui_manager
{
public:
    enum Attributes_type
    {
        _default,
        gpu_fan
    };
    void start();

private:
    void show_stats(System_analizer, COORD);
    void build_top_console_window();
    void hide_cursor();
    void set_bold_font();
    void show(System_analizer::DevicePart, string);
    void check_is_achtung(string, string, string);
    int convert_to_int(string);
    WORD get_wAttributes(string, Gui_manager::Attributes_type = _default);
    COORD build_coord();
};