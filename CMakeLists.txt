cmake_minimum_required(VERSION 3.10)

# set the project name
project(RayTracer
        VERSION 1.0
        DESCRIPTION "My first ray tracer"
        LANGUAGES CXX)

# add the executable
add_executable(rayTracer src/main.cpp)

# add the include directory
target_include_directories(rayTracer PRIVATE inc)

# specify the C++ standard
target_compile_features(rayTracer PRIVATE cxx_std_20)
target_compile_options(rayTracer PRIVATE -Wall -Wextra -Wpedantic)