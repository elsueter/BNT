cmake_minimum_required(VERSION 3.10)

# set the project name
project(BooleanNetworkWebApp)

#set CMake Cpp standard
set(CMAKE_CXX_STANDARD 14)

add_library(boolean_Network STATIC include/BooleanNetworkEmulator/src/basicNetwork.cpp include/BooleanNetworkEmulator/include/booleanNetwork.h)

# add the executable
add_executable(WebApp main.cpp)

target_link_libraries(cMake_executable PUBLIC boolean_Network)

target_include_directories(cMake_executable PUBLIC include/BooleanNetworkEmulator/include)

target_include_directories(cMake_executable PUBLIC include)

target_include_directories(cMake_executable PUBLIC include/boost_1_76_0)