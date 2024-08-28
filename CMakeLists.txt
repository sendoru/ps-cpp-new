cmake_minimum_required(VERSION 3.16)
project(untitled)

set(CMAKE_CXX_STANDARD 17)
include_directories(${CMAKE_SOURCE_DIR}/actoder)

add_executable(
    untitled.out
    ${CMAKE_SOURCE_DIR}/source/boj/14986.cpp
)

target_include_directories(untitled.out PUBLIC ${CMAKE_SOURCE_DIR})