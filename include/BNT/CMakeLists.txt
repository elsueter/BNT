add_library(boolean_Network STATIC 
    ${CMAKE_CURRENT_LIST_DIR}/src/netUtils.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/src/basicNetwork.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/src/nodeNetwork.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/booleanNetwork.h)

target_include_directories(boolean_Network PUBLIC ${CMAKE_CURRENT_LIST_DIR}/..)