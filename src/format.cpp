#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
    long hr{seconds/3600};
    long min{(seconds - hr*3600)/60};
    long secs{seconds - hr*3600 - min*60};
    return (std::to_string(hr) + ":" + std::to_string(min) + ":" + std::to_string(secs));
    }