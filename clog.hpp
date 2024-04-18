/*
 * MIT License
 *
 * Copyright (c) 2024 cyfney
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * For more information, please visit: https://github.com/cyfney/clog
 */

#pragma once
#ifndef __CLOG_H__
#define __CLOG_H__

#define CLOG_VERSION_MAJOR (1)
#define CLOG_VERSION_MINOR (0)
#define CLOG_VERSION_PATCH (2)

#ifndef CLOG_PREFIX_DATE
#define CLOG_PREFIX_DATE (1)
#endif

#ifndef CLOG_PREFIX_TIME
#define CLOG_PREFIX_TIME (1)
#endif

#ifndef CLOG_PREFIX_LOG_LEVEL
#define CLOG_PREFIX_LOG_LEVEL (1)
#endif

#ifndef CLOG_PREFIX_PID
#define CLOG_PREFIX_PID (1)
#endif

#ifndef CLOG_PREFIX_TID
#define CLOG_PREFIX_TID (1)
#endif

#ifndef CLOG_PREFIX_FILE_NAME
#define CLOG_PREFIX_FILE_NAME (1)
#endif

#ifndef CLOG_PREFIX_FILE_LINE
#define CLOG_PREFIX_FILE_LINE (1)
#endif

#ifndef CLOG_PREFIX_FUNCTION_NAME
#define CLOG_PREFIX_FUNCTION_NAME (1)
#endif

#ifndef CLOG_LEVEL
#define CLOG_LEVEL CLOG_LEVEL_VERBOSE
#endif

#define CLOG_LEVEL_VERBOSE (0)
#define CLOG_LEVEL_INFO (1)
#define CLOG_LEVEL_DEBUG (2)
#define CLOG_LEVEL_ERROR (3)
#define CLOG_LEVEL_FATAL (4)
#define CLOG_LEVEL_WARNING (5)
#define CLOG_LEVEL_NO_LOG (6)

#if CLOG_LEVEL <= CLOG_LEVEL_VERBOSE
#define CLOGV \
  Clog(&__FILE__[std::integral_constant<size_t, FileNameOffset(__FILE__)>()], __FUNCTION__, __LINE__, CLOG_LEVEL_VERBOSE)
#else
#define CLOGV ClogDummy()
#endif

#if CLOG_LEVEL <= CLOG_LEVEL_INFO
#define CLOGI \
  Clog(&__FILE__[std::integral_constant<size_t, FileNameOffset(__FILE__)>()], __FUNCTION__, __LINE__, CLOG_LEVEL_INFO)
#else
#define CLOGI ClogDummy()
#endif

#if CLOG_LEVEL <= CLOG_LEVEL_DEBUG
#define CLOGD \
  Clog(&__FILE__[std::integral_constant<size_t, FileNameOffset(__FILE__)>()], __FUNCTION__, __LINE__, CLOG_LEVEL_DEBUG)
#else
#define CLOGD ClogDummy()
#endif

#if CLOG_LEVEL <= CLOG_LEVEL_WARNING
#define CLOGW \
  Clog(&__FILE__[std::integral_constant<size_t, FileNameOffset(__FILE__)>()], __FUNCTION__, __LINE__, CLOG_LEVEL_WARNING)
#else
#define CLOGW ClogDummy()
#endif

#if CLOG_LEVEL <= CLOG_LEVEL_ERROR
#define CLOGE \
  Clog(&__FILE__[std::integral_constant<size_t, FileNameOffset(__FILE__)>()], __FUNCTION__, __LINE__, CLOG_LEVEL_ERROR)
#else
#define CLOGE ClogDummy()
#endif

#if CLOG_LEVEL <= CLOG_LEVEL_FATAL
#define CLOGF \
  Clog(&__FILE__[std::integral_constant<size_t, FileNameOffset(__FILE__)>()], __FUNCTION__, __LINE__, CLOG_LEVEL_FATAL)
#else
#define CLOGF ClogDummy()
#endif

#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <type_traits>

#if defined(__APPLE__) && (defined(CLOG_PREFIX_PID) || defined(CLOG_PREFIX_TID))
#include <unistd.h>
#elif defined(__ANDROID__)
#include <android/log.h>
#if defined(CLOG_PREFIX_PID) || defined(CLOG_PREFIX_TID)
#include <unistd.h>
#endif
#elif defined(_WIN32)
#pragma warning(disable : 4996)
#pragma warning(disable : 4709)
#if defined(CLOG_PREFIX_PID) || defined(CLOG_PREFIX_TID)
#include <windows.h>
#endif
#elif defined(__linux__) && (defined(CLOG_PREFIX_PID) || defined(CLOG_PREFIX_TID))
#include <unistd.h>
#elif defined(IDF_VER) && defined(CLOG_PREFIX_TID)
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#endif

