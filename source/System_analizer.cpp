#include "System_analizer.h"
#include <iostream>
#include <string>
#include <math.h>
#include <windows.h>

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
        return "0";
    }
}

double System_analizer::toGb(DWORDLONG num)
{
    return static_cast<double>(num) / pow(1024, 3);
}

string System_analizer::get_ram_usage()
{
    MEMORYSTATUSEX memInfo;
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

string System_analizer::get_gpu_usage()
{
    return extract("nvidia-smi --query-gpu=utilization.gpu --format=csv,noheader,nounits");
}

string System_analizer::get_gpu_temp()
{
    return extract("nvidia-smi --query-gpu=temperature.gpu --format=csv,noheader,nounits");
}

string System_analizer::get_cpu_usage()
{
    return extract("wmic cpu get loadpercentage");
}

string System_analizer::extract(const char *cmd)
{
    FILE *pipe = _popen(cmd, "r");
    char buffer[128];
    string digits;

    while (fgets(buffer, 128, pipe) != NULL)
    {
        for (int i = 0; isdigit(buffer[i]); i++)
            digits += buffer[i];
    }
    _pclose(pipe);

    return digits;
}