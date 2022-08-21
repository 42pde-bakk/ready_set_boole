cmake_minimum_required(VERSION 3.22)
project(ready_set_boole)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")

add_executable(ex00 ex00/adder.cpp)
add_executable(ex01 ex01/multiplier.cpp)
