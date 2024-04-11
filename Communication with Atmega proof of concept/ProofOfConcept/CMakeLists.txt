cmake_minimum_required(VERSION 3.5)

project(ProofOfConcept LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ProofOfConcept main.cpp gripper.h
    gripperDummy.h)

include(GNUInstallDirs)
install(TARGETS ProofOfConcept
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
