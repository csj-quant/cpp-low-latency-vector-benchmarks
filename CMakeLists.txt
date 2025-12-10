cmake_minimum_required(VERSION 3.16)
project(cpp_low_latency_vector_benchmarks)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Optimise for low latency tests
add_compile_options(-O3 -march=native -mtune=native -DNDEBUG -fno-exceptions)

#Clang recommended flags
add_compile_options(-Wall -Wextra -Wpedantic)

include_directories(src)

add_executable(vector_growth_analysis src/vector_growth_analysis.cpp src/mini_vector.cpp)
add_executable(vector_reallocation_diagnostics src/vector_reallocation_diagnostics.cpp src/mini_vector.cpp)
add_executable(vector_reserve_vs_noreserve src/vector_reserve_vs_noreserve.cpp src/mini_vector.cpp)
