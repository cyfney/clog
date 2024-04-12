#define CLOG_LEVEL (CLOG_LEVEL_DEBUG)  // Set the log severity level to Debug

#include "clog.hpp"  // Put the include statement for clog.hpp after the CLOG_XXX macro definitions

int main() {
  CLOGV << "This is verbose log";  // This log message will not be printed
  CLOGI << "This is info log";     // This log message will not be printed
  CLOGD << "This is debug log";
  CLOGW << "This is warning log";
  CLOGE << "This is error log";
  CLOGF << "This is fatal log";
  return 0;
}