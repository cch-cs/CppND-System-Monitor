#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
    string hr = std::to_string(seconds/3600);
    string min = std::to_string((seconds - (seconds/3600)*3600)/60);
    string secs = std::to_string(seconds - (seconds/3600)*3600 - ((seconds - (seconds/3600)*3600)/60)*60);
    return (hr + ':' + min + ':' + secs);
    }