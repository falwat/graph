cmake_minimum_required(VERSION 3.0.0)
project(demo VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(demo main.cpp graph.cpp)

target_compile_features(demo PUBLIC cxx_std_17)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
