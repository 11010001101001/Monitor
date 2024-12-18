#include "System_analizer.h"
#include <iostream>
#include <string>
#include <math.h>
#include <iomanip>
#include <windows.h>
#include <cctype>

MEMORYSTATUSEX System_analizer::memInfo;
unsigned long long System_analizer::FileTimeToInt64(const FILETIME &ft) { return (((unsigned long long)(ft.dwHighDateTime)) << 32) | ((unsigned long long)ft.dwLowDateTime); }

double System_analizer::toGb(DWORDLONG num)
{
    return static_cast<double>(num) / pow(1024, 3);
}

float System_analizer::CalculateCPULoad(unsigned long long idleTicks, unsigned long long totalTicks)
{
    static unsigned long long _previousTotalTicks = 0;
    static unsigned long long _previousIdleTicks = 0;

    unsigned long long totalTicksSinceLastTime = totalTicks - _previousTotalTicks;
    unsigned long long idleTicksSinceLastTime = idleTicks - _previousIdleTicks;

    float ret = 1.0f - ((totalTicksSinceLastTime > 0) ? ((float)idleTicksSinceLastTime) / totalTicksSinceLastTime : 0);

    _previousTotalTicks = totalTicks;
    _previousIdleTicks = idleTicks;
    return ret;
}

string System_analizer::analize(DevicePart part)
{
    switch (part)
    {
    case cpu:
        return get_cpu_usage();
        break;

    case ram:
        return get_ram_usage();
        break;

    case gpu:
        return get_gpu_usage();
        break;

    case gpu_temp:
        return get_gpu_temp();
        break;

    default:
        return "void";
    }
}

string System_analizer::get_ram_usage()
{
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);

    DWORDLONG ramTotal = memInfo.ullTotalPhys;
    DWORDLONG ramUsed = memInfo.ullTotalPhys - memInfo.ullAvailPhys;

    double ramTotalGb = toGb(ramTotal);
    double ramUsedGb = toGb(ramUsed);
    double ramUsedProcents = (ramUsedGb / ramTotalGb) * 100;
    double rounded = round(ramUsedProcents * 100) / 100;
    return to_string(static_cast<int>(rounded));
}

string System_analizer::get_cpu_usage()
{
    FILE *pipe = _popen("wmic cpu get loadpercentage", "r");
    char buffer[128];
    string digits;

    while (fgets(buffer, 128, pipe) != NULL)
    {
        string res = string(buffer);
        int i = res.length();

        for (i; i >= 0; i--)
            if (isdigit(res[i]))
            {
                digits += res[i];
            }
    }
    _pclose(pipe);

    return digits;
}

string System_analizer::get_gpu_usage()
{
    return extract("nvidia-smi --query-gpu=utilization.gpu --format=csv,noheader,nounits");
}

string System_analizer::get_gpu_temp()
{
    return extract("nvidia-smi --query-gpu=temperature.gpu --format=csv,noheader,nounits");
}

string System_analizer::extract(const char *cmd)
{
    FILE *pipe = _popen(cmd, "r");

    char buffer[128];

    if (fgets(buffer, 128, pipe) != NULL)
    {
        string res = string(buffer);
        return res.substr(0, res.find("\n"));
    }

    _pclose(pipe);

    return 0;
}