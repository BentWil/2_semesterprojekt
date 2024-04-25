cmake_minimum_required(VERSION 3.5)
project(combination)

set(DIR ${CMAKE_CURRENT_SOURCE_DIR})
message(STATUS "${DIR}")
find_package(ur_rtde REQUIRED PATHS "${DIR}/../../Build/ur_rtde" "${DIR}/../../build/ur_rtde")

add_executable(forcemode_example forcemode_example.cpp)
target_link_libraries(forcemode_example PUBLIC ur_rtde::rtde)
