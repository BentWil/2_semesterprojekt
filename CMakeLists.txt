cmake_minimum_required(VERSION 3.27)
project(2_semesterprojekt)

set(CMAKE_CXX_STANDARD 17)

add_executable(2_semesterprojekt main.cpp UserInterface.h
        PickAndPlace_allCups/pyramide.h
        PickAndPlace_allCups/vec.h
        PickAndPlace_allCups/pile.h)
