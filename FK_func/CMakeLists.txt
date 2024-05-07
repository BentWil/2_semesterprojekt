######################################################################
# CMakeLists.txt generated for component fkfunc
# Product type: static library
######################################################################
cmake_minimum_required(VERSION 3.12)
project(fkfunc)
if(DEFINED ENV{CMAKE_EXPORT_COMPILE_COMMANDS} AND NOT DEFINED CMAKE_EXPORT_COMPILE_COMMANDS)
    set(CMAKE_EXPORT_COMPILE_COMMANDS $ENV{CMAKE_EXPORT_COMPILE_COMMANDS})
endif()


######################################################################
## Path variables
######################################################################
get_filename_component(START_DIR . ABSOLUTE)
set(MATLAB_ROOT /mnt/hgfs/Shared_ubuntu/Semesterprojekt CACHE PATH "")
if(${CMAKE_CURRENT_BINARY_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
    set(BUILDING_IN_SOURCE_DIR TRUE)
    set(BINARY_START_DIR "${START_DIR}")
else()
    set(BUILDING_IN_SOURCE_DIR FALSE)
    set(BINARY_START_DIR "${CMAKE_BINARY_DIR}")
endif()
if(WIN32 AND NOT MINGW)
    set(SYSLIB_PREFIX "lib")
else()
    set(SYSLIB_PREFIX "")
endif()

######################################################################
## System libraries
######################################################################
find_library(FOUND_LIBM m NO_SYSTEM_ENVIRONMENT_PATH PATHS ${CMAKE_C_IMPLICIT_LINK_DIRECTORIES}
    ${CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES})
find_library(FOUND_LIBSTDCXX stdc++ NO_SYSTEM_ENVIRONMENT_PATH PATHS ${CMAKE_C_IMPLICIT_LINK_DIRECTORIES}
    ${CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES})

######################################################################
## Target definition and commands
######################################################################
add_library(fkfunc STATIC ${START_DIR}/rt_nonfinite.cpp
    ${START_DIR}/rtGetNaN.cpp
    ${START_DIR}/rtGetInf.cpp
    ${START_DIR}/fkfunc_initialize.cpp
    ${START_DIR}/fkfunc_terminate.cpp
    ${START_DIR}/fkfunc.cpp
    ${START_DIR}/svd.cpp
    ${START_DIR}/xnrm2.cpp
    ${START_DIR}/xdotc.cpp
    ${START_DIR}/sqrt.cpp
    ${START_DIR}/xaxpy.cpp
    ${START_DIR}/xrotg.cpp
    ${START_DIR}/xrot.cpp
    ${START_DIR}/xswap.cpp)
set_target_properties(fkfunc PROPERTIES
    PREFIX ""
    POSITION_INDEPENDENT_CODE ON
    RUNTIME_OUTPUT_DIRECTORY "${BINARY_START_DIR}/./$<0:>"
    LIBRARY_OUTPUT_DIRECTORY "${BINARY_START_DIR}/./$<0:>"
    ARCHIVE_OUTPUT_DIRECTORY "${BINARY_START_DIR}/./$<0:>")
target_compile_features(fkfunc PUBLIC cxx_std_11)
target_compile_definitions(fkfunc PRIVATE -DMODEL=fkfunc)
target_include_directories(fkfunc PUBLIC $<BUILD_INTERFACE:${START_DIR}>
    $<INSTALL_INTERFACE:$<INSTALL_PREFIX>>
    /mnt/hgfs/Shared_ubuntu/Semesterprojekt
    $<BUILD_INTERFACE:${MATLAB_ROOT}/extern/include>)
target_link_libraries(fkfunc INTERFACE $<$<BOOL:${FOUND_LIBM}>:m>
    $<$<BOOL:${FOUND_LIBSTDCXX}>:stdc++>)


######################################################################
## Build success message
######################################################################
add_custom_command(TARGET fkfunc POST_BUILD
     COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --cyan "\\#\\#\\# Created library: $<TARGET_FILE:fkfunc>")

######################################################################
## Call toolchain hook function if defined
######################################################################
if(COMMAND toolchain_target_hook)
    toolchain_target_hook(fkfunc)
endif()
