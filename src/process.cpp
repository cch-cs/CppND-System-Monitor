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
float Process::CpuUtilization() const {
  string line;
    float d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13;
    float utime, stime, cutime, cstime;
    float totaltime;
    std::ifstream stream(LinuxParser::kProcDirectory + to_string(_pid) + LinuxParser::kStatFilename);
    if (stream.is_open()){
        while(std::getline(stream,line)){
            std::istringstream linestream(line);
            linestream >> d1 >> d2 >> d3 >> d4 >> d5 >> d6 >> d7 >> d8 >> d9 >> d10 >> d11 >> d12 >> d13 >> utime >> stime >> cutime >> cstime;
            totaltime = utime + stime + cutime + cstime;
            //return (totaltime/sysconf(_SC_CLK_TCK)/UpTime());
           // std::cout << totaltime << std::endl;
            return (totaltime/sysconf(_SC_CLK_TCK)/UpTime());
            // return (totaltime);
            /*
            while (linestream >> val)
            {
                if (i == 14) {
                    utime = val;
                    linestream >> stime >> cutime >> cstime;
                    totaltime = utime + stime + cutime + cstime;
                    //return (totaltime/sysconf(_SC_CLK_TCK)/UpTime());
                    return (totaltime);
                }
                std::cout << i << std::endl;
                ++i;
            } */  
        }
    }
    // return (totaltime/sysconf(_SC_CLK_TCK)/UpTime());
    //std::cout << totaltime << std::endl;
    //return (totaltime);
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
    return this->CpuUtilization() > a.CpuUtilization(); 
    }