cmake_minimum_required(VERSION 3.10)
project(EfficientCpp CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(EfficientCpp main.cpp clocks.cpp)

include(CTest)
add_executable(micro-benchmark benchmark/micro-benchmark.cpp)
target_link_libraries(micro-benchmark PRIVATE benchmark)
