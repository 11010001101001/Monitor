#include <string>
#include <iostream>
#include <windows.h>
#include <math.h>

using namespace std;

class System_analizer
{
public:
    enum DevicePart
    {
        ram,
        gpu,
        gpu_temp,
        cpu
    };

    string analize(DevicePart);

private:
    double toGb(DWORDLONG);
    string get_cmd_output(const char *);
    string get_ram_usage();
    string get_gpu_usage();
    string get_gpu_temp();
    string get_cpu_usage();
};