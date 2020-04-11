#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid):_pid(pid){}
// TODO: Return this process's ID
int Process::Pid() {
    return _pid;
}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() const {
    string line;
    string val;
    int i{0};
    float utime, stime, cutime, cstime;
    float totaltime;
    float temp;
    float seconds;
    std::ifstream stream(LinuxParser::kProcDirectory + to_string(_pid) + LinuxParser::kStatFilename);
    if (stream.is_open()){
        while(std::getline(stream,line)){
            std::istringstream linestream(line);
            while (linestream >> val) {
                if (i == 14) {
                    utime = std::stof(val);
                    linestream >> val;
                    stime = std::stof(val);
                    linestream >> val;
                    cutime = std::stof(val);
                    linestream >> val;
                    cstime = std::stof(val);
                    totaltime = utime + stime + cutime + cstime;
                    temp = totaltime/sysconf(_SC_CLK_TCK);
                    seconds = LinuxParser::UpTime() - UpTime();
                    return (temp/seconds);
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
long int Process::UpTime() const {
    return LinuxParser::UpTime(_pid);
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const {
    return this->CpuUtilization() < a.CpuUtilization(); 
    }