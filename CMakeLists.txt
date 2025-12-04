cmake_minimum_required(VERSION 3.16)
project(cpp_low_latency_vector_benchmarks LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(cpp_low_latency_vector_benchmarks
    src/main.cpp
)
