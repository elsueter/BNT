add_library(boolean_Network STATIC 
    ${CMAKE_CURRENT_LIST_DIR}/src/netUtils.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/nodeNetwork.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/src/netStrucs.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/booleanNetwork.h 
    ${CMAKE_CURRENT_LIST_DIR}/src/boolAlgebra.cpp
    ${CMAKE_CURRENT_LIST_DIR}/booleanAlgebra.h)

target_include_directories(boolean_Network PUBLIC ${CMAKE_CURRENT_LIST_DIR}/..)

include_directories(${CMAKE_CURRENT_LIST_DIR}/..)