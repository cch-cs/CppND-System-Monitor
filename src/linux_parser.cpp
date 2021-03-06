#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  string line;
  float Memtotal, Memfree;
  string key;
  float value;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()) {
    while (std::getline(stream,line))
    {
      std::replace(line.begin(),line.end(),':',' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value)
      {
        if (key == "MemTotal"){
          Memtotal =  value;
        }
        if (key == "MemFree"){
          Memfree =  value;
      
          return ((Memtotal - Memfree)/Memtotal);
        }
      }
    }
  }
  return (((Memtotal - Memfree)/Memtotal)*100);
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
  string line;
  long a;
  long b;
  std::ifstream stream(kProcDirectory+kUptimeFilename);
  if (stream.is_open()) {
    while (std::getline(stream,line)){
      std::istringstream linestream(line);
      linestream >> a >> b;
  
      return a+b;
    }
  }
  return a+b;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
// I didn"t use the below function anywhere
//long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {
  string line;
  vector<string> cpu_utilize;
  std::ifstream stream(kProcDirectory+kStatFilename);
  if (stream.is_open()){
    while (std::getline(stream,line))
    {
      cpu_utilize.emplace_back(line);
      return cpu_utilize;
    }
  }
  return cpu_utilize;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  string key;
  int value;
  string line;
  std::ifstream stream(kProcDirectory+kStatFilename);
  if (stream.is_open()){
    while(std::getline(stream,line)){
      std::istringstream linestream(line);
      while(linestream >> key >> value){
        if (key == "processes"){
      
          return value;
        }
      }
    }
  }
  return value;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  string key;
  int value;
  string line;
  std::ifstream stream(kProcDirectory+kStatFilename);
  if (stream.is_open()){
    while(std::getline(stream,line)){
      std::istringstream linestream(line);
      while(linestream >> key >> value){
        if (key == "procs_running"){
      
          return value;
        }
      }
    }
  }
  return value;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
  string line;
  std::ifstream stream(kProcDirectory+to_string(pid)+kCmdlineFilename);
  if (stream.is_open()){
    while (std::getline(stream,line))
    {
      return line;
    }
  }
  return line;
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) {
  string line;
  string key;
  int value;
  std::ifstream stream(kProcDirectory+to_string(pid)+kStatusFilename);
  if (stream.is_open()){
    while(std::getline(stream,line)){
      std::replace(line.begin(),line.end(),':',' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value)
      {
        if (key == "VmSize"){
      
          return to_string(value/1000);
        }
      }
    }
  }
  return to_string(value/1000);
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) {
  string line;
  string key;
  int value;
  std::ifstream stream(kProcDirectory+to_string(pid)+kStatusFilename);
  if (stream.is_open()){
    while(std::getline(stream,line)){
      std::replace(line.begin(),line.end(),':',' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value)
      {
        if (key == "Uid"){
      
          return to_string(value);
        }
      }
    }
  }
  return to_string(value);
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) {
  string line;
  string value;
  string dummy;
  string key;
  std::ifstream stream(kPasswordPath);
  if (stream.is_open()){
    while (std::getline(stream,line))
    {
      std::replace(line.begin(),line.end(),':',' ');
      std::istringstream linestream(line);
      linestream >> value >> dummy >> key;
      if (key == Uid(pid)){
    
        return value;
      }
    }
  }
  return value;
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) {
  string line;
  string val;
  int i{1};
  std::ifstream stream(kProcDirectory+to_string(pid)+kStatFilename);
  if (stream.is_open()){
    while(std::getline(stream,line)){
      std::istringstream linestream(line);
      while (linestream >> val)
      {
        if (i == 22) {
          return (std::stol(val)/sysconf(_SC_CLK_TCK));
        }
        ++i;
      }
    }
  }
  return (std::stol(val)/sysconf(_SC_CLK_TCK));
}