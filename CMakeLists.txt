cmake_minimum_required(VERSION 3.5)

# set the project name
project(BooleanNetworkWebApp)

#set CMake Cpp standard
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/webServer)

#-----------------------------------------------------------------------------------------

find_package(Threads)
find_package(ZLIB)
find_package(OpenSSL)

if(OPENSSL_FOUND)
    include_directories(${OPENSSL_INCLUDE_DIR})
endif()

if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to Release")
    set(CMAKE_BUILD_TYPE "Release")
endif()

add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY)

if (MSVC)
    set(Boost_USE_STATIC_LIBS "On")
    find_package( Boost COMPONENTS system thread regex REQUIRED )
else()
    find_package( Boost COMPONENTS system thread REQUIRED )
endif()

include_directories(${Boost_INCLUDE_DIR})

#-----------------------------------------------------------------------------------------

# add the executable
add_executable(BNT src/main.cpp)

set(THREADS_PREFER_PTHREAD_FLAG ON)
target_link_libraries(BNT PRIVATE Threads::Threads)

include(include/BNT/CMakeLists.txt)

add_library(crow INTERFACE)
target_include_directories(crow INTERFACE libs)

include_directories(libs)

target_link_libraries(BNT PUBLIC crow)
target_link_libraries(BNT PUBLIC boolean_Network)

#-----------------------------------------------------------------------------------------

file(COPY src/webApp/index.html DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/webApp)
file(COPY src/webApp/index.css DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/webApp)


file(COPY src/shellScripts/deploy.sh DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY src/shellScripts/restart.sh DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY src/shellScripts/kill.sh DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY src/savedNetworks.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/networks)