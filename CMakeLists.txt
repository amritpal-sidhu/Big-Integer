cmake_minimum_required (VERSION 3.22)
project(big_int C CXX)

include(cmake/config.cmake)
include_guard(GLOBAL)

add_subdirectory(Third-Party/Unity)
target_compile_definitions(unity PUBLIC UNITY_INCLUDE_CONFIG_H)

set(LOCAL_SOURCES BigInt.cpp)
list(TRANSFORM LOCAL_SOURCES PREPEND ${CMAKE_CURRENT_LIST_DIR}/src/)

add_library(${PROJECT_NAME} STATIC ${LOCAL_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC inc)

run_tests_macro()
