# CLOG Cross-Platform Logging Library

- [中文版](README_CN.md)

## Overview

`clog` is a cross-platform logging library for `C++`, suitable for various operating systems and embedded systems. In the software development process, log recording is crucial for issue identification and resolution. The clog library aims to provide a simple, easy-to-use, and feature-rich logging solution, outputting logs with essential information such as date, time, filename, line number, and function name, allowing developers to quickly locate and solve project issues.

It is very convenient to use the clog library. You only need to include a single header file [clog.hpp](clog.hpp) and add it to your project to start printing logs, similar to stream-style printing with `std::cout`.

In addition to basic log output functionality, clog also supports formatted output and log severity level settings, giving you more flexibility in controlling log content and output. For example, you can customize the log time format, filename display mode, etc. Moreover, by setting the log severity level, you can easily filter out unnecessary log content, improving development efficiency.

## Getting Started

You can use the stream-like operators `CLOGV`, `CLOGI`, `CLOGD`, `CLOGW`, `CLOGE`, and `CLOGF` to print logs with different severity levels. These operators correspond to different [log severity levels](#log-severity-levels). Here is a simple example:

```cpp
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
```

The example program directory is located at [example/print](example/print). On a computer (Windows/Linux/MacOS), you can use the `cmake` command to compile and run the program. First, make sure you have installed `cmake`. If not, please refer to the official installation guide on the cmake website. Then, follow these steps. Other example projects have similar compilation methods, which will not be discussed in detail later.

- Enter the directory of the example project

  ```shell
  cd example/print
  ```

- Use the cmake command to compile

  ```shell
  cmake -B build -DCMAKE_BUILD_TYPE=Debug
  cmake --build build --config Debug
  ```

- Run

  - Windows

    ```shell
    ./build/Debug/example
    ```

  - Linux/MacOS

    ```shell
    ./build/example
    ```

- The output will look like this:

  ```log
  20240412 15:59:27.903 V 24060-18256 main.cpp:4 main] This is verbose log 
  20240412 15:59:27.907 I 24060-18256 main.cpp:5 main] This is info log 
  20240412 15:59:27.907 D 24060-18256 main.cpp:6 main] This is debug log 
  20240412 15:59:27.907 W 24060-18256 main.cpp:7 main] This is warning log 
  20240412 15:59:27.907 E 24060-18256 main.cpp:8 main] This is error log 
  20240412 15:59:27.908 F 24060-18256 main.cpp:9 main] This is fatal log 
  20240412 15:59:27.908 I 24060-18256 main.cpp:11 main] clog version: 1.0.0
  ```

## Log Severity Levels

The `Clog` library provides multiple stream operators (`CLOGV`, `CLOGI`, `CLOGD`, `CLODW`, `CLOGE`, and `CLOGF`) that correspond to different log severity levels. Users can set the current log severity level by defining the macro `CLOG_LEVEL`. Under this level, logs that do not meet the `CLOG_LEVEL` requirement will not be output.

The following table shows different log severity levels, their corresponding macro definitions, normally output stream operators, and blocked stream operators:

| Log Severity Level | Macro Definition | Normally Output Stream Operators | Blocked Stream Operators |
| --- | --- | --- | --- |
| verbose | `CLOG_LEVEL_VERBOSE` | `CLOGV`、`CLOGI`、`CLOGD`、`CLOGW`、`CLOGE`、`CLOGF` | |
| info  | `CLOG_LEVEL_INFO` | `CLOGI`、`CLOGD`、`CLOGW`、`CLOGE`、`CLOGF` | `CLOGV` |
| debug | `CLOG_LEVEL_DEBUG` | `CLOGD`、`CLOGW`、`CLOGE`、`CLOGF` | `CLOGV`、`CLOGI` |
| warning | `CLOG_LEVEL_WARNING` | `CLOGW`、`CLOGE`、`CLOGF` | `CLOGV`、`CLOGI`、`CLOGD` |
| error | `CLOG_LEVEL_ERROR` | `CLOGE`、`CLOGF` | `CLOGV`、`CLOGI`、`CLOGD`、`CLOGW` |
| fatal | `CLOG_LEVEL_FATAL` | `CLOGF` | `CLOGV`、`CLOGI`、`CLOGD`、`CLOGW`、`CLOGE` |
| no log | `CLOG_LEVEL_NO_LOG` | | `CLOGV`、`CLOGI`、`CLOGD`、`CLOGW`、`CLOGE`、`CLOGF` |

The default value of `CLOG_LEVEL` is `CLOG_LEVEL_VERBOSE`, indicating that all logs are output. The following example code shows how to set `CLOG_LEVEL` to `CLOG_LEVEL_DEBUG` to block verbose and info level logs and only output warning, debug, error, and fatal level logs:

```cpp
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
```

The example program directory is located at [example/custom_log_level_print](example/custom_log_level_print/). For compilation and running methods, please refer to the previously described example project [example/print](example/print) for compilation and running.

The output will look like this:

```log
20240412 18:25:34.586 D 21596-17668 main.cpp:8 main] This is debug log
20240412 18:25:34.589 W 21596-17668 main.cpp:9 main] This is warning log
20240412 18:25:34.589 E 21596-17668 main.cpp:10 main] This is error log
20240412 18:25:34.589 F 21596-17668 main.cpp:11 main] This is fatal log
```

## Prefix Format

By default, each line of log contains a fixed prefix, with the following format:

```log
yyyymmdd hh:mm:ss.SSS L pid-tid file:line function] message...
```

The meaning of each field is as follows:

| Field | Meaning |
| --- | --- |
| yyyy | Year |
| mm | Month |
| dd | Day |
| hh:mm:ss.SSS | Time, precise to millisecond |
| L | Log severity level, represented by a capital letter, e.g. I for info |
| pid | Process ID |
| tid | Thread ID |
| file | File name |
| line | Line number |
| function |  Function name |
| ] | Prefix terminator |

