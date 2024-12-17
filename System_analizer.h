#include <string>
#include <iostream>
#include <math.h>
#include <iomanip>
#include <windows.h>
#include <cctype>

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

    string analize(DevicePart part);

private:
    static MEMORYSTATUSEX memInfo;
    static unsigned long long FileTimeToInt64(const FILETIME &ft);

    double toGb(DWORDLONG num);
    static float CalculateCPULoad(unsigned long long idleTicks, unsigned long long totalTicks);
    string extract(const char *cmd);

    string get_ram_usage();
    string get_gpu_usage();
    string get_gpu_temp();
    string get_cpu_usage();
};