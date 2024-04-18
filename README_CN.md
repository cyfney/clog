# CLOG 跨平台日志打印库

## 概述

`clog`是一个`C++`跨平台的日志打印库，适用于多种操作系统和嵌入式系统。在软件开发过程中，日志记录对于问题定位和解决至关重要。clog库旨在提供一个简单易用且功能强大的日志打印解决方案，它能输出包含日期、时间、文件名、行号、函数名等关键信息的日志，便于开发者快速定位和解决项目中的问题。

使用`clog`库非常方便，只需将头文件[clog.hpp](clog.hpp)添加到你的项目中即可开始使用，使用方式类似于`std::cout`的流式打印。

除了基本的日志输出功能，clog还支持日志的格式化输出和日志严重级别设置，让您更灵活地控制日志的内容和输出。例如，您可以自定义日志的时间格式、文件名显示方式等。同时，通过设置日志严重级别，您可以轻松过滤掉不必要的日志内容，提高开发效率。

## 开始

你可以使用类似`std::cout`的流操作符`CLOGV`、`CLOGI`、`CLOGD`、`CLOGW`、`CLOGE`或者`CLOGF`来打印不同严重级别的日志。这些操作符分别对应于不同的[日志严重级别](#日志严重级别)。以下是一个简单的示例：

``` c++
#include "clog.hpp"

int main() {
  CLOGV << "This is verbose log";
  CLOGI << "This is info log";
  CLOGD << "This is debug log";
  CLOGW << "This is warning log";
  CLOGE << "This is error log";
  CLOGF << "This is fatal log";

  // 打印Clog版本号
  CLOGI << "clog version: " << CLOG_VERSION_MAJOR << '.' << CLOG_VERSION_MINOR << '.' << CLOG_VERSION_PATCH;
  return 0;
}
```

该示例程序目录位于[example/print](example/print)，你可以在电脑端（Windows/Linux/MacOS）上使用`cmake`命令进行编译。

首先，请确保您已安装cmake。如果没有，请参考cmake官方网站上的安装指南进行安装。然后，按照以下步骤操作，其他示例工程编译方式类似后续不再赘述。

- 进入到示例工程目录

  ```shell
  cd example/print
  ```

- 使用`cmake`命令编译

  ```shell
  cmake -B build -DCMAKE_BUILD_TYPE=Debug
  cmake --build build --config Debug
  ```

- 运行

  - Windows

    ```shell
    ./build/Debug/example
    ```

  - Linux/MacOS

    ```shell
    ./build/example
    ```

- 运行结果如下所示

  ```text
  20240412 15:59:27.903 V 24060-18256 main.cpp:4 main] This is verbose log
  20240412 15:59:27.907 I 24060-18256 main.cpp:5 main] This is info log
  20240412 15:59:27.907 D 24060-18256 main.cpp:6 main] This is debug log
  20240412 15:59:27.907 W 24060-18256 main.cpp:7 main] This is warning log
  20240412 15:59:27.907 E 24060-18256 main.cpp:8 main] This is error log
  20240412 15:59:27.908 F 24060-18256 main.cpp:9 main] This is fatal log
  20240412 15:59:27.908 I 24060-18256 main.cpp:11 main] clog version: 1.0.0
  ```

## 日志严重级别

`Clog`库提供了多个流操作符（`CLOGV`、`CLOGI`、`CLOGD`、`CLOGW`、`CLOGE`和`CLOGF`），它们分别对应不同的日志严重级别。用户可以通过定义宏`CLOG_LEVEL`来设置当前的日志严重级别。在该级别下，未达到`CLOG_LEVEL`的日志将不会被输出。

下表展示了不同的日志严重级别及其对应的宏定义、正常输出的流操作符和被屏蔽的流操作符：

| 日志严重级别 | 宏定义 | 正常输出的流操作符 | 被屏蔽的流操作符 |
| ---  | --- | --- | --- |
| verbose | `CLOG_LEVEL_VERBOSE` | `CLOGV`、`CLOGI`、`CLOGD`、`CLOGW`、`CLOGE`、`CLOGF` | |
| info  | `CLOG_LEVEL_INFO` | `CLOGI`、`CLOGD`、`CLOGW`、`CLOGE`、`CLOGF` | `CLOGV` |
| debug | `CLOG_LEVEL_DEBUG` | `CLOGD`、`CLOGW`、`CLOGE`、`CLOGF` | `CLOGV`、`CLOGI` |
| warning | `CLOG_LEVEL_WARNING` | `CLOGW`、`CLOGE`、`CLOGF` | `CLOGV`、`CLOGI`、`CLOGD` |
| error | `CLOG_LEVEL_ERROR` | `CLOGE`、`CLOGF` | `CLOGV`、`CLOGI`、`CLOGD`、`CLOGW` |
| fatal | `CLOG_LEVEL_FATAL` | `CLOGF` | `CLOGV`、`CLOGI`、`CLOGD`、`CLOGW`、`CLOGE` |
| no log | `CLOG_LEVEL_NO_LOG` | | `CLOGV`、`CLOGI`、`CLOGD`、`CLOGW`、`CLOGE`、`CLOGF` |

`CLOG_LEVEL`的默认值为`CLOG_LEVEL_VERBOSE`，表示将所有日志输出。下面是一个示例代码，展示了如何将`CLOG_LEVEL`定义为`CLOG_LEVEL_DEBUG`，从而屏蔽`CLOGV`和`CLOGI`级别的日志，只输出`CLOGD`、`CLOGW`、`CLOGE`和`CLOGF`级别的日志：

```c++
#define CLOG_LEVEL (CLOG_LEVEL_DEBUG)  // 设置日志严重级别为Debug

#include "clog.hpp" // 把包含头文件clog.hpp的语句写在CLOG_XXX宏定义之后

int main() {
  CLOGV << "This is verbose log";  // 这句日志将不会打印
  CLOGI << "This is info log";     // 这句日志将不会打印
  CLOGD << "This is debug log";
  CLOGW << "This is warning log";
  CLOGE << "This is error log";
  CLOGF << "This is fatal log";
  return 0;
}
```

该示例程序目录位于[example/custom_log_level_print](example/custom_log_level_print)，编译运行方式请参考之前描述的示例工程[example/print](example/print)的编译运行。

运行结果如下所示，info和verbose级别的日志将不会打印：

```log
20240412 18:25:34.586 D 21596-17668 main.cpp:8 main] This is debug log
20240412 18:25:34.589 W 21596-17668 main.cpp:9 main] This is warning log
20240412 18:25:34.589 E 21596-17668 main.cpp:10 main] This is error log
20240412 18:25:34.589 F 21596-17668 main.cpp:11 main] This is fatal log
```

## 前缀格式

默认每行日志会包含固定前缀，格式如下所示:

```log
yyyymmdd hh:mm:ss.SSS L pid-tid file:line function] message...
```

每个字段含义如下表所示：

| 字段 | 含义 |
| --- | --- |
| yyyy | 年 |
| mm | 月 |
| dd | 日 |
| hh:mm:ss.SSS | 时间，精确到毫秒 |
| L | 日志严重级别，用一个大写字母表示，例如`I`代表`info` |
| pid | 进程号 |
| tid | 线程号 |
| file | 文件名 |
| line | 行号 |
| function | 函数名 |
| ] | 前缀结束符 |

