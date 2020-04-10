#include "processor.h"
#include <vector>
#include <string>

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
    float user, nice, system, idle, iowait, irq, softirq, steal, guest, guestnice;
    float cpuNonidle;
    float cpuTotal;
    std::string dummy;
    std::vector<std::string> cpu_utilize = LinuxParser::CpuUtilization();
    for (std::string line : cpu_utilize){
        std::istringstream linestream(line);
        linestream >> dummy >> user >> nice  >> system >> idle >> iowait >> irq >> softirq >> steal >> guest >> guestnice;
        cpuNonidle = user + nice + system + irq + softirq + steal + guest + guestnice;
        cpuTotal = cpuNonidle + idle + iowait;
    }
    return cpuNonidle/cpuTotal;
}