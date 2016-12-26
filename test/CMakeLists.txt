project(cfref_ptr)
cmake_minimum_required(VERSION 2.8)

add_executable(cfref_ptr_test cfref_ptr_test.cpp)
include_directories(.. thirdparty/doctest/doctest)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework CoreFoundation")
