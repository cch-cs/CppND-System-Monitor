#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
   int hr = seconds/3600;
   int min = (seconds - hr*3600)/60;
   int secs = seconds - hr*3600 - min*60;
   char temp[3];
   sprintf(temp,"%02d",hr);
   string hr_(temp);
   sprintf(temp,"%02d",min);
   string min_(temp);
   sprintf(temp,"%02d",secs);
   string secs_(temp);
   return hr_ + ':' + min_ + ':' + secs_; 
    }