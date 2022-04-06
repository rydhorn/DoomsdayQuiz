cmake_minimum_required(VERSION 3.0.0)
project(DOOMSDAY VERSION 0.1.0)

include(CTest)
enable_testing()

#include_directories(DOOMSDAY PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCES main.cpp main.h Date.h)

add_executable(DOOMSDAY ${SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
