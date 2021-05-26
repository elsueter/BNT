cmake_minimum_required(VERSION 2.8)

# set the project name
project(BooleanNetworkWebApp)

#set CMake Cpp standard
set(CMAKE_CXX_STANDARD 14)

file(COPY src/index.html
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# add the executable
add_executable(app src/main.cpp)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(app PRIVATE Threads::Threads)

include(include/BNT/CMakeLists.txt)

target_link_libraries(app PUBLIC boolean_Network)

target_include_directories(app PUBLIC libs)

target_include_directories(app PUBLIC libs/boost_1_76_0)