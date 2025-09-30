#define CPU_USAGE_CMD "wmic cpu get loadpercentage"
#define GPU_USAGE_CMD "nvidia-smi --query-gpu=utilization.gpu --format=csv,noheader,nounits"
#define GPU_TEMP_CMD "nvidia-smi --query-gpu=temperature.gpu --format=csv,noheader,nounits"
#define GPU_FAN_SPEED "nvidia-smi --query-gpu=fan.speed --format=csv,noheader,nounits"
#define ZERO "0"

#include "system_analizer.h"
#include <iostream>
#include <string>
#include <math.h>
#include <windows.h>

string SystemAnalizer::analize(DevicePart part)
{
    switch (part)
    {
    case cpu:
        return getCpuUsage();
        break;

    case ram:
        return getRamUsage();
        break;

    case gpu:
        return getGpuUsage();
        break;

    case gpu_temp:
        return getGpuTemp();
        break;

    case gpu_fan_speed:
        return getGpuFanSpeed();
        break;

    default:
        return ZERO;
    }
}

double SystemAnalizer::toGb(DWORDLONG num)
{
    return static_cast<double>(num) / pow(1024, 3);
}

string SystemAnalizer::getRamUsage()
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

string SystemAnalizer::getGpuUsage()
{
    return getCmdOutput(GPU_USAGE_CMD);
}

string SystemAnalizer::getGpuTemp()
{
    return getCmdOutput(GPU_TEMP_CMD);
}

string SystemAnalizer::getGpuFanSpeed()
{
    return getCmdOutput(GPU_FAN_SPEED);
}

string SystemAnalizer::getCpuUsage()
{
    return getCmdOutput(CPU_USAGE_CMD);
}

string SystemAnalizer::getCmdOutput(const char *cmd)
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

    return digits.empty() ? ZERO : digits;
}