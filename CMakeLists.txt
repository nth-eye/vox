cmake_minimum_required(VERSION 3.0.0)
project(vox VERSION 0.1.0 LANGUAGES C)

include_directories(inc)
file(GLOB SRC_FILES src/*.c)
add_executable(vox main.c ${SRC_FILES})

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED true)
set(CMAKE_C_FLAGS "-Wall -Wextra -Wpedantic")
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