namespace {

inline char LogLevelToChar(const int log_level) {
  switch (log_level) {
    case CLOG_LEVEL_VERBOSE:
      return 'V';
    case CLOG_LEVEL_INFO:
      return 'I';
    case CLOG_LEVEL_DEBUG:
      return 'D';
    case CLOG_LEVEL_WARNING:
      return 'W';
    case CLOG_LEVEL_ERROR:
      return 'E';
    case CLOG_LEVEL_FATAL:
      return 'F';
    default:
      return ' ';
  }
}

template <typename T, size_t size>
constexpr size_t FileNameOffset(const T (&file_path)[size], size_t i = size - 1) {
  static_assert(size > 1, "");
  return file_path[i] == '/' || file_path[i] == '\\' ? i + 1 : (i == 0 ? 0 : FileNameOffset(file_path, i - 1));
}

struct ClogDummy {
  template <typename T>
  ClogDummy& operator<<(T) {
    return *this;
  }
};

class Clog : public std::ostringstream {
 public:
  Clog(const char* const file, const char* const function, const uint32_t line, const int log_level) : file_(file) {
#if CLOG_PREFIX_DATE || CLOG_PREFIX_TIME
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
#endif
    *this
#if CLOG_PREFIX_DATE && CLOG_PREFIX_TIME
        << std::put_time(std::localtime(&time), "%Y%m%d %H:%M:%S") << "." << std::setfill('0') << std::setw(3)
        << std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count() % 1000
#elif CLOG_PREFIX_DATE
        << std::put_time(std::localtime(&time), "%Y%m%d")
#elif CLOG_PREFIX_TIME
        << std::put_time(std::localtime(&time), "%H:%M:%S") << "." << std::setfill('0') << std::setw(3)
        << std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count() % 1000
#endif

#if CLOG_PREFIX_LOG_LEVEL
#if CLOG_PREFIX_DATE || CLOG_PREFIX_TIME
        << ' '
#endif
        << LogLevelToChar(log_level)
#endif

#if (CLOG_PREFIX_PID || CLOG_PREFIX_TID) && (CLOG_PREFIX_DATE || CLOG_PREFIX_TIME || CLOG_PREFIX_LOG_LEVEL)
        << ' '
#endif

#if CLOG_PREFIX_PID && CLOG_PREFIX_TID
        << ProcessId() << '-' << ThreadId()
#elif CLOG_PREFIX_PID
        << ProcessId()
#elif CLOG_PREFIX_TID
        << ThreadId()
#endif

#if (CLOG_PREFIX_FILE_NAME || CLOG_PREFIX_FILE_LINE) && \
    (CLOG_PREFIX_DATE || CLOG_PREFIX_TIME || CLOG_PREFIX_LOG_LEVEL || CLOG_PREFIX_PID || CLOG_PREFIX_TID)
        << ' '
#endif

#if CLOG_PREFIX_FILE_NAME && CLOG_PREFIX_FILE_LINE
        << file_ << ':' << line
#elif CLOG_PREFIX_FILE_NAME
        << file_
#elif CLOG_PREFIX_FILE_LINE
        << line
#endif

#if CLOG_PREFIX_FUNCTION_NAME

#if CLOG_PREFIX_DATE || CLOG_PREFIX_TIME || CLOG_PREFIX_LOG_LEVEL || CLOG_PREFIX_PID || CLOG_PREFIX_TID || \
    CLOG_PREFIX_FILE_NAME || CLOG_PREFIX_FILE_LINE
        << ' '
#endif
        << function
#endif

#if CLOG_PREFIX_DATE || CLOG_PREFIX_TIME || CLOG_PREFIX_LOG_LEVEL || CLOG_PREFIX_PID || CLOG_PREFIX_TID || \
    CLOG_PREFIX_FILE_NAME || CLOG_PREFIX_FILE_LINE || CLOG_PREFIX_FUNCTION_NAME
        << ']' << ' '
#endif
        ;
  }

  ~Clog() {
    *this << "\n";
    std::cout << str();
#if defined(__ANDROID__)
    __android_log_print(ANDROID_LOG_INFO, file_, "%s", str().c_str());
#endif
  }

 private:
  const char* const file_ = nullptr;

#if CLOG_PREFIX_PID
  static inline uintmax_t ProcessId() {
#if defined(__APPLE__) || defined(__ANDROID__) || defined(__linux__)
    return getpid();
#elif defined(_WIN32)
    return GetCurrentProcessId();
#else
    return 0;
#endif
  }
#endif

#if CLOG_PREFIX_TID
  static inline uintmax_t ThreadId() {
#if defined(__APPLE__)
    return pthread_mach_thread_np(pthread_self());
#elif defined(__ANDROID__) || defined(__linux__)
    return gettid();
#elif defined(_WIN32)
    return GetCurrentThreadId();
#elif defined(IDF_VER)
    return reinterpret_cast<uintmax_t>(xTaskGetCurrentTaskHandle());
#else
    return 0;
#endif
  }
#endif
};
}  // namespace
#endif