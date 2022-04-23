cmake_minimum_required(VERSION 3.0.0)
project(vox VERSION 0.1.0)

add_library(voxlib INTERFACE)
target_compile_features(voxlib INTERFACE cxx_std_11)
target_compile_options(voxlib INTERFACE "-Wall" "-Wextra" "-Wpedantic")
target_include_directories(voxlib INTERFACE inc)

add_executable(vox main.cpp)
target_compile_features(vox PUBLIC cxx_std_11)
target_link_libraries(vox PUBLIC voxlib)