You can define some macros before including the `clog.hpp` header file to disable some prefix fields and reduce the log length. Define the following macros as `0` to close the field or as `1` to open the field. The macro definitions are as follows:

| Field | Macro Definition | Default Value |
| --- | --- | --- |
| Date | CLOG_PREFIX_DATE | 1 |
| Time | CLOG_PREFIX_TIME | 1 |
| Log Severity Level  | CLOG_PREFIX_LOG_LEVEL | 1 |
| Process ID  | CLOG_PREFIX_PID | 1 |
| Thread ID  | CLOG_PREFIX_TID | 1 |
| File Name  | CLOG_PREFIX_FILE_NAME | 1 |
| File Line Number  | CLOG_PREFIX_FILE_LINE | 1 |
| Function Name  | CLOG_PREFIX_FUNCTION_NAME | 1 |

For example, in some embedded systems, you might not need process and thread IDs. In that case, you can define `CLOG_PREFIX_PID` and `CLOG_PREFIX_TID` as `0`. Generally, there is no date, so you can define `CLOG_PREFIX_DATE` as `0`. The following example code shows how to do this:

```c++
#define CLOG_PREFIX_DATE (0)           // Disable date printing
#define CLOG_PREFIX_PID (0)            // Disable process ID printing
#define CLOG_PREFIX_TID (0)            // Disable thread ID printing

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
```

The example program directory is located at [example/custom_prefix_print](example/custom_prefix_print). For compilation and running methods, please refer to the previously described example project [example/print](example/print) for compilation and running.

The output will look like this:

```log
18:25:56.975 V main.cpp:8 main] This is verbose log
18:25:56.982 I main.cpp:9 main] This is info log
18:25:56.982 D main.cpp:10 main] This is debug log
18:25:56.982 W main.cpp:11 main] This is warning log
18:25:56.983 E main.cpp:12 main] This is error log
18:25:56.983 F main.cpp:13 main] This is fatal log
```
