cmake_minimum_required(VERSION 3.5)

find_package(Qt5Sql REQUIRED)

project(ProofOfConcept LANGUAGES CXX)




set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(ProofOfConcept main.cpp gripper.h
    gripperDummy.h )
target_link_libraries(ProofOfConcept Qt5::Core Qt5::Sql)

include(GNUInstallDirs)
install(TARGETS ProofOfConcept
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
