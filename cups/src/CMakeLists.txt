# This is a simple CMakeLists.txt file

cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
Set(CMAKE_CXX_STANDARD 11)
project(Cups)



add_executable(Cups main.cpp vec.h pyramid.h pile.h)



