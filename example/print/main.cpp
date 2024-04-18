#include "clog.hpp"

int main() {
  CLOGV << "This is verbose log";
  CLOGI << "This is info log";
  CLOGD << "This is debug log";
  CLOGW << "This is warning log";
  CLOGE << "This is error log";
  CLOGF << "This is fatal log";

  // Print the clog version number
  CLOGI << "clog version: " << CLOG_VERSION_MAJOR << '.' << CLOG_VERSION_MINOR << '.' << CLOG_VERSION_PATCH;
  return 0;
}