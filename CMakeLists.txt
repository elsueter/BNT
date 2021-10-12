cmake_minimum_required(VERSION 3.5)

# set the project name
project(BooleanNetworkWebApp)

#set CMake Cpp standard
set(CMAKE_CXX_STANDARD 14)

#-----------------------------------------------------------------------------------------

if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to Release")
    set(CMAKE_BUILD_TYPE "Release")
endif()

#-----------------------------------------------------------------------------------------

# add the executable
add_executable(boolnetcli src/main.cpp)

include(include/BNT/CMakeLists.txt)

target_link_libraries(boolnetcli PUBLIC boolean_Network)

#-----------------------------------------------------------------------------------------