你可以在包含`clog.hpp`头文件前定义一些宏来关闭一些前缀字段，减小日志长度，将下列宏定义为`0`就会关闭字段，`1`就会打开字段，宏定义如下表所示，这些字段都定义在`clog.hpp`中，你也可以直接修改`clog.hpp`中的宏定义来打开或者关闭，默认都是打开的。

| 字段 | 宏定义 | 默认值 |
| --- | --- | --- |
| 日期 | CLOG_PREFIX_DATE | 1 |
| 时间 | CLOG_PREFIX_TIME | 1 |
| 日志严重级别 | CLOG_PREFIX_LOG_LEVEL | 1 |
| 进程号 | CLOG_PREFIX_PID | 1 |
| 线程号 | CLOG_PREFIX_TID | 1 |
| 文件名 | CLOG_PREFIX_FILE_NAME | 1 |
| 文件行号 | CLOG_PREFIX_FILE_LINE | 1 |
| 函数名 | CLOG_PREFIX_FUNCTION_NAME | 1 |

例如某些嵌入式系统中不需要进程号和线程号，那么可以把`CLOG_PREFIX_PID`和`CLOG_PREFIX_TID`定义为`0`，一般也没有日期，可以把`CLOG_PREFIX_DATE`定义为`0`，示例代码如下所示:

```c++
#define CLOG_PREFIX_DATE (0)           // 关闭日期打印
#define CLOG_PREFIX_PID (0)            // 关闭进程号打印
#define CLOG_PREFIX_TID (0)            // 关闭线程号打印

#include "clog.hpp"  // 把包含头文件clog.hpp的语句写在CLOG_XXX宏定义之后

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

该示例程序目录位于[example/custom_prefix_print](example/custom_prefix_print)，编译运行方式请参考之前描述的示例工程[example/print](example/print)的编译运行。

运行结果如下所示：

```log
18:25:56.975 V main.cpp:8 main] This is verbose log
18:25:56.982 I main.cpp:9 main] This is info log
18:25:56.982 D main.cpp:10 main] This is debug log
18:25:56.982 W main.cpp:11 main] This is warning log
18:25:56.983 E main.cpp:12 main] This is error log
18:25:56.983 F main.cpp:13 main] This is fatal log
```
