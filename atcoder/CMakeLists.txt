cmake_minimum_required(VERSION 3.23)
project(atcoder)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

add_library(atcoder STATIC ${SRC_FILES})
target_include_directories(atcoder PUBLIC ${CMAKE_SOURCE_DIR})