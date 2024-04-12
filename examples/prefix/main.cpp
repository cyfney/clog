#define CLOG_PREFIX_DATE (0)  // Disable date printing
#define CLOG_PREFIX_PID (0)   // Disable process ID printing
#define CLOG_PREFIX_TID (0)   // Disable thread ID printing

#include "clog.hpp"  // Put the include statement for clog.hpp after the CLOG_XXX macro definitions

int main() {
  CLOGV << "This is verbose log";
  CLOGI << "This is info log";
  CLOGD << "This is debug log";
  CLOGW << "This is warning log";
  CLOGE << "This is error log";
  CLOGF << "This is fatal log";
  return 0;
}