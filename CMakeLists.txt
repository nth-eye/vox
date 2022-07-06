cmake_minimum_required(VERSION 3.0.0)
project(vox VERSION 0.1.0)

add_library(libvox INTERFACE)
target_include_directories(libvox INTERFACE inc)
target_compile_features(libvox INTERFACE cxx_std_11)
target_compile_options(libvox INTERFACE "-Wall" "-Wextra" "-Wpedantic")

add_executable(vox main.cpp)
target_compile_features(vox PUBLIC cxx_std_11)
target_link_libraries(vox PUBLIC libvox)
