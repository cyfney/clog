cmake_minimum_required(VERSION 3.10)

project(example)

if (NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_VERBOSE_MAKEFILE ON)

enable_testing()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../)

add_executable(example main.cpp)

target_compile_options(example PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

set(CLOG_DEFINES
  CLOG_PREFIX_DATE
  CLOG_PREFIX_TIME
  CLOG_PREFIX_LOG_LEVEL
  CLOG_PREFIX_PID
  CLOG_PREFIX_TID
  CLOG_PREFIX_FILE_NAME
  CLOG_PREFIX_FILE_LINE
  CLOG_PREFIX_FUNCTION_NAME
  CLOG_LEVEL
)

foreach(clog_define ${CLOG_DEFINES})
  if (DEFINED ${clog_define})
    message("${clog_define}=${${clog_define}}")
    add_definitions(-D${clog_define}=${${clog_define}})
  endif()
endforeach()

add_test(NAME example COMMAND example)