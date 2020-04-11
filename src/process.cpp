#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

#include <iostream>

Process::Process(int pid):_pid(pid){}
// TODO: Return this process's ID
int Process::Pid() {
    return _pid;
}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() {
  string line;
    float val;
    float utime, stime, cutime, cstime;
    float totaltime;
    int i{1};
    std::ifstream stream(LinuxParser::kProcDirectory + to_string(Pid()) + LinuxParser::kStatFilename);
    if (stream.is_open()){
        while(std::getline(stream,line)){
            std::istringstream linestream(line);
            while (linestream >> val)
            {
                if (i == 14) {
                    utime = val;
                    linestream >> stime >> cutime >> cstime;
                    totaltime = utime + stime + cutime + cstime;
                    return (totaltime/sysconf(_SC_CLK_TCK)/UpTime());
                }
                ++i;
            }
        }
    }
    return (totaltime/sysconf(_SC_CLK_TCK)/UpTime());
}


// TODO: Return the command that generated this process
string Process::Command() {
    return LinuxParser::Command(_pid);
}

// TODO: Return this process's memory utilization
string Process::Ram() {
    return LinuxParser::Ram(_pid);
}

// TODO: Return the user (name) that generated this process
string Process::User() {
    return LinuxParser::User(_pid);
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() {
    return LinuxParser::UpTime(_pid);
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }