cmake_minimum_required(VERSION 3.10)

project(clog_test)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SOURCE_FILES)

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}/bin")

add_executable(test ${SOURCE_FILES})