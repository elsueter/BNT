cmake_minimum_required(VERSION 3.5)

# set the project name
project(BooleanNetworkWebApp)

#set CMake Cpp standard
set(CMAKE_CXX_STANDARD 14)

add_library(boolean_Network STATIC include/BooleanNetworkEmulator/src/basicNetwork.cpp include/BooleanNetworkEmulator/include/booleanNetwork.h)

# add the executable
add_executable(WebApp main.cpp)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(WebApp PRIVATE Threads::Threads)

target_link_libraries(WebApp PUBLIC boolean_Network)

target_include_directories(WebApp PUBLIC include/BooleanNetworkEmulator/include)

target_include_directories(WebApp PUBLIC include)

target_include_directories(WebApp PUBLIC include/boost_1_76_0)