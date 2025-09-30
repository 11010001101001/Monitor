#include <string>
#include <iostream>
#include <windows.h>
#include <math.h>

using namespace std;

class SystemAnalizer
{
public:
    enum DevicePart
    {
        ram,
        gpu,
        gpu_temp,
        gpu_fan_speed,
        cpu
    };

    string analize(DevicePart);

private:
    double toGb(DWORDLONG);
    string getCmdOutput(const char *);
    string getRamUsage();
    string getGpuUsage();
    string getGpuFanSpeed();
    string getGpuTemp();
    string getCpuUsage();
};