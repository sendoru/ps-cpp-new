cmake_minimum_required(VERSION 3.16)
project(untitled)

set(CMAKE_CXX_STANDARD 20)
# why i need to EXCLUDE this?
# include_directories(${CMAKE_SOURCE_DIR}/atcoder)

add_executable(
    untitled.out
    ${CMAKE_SOURCE_DIR}/source/atcoder/abc417_f.cpp
)

target_include_directories(untitled.out PUBLIC ${CMAKE_SOURCE_DIR})